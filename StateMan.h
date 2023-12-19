#pragma once

#include <stack>
#include <memory>

#include "State.h"

namespace Engine
{
    class StateMan
    {
    private:
        std::stack<std::unique_ptr<State>> m_stateStack; //�������� �������� ��������� � �������� ���������� ���������� ���������; ��������� ������ �������� �� �������� LIFO - ������ ������ ����������� ��������� ����������� �������
        std::unique_ptr<State> m_newState; //�������� ������ ���������, ������� ����������� � ���� m_stateStack

        bool m_add; //��������� ����������� ���������� ������ ���������
        bool m_replace; //��������� ����������� ������ �������� ��������� �����
      

    public:
        StateMan(); //�����������
        ~StateMan(); //����������

        void Add(std::unique_ptr<State> toAdd, bool replace = false); //���������� ������ ��������� 
        void ProcessStateChange(); //����������/������ �������� ��������� � ����� m_stateStack
        std::unique_ptr<State>& GetCurrent(); //���������� ������� ���������, ������� �������� �� �������� ����� m_stateStack
    };

} 
