//
//  MyTree.cpp
//  summerschool
//  Реализация простого дерева - шаг 1
//  Created by Roman N. on 02.07.2025.
//

#include "MyTree.hpp"
#include <limits>
#include <iostream>

NodeInt::NodeInt() {
    int value = 0;
    //int height;
    l = r = nullptr;
}

NodeInt::NodeInt(int value) {
    this->value = value;
    //int height;
    l = r = nullptr;
}

NodeInt::NodeInt(int value, NodeInt* l, NodeInt* r) {
    this->value = value;
    //int height;
    this->l = l;
    this->r = r;
}

NodeInt::~NodeInt() {
    delete l;
    delete r;
}

TreeInt::TreeInt() {
    root = nullptr;
    size = 0;
}

TreeInt::TreeInt(int f_value) {
    size = 1;
    root = new NodeInt(f_value);
}

TreeInt::TreeInt(NodeInt* root) {
    this->root = root;
    // ДЛЯ ПОДСЧЁТА РАЗМЕРА НЕОБХОДИМО ОБОЙТИ ВСЕ ПОДДЕРЕВО!!!
}

TreeInt::~TreeInt() {
    delete root;
}

// true, если получилось вставить!
bool TreeInt::insert(int value) {
    NodeInt* current_node = root;
    bool is_inserted = false;

    if (root == nullptr) {
        size = 1;
        root = new NodeInt(value);
        return true;
    }

    while (!is_inserted) {
        if (current_node->value > value) {
            if (current_node->l == nullptr) {
                current_node->l = new NodeInt(value);
                is_inserted = true;
            }
            current_node = current_node->l;
        } else if (current_node->value < value) {
            if (current_node->r == nullptr) {
                current_node->r = new NodeInt(value);
                is_inserted = true;
            }
            current_node = current_node->r;
        } else {
            return false;
        }
    }
    size += 1;
    return is_inserted;
}

int pos;

int TreeInt::find_by_pos(int index, NodeInt* curr_node) {
    int buffer;
    if (curr_node->l != nullptr) {
        if ((buffer = find_by_pos(index, curr_node->l)) != std::numeric_limits<int>::max()) {
            return buffer;
        }
    }
    if (pos == index) {
        return curr_node->value;
    }
    pos += 1;
    if (curr_node->r != nullptr) {
        if ((buffer = find_by_pos(index, curr_node->r)) != std::numeric_limits<int>::max()) {
            return buffer;
        }
    }
    return std::numeric_limits<int>::max();
}

// Возвращает int_max, если не смогли найти такой индекс!
int TreeInt::select(int index) {
    pos = 0;
    if (root == nullptr) {
        return std::numeric_limits<int>::max();
    }
    return find_by_pos(index, root);
}

int local_max;

int cnt = 0;

void TreeInt::find_floor(int value, NodeInt* curr_node) {
    cnt++;
    if (curr_node->value > value) {
        if (curr_node->l != nullptr) {
            find_floor(value, curr_node->l);
        }
    } else if (curr_node->value < value) {
        if (local_max < curr_node->value) {
            local_max = curr_node->value;
        }
        if (cnt == 4176) {
            std::cout << "???";
        }
        if (curr_node->r != nullptr) {
            find_floor(value, curr_node->r);
        }
    } else {
        curr_node = curr_node->l;
        if (curr_node == nullptr) {
            return;
        }
        while (curr_node->r != nullptr) {
            curr_node = curr_node->r;
        }
        local_max = curr_node->value;
    }
}

// Возвращает int_min, если не смогли найти такой меньший элемент!
int TreeInt::floor(int value) {
    local_max = std::numeric_limits<int>::min();
    if (root == nullptr) {
        return std::numeric_limits<int>::min();
    }
    find_floor(value, root);
    return local_max;
}

int local_min;

void TreeInt::find_ceiling(int value, NodeInt* curr_node) {
    if (curr_node->value > value) {
        if (local_min > curr_node->value) {
            local_min = curr_node->value;
        }
        if (curr_node->l != nullptr) {
            find_ceiling(value, curr_node->l);
        }
    }
    else if (curr_node->value < value) {
        if (curr_node->r != nullptr) {
            find_ceiling(value, curr_node->r);
        }
    }
    else {
        curr_node = curr_node->r;
        if (curr_node == nullptr) {
            return;
        }
        while (curr_node->l != nullptr) {
            curr_node = curr_node->l;
        }
        local_min = curr_node->value;
    }
}

// Возвращает int_max, если не смогли найти такой больший элемент!
int TreeInt::ceiling(int value) {
    local_min = std::numeric_limits<int>::max();
    if (root == nullptr) {
        return std::numeric_limits<int>::max();
    }
    find_ceiling(value, root);
    return local_min;
}

