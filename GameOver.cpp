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
void GameOver::ProcessInput() //ôóíêöèÿ äëÿ îáðàáîòêè ââîäà ïîëüçîâàòåëÿ è îáíîâëåíèÿ ñîñòîÿíèÿ â ñîîòâ. ñ ââîäîì
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) //ïîêà åñòü íåçàâåðøåííûå ñîáûòèÿ
    {
        if (event.type == sf::Event::Closed) //åñëè èìååò ìåñòî ñîáûòèå çàêðûòèÿ îêíà
        {
            m_context->m_window->close(); //çàêðûòü îêíî
        }
        else if (event.type == sf::Event::KeyPressed) //åñëè æå íàæàòà êíîïêà
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up: //íàæàòà êíîïêà ââåðõ
            {
                if (!m_isRetryButtonSelected) //åñëè êíîïêà Retry íå áûëà âûáðàíà
                {
                    m_isRetryButtonSelected = true; //òî ñòàíîâèòñÿ âûáðàííîé
                    m_isExitButtonSelected = false; //à Exit - íåâûáðàííîé
                }
                break;
            }
            case sf::Keyboard::Down: //íàæàòà êíîïêà âíèç
            {
                if (!m_isExitButtonSelected) //åñëè êíîïêà Exit íå áûëà âûáðàíà
                {
                    m_isRetryButtonSelected = false; //êíîïêà Retry ñòàíîâèòñÿ íåâûáðàííîé
                    m_isExitButtonSelected = true; //à Exit - âûáðàííîé
                }
                break;
            }
            case sf::Keyboard::Return: //íàæàò Enter
            {
                m_isExitButtonPressed = false;
                m_isRetryButtonPressed = false;
                if (m_isExitButtonSelected) //åñëè âûáðàí Exit
                {
                    m_isExitButtonPressed = true; //êíîïêà Exit ñòàíîâèòñÿ íàæàòîé
                }
                else
                {
                    m_isRetryButtonPressed = true; //èíà÷å êíîïêà Retry ñòàíîâèòñÿ íàæàòîé
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
void GameOver::Init() //ñîçäàíèå îêíà îêîí÷àíèÿ èãðû
{
    setlocale(LC_ALL, "");
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString(L"Âû ïðîèãðàëè...!");
    m_gameOverTitle.setCharacterSize(80);
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, m_gameOverTitle.getLocalBounds().height / 2);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 100.f);

    
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_retryButton.setString(L"Ïðîäîëæèòü èãðó");
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2 + 60.f, m_retryButton.getLocalBounds().height / 2);
    m_retryButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 10.f);
    m_retryButton.setCharacterSize(50);

    
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString(L"Âûõîä");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2 + 25.f, m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 60.f);
    m_exitButton.setCharacterSize(50);
}
void GameOver::Update(sf::Time deltaTime) //îáíîâëåíèå öâåòà è êîíòåêñòà â çàâèñèìîñòè îò âûáðàííîé êíîïêè
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

    if (m_isRetryButtonPressed) //åñëè íàæàòà Retry
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true); //äîáàâëåíèå íîâîãî ñîñòîÿíèÿ â ñòåê êîíòåêñòà
    }
    else if (m_isExitButtonPressed) //çàêðûòèå îêíà ïðè íàæàòèè Exit
    {
        m_context->m_window->close();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_gameOverTitle); //ðèñóåì çàãîëîâîê
    m_context->m_window->draw(m_retryButton); //ðèñóåì êíîïêó Retry
    m_context->m_window->draw(m_exitButton); //ðèñóåì êíîïêó Exit
    m_context->m_window->display(); //îòîáðàæåíèå âñåãî íà ýêðàíå
}
