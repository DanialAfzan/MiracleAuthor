# COMP3016 Assessment 1 — test checklist (record real evidence)

Tested by: ___________  Date/time: ___________  System: Windows ____ / Visual Studio 2022 ____  SDL3 version: _____

| Test | Expected result | Result (PASS/FAIL/NOT TESTED) | Actual evidence / fix |
|---|---|---|---|
| VS2022 builds x64 Debug | No compiler/linker errors | PASS | |
| VS2022 builds x64 Release | No compiler/linker errors | PASS | |
| Launch game | Menu appears | PASS | |
| Enter starts | Gameplay begins | PASS | |
| A/D and arrows move | Horizontal movement | PASS | |
| Space jumps and wall-jumps | Jump works; side walls give kick | FAIL | |
| Solid walls/platforms | Player blocked, no falling through | PASS | |
| Find all five sketches | Counter increases once per sketch | PASS | |
| Try gate at fewer than five | Gate remains locked | PASS | |
| Reach gate after five | Win screen appears | PASS | |
| Touch enemy | Health -1, 1 s immunity | PASS | |
| Zero health / timeout | Lose screen appears | PASS | |
| Press R | Full reset of game state | PASS | |
| Remove level file temporarily | Helpful error, no crash | NOT TESTED | |
| Alter level file to invalid data | Helpful error, no crash | NOT TESTED | |
| Open exe standalone (DLL + assets) | Game runs without VS debugger | NOT TESTED | |

If a peer plays the game, record their anonymous observations, the bug, your fix and a real Git commit. Do not claim checks passed until tested.
