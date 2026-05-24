#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "student.h"

int main() {
    srand(time(NULL));
    
    struct Student students[N];
    
    printf("До сортировки:");
    zapolnenie(students);
    printMass(students);
    
    sortMass(students);
    
    printf("\nПосле сортировки по среднему баллу (по возрастанию):");
    printMass(students);
    
    return 0;
}