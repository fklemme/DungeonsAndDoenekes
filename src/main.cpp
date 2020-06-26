#include "Game.hpp"
#include "utility/observer_ptr.hpp"

// Just for testing
// TODO: remove!
static void test() {
    float f = 5.0f;
    double d = 7.0;

    observer_ptr<float> f_ptr = &f;
    observer_ptr<double> d_ptr = &d;

    // auto f_ptr = make_observer(&f);
    // auto d_ptr = make_observer(&d);

    if (*f_ptr < *d_ptr) *f_ptr = *d_ptr;
}

int main() {
    test();

    Game game;

    // Game loop
    game.run();

    return 0;
}