## AI Development Log — Miracle Author

**AI Tool Used:** ChatGPT (OpenAI)

**Categories of Use:**
- Game concept and proposal planning.
- C++ and SDL3 code generation.
- Visual Studio 2022 project setup.
- SDL3 configuration and troubleshooting.
- Documentation and testing assistance.

**Example Prompts:**
- "Help me start Assessment 1 from scratch, including SDL3 project setup."
- "Let's do this under a day."
- "You might need to give me a new MVP ZIP to work with because the previous one doesn't work."

**Verification and Refinement:**

ChatGPT initially provided a CMake-based prototype, but I was unable to get it working in my development environment.

I switched to Visual Studio 2022 and requested a replacement project compatible with my existing SDL3 installation.

During setup, the SDL3 configuration initially failed because I supplied the path to `SDL3.lib` instead of the SDK directory. After correcting the path, I configured the project.

I subsequently compiled and played Miracle Author in Visual Studio 2022 to confirm that the game launched and functioned.

**Repository Evidence:**

The GitHub repository contains the submitted source code, development history and documentation.

Repository: https://github.com/DanialAfzan/MiracleAuthor

Further improvements, test results and any code modifications should be documented in their respective commits.
