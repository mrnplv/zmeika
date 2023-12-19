#include <locale>
#include "MainMenu.h"
#include "GamePlay.h"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context>& context)
    : m_context(context), m_isPlayButtonPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::ProcessInput() //������� ��� ��������� ����� ������������ � ���������� ��������� � �����. � ������
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) //���� ���� ������������� �������
    {
        if (event.type == sf::Event::Closed) //�������� ����
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) //������ ������ Enter
        {
            m_isPlayButtonPressed = true; //����� ������ Play ������
              
        }
    }
}
void MainMenu::Init() //�������� ���� ����
{
    setlocale(LC_ALL, "");
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/bitcell_memesbruh03.ttf");   
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString(L"����");
    m_gameTitle.setCharacterSize(100);
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 100.f);

    m_gameText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameText.setString(L"������� ������ Enter, ����� ������ ���� :)");
    m_gameText.setOrigin(m_gameTitle.getLocalBounds().width / 2 + 220.f, m_gameTitle.getLocalBounds().height / 2);
    m_gameText.setPosition(m_context->m_window->getSize().x / 2 - 40.f, m_context->m_window->getSize().y / 2 + 80.f);
    m_gameText.setCharacterSize(50);
    m_gameText.setFillColor(sf::Color::Magenta);
}
void MainMenu::Update(sf::Time deltaTime) //���������� ���������
{
    if (m_isPlayButtonPressed) //���� ����� Enter
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true); //���������� ������ ��������� GamePlay � ���� 
    }
}

void MainMenu::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_gameTitle); //������ ���������
    m_context->m_window->draw(m_gameText); //������ �����
    m_context->m_window->display(); //����������� ����� �� ������
}
