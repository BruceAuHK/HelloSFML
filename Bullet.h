//
// Created by Bruce au on 6/7/2022.
//

#ifndef HELLOSFML_BULLET_H
#define HELLOSFML_BULLET_H

#include <SFML/Graphics.hpp>
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "vector"
#include "iostream"

using namespace sf;

class Bullet {
private:
    Texture* texture;
    Sprite sprite;



    float maxVelocity;
    float acceleration;
    Vector2f currentVelocity;
    Vector2f direction;

public:
    Bullet(Texture *texture, Vector2f position, float maxVelocity, Vector2f direction, float acceleration);
    virtual ~Bullet();

    void Update();

    void Draw(RenderTarget &target);

    void Movement();

    //Accessors
    inline const FloatRect & getGlobalBounds() const{ return this->sprite.getGlobalBounds();}
    inline const Vector2f & getPosition() const{ return this->sprite.getPosition();}

};



#endif //HELLOSFML_BULLET_H