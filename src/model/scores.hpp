#pragma once

namespace biv {
class Scores {
private:
    int score = 0;
    
public:
    void add_enemy_kill() { score += 100; }
    void add_coin_collect() { score += 50; }
    void reset() { score = 0; }
    int get_score() const noexcept { return score; }
};
}