//
//  MyArray.hpp
//  summerschool
//  Заголовочный файл нашего самописного массива
//
//  Created by Roman N. on 30.06.2025.
//

class MyArray {
public:
    MyArray(); // Создание без параметров
    MyArray(int cap); // Создание с заданной емкостью
    MyArray(int siz, int v); // Создание с заданным размером
    
    ~MyArray(); // Деструктор - за динамической памятью надо следить!
    
    void pushBack(int v); // Вставка в конец
    void pushFront(int v); // Вставка в начало
    void popBack(); // Удаление из конца
    
    int getSize(); // Узнать размер
    int getCapacity(); // Узнать емкость
    int getElem(int pos); // Доступ к элементу - аналог индексации
    
    
private:
    int *arr; // Внутренний динамический массив
    int size; // Размер массива - количество элементов
    int capacity; // Емкость массива - сколько доступно памяти?
    
    void resize(int offset); // А если кончилась емкость?
};
