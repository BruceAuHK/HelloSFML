//
// Created by Bruce au on 6/7/2022.
//

#include "Player.h"

unsigned playerNumber = 0;

enum controls {UP = 0, DOWN, LEFT, RIGHT, SHOOT};

Player::Player(Texture * texture, Texture * bulletTexture, Texture *mainGunTexture,
               int UP, int DOWN,
               int LEFT, int RIGHT,
               int SHOOT)

        :level(1), exp(0), expNext(100),
         hp(10), hpMax(10), damage(1),
         damageMax(2), score(0)

{
    // Texture
    this->texture = texture;
    this->bulletTexture = bulletTexture;
    this->mainGunTexture = mainGunTexture;
    this->mainGunSprite.setTexture(*this->mainGunTexture);
    this->mainGunSprite.setOrigin(
            this->mainGunSprite.getGlobalBounds().width/2,
            this->mainGunSprite.getGlobalBounds().height/2
    );
    this->mainGunSprite.rotate(90);

    this->sprite.scale(0.15f,0.15f); //Scale down the photo


    this->shootTimerMax = 5;
    this->shootTimer = this->shootTimerMax;

    this->damageTimerMax = 10;
    this->damageTimer =this->damageTimerMax;

    this->sprite.setTexture(*this->texture);
    this->controls[controls::UP] = UP;
    this->controls[controls::DOWN] = DOWN;
    this->controls[controls::LEFT] = LEFT;
    this->controls[controls::RIGHT] = RIGHT;
    this->controls[controls::SHOOT] = SHOOT;

    // Movement
    this->maxVelocity = 35.f;
    this->acceleration = 1.f;
    this->stabilizerForce = 0.7f;


    std::cout << this->playerID << std::endl;
}


Player::~Player() {

}



void Player::Update(Vector2u windowBounds) {
    // Update timers
    if(this->shootTimer < this->shootTimerMax)
        shootTimer++;

    if(this->damageTimer < this->damageTimerMax)
        damageTimer++;




    this->Movement();
    this->UpdateAccessories();
    this->Combat();


    for(auto &bullet: bullets){
        bullet.Update();
    }

}

void Player::Movement() {
    if(Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP])))
//        this->sprite.move(0.f,-30.f);
        this->direction = {0.f,-1.f};
    if(abs(this->currentVelocity.y) < abs(this->maxVelocity))
        this->currentVelocity.y += this->direction.y * this->acceleration;

    if(Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN])))
//        this->sprite.move(0.f,30.f);
        this->direction = {0.f,1.f};
    if(abs(this->currentVelocity.y) < abs(this->maxVelocity))
        this->currentVelocity.y += this->direction.y * this->acceleration;

    if(Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT])))
//        this->sprite.move(-30.f,0.f);
        this->direction = {-1.f,0.f};
    if(abs(this->currentVelocity.x) < abs(this->maxVelocity))
        this->currentVelocity.x += this->direction.x * this->acceleration;

    if(Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT])))
//        this->sprite.move(30.f,0.f);
        this->direction = {1.f,0.f};
    if(abs(this->currentVelocity.x) < abs(this->maxVelocity))
        this->currentVelocity.x += this->direction.x * this->acceleration;

    // drag force
    if(this->currentVelocity.x  > 0) {
        this->currentVelocity.x -= this->stabilizerForce;

        if (this->currentVelocity.x < 0)
            this->currentVelocity.x = 0;
    }
    else if(this->currentVelocity.x  < 0) {
        this->currentVelocity.x += this->stabilizerForce;

        if (this->currentVelocity.x > 0)
            this->currentVelocity.x = 0;
    }

    if(this->currentVelocity.y  > 0) {
        this->currentVelocity.y -= this->stabilizerForce;

        if (this->currentVelocity.y < 0)
            this->currentVelocity.y = 0;
    }

    else if(this->currentVelocity.y  < 0) {
        this->currentVelocity.y += this->stabilizerForce;

        if (this->currentVelocity.y > 0)
            this->currentVelocity.y = 0;
    }



    // Finial move
    this->sprite.move(this->currentVelocity.x, this->currentVelocity.y);


    // Updates positions
    this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2;
    this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height/2;
}

void Player::Draw(RenderTarget &target) {
    for(auto &bullet: bullets)
        bullet.Draw(target);
    target.draw(this->mainGunSprite);
    target.draw(this->sprite);

}

void Player::Combat() {
    if(Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT])))
        this->bullets.push_back(
                Bullet(bulletTexture,
                       this->playerCenter,
                       100.f, Vector2f(1.f, 0.f), 10.f));
    this->shootTimer = 0;
}

void Player::UpdateAccessories() {
    this->mainGunSprite.setPosition(
            this->playerCenter.x + 20.f,
            this->playerCenter.y);
}