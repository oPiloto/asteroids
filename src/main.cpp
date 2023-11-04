#include "Game.hpp"

int main(int argc, char **argv) {
    auto game = std::make_unique<aste::Game>("Asteroids");
    game->run();
    return 0;
}
