#include "AssetMan.h"

Engine::AssetMan::AssetMan() 
{
}

Engine::AssetMan::~AssetMan() 
{
}

void Engine::AssetMan::AddTexture(int id, const std::string& filePath, bool wantRepeated) //ñîçäàíèå íîâîãî îáúåêòà òåêñòóðû è çàãðóçêà èçîáðàæåíèÿ ïî ïóòè ôàéëà, wantRepeated ïî óìîë÷àíèþ false
{
    auto texture = std::make_unique<sf::Texture>(); //óêàçàòåëü, êîòîðûé ññûëàåòñÿ íà îáúåêò òåêñòóðû
    if (texture->loadFromFile(filePath)) //åñëè òåêñòóðà óñïåøíî çàãðóçèëàñü èç ôàéëà
    {
        texture->setRepeated(wantRepeated); //ðàçðåøèòü ïîâòîðåíèå òåêñòóðû âíå åå ïðÿìîóãîëüíèêà, åñëè wantRepeated = true (ïî óìîë÷àíèþ false)
        m_textures[id] = std::move(texture); //äîáàâëåíèå òåêñòóðû â êîíòåéíåð â ñâÿçêå ñ id
    }
}
void Engine::AssetMan::AddFont(int id, const std::string& filePath) //ñîçäàíèå íîâîãî îáúåêòà øðèôòà è çàãðóçêà ïî ïóòè ôàéëà
{
    auto font = std::make_unique<sf::Font>(); // óêàçàòåëü, êîòîðûé ññûëàåòñÿ íà îáúåêò øðèôòà

    if (font->loadFromFile(filePath)) //åñëè øðèôò óñïåøíî çàãðóçèëñÿ èç ôàéëà
    {
        m_fonts[id] = std::move(font); //äîáàâëåíèå øðèôòà â êîíòåéíåð â ñâÿçêå ñ id
    }
}
const sf::Texture& Engine::AssetMan::GetTexture(int id) const //ïîëó÷åíèå ïîñòîÿííîé ññûëêè íà òåêñòóðó, õðàíÿùóþñÿ â êîíòåéíåðå, ïî id
{
    return *(m_textures.at(id).get());
}
const sf::Font& Engine::AssetMan::GetFont(int id) const //ïîëó÷åíèå ïîñòîÿííîé ññûëêè íà øðèôò, õðàíÿùèéñÿ â êîíòåéíåðå, ïî id
{
    return *(m_fonts.at(id).get());
}
