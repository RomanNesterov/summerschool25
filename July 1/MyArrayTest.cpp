//
//  MyArrayTest.cpp
//  summerschool
//  Тестирование работоспособности и замеры времени
//
//  Created by Roman N. on 01.07.2025.
//

#include <iostream>
#include <fstream> // для вывода в файл
#include <chrono> // замер времени, работает с версии С++17
#include "MyArray.hpp"

// using-объявления для понятности использования chrono
using clocks = std::chrono::high_resolution_clock;
using nanoseconds = std::chrono::nanoseconds;


// Проверка функциональности
// создания и вставки элементов
void basicTest() {
    // 1. Создание пустого массива без параметров
    MyArray arr1;
    std::cout << arr1.getSize() << " ";
    std::cout << arr1.getCapacity() << std::endl;
    
    // 2. Создание пустого массива заданной емкости
    MyArray arr2(10);
    std::cout << arr2.getSize() << " ";
    std::cout << arr2.getCapacity() << std::endl;
    
    // 3. Создание массива и заданного размера
    //    с значением по умолчанию
    MyArray arr3(10, -1);
    std::cout << arr3.getSize() << " ";
    std::cout << arr3.getCapacity() << std::endl;
    
    for (int i = 0; i < arr3.getSize(); ++i) {
        std::cout << arr3.getElem(i) << " ";
    }
    
    std::cout << std::endl; // переводим строку, чтобы вывод на
                            // экран не сливался вместе
    
    // 4. Вставка в конец
    for (int i = 0; i < 10; ++i) {
        arr1.pushBack(i);
    }
    
    std::cout << arr1.getSize() << " ";
    std::cout << arr1.getSize() << std::endl;
    
    for (int i = 0; i < arr1.getSize(); ++i) {
        std::cout << arr1.getElem(i) << " ";
    }
    
    std::cout << std::endl;
    
    // 5. Вставка в начало
    for (int i = 0; i < 10; ++i) {
        arr1.pushFront(i);
    }
    
    std::cout << arr1.getSize() << " ";
    std::cout << arr1.getCapacity() << std::endl;
    
    for (int i = 0; i < arr1.getSize(); ++i) {
        std::cout << arr1.getElem(i) << " ";
    }
    
    std::cout << std::endl;
    
    // 6. Удаление из конца
    for (int i = 0; i < 10; ++i) {
        arr1.popBack();
    }
    
    std::cout << arr1.getSize() << " ";
    std::cout << arr1.getCapacity() << std::endl;
    
    for (int i = 0; i < arr1.getSize(); ++i) {
        std::cout << arr1.getElem(i) << " ";
    }
    
    std::cout << std::endl;
}

// Замер реального времени базовых операций
// с нашим самописным массивом
void timeTest(int trials) {
    MyArray arr1;
    
    // Многие среды разработки могут потребовать полного пути до файла
    // не забывайте, что обратный слэш должен быть двойным
    std::ofstream outFile("/Users/romann./Downloads/timings1.csv");
    
    for (int i = 0; i < trials; ++i) {
        auto start = clocks::now(); // текущее время до выполнения
        arr1.pushBack(i);
        auto elapsed = clocks::now() - start; // текущее время после выполнения
        long long nanoSec = std::chrono::duration_cast<nanoseconds>(elapsed).count();
        
        outFile << nanoSec << std::endl; // записываем время работы в файл
    }
}

// Следите - в проекте должен быть один метод main!
int main() {
    basicTest();
    timeTest(10000);
}
