//
// Created by Bruce au on 6/7/2022.
//

#ifndef HELLOSFML_PLAYER_H
#define HELLOSFML_PLAYER_H

#include "Bullet.h"

class Player {
private:
    unsigned playerID;

    // timer
    int shootTimer;
    int shootTimerMax;
    int damageTimer; // how long you could get hit again?
    int damageTimerMax;
    Texture * texture;


    Sprite sprite;
    RectangleShape hitBox;

    // Accessories
    Texture *mainGunTexture;
    Sprite mainGunSprite;

    Vector2f playerCenter;

    // Bullet
    Texture * bulletTexture;
    std::vector<Bullet> bullets;

    // Movements
    int controls[5];
    Vector2f currentVelocity;
    float maxVelocity;
    float acceleration;
    Vector2f direction;
    float stabilizerForce;

    int level;
    int exp;
    int expNext;

    int hp;
    int hpMax;

    int damage;
    int damageMax;

    int score;

public:
    Player(Texture * texture, Texture * bulletTexture, Texture *mainGunTexture,
           int UP = 22, int DOWN = 18,
           int LEFT = 0, int RIGHT = 3,
           int SHOOT = 57);

    virtual ~Player();

    //Accessors
    inline std::vector<Bullet>& getBullets(){return this->bullets;}
    inline const Vector2f& getPosition() const{return this->sprite.getPosition();}
    inline const String getHpAsString()const {return std::to_string(this->hp) + "/" + std::to_string(this->hpMax);}

    // Functions
    void Combat();
    void Update(Vector2u windowsBounds);
    void Draw(RenderTarget &target);
    void Movement();    //keyboard stuff
    void UpdateAccessories();

    // static
//    static unsigned playerNumber;
};


#endif //HELLOSFML_PLAYER_H