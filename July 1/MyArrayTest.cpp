//
//  MyArrayTest.cpp
//  summerschool
//  Тестирование работоспособности и замеры времени
//
//  Created by Roman N. on 01.07.2025.
//  Updated on 02.07.2025
//

#include <iostream>
#include <fstream> // для вывода в файл
#include <chrono> // замер времени, работает с версии С++17
#include <mach/mach.h> // замер памяти на Mac OS
// для замера памяти на Windows
// #include <Windows.h>
// #include <Psapi.h>
#include "MyArray.hpp"

// using-объявления для понятности использования chrono
using clocks = std::chrono::high_resolution_clock;
using nanoseconds = std::chrono::nanoseconds;

// файл для записи замеров памяти
std::ofstream outFile1("/Users/romann./Downloads/mem.csv");

// Проверка функциональности
// создания и вставки элементов
void basicTest() {
    // 0. Индексация с помощью оператора
    MyArray arr5(10, 8);
           
    try {
        std::cout << arr5[0] << std::endl;
        std::cout << arr5[1] << std::endl;
        std::cout << arr5[2] << std::endl;

        arr5[5] = 9;
        std::cout << arr5[5] << std::endl;

        std::cout << arr5[11] << std::endl;
    } catch (int) {
        std::cout << "Index out of range!";
    }
    
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

// Замер памяти на текущий момент в Mac OS
void reportMemoryMacOS() {
    task_vm_info_data_t info;
    mach_msg_type_number_t count = TASK_VM_INFO_COUNT;
    
    if (task_info(mach_task_self(), TASK_VM_INFO,
                  (task_info_t)&info, &count) == KERN_SUCCESS) {
        // Виртуальная и физическая память
        //std::cout << "Physical memory (resident): "
        //         << info.resident_size / 1024 << " Kb\n";
        //std::cout << "Virtual memory: "
        //          << info.virtual_size / 1024 << " Kb\n";
        outFile1 << info.resident_size / 1024 << std::endl;
    }
}

// Замер памяти на текущий момент в Windows
//void reportMemoryWindows() {
//    PROCESS_MEMORY_COUNTERS pmc;
//
//    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
//        std::cout << "WorkingSet:" << pmc.WorkingSetSize << " bytes\n";
//    }
//}

// Замер реального времени базовых операций
// с нашим самописным массивом
void timeTest(int trials) {
    MyArray arr1;
    
    // Многие среды разработки могут потребовать полного пути до файла
    // не забывайте, что обратный слэш должен быть двойным
    std::ofstream outFile("/Users/romann./Downloads/timings1.csv");
    for (int i = 0; i < trials; ++i) {
        auto start = clocks::now(); // текущее время до выполнения
        arr1.pushFront(i);
        auto elapsed = clocks::now() - start; // текущее время после выполнения
        long long nanoSec = std::chrono::duration_cast<nanoseconds>(elapsed).count();
        
        outFile << nanoSec << std::endl; // записываем время работы в файл
        // reportMemoryMacOS();
    }
}

// Следите - в проекте должен быть один метод main!
int main() {
    // reportMemoryMacOS();
    basicTest();
    timeTest(10000);
}
