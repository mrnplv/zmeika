//управление текстурами и шрифтами
#include "AssetMan.h"

Engine::AssetMan::AssetMan() 
{
}

Engine::AssetMan::~AssetMan() 
{
}

void Engine::AssetMan::AddTexture(int id, const std::string& filePath, bool wantRepeated) //создание нового объекта текстуры и загрузка изображения по пути файла, wantRepeated по умолчанию false
{
    auto texture = std::make_unique<sf::Texture>(); //указатель, который ссылается на объект текстуры
    if (texture->loadFromFile(filePath)) //если текстура успешно загрузилась из файла
    {
        texture->setRepeated(wantRepeated); //разрешить повторение текстуры вне ее прямоугольника, если wantRepeated = true (по умолчанию false)
        m_textures[id] = std::move(texture); //добавление текстуры в контейнер в связке с id
    }
}
void Engine::AssetMan::AddFont(int id, const std::string& filePath) //создание нового объекта шрифта и загрузка по пути файла
{
    auto font = std::make_unique<sf::Font>(); // указатель, который ссылается на объект шрифта

    if (font->loadFromFile(filePath)) //если шрифт успешно загрузился из файла
    {
        m_fonts[id] = std::move(font); //добавление шрифта в контейнер в связке с id
    }
}
const sf::Texture& Engine::AssetMan::GetTexture(int id) const //получение постоянной ссылки на текстуру, хранящуюся в контейнере, по id
{
    return *(m_textures.at(id).get());
}
const sf::Font& Engine::AssetMan::GetFont(int id) const //получение постоянной ссылки на шрифт, хранящийся в контейнере, по id
{
    return *(m_fonts.at(id).get());
}
