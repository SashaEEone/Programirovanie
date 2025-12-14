#include <stdio.h>
// Принимает: массив и его размер
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Объявляем массив из нескольких чисел
    int a[] = {4, 2, 0, 9, 5, 1, 7, 3, 8};
    int n = sizeof(a) / sizeof(a[0]); // Вычисляем размер массива
    
    printf("Исходный массив: ");
    printArray(a, n);
    
    // Вызываем функцию сортировки
    bubbleSort(a, n);
    
    printf("Отсортированный массив: ");
    printArray(a, n);
    
    return 0;
}