#include "GamePlay.h"
#include "GameOver.h"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>


GamePlay::GamePlay(std::shared_ptr<Context>& context) : m_context(context), //������������� ������� Context ��� ������� � ���� ����, ��������� � ��. ��� �������� �������
m_snakeDirection({ 40.f, 0.f }),
m_elapsedTime(sf::Time::Zero),
m_score(0) 
{
    srand(time(nullptr)); //��������� ��������� �����
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init() //�������� ���� ����
{
    m_context->m_assets->AddTexture(GRASS, "assets/texture/grass.png", true); //���������� �������� ����� � �����������
    m_context->m_assets->AddTexture(FOOD, "assets/texture/food.png"); //���������� �������� ���
    m_context->m_assets->AddTexture(STONE, "assets/texture/stone.png", true); //���������� �������� ���������� � �����������
    m_context->m_assets->AddTexture(SNAKE, "assets/texture/snake.png"); //���������� �������� ������

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS)); //������������ ������� ����� �������� �� ������
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView())); //����� ����� ��������, ������� ����� ����������

    for (auto& stone : m_stone)
    {
        stone.setTexture(m_context->m_assets->GetTexture(STONE)); //������������ �������� ���������� �������� �� ������
    }
    //����������� ������� ����������
    m_stone[0].setTextureRect(sf::IntRect( 0, 0, m_context->m_window->getSize().x, 40 )); 
    m_stone[1].setTextureRect(sf::IntRect(0, 0, m_context->m_window->getSize().x, 40));
    m_stone[1].setPosition(0, m_context->m_window->getSize().y - 40);

    m_stone[2].setTextureRect(sf::IntRect( 0, 0, 40, m_context->m_window->getSize().y ));
    m_stone[3].setTextureRect(sf::IntRect( 0, 0, 40, m_context->m_window->getSize().y ));
    m_stone[3].setPosition(m_context->m_window->getSize().x - 40, 0);

    m_food.setTexture(m_context->m_assets->GetTexture(FOOD)); //������������ ������� ��� �������� �� ������
    m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2); //��������� ������� ���

    m_snake.Init(m_context->m_assets->GetTexture(SNAKE)); //�������� ������
    
    //������� �����
    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT)); 
    m_scoreText.setString("SCORE: " + std::to_string(m_score)); 
    m_scoreText.setPosition(10, m_context->m_window->getSize().y - 50);
    m_scoreText.setCharacterSize(40);
}
void GamePlay::ProcessInput() //������� ��� ��������� ����� ������������ � ���������� ��������� � �����. � ������
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) //���� ���� ������������� �������
    {
        if (event.type == sf::Event::Closed) //���� ����� ����� ������� �������� ����
        {
            m_context->m_window->close(); //�������
        }
        else if (event.type == sf::Event::KeyPressed) //���� �� ������ ������
        {
            sf::Vector2f newDirection = m_snakeDirection;
            //�������� ����������� �������� ������
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
//��������� c#
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


void GamePlay::Update(sf::Time deltaTime) //��������� ��������� � �������� �������
{
        m_elapsedTime += deltaTime;
        if (m_elapsedTime.asSeconds() > 0.1) //���� ������ > 0.1 �������
        {
            for (auto& stone : m_stone)
            {
                if (m_snake.IsOn(stone)) //���� ������ ����� �� ������
                {
                    m_context->m_states->Add(std::make_unique<GameOver>(m_context), true); //���������� ������ ��������� GameOver � ����
                    break;
                }
            }

            if (m_snake.IsOn(m_food)) //���� ������ ������ �� ���
            {
                m_snake.Grow(m_snakeDirection); //����������� ���� ������
                int x = 0, y = 0;

                //���������� ����� ���������� ��� ���
                x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 40, m_context->m_window->getSize().x - 2 * 40); 
                y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 40, m_context->m_window->getSize().y - 2 * 40);

                m_food.setPosition(x, y); //������������� ��� �� ����� �������
                m_score += 1; //���������� ����
                m_scoreText.setString("SCORE: " + std::to_string(m_score)); //��������� ����� � �������
            }
            else
            {
                m_snake.Move(m_snakeDirection); //����� ������ ���������
            }
            if (m_snake.IsSelfIntersecting()) //���� ������ ����� �� ���� ����
            {
                m_context->m_states->Add(std::make_unique<GameOver>(m_context), true); //���������� ������ ��������� GameOver � ���� � ������ ��������� �� GameOver
            }

            m_elapsedTime = sf::Time::Zero; //�������� ������
        }
}

//��������� c#
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


void GamePlay::Draw() //�������� ��������� �� �����
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass); //��������� �����

    for (auto& stone : m_stone)
    {
        m_context->m_window->draw(stone); //��������� ������
    }
    m_context->m_window->draw(m_food); //��������� ���
    m_context->m_window->draw(m_snake); //��������� ������
    m_context->m_window->draw(m_scoreText); //��������� ����� ������

    m_context->m_window->display(); //����������� ����� �� ������
}
