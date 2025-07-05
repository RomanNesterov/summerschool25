//
//  MyTree.cpp
//  summerschool
//  Реализация простого дерева - шаг 1, 2, 3
//  Created by Roman N. on 02.07.2025.
//

#include "MyTree.hpp"
#include <limits>
#include <iostream>
#include <algorithm> // для использования стандартных функций

NodeInt::NodeInt() {
    int value = 0;
    //int height;
    l = r = nullptr;
    height = 1;
}

NodeInt::NodeInt(int value) {
    this->value = value;
    //int height;
    l = r = nullptr;
    height = 1;
}

NodeInt::NodeInt(int value, NodeInt* l, NodeInt* r) {
    this->value = value;
    //int height;
    this->l = l;
    this->r = r;
    height = 1 + std::max(l->height, r->height);
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

// true, если получилось удалить!
bool TreeInt::remove(int value) {
    NodeInt* current_node = root, *parent = nullptr, *buffer;
    std::stack<NodeInt*> to_update;
    bool is_found = false, is_deleted = false;

    if (root == nullptr) {
        return false;
    }

    while (!is_found && current_node != nullptr) {
        if (current_node->value > value) {
            to_update.push(current_node);
            current_node = current_node->l;
        }
        else if (current_node->value < value) {
            to_update.push(current_node);
            current_node = current_node->r;
        } else {
            is_found = true;
            while (!is_deleted) {
                if (current_node->l != nullptr) {
                    current_node->value = current_node->l->value;
                    parent = current_node;
                    to_update.push(current_node);
                    current_node = current_node->l;
                } else if (current_node->r != nullptr) {
                    current_node->value = current_node->r->value;
                    parent = current_node;
                    to_update.push(current_node);
                    current_node = current_node->r;
                } else {
                    if (parent->r == current_node) {
                        parent->r = nullptr;
                    }
                    else if (parent->l == current_node) {
                        parent->l = nullptr;
                    }
                    delete current_node;
                    is_deleted = true;
                }
            }
            size -= 1;
            while (!to_update.empty())
            {
                buffer = to_update.top();
                to_update.pop();
                buffer->height = (buffer->l != nullptr) ? buffer->l->height + 1 : 1;
                buffer->height = (buffer->r != nullptr) ? std::max(buffer->height, buffer->r->height + 1) : buffer->height;
                // метод ребаланса - ссююю дааа!
            }
            return true;
        }
    }
    return false;
}

void TreeInt::insertRec(int val) {
    root = insertRecursive(root, val);
    size++;
}

NodeInt* TreeInt::insertRecursive(NodeInt* node, int val) {
    if (!node) return new NodeInt(val);
    
    if (val < node->value) {
        node->l = insertRecursive(node->l, val);
    } else if (val > node->value) {
        node->r = insertRecursive(node->r, val);
    } else {
        return node;
    }
    
    // благодаря рекурсии, обновятся высоты всех узлов
    updateHeight(node);
    return node;
}

int TreeInt::height() {
    return getHeight(root);
}

int TreeInt::getHeight(NodeInt* node) {
    return node ? node->height : 0;
}

void TreeInt::updateHeight(NodeInt* node) {
    if (node) {
        node->height = 1 + std::max(getHeight(node->l), getHeight(node->r));
    }
}
