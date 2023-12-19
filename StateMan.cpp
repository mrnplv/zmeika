//управление состояниями
#include "StateMan.h"

Engine::StateMan::StateMan() : m_add(false), m_replace(false) //объект создается, списком инициализации присваиваются занчения переменным
{
}

Engine::StateMan::~StateMan() //деструктор
{
}

void Engine::StateMan::Add(std::unique_ptr<State> toAdd, bool replace) //добавление нового состояния m_stateStack, по умолчанию replace = False 
{
    m_add = true;  //индикатор потребности добавления нового состояния - true
    m_newState = std::move(toAdd); //добавление в переменную нового состояния
    m_replace = replace; //индикатор потребности замены текущего состояния новым = replace - по умолчанию False
}

void Engine::StateMan::ProcessStateChange() //добавление/замена текущего состояния в стеке m_stateStack
{
    if (m_add) //если индикатор потребности добавления нового состояния - true
    {
        if (m_replace && (!m_stateStack.empty())) //если индикатор потребности замены текущего состояния новым = true и стек состояний не пуст
        {
            m_stateStack.pop(); //удаляем верхний элемент стека
            m_replace = false; //индикатор потребности замены текущего состояния становится false
        }
        m_stateStack.push(std::move(m_newState)); //добавление нового состояния в стек
        m_stateStack.top()->Init(); //инициализая ресурсов нового состояния
        m_add = false; //индикатор потребности добавления нового состояния становится false
    }
}
//адаптация c#
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


std::unique_ptr<Engine::State>& Engine::StateMan::GetCurrent() //возвращает текущее состояние
{
    return m_stateStack.top();
}
