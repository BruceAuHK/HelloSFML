//
// Created by Bruce au on 6/7/2022.
//

#include "Bullet.h"



Bullet::Bullet(Texture *texture, Vector2f position, float maxVelocity, Vector2f direction, float acceleration)
{
    this->texture = texture;
    this->sprite.setTexture(*this->texture);
    this->maxVelocity = maxVelocity;
    this->acceleration = acceleration;
    this->direction = direction;

    this->sprite.setScale(0.1f, 0.1f);
    this->sprite.setPosition(position);
    this->sprite.setPosition(
            Vector2f(position.x - this->sprite.getGlobalBounds().width/2,
                     position.y - this->sprite.getGlobalBounds().height/2)
    );

}

void Bullet::Update() {
    this->Movement();
}

Bullet::~Bullet() {

}

void Bullet::Draw(RenderTarget &target) {
    target.draw(this->sprite);
}

void Bullet::Movement() {
    if(this->acceleration > 0.f){
        if(this->currentVelocity.x < this->maxVelocity)
            this->currentVelocity.x += this->acceleration * this->direction.x;

        if(this->currentVelocity.y < this->maxVelocity)
            this->currentVelocity.y += this->acceleration * this->direction.y;
    }

    else{
        this->currentVelocity = Vector2f(
                this->maxVelocity * this->direction.x,
                this->maxVelocity * this->direction.y);
    }


    this->sprite.move(currentVelocity);
}