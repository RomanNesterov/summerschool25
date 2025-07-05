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
    int height;
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
    
    // получение высоты вершины (с обработкой пустого указателя)
    int getHeight(NodeInt* node);
    
    int find_by_pos(int index, NodeInt* curr_node);
    void find_floor(int value, NodeInt* curr_node);
    void find_ceiling(int value, NodeInt* curr_node);
    
    // Внутренняя рекусрвивная вставка
    NodeInt *insertRecursive(NodeInt* node, int val);
    
    // Обновление высоты узла после вставки или удаления
    void updateHeight(NodeInt* node);
    
public:
    TreeInt();
    TreeInt(int f_value);
    TreeInt(NodeInt* root);
    ~TreeInt();
    // Tree(std::vector<int>& vals);
    
    // получение высоты всего дерева
    int height();
    
    // true, если получилось вставить! (нерекурсивная)
    bool insert(int value);
    // Публичная функция вставки (рекурсивная)
    void insertRec(int val);
    // true, если получилось удалить! (нерекурсивная)
    bool remove(int value);
    
    // Возвращает int_max, если не смогли найти такой индекс!
    int select(int index);
    // При реализации поиска floor и ceiling используются строгие неравенства
    // Возвращает int_min, если не смогли найти такой меньший элемент!
    int floor(int value);
    // Возвращает int_max, если не смогли найти такой больший элемент!
    int ceiling(int value);
};
