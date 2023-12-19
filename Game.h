#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetMan.h"
#include "StateMan.h"

enum AssetId //������������ id ������� � �������
{
    MAIN_FONT = 0, 
    GRASS,
    FOOD, 
    STONE,
    SNAKE 
};

struct Context //��������� ��� �������� ���������� �� ���������� ������� ������� AssetMan, StateMan � sf::RenderWindow (��� ��������� �������� ����)
{
    std::unique_ptr<Engine::AssetMan> m_assets; //���������� ��������� �� ������ ������ AssetMan
    std::unique_ptr<Engine::StateMan> m_states; //���������� ��������� �� ������ ������ StateMan
    std::unique_ptr<sf::RenderWindow> m_window; //���������� ��������� �� ������ ������ RenderWindow

    Context() //�����������
    {
        m_assets = std::make_unique<Engine::AssetMan>(); //�������� �������, �� ������� ����� ��������� ���������� ���������
        m_states = std::make_unique<Engine::StateMan>();
        m_window = std::make_unique<sf::RenderWindow>();
    }
};

class Game 
{
private:
    std::shared_ptr<Context> m_context; //��������� �� ������ ��������� Context
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f); //���� �������� � �������� 60 ������ � �������

public:
    Game();
    ~Game();

    void Run(); //�������, ������� ����������� ������������ ����, ��������� � ������ ������� ��������� ���� � ������������ � ��������
};
