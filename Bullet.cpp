//
// Created by Bruce au on 6/7/2022.
//

#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<Texture> texture,
               Vector2f position,
               float maxVelocity,
               Vector2f direction,
               float acceleration) {
  // Initialize the bullet with provided parameters
  this->texture = texture;
  this->sprite.setTexture(*this->texture);
  this->maxVelocity = maxVelocity;
  this->acceleration = acceleration;
  this->direction = direction;

  // Set the scale and position of the bullet sprite
  this->sprite.setScale(0.1f, 0.1f);
  this->sprite.setPosition(position);
  this->sprite.setPosition(
      Vector2f(position.x - this->sprite.getGlobalBounds().width / 2,
               position.y - this->sprite.getGlobalBounds().height / 2)
  );
}

void Bullet::update() {
  // Update the bullet's velocity based on acceleration and direction
  if (acceleration > 0.f) {
    if (currentVelocity.x < maxVelocity)
      currentVelocity.x += acceleration * direction.x;

    if (currentVelocity.y < maxVelocity)
      currentVelocity.y += acceleration * direction.y;
  } else {
    // If acceleration is non-positive, set the velocity directly based on the maximum velocity and direction
    currentVelocity = Vector2f(
        maxVelocity * direction.x,
        maxVelocity * direction.y
    );
  }

  // Move the bullet based on its velocity
  sprite.move(currentVelocity);
}

void Bullet::draw(RenderTarget &target) const{
  // Draw the bullet sprite
  target.draw(sprite);
}

Bullet::~Bullet() {
}
