#ifndef HELLOSFML_GAME_H
#define HELLOSFML_GAME_H

#include "Player.h"
#include <SFML/Graphics.hpp>

class Game {
 private:
  sf::RenderWindow& window;                   // Reference to the SFML render window
  sf::Font font;                              // Font for UI text
  std::vector<sf::Text> followPlayerText;      // UI text for following players
  std::vector<sf::Text> staticPlayerText;      // UI text for static players
  std::vector<Player> players;                 // Vector of players
  sf::Texture playerTexture;                   // Texture for player sprite
  sf::Texture bulletTexture;                   // Texture for bullet sprite
  sf::Texture gunTexture01;                    // Texture for gun sprite

 public:
  Game(sf::RenderWindow& window);              // Constructor
  ~Game();                                     // Destructor

  void update();                               // Update game state
  void draw();                                 // Render game

 private:
  void updateUI();                             // Update UI elements
  void drawUI();                               // Draw UI elements
  void initUI();                               // Initialize UI
};

#endif // HELLOSFML_GAME_H
