#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetMan.h"
#include "StateMan.h"

enum AssetId //перечисление id текстур и шрифтов
{
    MAIN_FONT = 0, 
    GRASS,
    FOOD, 
    STONE,
    SNAKE 
};

struct Context //структура для хранения указателей на уникальные образцы классов AssetMan, StateMan и sf::RenderWindow (для отрисовки игрового окна)
{
    std::unique_ptr<Engine::AssetMan> m_assets; //уникальный указатель на объект класса AssetMan
    std::unique_ptr<Engine::StateMan> m_states; //уникальный указатель на объект класса StateMan
    std::unique_ptr<sf::RenderWindow> m_window; //уникальный указатель на объект класса RenderWindow

    Context() //конструктор
    {
        m_assets = std::make_unique<Engine::AssetMan>(); //создание объекта, на который будет указывать уникальный указатель
        m_states = std::make_unique<Engine::StateMan>();
        m_window = std::make_unique<sf::RenderWindow>();
    }
};

class Game 
{
private:
    std::shared_ptr<Context> m_context; //указатель на объект структуры Context
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f); //игра работает с частотой 60 кадров в секунду

public:
    Game();
    ~Game();

    void Run(); //функция, которая беспрерывно обрабатывает ввод, обновляет и рисует текущее состояние игры в соответствии с таймером
};
