//
//  MyTreeTest.cpp
//  summerschool
//  Базовые тесты для нашего самописного дерева
//  Created by Roman N. on 02.07.2025.
//

#include <iostream>
#include <fstream> // для вывода в файл
#include <chrono> // замер времени, работает с версии С++17
// анализ памяти в Windows
// #include <Windows.h>
// #include <Psapi.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <set>
#include "MyTree.hpp"

// using-объявления для понятности использования chrono
using clocks = std::chrono::high_resolution_clock;
using nanoseconds = std::chrono::nanoseconds;

// для учета статистики использования памяти
//size_t reportMemoryUsage() {
//    PROCESS_MEMORY_COUNTERS pmc;
//
//    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
//        return pmc.WorkingSetSize;
//    }
//}

// Сравнительный анализ времени и памяти для дерева и массива
// Дерево заполняется случайными значениями
void CompareTest() {
    // 1. Создание и сравнение памяти, выделяемой на массив и дерево;
    //    массив заполняется случайными числами через функцию rand()
    int size = 10000;
    std::vector<int> arr(size);
    // size_t zero = reportMemoryUsage();
    for (int& i : arr) {
        i = abs(std::rand() % size);
    }
    // size_t fst = reportMemoryUsage();
    TreeInt tree;
    for (int& i : arr) {
        tree.insert(i);
    }
    // size_t snd = reportMemoryUsage();
    // size_t delta = snd - fst;
    // std::cout << fst - zero << ' ' << delta << '\n';

    // 2. Анализ времени для поиска floor в дереве;
    //    запоминаем элементы, которые использовали, для честности
    std::vector<int> positions(10);
    auto start1 = clocks::now(); // текущее время до выполнения
    TreeInt tree1;
    for (int& i : arr) {
        tree1.insert(i);
    }
    for (int i = 0; i < 10; ++i) {
        positions[i] = abs(std::rand() % (int)(arr.size()));
        tree1.floor(arr[positions[i]]);
    }
    auto elapsed1 = clocks::now() - start1;
    long long nanoSec1 = std::chrono::duration_cast<nanoseconds>(elapsed1).count();
    
    // 3. Анализ времени для поиска floor в массиве;
    //    требуется выполнить сортировку
    auto start2= clocks::now(); // текущее время до выполнения
    std::vector<int> arr1(size);
    arr1 = arr;
    std::sort(arr1.begin(), arr1.end());
    for (int i = 0; i < 10; ++i) {
        // Можно найти предыдущий элемент массива, от найденного!
        *(std::find(arr1.begin(), arr1.end(), positions[i]) - 1);
    }
    auto elapsed2 = clocks::now() - start2;
    long long nanoSec2 = std::chrono::duration_cast<nanoseconds>(elapsed2).count();
    
    std::cout << nanoSec1 << ' ' << nanoSec2;
}

// Сравнительный анализ времени и памяти для дерева и массива
// Дерево заполняется значениями упорядоченными по возрастанию
void TestLinear() {
    // 1. Создание и сравнение памяти, выделяемой на массив и дерево;
    //    массив и дерево заполняются упорядоченно
    int size = 10000;
    std::vector<int> arr(size);
    // size_t zero = reportMemoryUsage();
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = i;
    }
    // size_t fst = reportMemoryUsage();
    TreeInt tree;
    for (int& i : arr) {
        tree.insert(i);
    }
    // size_t snd = reportMemoryUsage();
    // size_t delta = snd - fst;
    // std::cout << fst - zero << ' ' << delta << '\n';
    
    // 2. Анализ времени для поиска floor в дереве;
    //    запоминаем элементы, которые использовали, для честности
    std::vector<int> positions(10);
    auto start1 = clocks::now(); // текущее время до выполнения
    TreeInt tree1;
    for (int& i : arr) {
        tree1.insert(i);
    }
    for (int i = 0; i < 10; ++i) {
        positions[i] = abs(std::rand() % (int)(arr.size()));
        tree1.floor(arr[positions[i]]);
    }
    auto elapsed1 = clocks::now() - start1;
    long long nanoSec1 = std::chrono::duration_cast<nanoseconds>(elapsed1).count();
    
    // 3. Анализ времени для поиска floor в массиве;
    //    сортировка не требуется
    auto start2 = clocks::now(); // текущее время до выполнения
    std::vector<int> arr1(size);
    arr1 = arr;
    for (int i = 0; i < 10; ++i) {
        // Можно найти предыдущий элемент массива, от найденного!
        *(std::find(arr1.begin(), arr1.end(), positions[i]) - 1);
    }
    auto elapsed2 = clocks::now() - start2;
    long long nanoSec2 = std::chrono::duration_cast<nanoseconds>(elapsed2).count();
    std::cout << nanoSec1 << ' ' << nanoSec2;
}

void TestSet() {
    std::set<int> s1, s2;
    for (int i = 0; i < 5000; ++i) {
        s1.insert(i);
    }

    for (int i = 0; i < 5000; ++i) {
        s2.insert(std::rand() % 1000000);
    }

    unsigned long long int res1 = 0, res2 = 0;

    for (int i = 0; i < 4; ++i) {
        int buffer = std::rand() % 1000000;

        auto start1 = clocks::now();
        s1.insert(buffer);
        auto elapsed1 = clocks::now() - start1;
        res1 += std::chrono::duration_cast<nanoseconds>(elapsed1).count();
        
        auto start2 = clocks::now();
        s2.insert(buffer);
        auto elapsed2 = clocks::now() - start2;
        res2 += std::chrono::duration_cast<nanoseconds>(elapsed2).count();

    }
    std::cout << res1 / 4 << ' ' << res2 / 4;
}

void TestSetBuilding() {
    std::set<int> s1, s2;
    std::ofstream out;

    unsigned long long int res1 = 0, res2 = 0;

    out.open("D:\\Downloads\\sorts\\resTestSetBuilding1.txt");
    for (int i = 0; i < 50000; ++i) {
        auto start1 = clocks::now();
        s1.insert(std::rand() % 1000000);
        auto elapsed1 = clocks::now() - start1;
        //out << std::chrono::duration_cast<nanoseconds>(elapsed1).count() << '\n';

        start1 = clocks::now();
        s2.insert(i);
        elapsed1 = clocks::now() - start1;
        out << std::chrono::duration_cast<nanoseconds>(elapsed1).count() << '\n';
    }
    out.close();
}

void TestSetErasingStress() {
    std::set<int> s1, s2;
    std::ofstream out;
    int buffer;

    unsigned long long int res1 = 0, res2 = 0;

    out.open("D:\\Downloads\\sorts\\resTestSetErase1.txt");
    for (int i = 0; i < 50000; ++i) {
        s1.insert(std::rand() % 1000000);
        s1.insert(buffer = std::rand() % 1000000);
        auto start1 = clocks::now();
        s1.erase(buffer);
        auto elapsed1 = clocks::now() - start1;
        //out << std::chrono::duration_cast<nanoseconds>(elapsed1).count() << '\n';

        s1.insert(i);
        s1.insert(50000 + i);
        start1 = clocks::now();
        s2.erase(50000 + i);
        elapsed1 = clocks::now() - start1;
        out << std::chrono::duration_cast<nanoseconds>(elapsed1).count() << '\n';
    }
    out.close();
}

void TestSetErasing() {
    int buffer;
    std::vector<int> data, random_data;
    std::set<int> s1, s2;
    for (int i = 0; i < 5000; ++i) {
        s1.insert(i);
        data.push_back(i);
    }

    for (int i = 0; i < 5000; ++i) {
        s2.insert(buffer = std::rand() % 1000000);
        random_data.push_back(buffer);
    }

    unsigned long long int res1 = 0, res2 = 0;

    for (int i = 0; i < 4; ++i) {
        int buffer = std::rand() % 1000000;

        auto start1 = clocks::now();
        s1.erase(data[abs(std::rand() % 5000)]);
        auto elapsed1 = clocks::now() - start1;
        res1 += std::chrono::duration_cast<nanoseconds>(elapsed1).count();

        auto start2 = clocks::now();
        s2.erase(random_data[abs(std::rand() % 5000)]);
        auto elapsed2 = clocks::now() - start2;
        res2 += std::chrono::duration_cast<nanoseconds>(elapsed2).count();

    }
    std::cout << res1 / 4 << ' ' << res2 / 4;
}

// тест времени рекурсивной вставки и высоты нашего самописного дерева
// в результате вставки случайно перемешанной последовательности значений
void TestTreeInsert() {
    size_t totalNodes = pow(2, 14) - 1; // количество узлов 2^(h+1) - 1
    
    // два файла для хранения результатов - время работы и высота
    std::ofstream outFile1("/Users/romann./Downloads/insertTime.csv");
    std::ofstream outFile2("/Users/romann./Downloads/insertHeight.csv");
    
    // создание и перемешивание массива тестовых значений
    std::vector<int> testArr(totalNodes);
    for (int i = 0; i < totalNodes; ++i) {
        testArr[i] = i;
    }
    
    std::default_random_engine rng(std::random_device{}());
    std::shuffle(testArr.begin(), testArr.end(), rng);
    
    // внешний цикл по количеству экспериментов,
    // чтобы далее рассмотреть среднее время вставки
    for (int i = 0; i < 15; ++i) {
        TreeInt myTree;
        outFile1 << "Эксперимент " << i + 1 << ", ";
        for (int j = 0; j < totalNodes; ++j) {
            auto start = clocks::now();
            myTree.insertRec(testArr[j]);
            auto elapsed = clocks::now() - start;
            
            // ввиду большого числа значений можем записывать
            // только каждое десятое измерение
            if (j % 10 == 0) {
                outFile1 << std::chrono::duration_cast<nanoseconds>(elapsed).count();
                outFile1 << ", ";
            }
        }
        
        // переводим строку в файле после окончания
        // записи очередного эксперимента
        outFile1 << std::endl;
    }
    
    // динамику высоты достаточно посчитать один раз,
    // поскольку наше самописное дерево не является случайным
    TreeInt myTree1;
    for (int j = 0; j < totalNodes; ++j) {
        myTree1.insertRec(testArr[j]);
        
        if (j % 10 == 0) {
            outFile2 << myTree1.height() << ", ";
        }
    }
}

// следите - файл main() должен быть один!
int main() {
    //CompareTest();
    //TestLinear();
    TestTreeInsert();
}
