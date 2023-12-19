//���������� ���������� � ��������
#include "AssetMan.h"

Engine::AssetMan::AssetMan() 
{
}

Engine::AssetMan::~AssetMan() 
{
}

void Engine::AssetMan::AddTexture(int id, const std::string& filePath, bool wantRepeated) //�������� ������ ������� �������� � �������� ����������� �� ���� �����, wantRepeated �� ��������� false
{
    auto texture = std::make_unique<sf::Texture>(); //���������, ������� ��������� �� ������ ��������
    if (texture->loadFromFile(filePath)) //���� �������� ������� ����������� �� �����
    {
        texture->setRepeated(wantRepeated); //��������� ���������� �������� ��� �� ��������������, ���� wantRepeated = true (�� ��������� false)
        m_textures[id] = std::move(texture); //���������� �������� � ��������� � ������ � id
    }
}
void Engine::AssetMan::AddFont(int id, const std::string& filePath) //�������� ������ ������� ������ � �������� �� ���� �����
{
    auto font = std::make_unique<sf::Font>(); // ���������, ������� ��������� �� ������ ������

    if (font->loadFromFile(filePath)) //���� ����� ������� ���������� �� �����
    {
        m_fonts[id] = std::move(font); //���������� ������ � ��������� � ������ � id
    }
}
const sf::Texture& Engine::AssetMan::GetTexture(int id) const //��������� ���������� ������ �� ��������, ���������� � ����������, �� id
{
    return *(m_textures.at(id).get());
}
const sf::Font& Engine::AssetMan::GetFont(int id) const //��������� ���������� ������ �� �����, ���������� � ����������, �� id
{
    return *(m_fonts.at(id).get());
}
