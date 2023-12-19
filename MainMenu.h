#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "Game.h"
#include "State.h"

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameTitle;
    sf::Text m_gameText;

    bool m_isPlayButtonPressed;

public:
    MainMenu(std::shared_ptr<Context>& context);
    ~MainMenu();

    void ProcessInput() override;
    void Init() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};
