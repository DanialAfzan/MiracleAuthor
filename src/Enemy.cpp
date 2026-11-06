#include "Enemy.h"
#include <algorithm>

namespace {
    bool overlaps(const SDL_FRect& a, const SDL_FRect& b) {
        return a.x < b.x + b.w && a.x + a.w > b.x &&
               a.y < b.y + b.h && a.y + a.h > b.y;
    }
}

Enemy::Enemy(SDL_FRect spawn) : body_(spawn), homeX_(spawn.x) {}

void Enemy::update(float dt, const std::vector<SDL_FRect>& walls) {
    const float oldX = body_.x;
    body_.x += direction_ * 72.0f * dt;
    bool blocked = false;
    for (const auto& wall : walls) {
        if (overlaps(body_, wall)) blocked = true;
    }
    if (blocked || body_.x < homeX_ - 78.0f || body_.x > homeX_ + 78.0f) {
        body_.x = oldX;
        direction_ = -direction_;
    }
}

void Enemy::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 241, 104, 132, 255);
    SDL_RenderFillRect(renderer, &body_);
    SDL_FRect visor{body_.x + 5, body_.y + 6, body_.w - 10, 6};
    SDL_SetRenderDrawColor(renderer, 59, 36, 58, 255);
    SDL_RenderFillRect(renderer, &visor);
}
