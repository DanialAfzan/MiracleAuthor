#include "Level.h"
#include "Config.h"
#include <fstream>
#include <string>
#include <utility>

namespace {
    bool overlaps(const SDL_FRect& a, const SDL_FRect& b) {
        return a.x < b.x + b.w && a.x + a.w > b.x &&
               a.y < b.y + b.h && a.y + a.h > b.y;
    }
}

bool Level::load(const std::string& path, std::string& error) {
    std::ifstream file(path);
    if (!file) { error = "Cannot open " + path; return false; }

    int width = 0, height = 0;
    if (!(file >> width >> height) || width != Config::WindowWidth / Config::TileSize ||
        height != Config::WindowHeight / Config::TileSize) {
        error = "Level dimensions must be 24 x 15."; return false;
    }
    std::string row;
    std::getline(file, row);  // Consume the line break following dimensions.

    std::vector<SDL_FRect> walls;
    std::vector<Sketch> sketches;
    std::vector<SDL_FRect> enemies;
    SDL_FPoint playerStart{};
    SDL_FRect exitGate{};
    int playerCount = 0, gateCount = 0;

    for (int y = 0; y < height; ++y) {
        if (!std::getline(file, row) || static_cast<int>(row.size()) != width) {
            error = "Missing or incorrectly sized row " + std::to_string(y + 1); return false;
        }
        for (int x = 0; x < width; ++x) {
            const float px = static_cast<float>(x * Config::TileSize);
            const float py = static_cast<float>(y * Config::TileSize);
            switch (row[x]) {
                case '.': break;
                case '#': walls.push_back({px, py, 40.0f, 40.0f}); break;
                case 'P': playerStart = {px + 7, py + 4}; ++playerCount; break;
                case 'C': sketches.push_back({{px + 11, py + 10, 18, 18}, false}); break;
                case 'E': enemies.push_back({px + 6, py + 8, 28, 30}); break;
                case 'G': exitGate = {px + 4, py, 32, 40}; ++gateCount; break;
                default: error = "Unknown tile symbol at row " + std::to_string(y + 1); return false;
            }
        }
    }
    if (playerCount != 1 || gateCount != 1 ||
        static_cast<int>(sketches.size()) != Config::RequiredSketches || enemies.empty()) {
        error = "Level needs 1 P, 1 G, 5 C and at least 1 E."; return false;
    }
    // Avoid partial changes when invalid level files are encountered.
    walls_ = std::move(walls);
    sketches_ = std::move(sketches);
    patrolStarts_ = std::move(enemies);
    playerStart_ = playerStart;
    exitGate_ = exitGate;
    return true;
}

bool Level::hitsWall(const SDL_FRect& body) const {
    for (const auto& wall : walls_) {
        if (overlaps(body, wall)) return true;
    }
    return false;
}
