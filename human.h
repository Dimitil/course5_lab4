#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <memory>
#include <vector>
#include <iostream>

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

    void printParents(size_t lvl = 0);

    void printThis() { std::cout << m_name << '\n' ; }

    void printChilds(size_t lvl = 1);

    void printTree();

    static std::shared_ptr<human> child(const std::string& name,
                                        std::shared_ptr<human>& mather,
                                        std::shared_ptr<human>& father);
};

#endif // HUMAN_H
