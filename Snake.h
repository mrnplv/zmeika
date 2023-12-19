#pragma once

#include <list>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
private:
    std::list<sf::Sprite> m_body; //контейнер со спрайтами для тела змейки
    std::list<sf::Sprite>::iterator m_head; //итератор для обращения к голове
    std::list<sf::Sprite>::iterator m_tail; //итератор для обращения к хвосту

public:
    Snake();
    ~Snake();

    void Init(const sf::Texture& texture); //задаются текстуры и начальные позиции спрайтов
    void Move(const sf::Vector2f& direction); //движение змейки
    bool IsOn(const sf::Sprite& other) const; //контроль захода головы змейки на другой спрайт (возвращает true, если зашла)
    void Grow(const sf::Vector2f& direction); //добавление нового кусочка к телу змейки в заданном направлении
    bool IsSelfIntersecting() const; //контроль захода змейки на саму себя (возвращает true, если зашла)

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //отрисовка спрайтов контенера
};
