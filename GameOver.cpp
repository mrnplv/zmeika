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
void GameOver::ProcessInput() //������� ��� ��������� ����� ������������ � ���������� ��������� � �����. � ������
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) //���� ���� ������������� �������
    {
        if (event.type == sf::Event::Closed) //���� ����� ����� ������� �������� ����
        {
            m_context->m_window->close(); //������� ����
        }
        else if (event.type == sf::Event::KeyPressed) //���� �� ������ ������
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up: //������ ������ �����
            {
                if (!m_isRetryButtonSelected) //���� ������ Retry �� ���� �������
                {
                    m_isRetryButtonSelected = true; //�� ���������� ���������
                    m_isExitButtonSelected = false; //� Exit - �����������
                }
                break;
            }
            case sf::Keyboard::Down: //������ ������ ����
            {
                if (!m_isExitButtonSelected) //���� ������ Exit �� ���� �������
                {
                    m_isRetryButtonSelected = false; //������ Retry ���������� �����������
                    m_isExitButtonSelected = true; //� Exit - ���������
                }
                break;
            }
            case sf::Keyboard::Return: //����� Enter
            {
                m_isExitButtonPressed = false;
                m_isRetryButtonPressed = false;
                if (m_isExitButtonSelected) //���� ������ Exit
                {
                    m_isExitButtonPressed = true; //������ Exit ���������� �������
                }
                else
                {
                    m_isRetryButtonPressed = true; //����� ������ Retry ���������� �������
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
void GameOver::Init() //�������� ���� ��������� ����
{
    setlocale(LC_ALL, "");
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString(L"�� ���������...!");
    m_gameOverTitle.setCharacterSize(80);
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, m_gameOverTitle.getLocalBounds().height / 2);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 100.f);

    
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_retryButton.setString(L"���������� ����");
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2 + 60.f, m_retryButton.getLocalBounds().height / 2);
    m_retryButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 10.f);
    m_retryButton.setCharacterSize(50);

    
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString(L"�����");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2 + 25.f, m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 60.f);
    m_exitButton.setCharacterSize(50);
}
void GameOver::Update(sf::Time deltaTime) //���������� ����� � ��������� � ����������� �� ��������� ������
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

    if (m_isRetryButtonPressed) //���� ������ Retry
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true); //���������� ������ ��������� � ���� ���������
    }
    else if (m_isExitButtonPressed) //�������� ���� ��� ������� Exit
    {
        m_context->m_window->close();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_gameOverTitle); //������ ���������
    m_context->m_window->draw(m_retryButton); //������ ������ Retry
    m_context->m_window->draw(m_exitButton); //������ ������ Exit
    m_context->m_window->display(); //����������� ����� �� ������
}