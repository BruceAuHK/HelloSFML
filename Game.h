//
// Created by Bruce au on 6/7/2022.
//

#ifndef HELLOSFML_GAME_H
#define HELLOSFML_GAME_H

#include "Player.h"

class Game {
private:
    RenderWindow *window;


    // Text
    Font font;
    std::vector<Text> followPlayerText;
    std::vector<Text> staticPlayerText;

    // Player vector to store players
    std::vector<Player> players;

    // Texture
    Texture playerTexture;
    Texture bulletTexture;
    Texture gunTexture01;

public:
    Game(RenderWindow *window);
    virtual ~Game();

    // Accessors
    inline RenderWindow& getWindow() {return *this->window;};

    // Setters

    // Functions
    void Update();
    void Draw();

    // Text UI
    void UpdateUI();
    void DrawUI();
    void initUI();
};


#endif //HELLOSFML_GAME_H