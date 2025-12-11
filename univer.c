#include "univer.h"

struct SmartArray* createArray(int cap) {
    struct SmartArray* newArr = (struct SmartArray*)malloc(sizeof(struct SmartArray));
    if (newArr == NULL) {
        return NULL;
    }
    
    newArr->data = (struct Student*)malloc(cap * sizeof(struct Student));
    if (newArr->data == NULL) {
        free(newArr);
        return NULL;
    }
    
    newArr->size = 0;
    newArr->capacity = cap;
    
    return newArr;
}

void freeArray(struct SmartArray* arr) {
    if (arr != NULL) {
        if (arr->data != NULL) {
            free(arr->data);
        }
        free(arr);
    }
}

void addToArray(struct SmartArray* arr, struct Student stud) {
    if (arr->size >= arr->capacity) {
        arr->capacity = arr->capacity * 2;
        struct Student* temp = (struct Student*)realloc(arr->data, 
                                     arr->capacity * sizeof(struct Student));
        if (temp == NULL) {
            return;
        }
        arr->data = temp;
    }
    
    arr->data[arr->size] = stud;
    arr->size++;
}

void removeFromArray(struct SmartArray* arr, int index) {
    if (index < 0 || index >= arr->size) {
        return;
    }
    
    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    
    arr->size--;
}

void printStudent(struct Student* stud) {
    printf("----------------------------------\n");
    printf("ID: %d\n", stud->id);
    printf("ФИО: %s\n", stud->name);
    printf("институт: %s\n", stud->faculty);
    printf("Курс: %d\n", stud->course);
    printf("Средний балл: %.2f из 50\n", stud->avg_score);
    printf("Стипендия: %d руб.\n", stud->scholarship);
    printf("----------------------------------\n");
}

void printAll(struct SmartArray* arr) {
    if (arr->size == 0) {
        printf("База данных пуста!\n");
        return;
    }
    
    printf("\n=== БАЗА ДАННЫХ СТУДЕНТОВ ===\n");
    printf("Всего записей: %d\n\n", arr->size);
    
    for (int i = 0; i < arr->size; i++) {
        printf("Запись №%d:\n", i+1);
        printStudent(&arr->data[i]);
    }
}

void searchFaculty(struct SmartArray* arr, char* faculty) {
    int found = 0;
    
    printf("\nПоиск по институту: %s\n", faculty);
    
    for (int i = 0; i < arr->size; i++) {
        if (strcmp(arr->data[i].faculty, faculty) == 0) {
            printStudent(&arr->data[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Студентов в институте не найдено\n");
    }
}

void searchCourse(struct SmartArray* arr, int course) {
    int found = 0;
    
    printf("\nПоиск по %d курсу:\n", course);
    
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i].course == course) {
            printStudent(&arr->data[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Студентов на курсе не найдено\n");
    }
}

void addStudent(struct SmartArray* arr) {
    struct Student newStudent;
    
    printf("\nДобавление нового студента\n");
    
    newStudent.id = getNewId(arr);
    
    printf("Введите ФИО студента: ");
    getchar();
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    
    printf("Введите институт: ");
    fgets(newStudent.faculty, sizeof(newStudent.faculty), stdin);
    newStudent.faculty[strcspn(newStudent.faculty, "\n")] = 0;
    
    do {
        printf("Введите курс (%d-%d): ", MIN_COURSE, MAX_COURSE);
        scanf("%d", &newStudent.course);
        if (newStudent.course < MIN_COURSE || newStudent.course > MAX_COURSE) {
            printf("Ошибка! Курс должен быть от %d до %d\n", MIN_COURSE, MAX_COURSE);
        }
    } while (newStudent.course < MIN_COURSE || newStudent.course > MAX_COURSE);
    
    do {
        printf("Введите средний балл (%d-%d): ", MIN_SCORE, MAX_SCORE);
        scanf("%f", &newStudent.avg_score);
        if (newStudent.avg_score < MIN_SCORE || newStudent.avg_score > MAX_SCORE) {
            printf("Ошибка! Балл должен быть от %d до %d\n", MIN_SCORE, MAX_SCORE);
        }
    } while (newStudent.avg_score < MIN_SCORE || newStudent.avg_score > MAX_SCORE);
    
    printf("Введите размер стипендии: ");
    scanf("%d", &newStudent.scholarship);
    
    addToArray(arr, newStudent);
    
    printf("Студент успешно добавлен!\n");
    printf("Присвоен ID: %d\n", newStudent.id);
}

void removeStudent(struct SmartArray* arr, int id) {
    int found = 0;
    
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i].id == id) {
            printf("Вы действительно хотите удалить студента?\n");
            printf("ФИО: %s\n", arr->data[i].name);
            printf("ID: %d\n", arr->data[i].id);
            printf("1 - Да, 0 - Нет: ");
            
            int confirm;
            scanf("%d", &confirm);
            
            if (confirm == 1) {
                removeFromArray(arr, i);
                printf("Студент удален\n");
            } else {
                printf("Удаление отменено\n");
            }
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Студент с ID %d не найден!\n", id);
    }
}

void editStudent(struct SmartArray* arr, int id) {
    int found = 0;
    
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i].id == id) {
            printf("\nРедактирование студента\n");
            printf("Текущие данные:\n");
            printStudent(&arr->data[i]);
            
            printf("\nВведите новые данные:\n");
            
            printf("Новое ФИО: ");
            char temp[100];
            getchar();
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = 0;
            if (strlen(temp) > 0) {
                strcpy(arr->data[i].name, temp);
            }
            
            printf("Новый институт: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = 0;
            if (strlen(temp) > 0) {
                strcpy(arr->data[i].faculty, temp);
            }
            
            printf("Новый курс (%d-%d, 0 - не менять): ", MIN_COURSE, MAX_COURSE);
            int newCourse;
            scanf("%d", &newCourse);
            if (newCourse != 0) {
                if (newCourse >= MIN_COURSE && newCourse <= MAX_COURSE) {
                    arr->data[i].course = newCourse;
                }
            }
            
            printf("Новый средний балл (%d-%d, -1 - не менять): ", MIN_SCORE, MAX_SCORE);
            float newScore;
            scanf("%f", &newScore);
            if (newScore != -1) {
                if (newScore >= MIN_SCORE && newScore <= MAX_SCORE) {
                    arr->data[i].avg_score = newScore;
                }
            }
            
            printf("Новая стипендия (0 - не менять): ");
            int newScholarship;
            scanf("%d", &newScholarship);
            if (newScholarship > 0) {
                arr->data[i].scholarship = newScholarship;
            }
            
            printf("Данные успешно обновлены!\n");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Студент с ID %d не найден!\n", id);
    }
}

int saveToFile(struct SmartArray* arr, char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }
    
    fwrite(&arr->size, sizeof(int), 1, file);
    
    for (int i = 0; i < arr->size; i++) {
        fwrite(&arr->data[i], sizeof(struct Student), 1, file);
    }
    
    fclose(file);
    return 1;
}

int loadFromFile(struct SmartArray* arr, char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }
    
    int fileSize;
    fread(&fileSize, sizeof(int), 1, file);
    
    while (arr->capacity < fileSize) {
        arr->capacity *= 2;
        arr->data = (struct Student*)realloc(arr->data, 
                      arr->capacity * sizeof(struct Student));
    }
    
    for (int i = 0; i < fileSize; i++) {
        fread(&arr->data[i], sizeof(struct Student), 1, file);
    }
    
    arr->size = fileSize;
    
    fclose(file);
    return 1;
}

int getNewId(struct SmartArray* arr) {
    int maxId = 0;
    
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i].id > maxId) {
            maxId = arr->data[i].id;
        }
    }
    
    return maxId + 1;
}
