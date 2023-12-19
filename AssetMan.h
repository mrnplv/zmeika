#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Engine
{
    class AssetMan
    {
    private:
        std::map<int, std::unique_ptr<sf::Texture>> m_textures; //контейнер map для текстур (каждое значение ассоциировано с определенным ключом)
        std::map<int, std::unique_ptr<sf::Font>> m_fonts;  //контейнер map для шрифтов

    public:
        AssetMan();
        ~AssetMan();

        void AddTexture(int id, const std::string& filePath, bool wantRepeated = false); //создание нового объекта текстуры и загрузка изображения по пути файла
        void AddFont(int id, const std::string& filePath); //создание нового объекта шрифта и загрузка по пути файла

        const sf::Texture& GetTexture(int id) const; //получение постоянной ссылки на текстуру, хранящуюся в контейнере, по id
        const sf::Font& GetFont(int id) const; //получение постоянной ссылки на шрифт, хранящийся в контейнере, по id
    };

} 
