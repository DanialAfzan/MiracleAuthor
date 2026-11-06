# Miracle Author — COMP3016 Assessment 1 Report

## 1. Project Overview

Miracle Author is a 2D platformer developed in C++ using SDL3. The game follows an aspiring artist exploring a nighttime city to collect five sketches before her deadline, while avoiding patrolling officers.

The main objective is to collect all five sketches and reach the exit before the timer runs out or the player's health reaches zero.

## 2. Proposal and Development Changes

My original proposal planned a 2D platformer featuring movement, wall jumping, collectibles, enemy patrols, health, a timer and level progression.

For the final prototype, I prioritised one playable level using simple shapes instead of detailed sprites. Additional levels, music and animations were left out to focus on the core gameplay and technical requirements.

[Link to original proposal](Week2_Proposal.pdf)

## 3. Gameplay and Controls

Players must explore the level, collect five cyan sketches, avoid pink enemies and reach the green exit once all sketches are collected.

- **A/D or Left/Right:** Move horizontally.
- **Space, W or Up:** Jump and wall jump.
- **Enter:** Start the game.
- **R:** Restart the game.
- **Escape:** Exit.

The player starts with three health points and has 150 seconds to complete the level. Enemy contact removes one health point, followed by one second of temporary invulnerability.

## 4. Technical Implementation and OOP

The project uses C++ classes to separate different game responsibilities:

- **Game:** Manages the game loop, input, rendering and game states.
- **Player:** Handles movement, jumping, collisions, health and damage.
- **Level:** Loads level data from a text file and manages the environment.
- **Enemy:** Handles basic horizontal patrol behaviour.
- **Sketch:** Represents individual collectible objects.

A simple state system controls the Menu, Playing, Win and Lose screens.

The level is loaded from `assets/level1.txt` during execution. Each character in the file represents an element such as a wall, player spawn, enemy, collectible or exit.

Movement uses delta time, while collision detection checks overlapping rectangles. The level loader also checks for missing files and invalid level information.

## 5. Tools and Dependencies

The project uses Visual Studio 2022, C++, SDL3 version 3.4.18 and GitHub for source control.

SDL3 handles window creation, keyboard input, rendering and other game functionality. The project contains a Visual Studio solution and instructions for configuring SDL3.

## 6. AI-Assisted Development

ChatGPT assisted with the original proposal, gameplay planning, C++ prototype, Visual Studio project configuration, SDL3 setup instructions and documentation.

The original starter package did not work with my setup, so I requested a replacement designed for Visual Studio 2022. I configured the SDL3 SDK and successfully built and played the resulting game.

AI-generated code and documentation are identified as assisted work rather than independently written work. Further details, prompts, verification and limitations are recorded in the [AI Development Log](AI_Development_Log.md).

## 7. Testing and Validation

I successfully launched and played Miracle Author using Visual Studio 2022 and confirmed that the game was working before pushing it to GitHub.

The project includes a testing checklist for movement, collisions, collectibles, health, game states, restart and level loading. Individual test outcomes and any additional checks should be recorded in `Test_Checklist.md`.

<img width="957" height="626" alt="image" src="https://github.com/user-attachments/assets/4dbaa6b4-18e2-4ccf-8098-faf2234e4efb" />

<img width="945" height="623" alt="image" src="https://github.com/user-attachments/assets/344740a2-0ff3-445f-a44e-02efec9cf4ac" />

## 8. Demonstration Video

https://youtu.be/XXOADRSYSX4

The demonstration covers the gameplay, controls, code structure, technical implementation and AI-assisted development process.

## 9. Evaluation and Future Improvements

Miracle Author demonstrates the implementation of a playable 2D game using C++ and SDL3, including object-oriented design, collision detection, runtime level loading and gameplay state management.

The current version focuses on functionality rather than visual detail. With more development time, I would improve the character artwork, add animations and sound effects, create more levels and expand the overall city environment.

The project helped me gain experience working with SDL3, configuring C++ dependencies in Visual Studio and understanding how different classes contribute to a complete gameplay system.
