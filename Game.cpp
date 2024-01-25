#include "Game.h"

Game::Game(sf::RenderWindow& window)
    : window(window) {
  this->window.setFramerateLimit(60);

  this->font.loadFromFile("/Users/bruceau/CLionProjects/HelloSFML/Textures/Font/Dosis-VariableFont_wght.ttf");

  // Load textures for player, bullet, and gun
  this->playerTexture.loadFromFile("/Users/bruceau/CLionProjects/HelloSFML/Textures/ship.png");
  this->bulletTexture.loadFromFile("/Users/bruceau/CLionProjects/HelloSFML/Textures/Guns/missileTex01.png");
  this->gunTexture01.loadFromFile("/Users/bruceau/CLionProjects/HelloSFML/Textures/Guns/gun01.png");

  // Create players and initialize their textures
  this->players.emplace_back(std::make_shared<sf::Texture>(playerTexture),
                             std::make_shared<sf::Texture>(bulletTexture),
                             std::make_shared<sf::Texture>(gunTexture01));

  this->players.emplace_back(std::make_shared<sf::Texture>(playerTexture),
                             std::make_shared<sf::Texture>(bulletTexture),
                             std::make_shared<sf::Texture>(gunTexture01),
                             sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J,
                             sf::Keyboard::L, sf::Keyboard::RShift);

  this->initUI();
}

Game::~Game() {
}

void Game::update() {
  // Update players and remove bullets that are off-screen
  for (auto& player : players) {
    player.update(this->window.getSize());

    auto& bullets = player.getBullets();
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [this](const Bullet& bullet) {
                                   return bullet.getPosition().x > this->window.getSize().x;
                                 }),
                  bullets.end());
  }

  this->updateUI();
}

void Game::draw() {
  this->window.clear();

  // Draw players
  for (const auto& player : this->players)
    player.draw(this->window);

  this->drawUI();
  this->window.display();
}

void Game::updateUI() {
  // Update UI elements for follow players
  for (size_t i = 0; i < this->followPlayerText.size(); ++i) {
    this->followPlayerText[i].setPosition(this->players[i].getPosition());
    this->followPlayerText[i].setString(std::to_string(i) + " | " + this->players[i].getHpAsString());
  }

  // Update UI elements for static players
  for (size_t i = 0; i < this->staticPlayerText.size(); ++i) {
    this->staticPlayerText[i].setPosition(this->players[i].getPosition());
    this->staticPlayerText[i].setString(std::to_string(i) + " | " + this->players[i].getHpAsString());
  }
}

void Game::drawUI() {
  // Draw follow player UI texts
  for (const auto& text : this->followPlayerText)
    this->window.draw(text);

  // Draw static player UI texts
  for (const auto& text : this->staticPlayerText)
    this->window.draw(text);
}

void Game::initUI() {
  // Initialize UI texts for players
  for (const auto& player : this->players) {
    sf::Text tempText;
    tempText.setCharacterSize(120);
    tempText.setOutlineColor(sf::Color::White);
    tempText.setFillColor(sf::Color::White);
    tempText.setString("");
    this->staticPlayerText.push_back(tempText);
    this->followPlayerText.push_back(tempText);
  }
}
