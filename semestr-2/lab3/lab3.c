#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct room {
    char name[50];      // имя комнаты
    int level;          // уровень/сложность комнаты
    int number;         // номер комнаты
    int resolution;     // размер комнаты
    struct room* next;  
};

struct room *create_node(char name[], int level, int number, int resolution) {
    struct room *new_node = (struct room *)malloc(sizeof(struct room));
    if (new_node == NULL) {
        return NULL;
    }
    strcpy(new_node->name, name);
    new_node->level = level;
    new_node->number = number;
    new_node->resolution = resolution;
    new_node->next = NULL;
    return new_node;
}

struct room *add_to_end(struct room *head, char name[], int level, int number, int resolution) {
    struct room *new_node = create_node(name, level, number, resolution);
    if (new_node == NULL) {
        return head;  
    }

    if (head == NULL) {
        return new_node;
    }
    
    struct room *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    return head;
}
void print_list(struct room *head) {
    if (head == NULL) {
        printf("Список пуст!\n");
        return;
    }
    
    struct room *current = head;
    int count = 1;
    
    printf("\n=== Список комнат ===\n");
    while (current != NULL) {
        printf("%d. Название: %s\n", count, current->name);
        printf("   Уровень: %d\n", current->level);
        printf("   Номер: %d\n", current->number);
        printf("   Размер: %d\n", current->resolution);
        printf("   -----------------\n");
        
        current = current->next;
        count++;
    }
    printf("Всего комнат: %d\n", count - 1);
}

void free_list(struct room *head) {
    struct room *current = head;
    while (current != NULL) {
        struct room *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int n;
    char komnaty[10][30] = {
        "Прихожая", "Гостиная", "Спальня", "Кухня", "Ванная",
        "Туалет", "Детская", "Кабинет", "Балкон", "Кладовая"
    };
    

    printf("Введите количество комнат: ");
    scanf("%d", &n);

    struct room *head = NULL;
    
    for(int i = 0; i < n; i++) {

        head = add_to_end(head,
                         komnaty[rand() % 10],      
                         rand() % 15,               
                         rand() % 1000,              
                         rand() % 10 + 1);         
    }
    

    print_list(head);
    
    free_list(head);
    
    return 0;
}