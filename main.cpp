#include "Game.h"

int main()
{

    // Create window
    RenderWindow window(VideoMode(2560,1600), "Wingman Game", Style::Default);



    // Initialize Game and send it to the window
    Game game(&window);

    // Game Loop
    while (window.isOpen()){
        Event event;

        // End Game
        while (window.pollEvent(event)){
            if ((event.type == Event::Closed))
                window.close();
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                window.close();
        }

        // Running the Game
        game.Update();
        game.Draw();
    }
    return 0;
}