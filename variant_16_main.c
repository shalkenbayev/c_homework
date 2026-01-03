#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// --- Задание 1: Выражение ---
void task1_expression() {
    printf("\n=== Задание 1: Выражение на C ===\n");
    double x = 2.0; // Пример значения
    double a = 1.0; // Пример значения
    
    // Формула: sqrt((4|x| - a) / (x^2 - 2)) + cot(x) - 2/3
    // Примечание: cot(x) = 1/tan(x)
    
    if (tan(x) == 0) {
        printf("Ошибка: tan(x) равен 0, cot(x) не определен.\n");
        return;
    }

    double result = sqrt((4 * fabs(x) - a) / (x * x - 2)) + 1.0 / tan(x) - 2.0 / 3.0;
    
    printf("Входные данные: x = %.2f, a = %.2f\n", x, a);
    printf("Результат: %f\n", result);
}

// --- Задание 2: Условная логика ---
void task2_conditional() {
    printf("\n=== Задание 2: Проверка условной логики ===\n");
    
    // Тестирование таблицы истинности
    bool z_vals[] = {false, true, true};
    bool x_vals[] = {false, true, false}; // Соответствующие пары для теста
    
    for (int i = 0; i < 3; i++) {
        bool z = z_vals[i];
        bool x = x_vals[i];
        
        int v = 0;
        int c = 0;
        
        // Точная логика из ограничений
        if (z) {
            if (x) {
                c = 1;
            }
        } else {
            v = 5;
        }
        
        printf("Вход: z=%d, x=%d -> Результат: v=%d, c=%d\n", z, x, v, c);
    }
}

// --- Задание 3: Протокол выполнения (Трассировка) ---
#define N_TRACE 5
void task3_trace() {
    printf("\n=== Задание 3: Трассировка выполнения ===\n");
    int i, k;
    int a[N_TRACE] = {1, -7, -5, 2, -1};
    
    printf("Запуск цикла...\n");
    
    // Цикл точно как в задании
    // Добавлен printf внутри для визуализации трассировки
    for(i=0, k=0; i<N_TRACE && k<2; i++) {
        bool condition = (a[i] < 0);
        printf("  Шаг i=%d: a[%d]=%d, условие выполнено? %s", i, i, a[i], condition ? "ДА" : "НЕТ");
        
        if (a[i] < 0) k++;
        
        printf(" -> новое k=%d\n", k);
    }
        
    printf("Конец цикла: i=%d, k=%d\n", i, k);
    
    if (k==2) printf("Вывод: %d, %d\n", i-1, a[i-1]);
    else printf("Вывод: Нет двух отрицательных элементов\n");
}

// --- Задание 4: Анализ сортировки ---
#define N_SORT 5
void task4_sorting() {
    printf("\n=== Задание 4: Проверка сортировки ===\n");
    int i, j, k; 
    char r;
    char a[N_SORT] = {'a', 'e', 'c', 'b', 'd'};
    
    printf("Исходный: ");
    for (i=0; i<N_SORT; i++) printf("%3c,", a[i]);
    printf("\n");

    // Точный код из задания
    for(i=0; i<N_SORT-1; i++) {
        r = a[i]; k = i;
        for (j=i+1; j<N_SORT; j++) 
            if (a[j] > r) { k = j; r = a[j]; } // Примечание: Проверка на '>'
        a[k] = a[i]; a[i] = r;
        
        // Визуализация прохода
        printf("Проход %d:  ", i);
        for (int m=0; m<N_SORT; m++) printf("%3c,", a[m]);
        printf("\n");
    }
    
    printf("Итоговый: ");
    for (i=0; i<N_SORT; i++) printf("%3c,", a[i]);
    printf("\n");
}

// --- Задание 5: Сектор матрицы ---
#define N_MAT 5
void task5_matrix() {
    printf("\n=== Задание 5: Визуализация сектора матрицы ===\n");
    
    // 0 = Не выбрано, 1 = Выбрано
    int matrix[N_MAT][N_MAT] = {0};
    
    for (int i = 0; i < N_MAT; i++) {
        for (int j = 0; j < N_MAT; j++) {
            // Логические условия
            bool cond1 = (i + j < N_MAT - 1); // Выше побочной диагонали
            bool cond2 = (i - j >= 0);        // Ниже или на главной диагонали (i >= j)
            
            if (cond1 && cond2) {
                matrix[i][j] = 1;
            }
        }
    }
    
    printf("Сетка (X = Выбрано, . = Не выбрано):\n");
    printf("    0 1 2 3 4 (j)\n");
    printf("    _ _ _ _ _\n");
    for (int i = 0; i < N_MAT; i++) {
        printf("%d | ", i);
        for (int j = 0; j < N_MAT; j++) {
            if (matrix[i][j]) printf("X ");
            else printf(". ");
        }
        printf("\n");
    }
}

int main() {
    task1_expression();
    task2_conditional();
    task3_trace();
    task4_sorting();
    task5_matrix();
    return 0;
}
