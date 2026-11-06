#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <vector>

struct Sketch {
    SDL_FRect bounds{};
    bool collected = false;
};

class Level {
public:
    // Loads and validates a user-editable level file. Returns false, not a crash,
    // if the file is absent or malformed.
    bool load(const std::string& path, std::string& error);
    bool hitsWall(const SDL_FRect& body) const;
    const std::vector<SDL_FRect>& walls() const { return walls_; }
    std::vector<Sketch>& sketches() { return sketches_; }
    const std::vector<Sketch>& sketches() const { return sketches_; }
    const std::vector<SDL_FRect>& patrolStarts() const { return patrolStarts_; }
    SDL_FPoint playerStart() const { return playerStart_; }
    SDL_FRect exitGate() const { return exitGate_; }

private:
    std::vector<SDL_FRect> walls_;
    std::vector<Sketch> sketches_;
    std::vector<SDL_FRect> patrolStarts_;
    SDL_FPoint playerStart_{};
    SDL_FRect exitGate_{};
};
