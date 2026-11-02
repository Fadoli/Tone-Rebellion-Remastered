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
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr hdc, uint flags);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
}
"@
$ErrorActionPreference = "Stop"
New-Item -ItemType Directory -Force $OutDir | Out-Null
$script:failures = 0
$script:proc = $null

$script:statePath = Join-Path $OutDir "state.txt"
$env:TONE_REBELLION_E2E_STATE = $script:statePath

function State {
    # Parse the snapshot written by the remake (src/.../e2e_state.inc).
    $st = @{ floaters = @(); locations = @(); clips = @(); dots = @() }
    if (-not (Test-Path $script:statePath)) { return $st }
    foreach ($line in (Get-Content $script:statePath -ErrorAction SilentlyContinue)) {
        $t = $line -split ' '
        if ($t[0] -eq 'floater') {
            $f = @{ index = [int]$t[1]; x = [int]$t[2]; y = [int]$t[3] }
            foreach ($kv in $t[4..($t.Length - 1)]) { $k, $v = $kv -split '='; $f[$k] = [int]$v }
            $st.floaters += , $f
        } elseif ($t[0] -eq 'location') {
            $l = @{ index = [int]$t[1]; x = [int]$t[2]; y = [int]$t[3] }
            foreach ($kv in $t[4..($t.Length - 1)]) { $k, $v = $kv -split '='; $l[$k] = [int]$v }
            $st.locations += , $l
        } elseif ($t[0] -eq 'clip_dots') {
            $st.dots += , ([int]$t[2])
        } elseif ($t[0] -eq 'clip_slot') {
            $st.clips += , @{ slot = [int]$t[1]; island = [int]$t[2]; location = [int]$t[3] }
        } elseif ($t.Length -eq 2) { $st[$t[0]] = [int]$t[1] }
    }
    $st
}
function WaitState($pred, $seconds = 5) {
    $end = (Get-Date).AddSeconds($seconds)
    do { $st = State; if (& $pred $st) { return $st }; Start-Sleep -Milliseconds 150 } while ((Get-Date) -lt $end)
    State
}
# Island coordinates -> logical screen coordinates for the current scroll.
function ScreenX($st, $x) { $x - $st.scroll }

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
    # PrintWindow renders the window itself, so other windows on top do not matter.
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $hdc = $g.GetHdc()
    [E2E]::PrintWindow((Handle), $hdc, 2) | Out-Null
    $g.ReleaseHdc($hdc); $g.Dispose()
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


# Fraction of clearly lit pixels in a logical rectangle of a capture.
function LitFraction($bmp, $lx0, $ly0, $lx1, $ly1) {
    $c = Client
    $r = New-Object E2E+RECT
    [E2E]::GetWindowRect((Handle), [ref]$r) | Out-Null
    $offX = (($r.R - $r.L) - $c.R) / 2
    $offY = ($r.B - $r.T) - $c.B - $offX
    $x0 = [int]($offX + $lx0 * $c.R / 640.0); $x1 = [int]($offX + $lx1 * $c.R / 640.0)
    $y0 = [int]($offY + $ly0 * $c.B / 480.0); $y1 = [int]($offY + $ly1 * $c.B / 480.0)
    $lit = 0; $total = 0
    for ($y = $y0; $y -lt $y1; $y++) {
        for ($x = $x0; $x -lt $x1; $x++) {
            $p = $bmp.GetPixel($x, $y)
            if ($p.R + $p.G + $p.B -gt 250) { $lit++ }
            $total++
        }
    }
    $lit / [math]::Max($total, 1)
}

function ClickBridge($st, $l) {
    # Scroll the marker into view, then click it (retry if a floater shadows it).
    for ($try = 0; $try -lt 3; $try++) {
        $cur = State
        $guard = 0
        while ((ScreenX $cur $l.x) -lt 40 -and $cur.scroll -gt 0 -and $guard++ -lt 80) { Key 0x25 5; $cur = State }
        while ((ScreenX $cur $l.x) -gt 600 -and $guard++ -lt 160) { Key 0x27 5; $cur = State }
        $from = $cur.island
        # Floaters win over sites inside 20 px: wait until none hovers over it.
        for ($wait = 0; $wait -lt 40; $wait++) {
            $cur = State
            $shadow = $false
            foreach ($f in $cur.floaters) {
                if ([math]::Max([math]::Abs($f.x - $l.x), [math]::Abs($f.y - $l.y)) -lt 26) { $shadow = $true }
            }
            if (-not $shadow) { break }
            Start-Sleep -Milliseconds 200
        }
        Click (ScreenX $cur $l.x) $l.y
        $now = WaitState { param($s) $s.island -ne $from } 3
        if ($now.island -ne $from) { return $true }
        Start-Sleep -Milliseconds 700
    }
    $false
}
function ExploreTo($target, $visited) {
    $st = State
    if ($st.island -eq $target) { return $true }
    $visited[$st.island] = $true
    $from = $st.island
    foreach ($l in $st.locations) {
        if ($l.class -ne 2 -or $l.bridge -ne 1 -or $l.neighbor -lt 0 -or $visited.ContainsKey($l.neighbor)) { continue }
        if (-not (ClickBridge $st $l)) { continue }
        if (ExploreTo $target $visited) { return $true }
        $now = State
        $back = $null
        foreach ($b in $now.locations) { if ($b.class -eq 2 -and $b.bridge -eq 1 -and $b.neighbor -eq $from) { $back = $b; break } }
        if ($back) { ClickBridge $now $back | Out-Null }
    }
    $false
}

Get-Process ToneRebellion_Remake -ErrorAction SilentlyContinue | Stop-Process -Force
$script:proc = Start-Process $Exe -PassThru
try {
    Start-Sleep -Seconds 6
    [E2E]::SetForegroundWindow((Handle)) | Out-Null   # captures use the screen
    Start-Sleep -Milliseconds 500
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
    Key 0x52        # R (E2E test aid) -> reopen the same island
    Start-Sleep -Seconds 2
    Check ((Title) -like "*Island*") "the island reopens" (Title)
    $m2 = Capture "island_reentered"
    $c2 = MarkerColumn $m2 195 332 445 357
    Check ([math]::Abs($c2 - $c1) -le 3) "scroll position is kept on re-entry" "marker $c1 -> $c2"
    Check ($c2 -gt $c0) "re-entry does not reset scroll to 0" "marker $c0 -> $c2"

    # --- State-driven checks (use the remake's TONE_REBELLION_E2E_STATE dump)
    $st = WaitState { param($s) $s.screen -eq 3 -and $s.floaters.Count -gt 0 }
    $tribe = $st.tribe
    if ($st.island -ne $st.hall_island) {
        Check ($st.hall_player -eq $tribe) "the Hall is selected by default on another island" "island $($st.island) hall_island $($st.hall_island) hall_player $($st.hall_player)"
    } else { "SKIP  Hall default on another island (the resume starts on the Hall island)" }

    # Leviathan (owner 4) selection: native FUN_00435581 skips only flag bit 1,
    # needs no explored cell, and returns the first match in list order.
    $cand = $null
    foreach ($f in $st.floaters) {
        $sx = ScreenX $st $f.x
        if ($f.owner -ne 4 -or ($f.flags -band 1) -ne 0) { continue }
        if ($sx -lt 25 -or $sx -gt 615 -or $f.y -lt 45 -or $f.y -gt 300) { continue }
        $shadow = $false
        foreach ($g in $st.floaters) {
            if ($g.index -lt $f.index -and ($g.flags -band 1) -eq 0 -and
                [math]::Max([math]::Abs($g.x - $f.x), [math]::Abs($g.y - $f.y)) -lt 20) { $shadow = $true }
        }
        if (-not $shadow) { $cand = $f; break }
    }
    if ($cand) {
        Click (ScreenX $st $cand.x) $cand.y
        $after = WaitState { param($s) $s.selected_floater -ge 0 } 2
        Check ($after.selected_floater -eq $cand.index) "clicking a Leviathan selects it" "wanted $($cand.index) got $($after.selected_floater)"
    } else { "SKIP  clicking a Leviathan (none on screen)" }

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

    # Bridge entry: a constructed class-2 marker switches to its partner island.
    $startIsland = $st.island
    $bridge = $null
    foreach ($l in $st.locations) {
        if ($l.class -ne 2 -or $l.bridge -ne 1 -or $l.neighbor -lt 0) { continue }
        $near = $false
        foreach ($f in $st.floaters) {
            if ([math]::Max([math]::Abs($f.x - $l.x), [math]::Abs($f.y - $l.y)) -lt 22) { $near = $true }
        }
        if (-not $near) { $bridge = $l; break }
    }
    if ($bridge) {
        # Open the Tasks panel first: the crossing re-selects the kept location
        # through FUN_0042f755(rec, 1), the building panel (mode 3).
        Click 130 450
        $pre = WaitState { param($s) $s.panel_mode -eq 2 } 2
        $st2 = State
        ClickBridge $st2 $bridge | Out-Null
        $in = WaitState { param($s) $s.island -ne $startIsland } 4
        Check ($in.island -eq $bridge.neighbor) "clicking a built bridge enters the partner island" "wanted $($bridge.neighbor) got $($in.island)"
        if ($pre.selected_location -ge 0) {
            Check ($in.panel_mode -eq 3 -and $in.selected_location -eq $pre.selected_location) "the bridge crossing keeps the selection in the building panel" "panel_mode $($in.panel_mode) selected $($in.selected_location) was $($pre.selected_location)"
        }
        $partner = $null
        foreach ($l in $in.locations) { if ($l.class -eq 2 -and $l.neighbor -eq $startIsland) { $partner = $l; break } }
        if ($partner) {
            $psx = ScreenX $in $partner.x
            Check ($psx -gt 0 -and $psx -lt 640) "the view is scrolled to the arrival bridge" "partner screen x $psx"
        }
        Capture "after_bridge" | Out-Null
    } else { "SKIP  bridge entry (no clear constructed bridge on the island)" }

    # --- Hall island: the test-only 'H' key on the world map opens it.
    Key 0x1B
    Key 0x48
    $st = WaitState { param($s) $s.screen -eq 3 -and $s.island -eq $s.hall_island } 4
    Check ($st.screen -eq 3 -and $st.island -eq $st.hall_island) "the Hall island opens" "island $($st.island) hall $($st.hall_island)"
    if ($st.island -eq $st.hall_island) {
        Check ($st.hall_player -eq $tribe) "the Hall is selected by default on its own island"
        Click 604 441                      # BC_Trade
        $tr = WaitState { param($s) $s.panel_mode -eq 7 } 2
        Check ($tr.panel_mode -eq 7) "Hall Trade button opens the Commerce panel" "panel_mode $($tr.panel_mode)"
        Capture "commerce" | Out-Null
        Click 130 450                      # TASKLIST toggles Tasks, then back
        Click 130 450
        # F9 test aid: place a training building and link two workers to it.
        Key 0x78
        Start-Sleep -Milliseconds 800
        $tb = State
        $train = $null
        foreach ($l in $tb.locations) {
            $base = $l.item - $l.owner * 16
            if ($l.owner -eq $tribe -and $base -ge 0x2c -and $base -le 0x2e) { $train = $l; break }
        }
        Check ($null -ne $train) "F9 test aid places a training building" "locations $($tb.locations.Count)"
        $afterClip = Capture "clip_after"
        $dotsShown = 0
        foreach ($d in $tb.dots) { $dotsShown += $d }
        Check ($dotsShown -gt 0) "the active shortcut group lists training buildings" "dots $($tb.dots -join ',')"
        Check ((LitFraction $afterClip 159 364 183 465) -gt 0.003) "the shortcut slots are drawn lit" "lit $(LitFraction $afterClip 159 364 183 465)"
        Check ($tb.clips.Count -gt 0) "training buildings register in the shortcut strip"
        # Click a worker linked to the new building (positions drift, so retry).
        $picked = $false
        for ($try = 0; $try -lt 10 -and -not $picked; $try++) {
            $cur = State
            $linked = $null
            # Bring the first linked worker into view.
            foreach ($f in $cur.floaters) {
                if ($f.owner -eq $tribe -and $f.link -ne -1) {
                    $g = 0
                    while ((ScreenX $cur $f.x) -lt 60 -and $g++ -lt 60) { Key 0x25 5; $cur = State }
                    while ((ScreenX $cur $f.x) -gt 580 -and $g++ -lt 120) { Key 0x27 5; $cur = State }
                    break
                }
            }
            foreach ($f in $cur.floaters) {
                $sx = ScreenX $cur $f.x
                if ($f.owner -eq $tribe -and $f.link -ne -1 -and $sx -gt 25 -and $sx -lt 615 -and $f.y -gt 45 -and $f.y -lt 300) {
                    $shadow = $false
                    foreach ($g in $cur.floaters) {
                        if ($g.index -lt $f.index -and ($g.flags -band 1) -eq 0 -and
                            [math]::Max([math]::Abs($g.x - $f.x), [math]::Abs($g.y - $f.y)) -lt 20) { $shadow = $true }
                    }
                    if (-not $shadow) { $linked = $f; break }
                }
            }
            if ($linked) {
                Click (ScreenX $cur $linked.x) $linked.y
                $sel = WaitState { param($s) $s.selected_floater -ge 0 } 1
                if ($sel.selected_floater -ge 0) { $picked = $true; Capture "linked_floater" | Out-Null }
            } else { Start-Sleep -Milliseconds 500 }
        }
        Check $picked "clicking a linked worker selects it" "no linked worker could be clicked"
        # Cross-island shortcut: leave through a bridge, then use the slot.
        # FUN_0042fa0f msgs 3001..3003 select the remembered building on its
        # own island without changing the viewed island (building panel, mode 3).
        $tb = State
        $exit = $null
        foreach ($l in $tb.locations) { if ($l.class -eq 2 -and $l.bridge -eq 1 -and $l.neighbor -ge 0) { $exit = $l; break } }
        if ($exit -and $tb.clips.Count -gt 0) {
            $homeIsland = $tb.island
            $slot = $tb.clips[0]
            if (ClickBridge $tb $exit) {
                $away = State
                Click 171 381                  # CLIPBD1
                $sel = WaitState { param($s) $s.selection_island -eq $slot.island } 3
                Check ($sel.island -eq $away.island -and $sel.island -ne $homeIsland) "a shortcut slot keeps the viewed island" "island $($sel.island)"
                Check ($sel.selection_island -eq $slot.island -and $sel.selected_location -eq $slot.location -and $sel.panel_mode -eq 3) "a shortcut slot selects its building on another island" "sel $($sel.selection_island)/$($sel.selected_location) mode $($sel.panel_mode)"
            }
        }
    }

}
finally {
    if ($script:proc -and -not $script:proc.HasExited) { Stop-Process -Id $script:proc.Id -Force }
}
"captures in $OutDir"
if ($script:failures -gt 0) { "$script:failures check(s) failed"; exit 1 }
"all checks passed"
