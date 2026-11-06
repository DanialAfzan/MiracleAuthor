#include "Game.h"
#include "Config.h"
#include <algorithm>
#include <cmath>
#include <string>

namespace {
    bool overlaps(const SDL_FRect& a, const SDL_FRect& b) {
        return a.x < b.x + b.w && a.x + a.w > b.x &&
               a.y < b.y + b.h && a.y + a.h > b.y;
    }
    void fill(SDL_Renderer* r, SDL_FRect rect, Uint8 red, Uint8 green, Uint8 blue) {
        SDL_SetRenderDrawColor(r, red, green, blue, 255);
        SDL_RenderFillRect(r, &rect);
    }
}

Game::~Game() {
    if (renderer_) SDL_DestroyRenderer(renderer_);
    if (window_) SDL_DestroyWindow(window_);
    if (sdlReady_) SDL_Quit();
}

bool Game::loadLevel() {
    const char* base = SDL_GetBasePath();
    const std::string baseDir = base ? base : "";
    std::string error;
    // CLion typically runs with project root as working directory; exe launch
    // typically uses the directory containing the exe. Support both.
    const std::vector<std::string> candidates = {
        "assets/level1.txt", baseDir + "assets/level1.txt"
    };
    for (const auto& path : candidates) {
        if (level_.load(path, error)) {
            levelPath_ = path;
            return true;
        }
    }
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Level loading failed: %s", error.c_str());
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Miracle Author: Level Error",
                             error.c_str(), window_);
    return false;
}

bool Game::initialize() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init: %s", SDL_GetError());
        return false;
    }
    sdlReady_ = true;
    if (!SDL_CreateWindowAndRenderer("Miracle Author", Config::WindowWidth,
                                     Config::WindowHeight, 0, &window_, &renderer_)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window: %s", SDL_GetError());
        return false;
    }
    if (!loadLevel()) return false;
    startNewRun();
    state_ = State::Menu;
    running_ = true;
    return true;
}

void Game::startNewRun() {
    // Reload from disk, so editing the level file takes effect after restart.
    std::string error;
    if (!level_.load(levelPath_, error)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Restart load failed: %s", error.c_str());
        running_ = false;
        return;
    }
    player_.reset(level_.playerStart());
    enemies_.clear();
    for (const auto& spawn : level_.patrolStarts()) enemies_.emplace_back(spawn);
    collected_ = 0;
    timeLeft_ = Config::DeadlineSeconds;
    jumpPending_ = false;
    state_ = State::Playing;
}

void Game::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) running_ = false;
        if (event.type != SDL_EVENT_KEY_DOWN || event.key.repeat) continue;
        if (event.key.scancode == SDL_SCANCODE_ESCAPE) running_ = false;
        if (event.key.scancode == SDL_SCANCODE_RETURN ||
            event.key.scancode == SDL_SCANCODE_KP_ENTER) {
            if (state_ == State::Menu) startNewRun();
        }
        if (event.key.scancode == SDL_SCANCODE_R && state_ != State::Menu)
            startNewRun();
        if (event.key.scancode == SDL_SCANCODE_SPACE ||
            event.key.scancode == SDL_SCANCODE_W ||
            event.key.scancode == SDL_SCANCODE_UP) jumpPending_ = true;
    }
}

void Game::update(float dt) {
    if (state_ != State::Playing) { jumpPending_ = false; return; }
    const bool* keys = SDL_GetKeyboardState(nullptr);
    player_.update(keys, jumpPending_, dt, level_.walls());
    jumpPending_ = false;
    for (auto& enemy : enemies_) {
        enemy.update(dt, level_.walls());
        if (overlaps(player_.bounds(), enemy.bounds())) player_.damage();
    }
    if (player_.health() <= 0 || player_.bounds().y > Config::WindowHeight) {
        state_ = State::Lose;
        return;
    }
    for (auto& sketch : level_.sketches()) {
        if (!sketch.collected && overlaps(player_.bounds(), sketch.bounds)) {
            sketch.collected = true;
            ++collected_;
        }
    }
    if (collected_ == Config::RequiredSketches &&
        overlaps(player_.bounds(), level_.exitGate())) {
        state_ = State::Win;
        return;
    }
    timeLeft_ = std::max(0.0f, timeLeft_ - dt);
    if (timeLeft_ <= 0) state_ = State::Lose;
}

void Game::run() {
    Uint64 previous = SDL_GetTicks();
    while (running_) {
        processEvents();
        const Uint64 current = SDL_GetTicks();
        const float delta = std::min(0.033f, static_cast<float>(current - previous) / 1000.0f);
        previous = current;
        if (!running_) break;
        update(delta);
        render();
        SDL_Delay(1);
    }
}

void Game::drawBackdrop() {
    SDL_SetRenderDrawColor(renderer_, 15, 21, 42, 255);
    SDL_RenderClear(renderer_);
    fill(renderer_, {780, 50, 48, 48}, 234, 225, 171); // moon
    for (int i = 0; i < 12; ++i) {
        float x = static_cast<float>(i * 90 - 10);
        float top = static_cast<float>(255 + (i * 43) % 100);
        fill(renderer_, {x, top, 69, 560 - top}, 30, 39, 65);
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 3; ++k) {
                if ((i + j + k) % 3 != 0)
                    fill(renderer_, {x + 11 + k * 18, top + 14 + j * 23, 7, 8},
                         114, 105, 101);
            }
        }
    }
}

void Game::drawWorld() {
    drawBackdrop();
    for (const auto& wall : level_.walls()) {
        fill(renderer_, wall, 59, 78, 108);
        fill(renderer_, {wall.x, wall.y, wall.w, 5}, 105, 125, 146);
    }
    const SDL_FRect gate = level_.exitGate();
    if (collected_ == Config::RequiredSketches)
        fill(renderer_, gate, 95, 222, 168);
    else
        fill(renderer_, gate, 104, 110, 131);
    fill(renderer_, {gate.x + 5, gate.y + 8, 5, 5}, 21, 30, 46);
    for (const auto& sketch : level_.sketches()) {
        if (!sketch.collected) {
            fill(renderer_, sketch.bounds, 89, 225, 241);
            fill(renderer_, {sketch.bounds.x + 4, sketch.bounds.y + 4, 9, 9}, 224, 247, 235);
        }
    }
    for (const auto& enemy : enemies_) enemy.render(renderer_);
    player_.render(renderer_);
    fill(renderer_, {0, 0, 960, 44}, 18, 29, 49);
    SDL_SetRenderDrawColor(renderer_, 244, 238, 222, 255);
    drawText("SKETCHES " + std::to_string(collected_) + "/5", 18, 13);
    drawText("HEALTH " + std::to_string(player_.health()), 340, 13);
    drawText("TIME " + std::to_string(static_cast<int>(std::ceil(timeLeft_))), 630, 13);
}

void Game::drawText(const std::string& text, float x, float y, int scale) {
    SDL_SetRenderScale(renderer_, static_cast<float>(scale), static_cast<float>(scale));
    SDL_RenderDebugText(renderer_, x / scale, y / scale, text.c_str());
    SDL_SetRenderScale(renderer_, 1.0f, 1.0f);
}

void Game::drawCentered(const std::string& text, float y, int scale) {
    const float width = static_cast<float>(text.length() * 8 * scale);
    drawText(text, (Config::WindowWidth - width) / 2, y, scale);
}

void Game::render() {
    drawWorld();
    if (state_ != State::Playing) {
        fill(renderer_, {105, 156, 750, 260}, 18, 28, 48);
        SDL_SetRenderDrawColor(renderer_, 240, 233, 213, 255);
        if (state_ == State::Menu) {
            drawCentered("MIRACLE AUTHOR", 202, 3);
            drawCentered("Collect five sketches. Avoid patrols.", 257, 2);
            drawCentered("A / D or ARROWS = move    SPACE = jump", 297, 2);
            drawCentered("Press ENTER to start", 345, 2);
        } else if (state_ == State::Win) {
            drawCentered("DEADLINE MET - YOU WIN!", 213, 3);
            drawCentered("All five city sketches completed.", 275, 2);
            drawCentered("Press R to try again", 328, 2);
        } else {
            drawCentered("GAME OVER", 213, 3);
            drawCentered("No health or time remaining.", 275, 2);
            drawCentered("Press R to restart", 328, 2);
        }
    }
    SDL_RenderPresent(renderer_);
}
