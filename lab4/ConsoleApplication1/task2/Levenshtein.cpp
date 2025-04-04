﻿// - Levenshtein.cpp
#include <iomanip>   // Для форматированного вывода
#include <algorithm> // Для std::min
#include "Levenshtein.h"

#define DD(i, j) d[(i) * (ly + 1) + (j)] // Макрос для удобного обращения к элементам матрицы d

// Функция для нахождения минимума из трёх чисел
int min3(int x1, int x2, int x3) {
    return std::min(std::min(x1, x2), x3);
}

// Функция для вычисления расстояния Левенштейна с помощью динамического программирования
int levenshtein(int lx, const char x[], int ly, const char y[]) {
    // Создаём одномерный массив (используется как двумерный)
    int* d = new int[(lx + 1) * (ly + 1)];

    // Заполняем первую строку: если строка `y` пустая, то расстояние = i (удаление всех символов `x`)
    for (int i = 0; i <= lx; i++)
        DD(i, 0) = i;

    // Заполняем первый столбец: если строка `x` пустая, то расстояние = j (вставка всех символов `y`)
    for (int j = 0; j <= ly; j++)
        DD(0, j) = j;

    // Основной цикл для заполнения матрицы расстояний
    for (int i = 1; i <= lx; i++) {
        for (int j = 1; j <= ly; j++) {
            // Если символы совпадают, то операция замены не требуется (стоимость = 0)
            int cost = (x[i - 1] == y[j - 1]) ? 0 : 1;

            // Выбираем минимальную стоимость операции:
            // 1. Удаление символа из `x` (DD(i - 1, j) + 1)
            // 2. Вставка символа в `x` (DD(i, j - 1) + 1)
            // 3. Замена символа (DD(i - 1, j - 1) + cost)
            DD(i, j) = min3(DD(i - 1, j) + 1,  // Удаление
                DD(i, j - 1) + 1,  // Вставка
                DD(i - 1, j - 1) + cost); // Замена
        }
    }

    int result = DD(lx, ly); // Итоговое значение - расстояние Левенштейна между x и y
    delete[] d; // Освобождаем память
    return result;
}

// Рекурсивная функция для вычисления расстояния Левенштейна (без оптимизации)
int levenshtein_r(int lx, const char x[], int ly, const char y[]) {
    // Базовые случаи:
    if (lx == 0) return ly; // Если `x` пустая, то все символы `y` нужно вставить
    if (ly == 0) return lx; // Если `y` пустая, то все символы `x` нужно удалить

    // Если обе строки состоят из одного символа
    if (lx == 1 && ly == 1)
        return (x[0] == y[0]) ? 0 : 1; // Если символы равны - расстояние 0, иначе 1

    // Основной рекурсивный вызов:
    return min3(
        levenshtein_r(lx - 1, x, ly, y) + 1,  // Удаление символа из `x`
        levenshtein_r(lx, x, ly - 1, y) + 1,  // Вставка символа в `x`
        levenshtein_r(lx - 1, x, ly - 1, y) + ((x[lx - 1] == y[ly - 1]) ? 0 : 1) // Замена символа
    );
}
