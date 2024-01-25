//
// Created by Bruce au on 6/7/2022.
//

#ifndef HELLOSFML_PLAYER_H
#define HELLOSFML_PLAYER_H

#include "Bullet.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
 private:
  unsigned playerID;
  int shootTimer;
  int shootTimerMax;
  int damageTimer;
  int damageTimerMax;
  std::shared_ptr<sf::Texture> texture;
  sf::Sprite sprite;
  sf::RectangleShape hitBox;
  std::shared_ptr<sf::Texture> mainGunTexture;
  sf::Sprite mainGunSprite;
  sf::Vector2f playerCenter;
  std::shared_ptr<sf::Texture> bulletTexture;
  std::vector<Bullet> bullets;
  int controls[5];
  sf::Vector2f currentVelocity;
  float maxVelocity;
  float acceleration;
  sf::Vector2f direction;
  float stabilizerForce;
  int level;
  int exp;
  int expNext;
  int hp;
  int hpMax;
  int damage;
  int damageMax;
  int score;

  // Movement helper functions
  void handleInput();
  void updateVelocity();
  void applyStabilizerForce();
  void moveSprite();
  void updatePlayerCenter();

 public:
  Player(std::shared_ptr<sf::Texture> texture, std::shared_ptr<sf::Texture> bulletTexture,
         std::shared_ptr<sf::Texture> mainGunTexture,
         int UP = 22, int DOWN = 18,
         int LEFT = 0, int RIGHT = 3,
         int SHOOT = 57);

  virtual ~Player();

  std::vector<Bullet> &getBullets();
  const sf::Vector2f &getPosition() const;
  const std::string getHpAsString() const;

  // Player actions
  void combat();
  void update(sf::Vector2u windowBounds);
  void draw(sf::RenderTarget &target) const;
  void movement();
  void updateAccessories();
};

#endif //HELLOSFML_PLAYER_H
