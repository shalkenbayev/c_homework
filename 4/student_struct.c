#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Максимальная длина для строковых полей */
#define MAX_NAME 50
#define MAX_STUDENTS 100

/* Структура для хранения информации о студенте */
typedef struct {
    char last_name[MAX_NAME];    /* Фамилия */
    char first_name[MAX_NAME];   /* Имя */
    char patronymic[MAX_NAME];   /* Отчество */
    int age;                     /* Возраст */
    int course;                  /* Курс */
    char group[MAX_NAME];        /* Группа */
    double scholarship;          /* Размер стипендии */
} Student;

/* Прототипы функций */
void inputStudent(Student *s);
void displayStudents(const Student students[], int count);
void sortStudents(Student students[], int count, int sortByAge);
void clearBuffer();

/**
 * Главная функция: Интерактивное управление и цикл программы
 * Требования: инициализация первых нескольких объектов, многократное выполнение
 */
int main() {
    /* Инициализированные данные для первых нескольких объектов согласно требованиям варианта */
    Student students[MAX_STUDENTS] = {
        {"Иванов", "Иван", "Иванович", 20, 2, "ИИ-21", 1500.50},
        {"Петров", "Петр", "Петрович", 19, 1, "ИИ-22", 1200.00},
        {"Сидоров", "Сидор", "Сидорович", 21, 3, "ИИ-20", 1800.75}
    };
    int current_count = 3;
    int choice;
    char repeat_str[10] = "y";

    printf("--- Система управления записями студентов ---\n");

    while (repeat_str[0] == 'y' || repeat_str[0] == 'Y' || 
           strcmp(repeat_str, "д") == 0 || strcmp(repeat_str, "Д") == 0) {
        printf("\n1. Добавить нового студента\n");
        printf("2. Показать всех студентов\n");
        printf("3. Сортировать студентов по Фамилии (по убыванию)\n");
        printf("4. Сортировать студентов по Возрасту (по убыванию)\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода. Пожалуйста, введите число.\n");
            clearBuffer();
            continue;
        }
        /* Очистка буфера после scanf для избежания проблем с последующими fgets или scanf */
        clearBuffer();

        /* Определение действия на основе ввода пользователя */
        switch (choice) {
            case 1:
                /* Проверка наличия свободного места в массиве перед добавлением */
                if (current_count < MAX_STUDENTS) {
                    inputStudent(&students[current_count]);
                    current_count++; /* Увеличение счетчика активных студентов */
                } else {
                    printf("Достигнут лимит студентов!\n");
                }
                break;
            case 2:
                /* Вывод списка всех хранящихся студентов */
                displayStudents(students, current_count);
                break;
            case 3:
                /* Применение пузырьковой сортировки с использованием фамилии в качестве ключа */
                sortStudents(students, current_count, 0);
                printf("Студенты отсортированы по Фамилии (по убыванию).\n");
                displayStudents(students, current_count);
                break;
            case 4:
                /* Применение пузырьковой сортировки с использованием возраста в качестве ключа */
                sortStudents(students, current_count, 1);
                printf("Студенты отсортированы по Возрасту (по убыванию).\n");
                displayStudents(students, current_count);
                break;
            case 5:
                /* Завершение программы */
                printf("Выход из программы...\n");
                return 0;
            default:
                /* Обработка числового ввода, не соответствующего ни одному пункту меню */
                printf("Неверный выбор. Попробуйте еще раз.\n");
        }

        /* Запрос у пользователя на продолжение работы */
        printf("\nХотите продолжить? (y/n или д/н): ");
        scanf("%9s", repeat_str);
        clearBuffer(); /* Очистка буфера */
    }

    return 0;
}

/**
 * Функция для ввода данных студента в интерактивном режиме
 */
void inputStudent(Student *s) {
    printf("Введите фамилию: ");
    fgets(s->last_name, MAX_NAME, stdin);
    s->last_name[strcspn(s->last_name, "\n")] = 0;

    printf("Введите имя: ");
    fgets(s->first_name, MAX_NAME, stdin);
    s->first_name[strcspn(s->first_name, "\n")] = 0;

    printf("Введите отчество: ");
    fgets(s->patronymic, MAX_NAME, stdin);
    s->patronymic[strcspn(s->patronymic, "\n")] = 0;

    printf("Введите возраст: ");
    scanf("%d", &s->age);
    clearBuffer();

    printf("Введите курс: ");
    scanf("%d", &s->course);
    clearBuffer();

    printf("Введите группу: ");
    fgets(s->group, MAX_NAME, stdin);
    s->group[strcspn(s->group, "\n")] = 0;

    printf("Введите размер стипендии: ");
    scanf("%lf", &s->scholarship);
    clearBuffer();
}

/**
 * Функция для отображения информации о студентах в табличном формате
 */
void displayStudents(const Student students[], int count) {
    if (count == 0) {
        printf("Нет данных для отображения.\n");
        return;
    }
    
    /* Вывод заголовка таблицы для наглядности */
    printf("\n%-15s %-15s %-15s %-8s %-6s %-10s %-10s\n", 
           "Фамилия", "Имя", "Отчество", "Возраст", "Курс", "Группа", "Стипендия");
    printf("---------------------------------------------------------------------------------------------\n");
    
    /* Проход по массиву и вывод данных каждого студента */
    for (int i = 0; i < count; i++) {
        printf("%-15s %-15s %-15s %-8d %-6d %-10s %-10.2f\n",
               students[i].last_name, students[i].first_name, students[i].patronymic,
               students[i].age, students[i].course, students[i].group, students[i].scholarship);
    }
}

/**
 * Метод пузырька с индикатором перестановки (флагом)
 * Сортирует элементы в порядке убывания.
 */
void sortStudents(Student students[], int count, int sortByAge) {
    int i, j;
    int swapped;
    Student temp;

    /* Внешний цикл по количеству проходов */
    for (i = 0; i < count - 1; i++) {
        swapped = 0; /* Сброс флага в начале каждого прохода */
        
        /* Внутренний цикл для попарного сравнения */
        for (j = 0; j < count - i - 1; j++) {
            int condition = 0;
            
            /* Выбор поля сортировки на основе параметра функции */
            if (sortByAge) {
                /* Сортировка по возрасту в порядке убывания (сначала старшие) */
                if (students[j].age < students[j + 1].age) {
                    condition = 1;
                }
            } else {
                /* Сортировка по фамилии в порядке убывания (от Я до А) */
                if (strcmp(students[j].last_name, students[j + 1].last_name) < 0) {
                    condition = 1;
                }
            }

            /* Если условие выполнено, меняем структуры местами */
            if (condition) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
                swapped = 1; /* Отметка о том, что перестановка произошла */
            }
        }
        
        /* Оптимизация: если не было ни одной перестановки, массив уже отсортирован */
        if (swapped == 0)
            break;
    }
}

/**
 * Вспомогательная функция для очистки буфера ввода
 */
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
