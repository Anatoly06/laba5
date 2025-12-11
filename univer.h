#ifndef UNIVER_H
#define UNIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MIN_COURSE 1
#define MAX_COURSE 6
#define MIN_SCORE 0
#define MAX_SCORE 50

struct Student {
    int id;
    char name[100];
    char faculty[50];
    int course;
    float avg_score;
    int scholarship;
};

struct SmartArray {
    struct Student* data;
    int size;
    int capacity;
};

struct SmartArray* createArray(int cap);
void freeArray(struct SmartArray* arr);
void addToArray(struct SmartArray* arr, struct Student stud);
void removeFromArray(struct SmartArray* arr, int index);

void printStudent(struct Student* stud);
void printAll(struct SmartArray* arr);

void searchFaculty(struct SmartArray* arr, char* faculty);
void searchCourse(struct SmartArray* arr, int course);

void addStudent(struct SmartArray* arr);
void removeStudent(struct SmartArray* arr, int id);
void editStudent(struct SmartArray* arr, int id);

int saveToFile(struct SmartArray* arr, char* filename);
int loadFromFile(struct SmartArray* arr, char* filename);

int getNewId(struct SmartArray* arr);

#endif
