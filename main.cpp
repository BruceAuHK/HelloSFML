#include "Game.h"
#include <memory>

int main() {
  // Create window
  sf::RenderWindow window(sf::VideoMode(2560, 1600), "Wingman Game", sf::Style::Default);

  // Initialize Game and send it to the window
  Game game(window);

  // Game Loop
  while (window.isOpen()) {
    sf::Event event;

    // Handle events
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed
          || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        window.close();
    }

    // Update game state
    game.update();

    // Render game
    game.draw();
  }

  return 0;
}
