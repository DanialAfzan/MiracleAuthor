#pragma once
#include <SDL3/SDL.h>
#include <vector>

class Player {
public:
    void reset(SDL_FPoint start);
    void update(const bool* keys, bool jumpPressed, float delta,
                const std::vector<SDL_FRect>& walls);
    void render(SDL_Renderer* renderer) const;
    bool damage(); // Return false if still invulnerable.
    const SDL_FRect& bounds() const { return body_; }
    int health() const { return health_; }

private:
    SDL_FRect body_{0, 0, 26, 34};
    float velocityY_ = 0.0f;
    float kickTimer_ = 0.0f;
    float kickVelocity_ = 0.0f;
    float invulnerability_ = 0.0f;
    int health_ = 3;
    bool grounded_ = false;
};
