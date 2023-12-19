#pragma once

#include <stack>
#include <memory>

#include "State.h"

namespace Engine
{
    class StateMan
    {
    private:
        std::stack<std::unique_ptr<State>> m_stateStack; //хранение текущего состояния и проверка активности предыдущих состояний; структура данных работает по принципу LIFO - первым всегда извлекается последний добавленный элемент
        std::unique_ptr<State> m_newState; //хранение нового состояния, которое добавляется в стек m_stateStack

        bool m_add; //индикатор потребности добавления нового состояния
        bool m_replace; //индикатор потребности замены текущего состояния новым
      

    public:
        StateMan(); //конструктор
        ~StateMan(); //деструктор

        void Add(std::unique_ptr<State> toAdd, bool replace = false); //добавление нового состояния 
        void ProcessStateChange(); //добавление/замена текущего состояния в стеке m_stateStack
        std::unique_ptr<State>& GetCurrent(); //возвращает текущее состояние, которое хранится на верхушке стека m_stateStack
    };

} 
