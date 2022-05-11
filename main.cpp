#include "engine.h"

int main()
{
    // Declare an instance of Game Engine
    Engine engine;

    // Start the engine, works as a game/event loop
    engine.start();

    // Quit if the engine is stopped
    return 0;
}