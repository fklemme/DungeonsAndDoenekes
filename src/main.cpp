#include "Game.hpp"

// Just for testing
// TODO: remove!
#include <iostream>
#include <vector>
#include "utility/observer_ptr.hpp"
#include <memory>

static void test() {
    auto owning_int_ptr = std::make_unique<int>(5);
    observer_ptr<int> int_ptr(owning_int_ptr);
    std::cout << std::is_convertible_v<int*, int*> << std::endl;
}

int main() {
    //test();
    //return 0;

    Game game;

    // Game loop
    game.run();

    return 0;
}