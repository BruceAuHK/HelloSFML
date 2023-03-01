//
// Created by Bruce au on 6/7/2022.
//

#include "Game.h"

Game::Game(RenderWindow *window) {
    // local window pointer always in Game
    this->window = window;

    // Frame Rate Limit
    this->window->setFramerateLimit(60);

    // Init fonts
    this->font.loadFromFile("/Users/bruceau/CLionProjects/HelloSFML/Textures/Font/Dosis-VariableFont_wght.ttf");

    // Init textures
    this->playerTexture.loadFromFile("/Users/bruceau/CLionProjects/HelloSFML/Textures/ship.png");
    this->bulletTexture.loadFromFile(("/Users/bruceau/CLionProjects/HelloSFML/Textures/Guns/missileTex01.png"));
    this->gunTexture01.loadFromFile("/Users/bruceau/CLionProjects/HelloSFML/Textures/Guns/gun01.png");

    // Init player 1
    this->players.push_back(Player(&playerTexture, &bulletTexture, &gunTexture01));

    // Init player 2 with I,K,J,L,RShift
    this->players.push_back(Player(&playerTexture, &bulletTexture, &gunTexture01,
                                   Keyboard::I, Keyboard::K, Keyboard::J,
                                   Keyboard::L, Keyboard::RShift));

    // Init UI
    this->initUI();

}

Game::~Game() {
}

void Game::Update() {
    for(auto & player : players){
        // Update Players
        player.Update(this->window->getSize());

        //Bullets update
        // Window bounds check
        for (auto it = player.getBullets().begin(); it != player.getBullets().end();) {
            if( it->getPosition().x > (this->window->getSize().x))
                player.getBullets().erase(it);
            break;
        }
    }

    // Update UI
    this->UpdateUI();
}

void Game::DrawUI(){

    for (int i = 0; i < this->followPlayerText.size(); i++) {
        this->window->draw(this->followPlayerText[i]);
    }
    for (int i = 0; i < this->staticPlayerText.size(); i++) {
        this->window->draw(this->staticPlayerText[i]);
    }

}

void Game::Draw() {
    this->window->clear();
    for(auto & player : this->players)
        player.Draw(*this->window);
    this->DrawUI();
    this->window->display();
}



void Game::UpdateUI() {

    for (int i = 0; i < this->followPlayerText.size(); i++) {
        this->followPlayerText[i].setPosition(this->players[i].getPosition());
        this->followPlayerText[i].setString(std::to_string(i) + " | " + this->players[i].getHpAsString() ) ;
    }

    for (int i = 0; i < this->staticPlayerText.size(); i++) {
        this->staticPlayerText[i].setPosition(this->players[i].getPosition());
        this->staticPlayerText[i].setString(std::to_string(i) + " | " + this->players[i].getHpAsString() ) ;
    }
}

void Game::initUI() {
    int i = 0;
    for(auto player: this->players){

        // Follow text init
        Text tempText;
        tempText.setCharacterSize(120);
        tempText.setOutlineColor(Color::White);
        tempText.setFillColor(Color::White);
        tempText.setString(std::to_string(i++));

        this->followPlayerText.push_back(Text(tempText));

        // Static text init
        tempText.setString("");
        this->staticPlayerText.push_back(Text(tempText));

    }
}