const { spawnSync } = require('node:child_process');

const iterations = Number(process.argv[2] || 100000);
if (!Number.isInteger(iterations) || iterations < 1000) {
  throw new Error('iterations must be an integer >= 1000');
}

const script = String.raw`
$ErrorActionPreference = 'Stop'
Add-Type -TypeDefinition @'
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
public static class SpriteDcBench {
  [DllImport("gdi32.dll")] static extern IntPtr CreateCompatibleDC(IntPtr hdc);
  [DllImport("gdi32.dll")] static extern IntPtr CreateCompatibleBitmap(IntPtr hdc, int w, int h);
  [DllImport("gdi32.dll")] static extern IntPtr SelectObject(IntPtr hdc, IntPtr obj);
  [DllImport("gdi32.dll")] static extern bool DeleteDC(IntPtr hdc);
  [DllImport("gdi32.dll")] static extern bool DeleteObject(IntPtr obj);
  static double Churn(int n, IntPtr bitmap) {
    var sw = Stopwatch.StartNew();
    for (int i = 0; i < n; ++i) {
      IntPtr dc = CreateCompatibleDC(IntPtr.Zero);
      IntPtr old = SelectObject(dc, bitmap);
      SelectObject(dc, old);
      DeleteDC(dc);
    }
    return sw.Elapsed.TotalMilliseconds;
  }
  static double Reuse(int n, IntPtr bitmap) {
    IntPtr dc = CreateCompatibleDC(IntPtr.Zero);
    var sw = Stopwatch.StartNew();
    for (int i = 0; i < n; ++i) {
      IntPtr old = SelectObject(dc, bitmap);
      SelectObject(dc, old);
    }
    sw.Stop();
    DeleteDC(dc);
    return sw.Elapsed.TotalMilliseconds;
  }
  public static object Measure(int n) {
    IntPtr refDc = CreateCompatibleDC(IntPtr.Zero);
    IntPtr bitmap = CreateCompatibleBitmap(refDc, 1, 1);
    DeleteDC(refDc);
    Churn(1000, bitmap); Reuse(1000, bitmap);
    double[] a = new double[5], b = new double[5];
    for (int r = 0; r < 5; ++r) { a[r] = Churn(n, bitmap); b[r] = Reuse(n, bitmap); }
    Array.Sort(a); Array.Sort(b);
    DeleteObject(bitmap);
    return new { iterations = n, churn_ms = a[2], reuse_ms = b[2], speedup = a[2] / b[2] };
  }
}
'@
[SpriteDcBench]::Measure(${iterations}) | ConvertTo-Json -Compress
`;
const result = spawnSync('powershell.exe', ['-NoProfile', '-Command', script], {
  encoding: 'utf8',
  windowsHide: true,
});
if (result.error) throw result.error;
if (result.status !== 0) throw new Error(result.stderr || `PowerShell exited ${result.status}`);
process.stdout.write(result.stdout.trim() + '\n');
