#include "human.h"

std::shared_ptr<human> human::child(const std::string& name,
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

void human::printParents(size_t lvl) {
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

void human::printChilds(size_t lvl) {
    for (auto &el : m_childs) {
        for(size_t i = 0; i < lvl; i++) std::cout<<'\t';
        std::cout << el.lock() ->m_name << '\n';
        el.lock()->printChilds(lvl+1);
    }
}

void human::printTree() {
   printParents();
   printThis();
   printChilds();
}
