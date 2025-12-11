#include "univer.h"

#define FILENAME "students.bin"
#define INIT_SIZE 5

void showMenu();

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    printf("\n");
    printf("    БАЗА ДАННЫХ ПОЛИТЕХА\n");
    printf("\n");
    
    struct SmartArray* database = createArray(INIT_SIZE);
    if (database == NULL) {
        printf("Ошибка создания базы данных!\n");
        return 1;
    }
    
    if (loadFromFile(database, FILENAME)) {
        printf("База данных загружена из файла\n");
        printf("Загружено записей: %d\n", database->size);
    } else {
        printf("Создана новая база данных\n");
    }
    
    int choice = -1;
    
    while (choice != 0) {
        showMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода! Введите число от 0 до 7\n");
            while(getchar() != '\n');
            continue;
        }
        
        switch(choice) {
            case 1:
                printAll(database);
                break;
                
            case 2:
                {
                    char faculty[50];
                    printf("Введите название института: ");
                    getchar();
                    fgets(faculty, sizeof(faculty), stdin);
                    faculty[strcspn(faculty, "\n")] = 0;
                    searchFaculty(database, faculty);
                }
                break;
                
            case 3:
                {
                    int course;
                    printf("Введите номер курса: ");
                    scanf("%d", &course);
                    if (course >= MIN_COURSE && course <= MAX_COURSE) {
                        searchCourse(database, course);
                    } else {
                        printf("Неверный номер курса! Введите от %d до %d\n", MIN_COURSE, MAX_COURSE);
                    }
                }
                break;
                
            case 4:
                addStudent(database);
                break;
                
            case 5:
                {
                    int id;
                    printf("Введите ID студента для удаления: ");
                    scanf("%d", &id);
                    removeStudent(database, id);
                }
                break;
                
            case 6:
                {
                    int id;
                    printf("Введите ID студента для редактирования: ");
                    scanf("%d", &id);
                    editStudent(database, id);
                }
                break;
                
            case 7:
                if (saveToFile(database, FILENAME)) {
                    printf("Данные сохранены в файл\n");
                }
                break;
                
            case 0:
                printf("\nВыход из программы...\n");
                saveToFile(database, FILENAME);
                printf("Всего записей в базе: %d\n", database->size);
                break;
                
            default:
                printf("Неверный пункт меню! Выберите от 0 до 7\n");
        }
        
        if (choice != 0) {
            printf("\nНажмите Enter для продолжения...");
            getchar();
            getchar();
        }
    }
    
    freeArray(database);
    
    return 0;
}

void showMenu() {
    printf("\n");
    printf("----------- ГЛАВНОЕ МЕНЮ -----------\n");
    printf("1. Показать всех студентов\n");
    printf("2. Поиск по институту\n");
    printf("3. Поиск по курсу\n");
    printf("4. Добавить нового студента\n");
    printf("5. Удалить студента\n");
    printf("6. Редактировать данные студента\n");
    printf("7. Сохранить данные в файл\n");
    printf("0. Выйти из программы\n");
    printf("-------------------------------------\n");
    printf("Ваш выбор: ");
}
