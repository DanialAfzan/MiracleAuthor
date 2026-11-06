#pragma once
#include "Enemy.h"
#include "Level.h"
#include "Player.h"
#include <SDL3/SDL.h>
#include <string>
#include <vector>

class Game {
public:
    ~Game();
    bool initialize();
    void run();

private:
    enum class State { Menu, Playing, Win, Lose };
    bool loadLevel();
    void startNewRun();
    void processEvents();
    void update(float dt);
    void render();
    void drawBackdrop();
    void drawWorld();
    void drawText(const std::string& text, float x, float y, int scale = 2);
    void drawCentered(const std::string& text, float y, int scale = 2);

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    bool sdlReady_ = false;
    bool running_ = false;
    bool jumpPending_ = false;
    State state_ = State::Menu;
    Level level_;
    Player player_;
    std::vector<Enemy> enemies_;
    int collected_ = 0;
    float timeLeft_ = 0;
    std::string levelPath_;
};
