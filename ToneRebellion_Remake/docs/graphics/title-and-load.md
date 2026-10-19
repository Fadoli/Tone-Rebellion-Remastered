# Title and load screens

- Title art uses frame 0 of `TITSCRN` as the 640×480 background and frames 2, 4, 6, and 8 at the four button panes from `windows.txt`.
- The load screen uses `LOADSAV0.SHP` frames 0 and 1. `windows.txt`'s load-state background and overlay both cover the 640×480 client area. The remake scans the eight save slots with the original header checks and returns to the title when an empty slot is clicked; valid-save restoration remains unimplemented.
