# End-to-end smoke test for the Win32 remake: drives the real window with
# posted mouse/keyboard messages and asserts on screen captures.
# Needs an existing remake save (the title screen must show REPRENDRE PARTIE).
# Usage: powershell -File tests/e2e/island_e2e.ps1 [-Exe path] [-OutDir dir]
param(
    [string]$Exe = (Join-Path $PSScriptRoot "..\..\ToneRebellion_Remake.exe"),
    [string]$OutDir = (Join-Path $env:TEMP "remake_e2e")
)
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System; using System.Runtime.InteropServices;
public class E2E {
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
}
"@
$ErrorActionPreference = "Stop"
New-Item -ItemType Directory -Force $OutDir | Out-Null
$script:failures = 0
$script:proc = $null

function Check($ok, $name, $detail = "") {
    if ($ok) { "PASS  $name" } else { "FAIL  $name  $detail"; $script:failures++ }
}
function Handle { $script:proc.Refresh(); $script:proc.MainWindowHandle }
function Title { $script:proc.Refresh(); $script:proc.MainWindowTitle }
function Client {
    $r = New-Object E2E+RECT
    [E2E]::GetClientRect((Handle), [ref]$r) | Out-Null
    $r
}
# Logical 640x480 coordinates -> posted client coordinates.
function Logical2Client($lx, $ly) {
    $c = Client
    [int]($lx * $c.R / 640.0), [int]($ly * $c.B / 480.0)
}
function Click($lx, $ly) {
    $x, $y = Logical2Client $lx $ly
    $l = [IntPtr](($y -shl 16) -bor $x)
    [E2E]::PostMessage((Handle), 0x200, [IntPtr]0, $l) | Out-Null
    Start-Sleep -Milliseconds 300
    [E2E]::PostMessage((Handle), 0x201, [IntPtr]1, $l) | Out-Null
    Start-Sleep -Milliseconds 100
    [E2E]::PostMessage((Handle), 0x202, [IntPtr]0, $l) | Out-Null
    Start-Sleep -Milliseconds 400
}
function Key($vk, $count = 1) {
    for ($i = 0; $i -lt $count; $i++) {
        [E2E]::PostMessage((Handle), 0x100, [IntPtr]$vk, [IntPtr]0) | Out-Null
        Start-Sleep -Milliseconds 40
        [E2E]::PostMessage((Handle), 0x101, [IntPtr]$vk, [IntPtr]0) | Out-Null
        Start-Sleep -Milliseconds 40
    }
    Start-Sleep -Milliseconds 400
}
function Capture($name) {
    $r = New-Object E2E+RECT
    [E2E]::GetWindowRect((Handle), [ref]$r) | Out-Null
    $bmp = New-Object System.Drawing.Bitmap ($r.R - $r.L), ($r.B - $r.T)
    [System.Drawing.Graphics]::FromImage($bmp).CopyFromScreen($r.L, $r.T, 0, 0, $bmp.Size)
    $bmp.Save((Join-Path $OutDir "$name.png"))
    $bmp
}
# Fraction of differing pixels in a logical rectangle (client area offset by
# the window frame: the capture includes title bar and borders).
function RegionDiff($a, $b, $lx0, $ly0, $lx1, $ly1) {
    $c = Client
    $r = New-Object E2E+RECT
    [E2E]::GetWindowRect((Handle), [ref]$r) | Out-Null
    $offX = (($r.R - $r.L) - $c.R) / 2
    $offY = ($r.B - $r.T) - $c.B - $offX
    $x0 = [int]($offX + $lx0 * $c.R / 640.0); $x1 = [int]($offX + $lx1 * $c.R / 640.0)
    $y0 = [int]($offY + $ly0 * $c.B / 480.0); $y1 = [int]($offY + $ly1 * $c.B / 480.0)
    $diff = 0; $total = 0
    for ($y = $y0; $y -lt $y1; $y += 2) {
        for ($x = $x0; $x -lt $x1; $x += 2) {
            $pa = $a.GetPixel($x, $y); $pb = $b.GetPixel($x, $y)
            if ([math]::Abs($pa.R - $pb.R) + [math]::Abs($pa.G - $pb.G) + [math]::Abs($pa.B - $pb.B) -gt 60) { $diff++ }
            $total++
        }
    }
    $diff / [math]::Max($total, 1)
}

# Column (in capture pixels) with the most near-white pixels in a logical band:
# the IWLilMap viewport marker, whose x follows the island scroll position.
function MarkerColumn($bmp, $lx0, $ly0, $lx1, $ly1) {
    $c = Client
    $r = New-Object E2E+RECT
    [E2E]::GetWindowRect((Handle), [ref]$r) | Out-Null
    $offX = (($r.R - $r.L) - $c.R) / 2
    $offY = ($r.B - $r.T) - $c.B - $offX
    $x0 = [int]($offX + $lx0 * $c.R / 640.0); $x1 = [int]($offX + $lx1 * $c.R / 640.0)
    $y0 = [int]($offY + $ly0 * $c.B / 480.0); $y1 = [int]($offY + $ly1 * $c.B / 480.0)
    $best = -1; $bestCount = 0
    for ($x = $x0; $x -lt $x1; $x++) {
        $n = 0
        for ($y = $y0; $y -lt $y1; $y += 2) {
            $p = $bmp.GetPixel($x, $y)
            if ($p.R -gt 220 -and $p.G -gt 220 -and $p.B -gt 220) { $n++ }
        }
        if ($n -gt $bestCount) { $bestCount = $n; $best = $x }
    }
    $best
}

Get-Process ToneRebellion_Remake -ErrorAction SilentlyContinue | Stop-Process -Force
$script:proc = Start-Process $Exe -PassThru
try {
    Start-Sleep -Seconds 6
    Check ((Title) -like "*Title*") "starts on the title screen" (Title)

    Click 323 305   # REPRENDRE PARTIE
    Start-Sleep -Seconds 4
    Check ((Title) -like "*Island*") "REPRENDRE opens the island view" (Title)

    # Island scroll memory (DAT_005dbee0): the minimap viewport marker lives in
    # IWLilMap (logical 192,328..447,359).
    $m0 = Capture "island_scroll0"
    Key 0x27 30     # Right arrow
    $m1 = Capture "island_scrolled"
    $c0 = MarkerColumn $m0 195 332 445 357
    $c1 = MarkerColumn $m1 195 332 445 357
    Check ($c1 -gt $c0) "arrow keys scroll the island" "marker $c0 -> $c1"
    Key 0x1B        # Esc -> world map
    Check ((Title) -like "*World Map*") "Esc returns to the world map" (Title)
    Key 0x0D        # Return -> reopen the same island
    Start-Sleep -Seconds 2
    Check ((Title) -like "*Island*") "Return reopens the island" (Title)
    $m2 = Capture "island_reentered"
    $c2 = MarkerColumn $m2 195 332 445 357
    Check ([math]::Abs($c2 - $c1) -le 3) "scroll position is kept on re-entry" "marker $c1 -> $c2"
    Check ($c2 -gt $c0) "re-entry does not reset scroll to 0" "marker $c0 -> $c2"

    # Sweep clicks over the playfield; some must select something and fill the
    # info panels (IWLocInfo 192,368..447,471 / IWTextInfo 456,328..631,395).
    $before = Capture "sweep_before"
    $hits = 0
    foreach ($ly in 40, 100, 160, 220, 280) {
        foreach ($lx in 40, 120, 200, 280, 360, 440, 520, 600) {
            Click $lx $ly
            $shot = Capture "sweep_$lx`_$ly"
            if ((RegionDiff $before $shot 192 368 447 471) -gt 0.02) { $hits++ }
            $shot.Dispose()
        }
    }
    Check ($hits -gt 0) "clicking the playfield selects something" "hits=$hits"
}
finally {
    if ($script:proc -and -not $script:proc.HasExited) { Stop-Process -Id $script:proc.Id -Force }
}
"captures in $OutDir"
if ($script:failures -gt 0) { "$script:failures check(s) failed"; exit 1 }
"all checks passed"
