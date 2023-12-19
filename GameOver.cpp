#include <locale>
#include "GameOver.h"
#include "GamePlay.h"

#include <SFML/Window/Event.hpp>


GameOver::GameOver(std::shared_ptr<Context>& context)
    : m_context(context), m_isRetryButtonSelected(true),
    m_isRetryButtonPressed(false), m_isExitButtonSelected(false),
    m_isExitButtonPressed(false)
{
}

GameOver::~GameOver()
{
}
void GameOver::ProcessInput() //функция для обработки ввода пользователя и обновления состояния в соотв. с вводом
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) //пока есть незавершенные события
    {
        if (event.type == sf::Event::Closed) //если имеет место событие закрытия окна
        {
            m_context->m_window->close(); //закрыть окно
        }
        else if (event.type == sf::Event::KeyPressed) //если же нажата кнопка
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up: //нажата кнопка вверх
            {
                if (!m_isRetryButtonSelected) //если кнопка Retry не была выбрана
                {
                    m_isRetryButtonSelected = true; //то становится выбранной
                    m_isExitButtonSelected = false; //а Exit - невыбранной
                }
                break;
            }
            case sf::Keyboard::Down: //нажата кнопка вниз
            {
                if (!m_isExitButtonSelected) //если кнопка Exit не была выбрана
                {
                    m_isRetryButtonSelected = false; //кнопка Retry становится невыбранной
                    m_isExitButtonSelected = true; //а Exit - выбранной
                }
                break;
            }
            case sf::Keyboard::Return: //нажат Enter
            {
                m_isExitButtonPressed = false;
                m_isRetryButtonPressed = false;
                if (m_isExitButtonSelected) //если выбран Exit
                {
                    m_isExitButtonPressed = true; //кнопка Exit становится нажатой
                }
                else
                {
                    m_isRetryButtonPressed = true; //иначе кнопка Retry становится нажатой
                }
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}
void GameOver::Init() //создание окна окончания игры
{
    setlocale(LC_ALL, "");
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString(L"Вы проиграли...!");
    m_gameOverTitle.setCharacterSize(80);
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, m_gameOverTitle.getLocalBounds().height / 2);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 100.f);

    
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_retryButton.setString(L"Продолжить игру");
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2 + 60.f, m_retryButton.getLocalBounds().height / 2);
    m_retryButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 10.f);
    m_retryButton.setCharacterSize(50);

    
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString(L"Выход");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2 + 25.f, m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 60.f);
    m_exitButton.setCharacterSize(50);
}
void GameOver::Update(sf::Time deltaTime) //обновление цвета и контекста в зависимости от выбранной кнопки
{
    if (m_isRetryButtonSelected)
    {
        m_retryButton.setFillColor(sf::Color::Magenta);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else
    {
        m_exitButton.setFillColor(sf::Color::Magenta);
        m_retryButton.setFillColor(sf::Color::White);
    }

    if (m_isRetryButtonPressed) //если нажата Retry
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true); //добавление нового состояния в стек контекста
    }
    else if (m_isExitButtonPressed) //закрытие окна при нажатии Exit
    {
        m_context->m_window->close();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_gameOverTitle); //рисуем заголовок
    m_context->m_window->draw(m_retryButton); //рисуем кнопку Retry
    m_context->m_window->draw(m_exitButton); //рисуем кнопку Exit
    m_context->m_window->display(); //отображение всего на экране
}