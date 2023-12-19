#include "GamePlay.h"
#include "GameOver.h"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>


GamePlay::GamePlay(std::shared_ptr<Context>& context) : m_context(context), //инициализация объекта Context для доступа к окну игры, текстурам и тд. при создании объекта
m_snakeDirection({ 40.f, 0.f }),
m_elapsedTime(sf::Time::Zero),
m_score(0) 
{
    srand(time(nullptr)); //генерация случайных чисел
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init() //создание окна игры
{
    m_context->m_assets->AddTexture(GRASS, "assets/texture/grass.png", true); //добавление текстуры травы с повторением
    m_context->m_assets->AddTexture(FOOD, "assets/texture/food.png"); //добавление текстуры еды
    m_context->m_assets->AddTexture(STONE, "assets/texture/stone.png", true); //добавление текстуры ограждений с повторением
    m_context->m_assets->AddTexture(SNAKE, "assets/texture/snake.png"); //добавление текстуры змейки

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS)); //присваивание спрайту травы текстуры по ссылке
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView())); //выбор части текстуры, которая будет отображена

    for (auto& stone : m_stone)
    {
        stone.setTexture(m_context->m_assets->GetTexture(STONE)); //присваивание спрайтам ограждения текстуры по ссылке
    }
    //настраиваем размеры ограждений
    m_stone[0].setTextureRect(sf::IntRect( 0, 0, m_context->m_window->getSize().x, 40 )); 
    m_stone[1].setTextureRect(sf::IntRect(0, 0, m_context->m_window->getSize().x, 40));
    m_stone[1].setPosition(0, m_context->m_window->getSize().y - 40);

    m_stone[2].setTextureRect(sf::IntRect( 0, 0, 40, m_context->m_window->getSize().y ));
    m_stone[3].setTextureRect(sf::IntRect( 0, 0, 40, m_context->m_window->getSize().y ));
    m_stone[3].setPosition(m_context->m_window->getSize().x - 40, 0);

    m_food.setTexture(m_context->m_assets->GetTexture(FOOD)); //присваивание спрайту еды текстуры по ссылке
    m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2); //настройка позиции еды

    m_snake.Init(m_context->m_assets->GetTexture(SNAKE)); //создание змейки
    
    //счетчик очков
    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT)); 
    m_scoreText.setString("SCORE: " + std::to_string(m_score)); 
    m_scoreText.setPosition(10, m_context->m_window->getSize().y - 50);
    m_scoreText.setCharacterSize(40);
}
void GamePlay::ProcessInput() //функция для обработки ввода пользователя и обновления состояния в соотв. с вводом
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) //пока есть незавершенные события
    {
        if (event.type == sf::Event::Closed) //если имеет место событие закрытия окна
        {
            m_context->m_window->close(); //закрыть
        }
        else if (event.type == sf::Event::KeyPressed) //если же нажата кнопка
        {
            sf::Vector2f newDirection = m_snakeDirection;
            //изменяем направление движения змейки
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                newDirection = { 0.f, -40.f };
                break;
            case sf::Keyboard::Down:
                newDirection = { 0.f, 40.f };
                break;
            case sf::Keyboard::Left:
                newDirection = { -40.f, 0.f };
                break;
            case sf::Keyboard::Right:
                newDirection = { 40.f, 0.f };
                break;
            default:
                break;
            }
            if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) ||
                std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
            {
                m_snakeDirection = newDirection;
            }
        }
    }
}
//адаптация c#
//namespace GamePlay
//{
 /*   void ProcessInput()
    {
        Event event;
        while (m_context.m_window.pollEvent(event))
        {
            if (event.type == Event.Closed)
            {
                m_context.m_window.close();
            }
            else if (event.type == Event.KeyPressed)
            {
                sf.Vector2f newDirection = m_snakeDirection;

                switch (event.key.code)
                {
                case Keyboard.Up:
                    newDirection = new Vector2f(0f, -40f);
                    break;
                case Keyboard.Down:
                    newDirection = new Vector2f(0f, 40f);
                    break;
                case Keyboard.Left:
                    newDirection = new Vector2f(-40f, 0f);
                    break;
                case Keyboard.Right:
                    newDirection = new Vector2f(40f, 0f);
                    break;
                default:
                    break;
                }
                if (Math.Abs(m_snakeDirection.x) != Math.Abs(newDirection.x) ||
                    Math.Abs(m_snakeDirection.y) != Math.Abs(newDirection.y))
                {
                    m_snakeDirection = newDirection;
                }
            }
        }
    }
  }*/


void GamePlay::Update(sf::Time deltaTime) //обновляет состояние с течением времени
{
        m_elapsedTime += deltaTime;
        if (m_elapsedTime.asSeconds() > 0.1) //если прошло > 0.1 секунды
        {
            for (auto& stone : m_stone)
            {
                if (m_snake.IsOn(stone)) //если змейка зашла на камень
                {
                    m_context->m_states->Add(std::make_unique<GameOver>(m_context), true); //добавление нового состояния GameOver в стек
                    break;
                }
            }

            if (m_snake.IsOn(m_food)) //если змейка попала на еду
            {
                m_snake.Grow(m_snakeDirection); //увеличиваем тело змейки
                int x = 0, y = 0;

                //генерируем новые координаты для еды
                x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 40, m_context->m_window->getSize().x - 2 * 40); 
                y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 40, m_context->m_window->getSize().y - 2 * 40);

                m_food.setPosition(x, y); //устанавливаем еду на новую позицию
                m_score += 1; //прибавляем очки
                m_scoreText.setString("SCORE: " + std::to_string(m_score)); //обновляем табло с баллами
            }
            else
            {
                m_snake.Move(m_snakeDirection); //иначе змейка двигается
            }
            if (m_snake.IsSelfIntersecting()) //если змейка зашла на саму себя
            {
                m_context->m_states->Add(std::make_unique<GameOver>(m_context), true); //добавление нового состояния GameOver в стек и замена состояния на GameOver
            }

            m_elapsedTime = sf::Time::Zero; //обнуляем таймер
        }
}

//адаптация c#
//namespace GamePlay
//{
//void Update(Time deltaTime)
//{
//    m_elapsedTime += deltaTime;
//    if (m_elapsedTime.TotalSeconds > 0.1)
//    {
//        foreach(var stone in m_stone)
//        {
//            if (m_snake.IsOn(stone))
//            {
//                m_context.m_states.Add(new GameOver(m_context), true);
//                break;
//            }
//        }
//        if (m_snake.IsOn(m_food))
//        {
//            m_snake.Grow(m_snakeDirection);
//            int x = 0, y = 0;
//            x = Math.Clamp(rand.Next() % m_context.m_window.Size.X, 40, m_context.m_window.Size.X - 2 * 40);
//            y = Math.Clamp(rand.Next() % m_context.m_window.Size.Y, 40, m_context.m_window.Size.Y - 2 * 40);
//            m_food.Position = new Vector2(x, y);
//            m_score += 1;
//            m_scoreText.String = "SCORE: " + m_score.ToString();
//        }
//        else
//        {
//            m_snake.Move(m_snakeDirection);
//        }
//        if (m_snake.IsSelfIntersecting())
//        {
//            m_context.m_states.Add(new GameOver(m_context), true);
//        }
//        m_elapsedTime = TimeSpan.Zero;
//    }
// }
//}


void GamePlay::Draw() //передача состояния на экран
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass); //отрисовка травы

    for (auto& stone : m_stone)
    {
        m_context->m_window->draw(stone); //отрисовка ограды
    }
    m_context->m_window->draw(m_food); //отрисовка еды
    m_context->m_window->draw(m_snake); //отрисовка змейки
    m_context->m_window->draw(m_scoreText); //отрисовка счета баллов

    m_context->m_window->display(); //отображение всего на экране
}
