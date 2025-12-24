/**
 * @file matrix_task.c
 * @brief Алгоритмическая обработка двумерного целочисленного массива (Вариант 16).
 * 
 * Задачи:
 * 1. Модульная структура программы с использованием функций.
 * 2. Интерактивное или случайное заполнение матрицы.
 * 3. Выделение элементов на основе условий секторов.
 * 4. Оптимизированный обход секторов (Верхний, Нижний треугольники и Главная диагональ).
 * 5. Расчет суммы и количества элементов при определенных условиях.
 * 
 * Часть 1: Расчет суммы элементов > порога в Секторе 5 (Верхний и Нижний треугольники).
 * Часть 2: Подсчет и обнуление элементов в Секторе 3\ (Нижний треугольник + Главная диагональ).
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100 // Максимально допустимый размер матрицы

/**
 * @brief Ручной ввод элементов матрицы пользователем.
 * @param n Размерность матрицы (n x n).
 * @param matrix Двумерный массив для заполнения.
 */
void input_manual(int n, int matrix[MAX_SIZE][MAX_SIZE]) {
    printf("\n--- Ручной ввод матрицы ---\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // nom = i * n + j + 1 согласно технической подсказке
            printf("Введите элемент [%d][%d] (Порядковый номер %d): ", i, j, i * n + j + 1);
            while (scanf("%d", &matrix[i][j]) != 1) {
                printf("Некорректный ввод. Пожалуйста, введите целое число: ");
                while (getchar() != '\n'); // Очистка буфера
            }
        }
    }
}

/**
 * @brief Заполнение матрицы случайными целыми числами в диапазоне [-50, 50].
 * @param n Размерность матрицы.
 * @param matrix Двумерный массив для заполнения.
 */
void input_random(int n, int matrix[MAX_SIZE][MAX_SIZE]) {
    srand(time(NULL));
    printf("\n--- Матрица заполнена случайными числами ---\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 101 - 50; // Случайный диапазон от -50 до 50
        }
    }
}

/**
 * @brief Вспомогательная функция для проверки принадлежности Сектору 5.
 * Сектор 5: Верхний и Нижний треугольники (исключая диагонали).
 */
int is_in_sector5(int i, int j, int n) {
    int is_top = (j > i) && (j + i < n - 1);
    int is_bottom = (j < i) && (j + i > n - 1);
    return is_top || is_bottom;
}

/**
 * @brief Отображает матрицу с опциональным выделением Сектора 5.
 * @param n Размерность матрицы.
 * @param matrix Двумерный массив.
 * @param highlight Флаг выделения Сектора 5.
 */
void output_matrix(int n, int matrix[MAX_SIZE][MAX_SIZE], int highlight) {
    printf("\nМатрица (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (highlight && is_in_sector5(i, j, n)) {
                printf("*%4d* ", matrix[i][j]); // Выделение Сектора 5
            } else {
                printf(" %4d  ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * @brief Часть 1: Вычисляет сумму элементов > порога в Секторе 5.
 * Использует оптимизированный обход Верхнего и Нижнего треугольников.
 */
long long process_part1(int n, int matrix[MAX_SIZE][MAX_SIZE], int threshold) {
    long long sum = 0;
    
    // Обход верхнего треугольника
    for (int i = 0; i < n / 2; i++) {
        for (int j = i + 1; j < n - 1 - i; j++) {
            if (matrix[i][j] > threshold) {
                sum += matrix[i][j];
            }
        }
    }
    
    // Обход нижнего треугольника
    for (int i = n / 2 + 1; i < n; i++) {
        for (int j = n - i; j < i; j++) {
            if (matrix[i][j] > threshold) {
                sum += matrix[i][j];
            }
        }
    }
    
    return sum;
}

/**
 * @brief Часть 2: Подсчитывает и обнуляет элементы в Секторе 3\ (Низ + Главная диагональ).
 * Использует оптимизированный обход.
 */
int process_part2(int n, int matrix[MAX_SIZE][MAX_SIZE]) {
    int count = 0;
    
    // Обход нижнего треугольника (Сектор 3)
    for (int i = n / 2 + 1; i < n; i++) {
        for (int j = n - i; j < i; j++) {
            count++;
            matrix[i][j] = 0;
        }
    }
    
    // Обход главной диагонали (часть \)
    for (int i = 0; i < n; i++) {
        count++;
        matrix[i][i] = 0;
    }
    
    return count;
}

int main() {
    int n, choice, threshold;
    int matrix[MAX_SIZE][MAX_SIZE];

    printf("Введите размерность матрицы n (макс %d): ", MAX_SIZE);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
        printf("Некорректная размерность. Выход.\n");
        return 1;
    }

    printf("Выберите метод заполнения:\n1. Вручную\n2. Случайно\nВаш выбор: ");
    scanf("%d", &choice);

    if (choice == 1) {
        input_manual(n, matrix);
    } else {
        input_random(n, matrix);
    }

    printf("Введите значение порога для Части 1: ");
    scanf("%d", &threshold);

    // Начальный вывод с выделением
    printf("\n--- Исходная матрица (Сектор 5 выделен символом *) ---");
    output_matrix(n, matrix, 1);

    // Часть 1
    long long sum1 = process_part1(n, matrix, threshold);
    printf("\nЧасть 1 (Сектор 5): Сумма элементов > %d = %lld\n", threshold, sum1);

    // Часть 2
    int count2 = process_part2(n, matrix);
    printf("Часть 2 (Сектор 3\\): Количество обработанных элементов = %d\n", count2);

    // Финальный вывод
    printf("\n--- Обработанная матрица (Сектор 3\\ обнулен) ---");
    output_matrix(n, matrix, 0);

    return 0;
}
