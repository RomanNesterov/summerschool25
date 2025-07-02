//
//  MyTree.hpp
//  summerschool
//  Заголовочный файл - бинарное дерево поиска
//  Created by Roman N. on 02.07.2025.
//

#pragma once
class NodeInt {
public:
    int value;
    //int height;
    NodeInt *l, *r;
    NodeInt();
    NodeInt(int value);
    NodeInt(int value, NodeInt* l, NodeInt* r);
    ~NodeInt();
};

class TreeInt {
private:
    NodeInt* root;
    //int height;
    int size;
    int find_by_pos(int index, NodeInt* curr_node);
    void find_floor(int value, NodeInt* curr_node);
    void find_ceiling(int value, NodeInt* curr_node);
public:
    TreeInt();
    TreeInt(int f_value);
    TreeInt(NodeInt* root);
    ~TreeInt();
    // Tree(std::vector<int>& vals);
    // true, если получилось вставить!
    bool insert(int value);
    // Возвращает int_max, если не смогли найти такой индекс!
    int select(int index);
    
    // При реализации поиска floor и ceiling используются строгие неравенства
    // Возвращает int_min, если не смогли найти такой меньший элемент!
    int floor(int value);
    // Возвращает int_max, если не смогли найти такой больший элемент!
    int ceiling(int value);
};
