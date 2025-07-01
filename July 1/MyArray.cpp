//
//  MyArray.cpp
//  summerschool
//  Реализация функций нашего самописного массива
//
//  Created by Roman N. on 30.06.2025.
//
#include "MyArray.hpp"


MyArray::MyArray() {
    size = 0;
    capacity = 5;
    
    arr = new int[capacity]; // Выделение памяти блоком, а не одной ячейкой
}

MyArray::MyArray(int cap) {
    size = 0;
    capacity = cap;

    arr = new int[cap];
}

MyArray::MyArray(int siz, int v) {
    size = siz;
    capacity = siz + 1; // зависимость емкости от заданного размера может быть любой (например, в два раза больше и т.п.)

    arr = new int[capacity];

    for (int i = 0; i < size; i++) {
        arr[i] = v;
    }
}

MyArray::~MyArray() {
    delete[] arr; // каждому new свой delete!
}

void MyArray::resize(int offset) {
    int* oldArr = arr;
    int* newArr = new int[capacity * 2];

    for (int i = 0; i < size; ++i) {
        newArr[i + offset] = oldArr[i];
    }

    delete[] oldArr;
    arr = newArr;
    capacity *= 2;
}

void MyArray::pushBack(int v) {
    if (size == capacity) {
        resize(0);
    }

    ++size;
    arr[size - 1] = v;
}

void MyArray::pushFront(int v) {
    if (size == capacity) {
        resize(0);
    }

    for (int i = size - 1; i >= 0; --i) {
        arr[i + 1] = arr[i];
    }

    ++size;
    arr[0] = v;
}

void MyArray::popBack() {
    if (size == 0){
        return;
    }

    --size;
}

int MyArray::getSize() {
    return size;
}

int MyArray::getCapacity() {
    return capacity;
}

int MyArray::getElem(int pos) {
    return arr[pos];
}
