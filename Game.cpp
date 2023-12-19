#include "Game.h"
#include "MainMenu.h"

#include <SFML/Graphics/CircleShape.hpp>

Game::Game() : m_context(std::make_shared<Context>()) //инициализация указателя на объект структуры Context при создании объекта
{
    m_context->m_window->create(sf::VideoMode(1300, 704), "Classic Snake", sf::Style::Close); //создание начального окна заданных размеров с кнопкой закрытия
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context)); //добавление нового состояния MainMenu в стек 
}

Game::~Game()
{
}

void Game::Run() //функция, которая беспрерывно обрабатывает ввод, обновляет и рисует текущее состояние игры в соответствии с таймером
{
    sf::Clock clock;
    sf::Time timeSinceeLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        timeSinceeLastFrame += clock.restart();

        while (timeSinceeLastFrame > TIME_PER_FRAME)
        {
            timeSinceeLastFrame -= TIME_PER_FRAME;

            m_context->m_states->ProcessStateChange();
            m_context->m_states->GetCurrent()->ProcessInput();
            m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
            m_context->m_states->GetCurrent()->Draw();
        }
    }
}

//адаптация c#
//namespace Game{
//public void Run()
//{
//    Clock clock = new Clock();
//    Time timeSinceLastFrame = Time.Zero;
//    while (m_context.m_window.IsOpen)
//    {
//        timeSinceLastFrame += clock.Restart();
//        while (timeSinceLastFrame > TIME_PER_FRAME)
//        {
//            timeSinceLastFrame -= TIME_PER_FRAME;
//            m_context.m_states.ProcessStateChange();
//            m_context.m_states.GetCurrent().ProcessInput();
//            m_context.m_states.GetCurrent().Update(TIME_PER_FRAME);
//            m_context.m_states.GetCurrent().Draw();
//        }
//    }
// }
//}

