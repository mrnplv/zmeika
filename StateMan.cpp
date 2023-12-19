//���������� �����������
#include "StateMan.h"

Engine::StateMan::StateMan() : m_add(false), m_replace(false) //������ ���������, ������� ������������� ������������� �������� ����������
{
}

Engine::StateMan::~StateMan() //����������
{
}

void Engine::StateMan::Add(std::unique_ptr<State> toAdd, bool replace) //���������� ������ ��������� m_stateStack, �� ��������� replace = False 
{
    m_add = true;  //��������� ����������� ���������� ������ ��������� - true
    m_newState = std::move(toAdd); //���������� � ���������� ������ ���������
    m_replace = replace; //��������� ����������� ������ �������� ��������� ����� = replace - �� ��������� False
}

void Engine::StateMan::ProcessStateChange() //����������/������ �������� ��������� � ����� m_stateStack
{
    if (m_add) //���� ��������� ����������� ���������� ������ ��������� - true
    {
        if (m_replace && (!m_stateStack.empty())) //���� ��������� ����������� ������ �������� ��������� ����� = true � ���� ��������� �� ����
        {
            m_stateStack.pop(); //������� ������� ������� �����
            m_replace = false; //��������� ����������� ������ �������� ��������� ���������� false
        }
        m_stateStack.push(std::move(m_newState)); //���������� ������ ��������� � ����
        m_stateStack.top()->Init(); //����������� �������� ������ ���������
        m_add = false; //��������� ����������� ���������� ������ ��������� ���������� false
    }
}
//��������� c#
//namespace Engine
//{
//    public class StateMan
//    {
//        public void ProcessStateChange()
//        {
//            if (m_add)
//            {
//                if (m_replace && (m_stateStack.Count > 0))
//                {
//                    m_stateStack.Pop();
//                    m_replace = false;
//                }
//                m_stateStack.Push(m_newState);
//                m_stateStack.Peek().Init();
//                m_add = false;
//            }
//        }
//    }
//}


std::unique_ptr<Engine::State>& Engine::StateMan::GetCurrent() //���������� ������� ���������
{
    return m_stateStack.top();
}
