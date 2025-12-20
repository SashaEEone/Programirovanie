#include <stdio.h>
#include <math.h>

struct Vector{
    int x;
    int y;
    int z;
};

void CreateVector(struct Vector mass[], int M){
    for (int i = 0; i < M; i++){
        printf("Вектор %d, введите - x, y, z: ", i+1);
        scanf("%d %d %d", &mass[i].x, &mass[i].y, &mass[i].z);
    }
}

double Length(struct Vector v){
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); 
}

int main(){
    int M;
    printf("Введите кол-во векторов: \n");
    scanf ("%d", &M);
    struct Vector mass[M];
    CreateVector (mass, M);
    int nomerlongs = 0;
    double makslength = Length(mass[0]);
    for (int i = 1; i < M; i++){
        double realverylong = Length(mass[i]);
        if (realverylong > makslength){
            makslength = realverylong;
            nomerlongs = i;
        }

    }
    printf("Самый длинный вектор - %d\n", nomerlongs + 1);
    printf("Длина: %.1f\n", makslength);
}