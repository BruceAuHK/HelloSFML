//
// Created by Bruce au on 6/7/2022.
//

#include "Player.h"

unsigned playerNumber = 0;

enum controls { UP = 0, DOWN, LEFT, RIGHT, SHOOT };

Player::Player(std::shared_ptr<sf::Texture> texture, std::shared_ptr<sf::Texture> bulletTexture,
               std::shared_ptr<sf::Texture> mainGunTexture,
               int UP, int DOWN,
               int LEFT, int RIGHT,
               int SHOOT)
    : level(1), exp(0), expNext(100),
      hp(10), hpMax(10), damage(1),
      damageMax(2), score(0),
      maxVelocity(100.f),
      acceleration(20.f) {
  // Initialize member variables
  this->texture = texture;
  this->bulletTexture = bulletTexture;
  this->mainGunTexture = mainGunTexture;

  // Set up main gun sprite
  this->mainGunSprite.setTexture(*this->mainGunTexture);
  this->mainGunSprite.setOrigin(
      this->mainGunSprite.getGlobalBounds().width / 2,
      this->mainGunSprite.getGlobalBounds().height / 2
  );
  this->mainGunSprite.rotate(90);

  // Set up player sprite
  this->sprite.setTexture(*this->texture);
  this->sprite.scale(0.15f, 0.15f);

  // Initialize timers
  this->shootTimerMax = 5;
  this->shootTimer = this->shootTimerMax;
  this->damageTimerMax = 10;
  this->damageTimer = this->damageTimerMax;

  // Set up controls
  this->controls[controls::UP] = UP;
  this->controls[controls::DOWN] = DOWN;
  this->controls[controls::LEFT] = LEFT;
  this->controls[controls::RIGHT] = RIGHT;
  this->controls[controls::SHOOT] = SHOOT;

  // Set up movement properties
  this->maxVelocity = 50.f;
  this->acceleration = 2.f;
  this->stabilizerForce = 0.7f;

  std::cout << this->playerID << std::endl;
}

Player::~Player() {
}

void Player::update(sf::Vector2u windowBounds) {
  // Update shoot timer
  if (shootTimer < shootTimerMax)
    shootTimer++;

  // Perform player actions
  movement();
  updateAccessories();
  combat();

  // Update bullet positions
  for (auto &bullet : bullets) {
    bullet.update();
  }
}

void Player::movement() {
  // Handle player input
  handleInput();

  // Update player velocity based on input
  updateVelocity();

  // Apply stabilizer force to gradually stop the player's movement
  applyStabilizerForce();

  // Move the player sprite based on velocity
  moveSprite();

  // Update the center position of the player
  updatePlayerCenter();
}

void Player::handleInput() {
  // Check keyboard input and set the movement direction
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(controls[controls::UP])))
    direction = {0.f, -1.f};

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(controls[controls::DOWN])))
    direction = {0.f, 1.f};

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(controls[controls::LEFT])))
    direction = {-1.f, 0.f};

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(controls[controls::RIGHT])))
    direction = {1.f, 0.f};
}

void Player::updateVelocity() {
  // Update the player's velocity based on acceleration and direction
  if (std::abs(currentVelocity.y) < std::abs(maxVelocity))
    currentVelocity.y += direction.y * acceleration;

  if (std::abs(currentVelocity.x) < std::abs(maxVelocity))
    currentVelocity.x += direction.x * acceleration;
}

void Player::applyStabilizerForce() {
  // Apply stabilizer force to gradually stop the player's movement
  if (currentVelocity.x > 0) {
    currentVelocity.x -= stabilizerForce;

    if (currentVelocity.x < 0)
      currentVelocity.x = 0;
  } else if (currentVelocity.x < 0) {
    currentVelocity.x += stabilizerForce;

    if (currentVelocity.x > 0)
      currentVelocity.x = 0;
  }

  if (currentVelocity.y > 0) {
    currentVelocity.y -= stabilizerForce;

    if (currentVelocity.y < 0)
      currentVelocity.y = 0;
  } else if (currentVelocity.y < 0) {
    currentVelocity.y += stabilizerForce;

    if (currentVelocity.y > 0)
      currentVelocity.y = 0;
  }
}

void Player::moveSprite() {
  // Move the player sprite based on its velocity
  sprite.move(currentVelocity.x, currentVelocity.y);
}

void Player::updatePlayerCenter() {
  // Update the center position of the player
  playerCenter.x = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
  playerCenter.y = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;
}

void Player::draw(sf::RenderTarget &target) const{
  // Draw bullets, main gun sprite, and player sprite
  for (auto &bullet : bullets)
    bullet.draw(target);

  target.draw(mainGunSprite);
  target.draw(sprite);
}

void Player::combat() {
  // Handle shooting action
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(controls[controls::SHOOT]))) {
    if (shootTimer >= shootTimerMax) {
      bullets.push_back(Bullet(bulletTexture, playerCenter, 100.f, sf::Vector2f(1.f, 0.f), 10.f));
      shootTimer = 0;
    }
  }
}

void Player::updateAccessories() {
  // Update the position of the main gun sprite
  mainGunSprite.setPosition(playerCenter.x + 20.f, playerCenter.y);
}

std::vector<Bullet> &Player::getBullets() {
  // Return a reference to the player's bullets vector
  return bullets;
}

const sf::Vector2f &Player::getPosition() const {
  // Return the position of the player sprite
  return sprite.getPosition();
}

const std::string Player::getHpAsString() const {
  // Return the player's HP as a string
  return std::to_string(hp) + "/" + std::to_string(hpMax);
}