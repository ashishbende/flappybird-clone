﻿#include<iostream>
#include<sstream>
#include "definitions.h"
#include "gamestate.h"
#include "gameoverstate.h"

namespace Game {
GameState::GameState(GameDataRef data)
    : _data(data) {}

void GameState::Init()
{
    _data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
    _data->assets.LoadTexture("Pipe Up", PIPE_UP_BACKGROUND_FILEPATH);
    _data->assets.LoadTexture("Pipe Down", PIPE_DOWN_BACKGROUND_FILEPATH);
    _data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
    _data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
    _data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
    _data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);



    _data->assets.LoadTexture("Land", LAND_FILEPATH);

    pipe = new Pipe(_data);
    land = new Land(_data);
    bird = new Bird(_data);

    _background.setTexture(this->_data->assets.GetTexture("Game Background"));
    // _background.setTexture(this->_data->assets.GetTexture("Pipe Up Background"));
    //_background.setTexture(this->_data->assets.GetTexture("Pipe Down Background"));
}

void GameState::HandleInput()
{
    sf::Event event;
    while (_data->window.pollEvent(event))
    {

        if (sf::Event::Closed == event.type)
        {
            _data->window.close();
            //_data->machine.AddState(StateRef(new GameOverState(_data)),true);
        }

        if (_data->input.IsSpriteClicked(_background, sf::Mouse::Left, _data->window))
        {
            bird->Tap();
        }
    }
}

void GameState::Update(float dt)
{
    pipe ->MovePipes(dt);
    land ->MoveLand(dt);
    if (_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
    {
        pipe->RandomisePipeOffset();
        pipe->SpawnInvisiblePipe();
        pipe->SpawnBottomPipe();
        pipe->SpawnTopPipe();
        _clock.restart();
    }
    bird->Animate(dt);
    bird->Update(dt);
}

void GameState::Draw(float dt)
{
    _data->window.clear();
    _data->window.draw(_background);
    pipe->DrawPipes();
    land->DrawLand();
    bird->Draw();
    _data->window.display();
}
}

