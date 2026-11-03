# End-to-end checks on a static fixture game (no player save involved):
# TONE_REBELLION_E2E_FIXTURE=badges builds world 0 / tribe 0 / fixed seed and
# adds known units beside the Hall (src/.../e2e_state.inc, e2e_build_fixture).
# Saves and settings go to a temporary folder (TONE_REBELLION_SAVE_DIR).
# Usage: powershell -File tests/e2e/fixture_e2e.ps1 [-Exe path] [-OutDir dir]
param(
    [string]$Exe = (Join-Path $PSScriptRoot "..\..\ToneRebellion_Remake.exe"),
    [string]$OutDir = (Join-Path $env:TEMP "remake_fixture_e2e")
)
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System; using System.Runtime.InteropServices;
public class FixtureE2E {
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr hdc, uint flags);
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
}
"@
$ErrorActionPreference = "Stop"
$Exe = (Resolve-Path $Exe).Path
New-Item -ItemType Directory -Force $OutDir | Out-Null
$saves = Join-Path $OutDir "saves"
if (Test-Path $saves) { Remove-Item -Recurse -Force $saves }
New-Item -ItemType Directory -Force $saves | Out-Null
# Settings for the run only: no sound-device prompt, 1:1 scale for clicks.
Set-Content -Path (Join-Path $saves "audio.cfg") -Value "0 0 0 0" -Encoding ascii
Set-Content -Path (Join-Path $saves "video.cfg") -Value "scale 1" -Encoding ascii
$statePath = Join-Path $OutDir "state.txt"
if (Test-Path $statePath) { Remove-Item $statePath }
$env:TONE_REBELLION_SAVE_DIR = $saves
$env:TONE_REBELLION_E2E_STATE = $statePath
$env:TONE_REBELLION_E2E_FIXTURE = "badges"
Remove-Item Env:TONE_REBELLION_E2E_LOAD -ErrorAction SilentlyContinue
$script:failures = 0

function Check($ok, $name, $detail) {
    if ($ok) { "PASS  $name" } else { "FAIL  $name  $detail"; $script:failures++ }
}
function State {
    $st = @{ floaters = @(); locations = @() }
    foreach ($line in (Get-Content $statePath -ErrorAction SilentlyContinue)) {
        $t = $line -split ' '
        if ($t[0] -eq 'floater') {
            $f = @{ index = [int]$t[1]; x = [int]$t[2]; y = [int]$t[3] }
            foreach ($kv in $t[4..($t.Length - 1)]) { $k, $v = $kv -split '='; $f[$k] = [int]$v }
            $st.floaters += , $f
        } elseif ($t[0] -eq 'location') {
            $l = @{ index = [int]$t[1]; x = [int]$t[2]; y = [int]$t[3] }
            foreach ($kv in $t[4..($t.Length - 1)]) { $k, $v = $kv -split '='; $l[$k] = [int]$v }
            $st.locations += , $l
        } elseif ($t[0] -eq 'text_info') {
            $st.text_info = $t[1]
        } elseif ($t.Length -eq 2 -and $t[1] -match '^-?\d+$') {
            $st[$t[0]] = [int]$t[1]
        }
    }
    $st
}
function Click($lx, $ly) {
    $r = New-Object FixtureE2E+RECT; [FixtureE2E]::GetClientRect($script:h, [ref]$r) | Out-Null
    $k = [math]::Min($r.R / 640.0, $r.B / 480.0); $ox = ($r.R - 640 * $k) / 2; $oy = ($r.B - 480 * $k) / 2
    $l = [IntPtr]((([int]($oy + $ly * $k)) -shl 16) -bor ([int]($ox + $lx * $k)))
    [FixtureE2E]::PostMessage($script:h, 0x200, [IntPtr]0, $l) | Out-Null; Start-Sleep -Milliseconds 200
    [FixtureE2E]::PostMessage($script:h, 0x201, [IntPtr]1, $l) | Out-Null; Start-Sleep -Milliseconds 80
    [FixtureE2E]::PostMessage($script:h, 0x202, [IntPtr]0, $l) | Out-Null; Start-Sleep -Milliseconds 400
}
function Capture($name) {
    $r = New-Object FixtureE2E+RECT; [FixtureE2E]::GetWindowRect($script:h, [ref]$r) | Out-Null
    $bmp = New-Object System.Drawing.Bitmap ($r.R - $r.L), ($r.B - $r.T)
    $g = [System.Drawing.Graphics]::FromImage($bmp); $hdc = $g.GetHdc()
    [FixtureE2E]::PrintWindow($script:h, $hdc, 2) | Out-Null; $g.ReleaseHdc($hdc); $g.Dispose()
    $bmp.Save((Join-Path $OutDir "$name.png")); $bmp.Dispose()
}

function Launch($fixture) {
    if (Test-Path $statePath) { Remove-Item $statePath }
    $env:TONE_REBELLION_E2E_FIXTURE = $fixture
    $script:proc = Start-Process -FilePath $Exe -WorkingDirectory (Split-Path $Exe) -PassThru
    $script:h = [IntPtr]::Zero
    for ($i = 0; $i -lt 60 -and $script:h -eq [IntPtr]::Zero; $i++) {
        Start-Sleep -Milliseconds 250; $script:proc.Refresh(); $script:h = $script:proc.MainWindowHandle
    }
    Start-Sleep -Seconds 2
}
function Quit {
    if ($script:proc -and -not $script:proc.HasExited) {
        [FixtureE2E]::PostMessage($script:h, 0x0010, [IntPtr]0, [IntPtr]0) | Out-Null
        $script:proc.WaitForExit(10000) | Out-Null
        if (-not $script:proc.HasExited) { Stop-Process -Id $script:proc.Id -Force }
    }
}

try {
    Launch "badges"
    $st = State
    Check ($st.screen -eq 3 -and $st.tribe -eq 0) "the fixture opens the island view" "screen $($st.screen) tribe $($st.tribe)"
    $warrior = $st.floaters | Where-Object { $_.owner -eq 0 -and $_.subtype -eq 4 } | Select-Object -First 1
    $leviathan = $st.floaters | Where-Object { $_.type -eq 4 -and $_.subtype -eq 12 } | Select-Object -First 1
    $enemy = $st.floaters | Where-Object { $_.owner -eq 1 -and $_.subtype -eq 1 } | Select-Object -First 1
    Check ($null -ne $warrior) "the fixture has the own warrior" ""
    Check ($null -ne $leviathan) "the fixture has the subtype-12 Leviathan" ""
    Check ($null -ne $enemy) "the fixture has the enemy unit" ""

    Click 30 450                                   # TOGREALM: world badges on
    Start-Sleep -Milliseconds 600
    Capture "badges_world"

    if ($warrior) {
        $st = State
        $w = $st.floaters | Where-Object { $_.index -eq $warrior.index }
        Click ($w.x - $st.scroll) $w.y
        Start-Sleep -Milliseconds 600
        $sel = State
        Check ($sel.selected_floater -eq $warrior.index) "clicking the warrior selects it" "selected $($sel.selected_floater)"
        Capture "warrior_panel"
    }
    Quit

    # Another tribe's Hall (item 0x2a, raw 0x2a + owner * 16) shows that
    # tribe's NEWGAME<owner> name in IWTextInfo (FUN_00439673 mode 0).
    Launch "enemy_hall"
    $st = State
    $hall = $st.locations | Where-Object { $_.owner -eq 1 -and $_.class -eq 0 -and $_.item -eq 0x3a } | Select-Object -First 1
    Check ($null -ne $hall) "the enemy_hall fixture shows tribe 1's Hall" "island $($st.island)"
    Quit
    if ($hall) {
        # Its workers stand on it, so a click would pick one of them: start
        # again with the Hall selected (TONE_REBELLION_E2E_SELECT); this checks
        # what IWTextInfo draws, not click hit-testing.
        $env:TONE_REBELLION_E2E_SELECT = [string]$hall.index
        Launch "enemy_hall"
        Remove-Item Env:TONE_REBELLION_E2E_SELECT
        Start-Sleep -Seconds 1
        $sel = State
        Check ($sel.selected_location -eq $hall.index -and $sel.text_info -eq "NEWGAME1") "another tribe's Hall shows its tribe name" "selected $($sel.selected_location) text $($sel.text_info)"
        Capture "enemy_hall"
    }
    Quit

    # A spell cast: tribe 0's BC_Spell7 on a 0x2f building is kind 14 (no
    # target pick). FUN_0042383d starts the effect at cast tick 10 and
    # FUN_004239e9 applies it when FUN_0041760b's animation ends.
    Launch "spell"
    $st = State
    $tower = $st.locations | Where-Object { $_.index -eq $st.selected_location } | Select-Object -First 1
    Check ($null -ne $tower -and $tower.item -eq 0x2f) "the spell fixture selects its spell building" "selected $($st.selected_location) item $($tower.item)"
    Click 592 453                                  # BC_Spell7
    $started = $false
    for ($i = 0; $i -lt 40 -and -not $started; $i++) {
        Start-Sleep -Milliseconds 150
        if ((State).cast_effects -gt 0) { $started = $true; Capture "spell_cast" }
    }
    Check $started "BC_Spell7 starts a cast effect" "cast_effects stayed 0"
    $ended = $false
    for ($i = 0; $i -lt 60 -and $started -and -not $ended; $i++) {
        Start-Sleep -Milliseconds 200
        if ((State).cast_effects -eq 0) { $ended = $true }
    }
    Check $ended "the cast effect ends after its animation" ""
}
finally {
    Quit
}
"captures in $OutDir"
if ($script:failures -gt 0) { "$($script:failures) check(s) failed"; exit 1 }
