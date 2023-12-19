#include "Snake.h"

Snake::Snake() : m_body(std::list<sf::Sprite>(4)) //создается контейнер для тела с 4 элементами
{
    m_head = --m_body.end(); //итератор указывает на последний элемент контейнера (голова)
    m_tail = m_body.begin(); //итератор указывает на первый элемент контейнера (хвост)
}

Snake::~Snake()
{
}

void Snake::Init(const sf::Texture& texture) //задаются текстуры и начальные позиции спрайтов
{
    float x = 40.f;
    for (auto& piece : m_body)
    {
        piece.setTexture(texture); //устанавливается текстура для спрайта
        piece.setPosition({ x, 40.f }); //устанавливается позиция спрайта
        x += 40.f; //увеличение х для установки позиции след. спрайта
    }
}

void Snake::Move(const sf::Vector2f& direction)  //движение змейки
{
    m_tail->setPosition(m_head->getPosition() + direction); 
    m_head = m_tail;
    ++m_tail;

    if (m_tail == m_body.end())
    {
        m_tail = m_body.begin();
    }
}

bool Snake::IsOn(const sf::Sprite& other) const //контроль захода головы змейки на другой спрайт (возвращает true, если зашла)
{
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}
void Snake::Grow(const sf::Vector2f& direction) //добавление нового кусочка к телу змейки в заданном направлении
{
    sf::Sprite newPiece;
    newPiece.setTexture(*(m_body.begin()->getTexture())); //задаем текстуру нового кусочка
    newPiece.setPosition(m_head->getPosition() + direction); //задаем позицию

    m_head = m_body.insert(++m_head, newPiece); //добавляем кусочек в контейнер
}
bool Snake::IsSelfIntersecting() const //контроль захода змейки на саму себя (возвращает true, если зашла)
{
    bool flag = false;
    for (auto piece = m_body.begin(); piece != m_body.end(); ++piece)
    {
        if (m_head != piece)
        {
            flag = IsOn(*piece);
            if (flag)
            {
                break;
            }
        }
    }
    return flag;
}
void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const //отрисовка спрайтов контейнера
{
    for (auto& piece : m_body)
    {
        target.draw(piece);
    }
}
