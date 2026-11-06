# Miracle Author — COMP3016 Coursework 1 (VS2022 MVP)

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

## Assessment Report
[View Final Report](docs/REPORT_TEMPLATE.md)
