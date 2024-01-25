//
// Created by Bruce au on 6/7/2022.
//

#ifndef HELLOSFML_BULLET_H
#define HELLOSFML_BULLET_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

using namespace sf;

class Bullet {
 private:
  std::shared_ptr<Texture> texture;
  Sprite sprite;
  float maxVelocity;          // Maximum velocity of the bullet
  float acceleration;         // Acceleration of the bullet
  Vector2f currentVelocity;   // Current velocity of the bullet
  Vector2f direction;         // Direction of the bullet

 public:
  Bullet(std::shared_ptr<Texture> texture,
         Vector2f position,
         float maxVelocity,
         Vector2f direction,
         float acceleration);
  virtual ~Bullet();

  void update();                    // Update the bullet's position
  void draw(RenderTarget &target) const;   // Draw the bullet on the render target

  // Accessors
  inline FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }   // Get the global bounding rectangle of the bullet
  inline Vector2f getPosition() const { return sprite.getPosition(); }   // Get the position of the bullet
};

#endif // HELLOSFML_BULLET_H
