#include <stdio.h>

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        printf("Ошибка: Деление на ноль!\n");
        return 0;
    }
    return a / b;
}
/*
int main() {
    double num1, num2, result;
    char operation;
    
    printf("Простейший калькулятор\n");
    printf("Доступные операции: +, -, *, /\n");
    printf("Формат ввода: число операция число\n");
    printf("Пример: 5 + 3\n\n");
    
    printf("Введите выражение: ");
    scanf("%lf %c %lf", &num1, &operation, &num2);
    
    switch(operation) {
        case '+':
            result = add(num1, num2);
            printf("%.2lf + %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '-':
            result = subtract(num1, num2);
            printf("%.2lf - %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '*':
            result = multiply(num1, num2);
            printf("%.2lf * %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '/':
            result = divide(num1, num2);
            if (num2 != 0) {
                printf("%.2lf / %.2lf = %.2lf\n", num1, num2, result);
            }
            break;
        default:
            printf("Ошибка: Неподдерживаемая операция '%c'\n", operation);
    }
    
    return 0;
}
*/