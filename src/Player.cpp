#include "Player.h"
#include "Config.h"
#include <algorithm>

namespace {
    constexpr float MoveSpeed = 255.0f;
    constexpr float Gravity = 1470.0f;
    constexpr float JumpSpeed = -630.0f;
    bool overlaps(const SDL_FRect& a, const SDL_FRect& b) {
        return a.x < b.x + b.w && a.x + a.w > b.x &&
               a.y < b.y + b.h && a.y + a.h > b.y;
    }
}

void Player::reset(SDL_FPoint start) {
    body_ = {start.x, start.y, 26, 34};
    velocityY_ = 0;
    kickTimer_ = 0;
    kickVelocity_ = 0;
    invulnerability_ = 0;
    health_ = 3;
    grounded_ = false;
}

void Player::update(const bool* keys, bool jumpPressed, float dt,
                    const std::vector<SDL_FRect>& walls) {
    invulnerability_ = std::max(0.0f, invulnerability_ - dt);
    kickTimer_ = std::max(0.0f, kickTimer_ - dt);
    const bool left = keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT];
    const bool right = keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT];
    const float dx = static_cast<float>(right) - static_cast<float>(left);

    // Small side probes detect whether the player is touching a wall.
    SDL_FRect leftProbe{body_.x - 3, body_.y + 3, 4, body_.h - 6};
    SDL_FRect rightProbe{body_.x + body_.w - 1, body_.y + 3, 4, body_.h - 6};
    bool leftWall = false, rightWall = false;
    for (const auto& wall : walls) {
        leftWall |= overlaps(leftProbe, wall);
        rightWall |= overlaps(rightProbe, wall);
    }

    if (jumpPressed) {
        if (grounded_) {
            velocityY_ = JumpSpeed;
            grounded_ = false;
        } else if (leftWall || rightWall) {
            // Wall jump: kick away from the surface for a short duration.
            velocityY_ = JumpSpeed * 0.90f;
            kickVelocity_ = leftWall ? 330.0f : -330.0f;
            kickTimer_ = 0.16f;
        }
    }

    float movement = (kickTimer_ > 0 ? kickVelocity_ : dx * MoveSpeed) * dt;
    body_.x += movement;
    for (const auto& wall : walls) {
        if (overlaps(body_, wall)) {
            if (movement > 0) body_.x = wall.x - body_.w;
            else if (movement < 0) body_.x = wall.x + wall.w;
        }
    }
    body_.x = std::clamp(body_.x, 0.0f,
                          static_cast<float>(Config::WindowWidth) - body_.w);

    velocityY_ += Gravity * dt;
    velocityY_ = std::min(velocityY_, 900.0f);
    const float movementY = velocityY_ * dt;
    body_.y += movementY;
    grounded_ = false;
    for (const auto& wall : walls) {
        if (overlaps(body_, wall)) {
            if (movementY >= 0) {
                body_.y = wall.y - body_.h;
                grounded_ = true;
            } else {
                body_.y = wall.y + wall.h;
            }
            velocityY_ = 0;
        }
    }
    if (body_.y < 0) { body_.y = 0; velocityY_ = 0; }
}

bool Player::damage() {
    if (invulnerability_ > 0) return false;
    --health_;
    invulnerability_ = 1.0f;
    return true;
}

void Player::render(SDL_Renderer* renderer) const {
    // Blinking feedback during one second of invulnerability.
    if (invulnerability_ > 0 && static_cast<int>(invulnerability_ * 12) % 2 == 0) return;
    SDL_SetRenderDrawColor(renderer, 245, 194, 98, 255);
    SDL_RenderFillRect(renderer, &body_);
    SDL_FRect face{body_.x + 16, body_.y + 9, 4, 4};
    SDL_SetRenderDrawColor(renderer, 37, 40, 58, 255);
    SDL_RenderFillRect(renderer, &face);
}
