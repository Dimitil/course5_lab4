#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <memory>
#include <vector>
#include <iostream>

//Задание 6. shared_ptr и weak_ptr
//Создаем генеалогическое дерево посредством класса human. В классе хранятся:
//имя - string
//возможно признак: жив или уже нет...
//родители - shared_ptr (родители не всегда известны...)
//дети - контейнер из weak_ptr (чтобы избежать циклических зависимостей)

//Методы класса human:
//конструктор - для инициализации имени и признака
//конструктор копирования, оператор присваивания, move ???
//статический метод child() -
//				должен создать создать и вернуть обертку для родившегося человека
//				+ сформировать все связи ребенка с родителями и наоборот

//Ввести возможность распечатать генеалогическое дерево для указанного индивидума


//История должна с кого-то начинаться => "Жили-были дед да баба, например, Адам и Ева"
//(то есть на самом деле два деда и две бабы):


//std::shared_ptr<human> grandM1(new human("Eva"));
//...

//у них появились дети - child():


//а у детей в свою очередь свои дети:


//...
class human
{
    std::string m_name;
    std::shared_ptr<human> m_father = nullptr;
    std::shared_ptr<human> m_mather = nullptr;
    std::vector <std::weak_ptr<human>> m_childs;
public:

    human(std::string name) : m_name(name) {}

    human(const human& other) = delete;
    human& operator=(const human* other) = delete;
    human(human&& other) = delete;
    human& operator=(human&& other) = delete;

    void printParents(size_t lvl = 0) {
        if(m_mather) {
            m_mather->printParents(lvl + 1);
            for(size_t i = 0; i < lvl; i++) std::cout<<'\t';
            std::cout << '\t' << m_mather->m_name << '\n';
           }
        if(m_father) {
            m_father->printParents(lvl + 1);
            for(size_t i = 0; i < lvl; i++) std::cout<<'\t';
            std::cout << '\t' << m_father->m_name << '\n';
        }
    }

    void printThis() {
        std::cout << m_name << '\n' ;
    }
    void printChilds(size_t lvl = 1) {
        for (auto &el : m_childs) {
            for(size_t i = 0; i < lvl; i++) std::cout<<'\t';
            std::cout << el.lock() ->m_name << '\n';
            el.lock()->printChilds(lvl+1);
        }
    }

    void printTree() {
       printParents();
       printThis();
       printChilds();
    }

    static std::shared_ptr<human> child(const std::string& name,
                                        std::shared_ptr<human>& mather,
                                        std::shared_ptr<human>& father)
    {
        auto child = std::make_shared<human>(name);

        if(mather) {
            child->m_mather = mather;
            mather->m_childs.push_back(child);
        }

        if(father) {
            child->m_father = father;
            father->m_childs.push_back(child);
        }

        return child;
    }
};

#endif // HUMAN_H
