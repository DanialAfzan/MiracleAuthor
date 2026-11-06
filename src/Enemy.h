#pragma once
#include <SDL3/SDL.h>
#include <vector>

class Enemy {
public:
    explicit Enemy(SDL_FRect spawn);
    void update(float dt, const std::vector<SDL_FRect>& walls);
    void render(SDL_Renderer* renderer) const;
    const SDL_FRect& bounds() const { return body_; }

private:
    SDL_FRect body_{};
    float homeX_ = 0.0f;
    float direction_ = 1.0f;
};
