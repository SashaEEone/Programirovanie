#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "student.h"

void zapolnenie (struct Student mass[]){
    char* Familias[] = {"Лыков", "Быков", "Старк", "Крофт"};
    char* Names[] = {"Саша", "Миша", "Влад", "Женя"};
    char* groups[] = {"ИКС-532", "ИКС-531", "БПИ-212", "ИТИ-618"};
    
    for (int i = 0; i < N; i++){
        strcpy(mass[i].Familia, Familias[rand() % 4]);
        strcpy(mass[i].Name, Names[rand() % 4]);
        strcpy(mass[i].group, groups[rand() % 4]);
        mass[i].sredball = 1 + rand() % 100;
    }
}

void printMass(struct Student mass[]){
    printf("\nФамилия\tИмя\tГруппа\tБалл\n");
    printf("----------------------------------------\n");
    for(int i = 0; i < N; i++) {
        printf("%s\t%s\t%s\t%d\n", 
               mass[i].Familia, 
               mass[i].Name, 
               mass[i].group, 
               mass[i].sredball);
    }
}

void sortMass(struct Student mass[]) {
    for(int i = 0; i < N - 1; i++) {
        for(int j = 0; j < N - i - 1; j++) {
            if(mass[j].sredball > mass[j + 1].sredball) {
                struct Student temp = mass[j];
                mass[j] = mass[j + 1];
                mass[j + 1] = temp;
            }
        }
    }
}