#include <stdio.h>
#include <math.h>

/**
 * Задача: Реализация кусочно-заданной функции (Вариант 16)
 * Алгоритм 2: Отложенное сообщение об ошибках
 */

int main() {
    double x, a, b, f_x;
    int range_code;
    int error_code = 0; // 0: Успех, 1: x>=7, 2: ax<0

    // Ввод параметров от пользователя
    printf("Введите x: ");
    if (scanf("%lf", &x) != 1) return 1;
    printf("Введите a: ");
    if (scanf("%lf", &a) != 1) return 1;
    printf("Введите b: ");
    if (scanf("%lf", &b) != 1) return 1;

    // Сразу проверяем ОДЗ для x, но откладываем вывод сообщения
    if (x >= 7) {
        error_code = 1; 
    } else {
        // Сопоставление непрерывного значения x с дискретными кодами для оператора switch
        if (x < 4) {
            range_code = 1;
        } else if (x == 4) {
            range_code = 2;
        } else {
            range_code = 3;
        }

        switch (range_code) {
            case 1:
                f_x = cos(x);
                break;
            case 2:
                f_x = pow(x, 3) - b * x + 1;
                break;
            case 3:
                if (a * x < 0) {
                    error_code = 2;
                } else {
                    f_x = sqrt(a * x);
                }
                break;
        }
    }

    // Отложенный вывод: Результат или сообщение об ошибке
    if (error_code == 1) {
        printf("ОШИБКА: Функция не определена для x >= 7 (x = %.2f).\n", x);
    } else if (error_code == 2) {
        printf("ОШИБКА: Обнаружено отрицательное значение под корнем (ax = %.2f).\n", a * x);
    } else {
        // Вывод результата только в случае отсутствия ошибок
        printf("Вычисление завершено успешно.\n");
        printf("Результат f(x) = %.4f\n", f_x);
    }

    return 0;
}
