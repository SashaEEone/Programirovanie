#ifndef STUDENT_H
#define STUDENT_H

#define N 4

struct Student 
{
    char Familia[20];
    char Name[20];
    char group[15];
    int sredball;
};

void zapolnenie(struct Student mass[]);
void printMass(struct Student mass[]);
void sortMass(struct Student mass[]);

#endif