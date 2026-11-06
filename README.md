# Miracle Author — COMP3016 Coursework 1 (VS2022 MVP)

**Important:** AI-assisted starter prototype. You must actually compile, test, refine and document this project; it is not a preverified final submission. This replacement adds a native Visual Studio 2022 solution; it does not require CLion/CMake/Git downloads to build.

## Fastest Visual Studio 2022 setup (Windows, x64)

1. Extract the whole ZIP, preserving the folder structure. Open the extracted folder.
2. **Double-click `SETUP_SDL3.cmd`.** Give the path to your extracted `SDL3-devel-...-VC` SDK folder. This is not the same as a folder containing only `SDL3.dll`. The tool copies SDK headers, `SDL3.lib` and `SDL3.dll` to `third_party/SDL3` (offline after you have the SDK).
3. Open `MiracleAuthor.sln` in **Visual Studio 2022** (not VS Code).
4. Select **x64** and **Debug** (or Release), **Build > Build Solution** (`Ctrl+Shift+B`). Ensure the "Desktop development with C++" workload / MSVC v143 and a Windows 10/11 SDK are installed.
5. Press **Ctrl+F5** to run. Look for a menu reading `MIRACLE AUTHOR`, then press Enter.

If build works, `build\Debug` or `build\Release` will contain `MiracleAuthor.exe`, `SDL3.dll` and `assets\level1.txt`. That folder can run on Windows without Visual Studio if the machine has the appropriate VC++ runtime. Test on an independent machine where possible.

### If your existing SDL3 package is different

You need the **SDL3 developer SDK for Visual C++ (VC)**, preferably version 3.4.x or at least SDL 3.2.0. Correct structure:

```
SDL3-devel-3.x.x-VC/SDL3-3.x.x/
  include/SDL3/SDL.h
  lib/x64/SDL3.lib
  lib/x64/SDL3.dll
```

Some SDK ZIPs have only one root directory; either layout works. The setup script accepts the SDK root or its parent folder. If you installed SDL3 elsewhere, you can use project settings instead, but the provided copy script is simplest.

Official SDK archive: https://www.libsdl.org/release/SDL3-devel-3.4.18-VC.zip

## Controls and goal

- `Enter` start, `R` restart, `Esc` quit
- `A/D` or `Left/Right` move
- `Space`, `W` or `Up` jump; repeat a jump against a solid wall to wall-jump
- Collect five **cyan sketches**, avoid **pink officers** (3 health), then reach the **green exit** before the timer expires.

The game uses the original sketch-collecting New York night-city concept, but intentionally minimal rectangle art and one level. The second level, sound and animation were stretch goals and are not included.

## Technical design

- `Game`: manages SDL3 input, main loop, states and drawing.
- `Level`: parses the level at runtime, validates dimensions, tile symbols, entities; stores walls and sketches.
- `Player`: delta-time movement, axis-aligned collision, jump/wall jump, health/invulnerability.
- `Enemy`: fixed horizontal patrol with wall avoidance.
- `Sketch`: minimal data object; the `Game` marks its collected state.
- Pattern: simple State pattern (`Menu`, `Playing`, `Win`, `Lose`).

The text level at `assets/level1.txt` starts with `24 15` (width/height) followed by 15 rows of 24 characters. `#` = wall, `P` = player, `C` = sketch, `E` = officer, `G` = gate, `.` = empty. Exactly one P, one G and five C, plus at least one E are required. A missing or invalid file triggers an error message instead of silently continuing.

## CMake option

`CMakeLists.txt` is included for convenience. The **native .sln is recommended**. For an already prepared SDK: `cmake -S . -B build-cmake` followed by `cmake --build build-cmake --config Release` (CMake defaults to local third_party/SDL3). Otherwise install an SDL3 CMake config and supply `-DCMAKE_PREFIX_PATH=...`.

## Assessment-critical to do list

1. Confirm it builds in VS2022, then play through. See `docs/Test_Checklist.md` and record actual evidence.
2. Make genuine feature/fix commits in GitHub, not backdated or fabricated commits. This starter alone cannot satisfy past weekly-commit expectations.
3. Edit `docs/AI_Development_Log.md` to state what ChatGPT provided, how you reviewed it and what you changed.
4. Document proposal fulfilment and real scope decisions in `docs/REPORT_TEMPLATE.md` / public GitHub README. Include gameplay, OOP/UML, dependency details, test cases, screenshots, reflection.
5. Record a **maximum 10-minute video** with code walkthrough and gameplay demonstration; include your face for authentication as stated in the brief, upload and link in your report.
6. Complete and sign the AI declaration form from DLE.
7. ZIP final code + the SDK headers/lib needed to compile, built game folder (exe/dll/assets), proposal, your report/log, and a `GitHub_Link.txt` containing the public repo/README URL; stay under **150MB**. Ensure the final ZIP contents match your report and video.

## Sources / provenance

Original proposal: `docs/Week2_Proposal.pdf` (student's plan). SDL3 (library; zlib licence) must be supplied from the user's existing SDK. The base C++ prototype and Visual Studio scaffolding were AI-assisted; review, test, and adapt everything before submission. All later modifications and third-party assets should be cited appropriately.

**Limitations:** Windows build and runtime have not been directly tested by the assistant; only structural/source checks may be performed here. Visual appearance and behaviour must be confirmed on your PC. Visuals use SDL3's built-in debug text (available since SDL 3.2) and rectangles rather than production sprite art.
