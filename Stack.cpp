#include <iostream>

struct list{
    char value;
     list * next;
};

int ins( list** head, char value){
    list* new_list = new list;
    new_list->value = value;
    if (!*head){
        new_list -> next = nullptr;
        *head = new_list;
        return 1;
    }
    new_list -> next = *head;
    *head = new_list;
    return 0;
}


int pop( list** head){
    if (*head == nullptr) {
        return -1;
    }
     list * tmp = *head;
    *head = (*head) -> next;
    free(tmp);
    return 0;
}


void printing( list * head){
    if (head){
        printing(head->next);
        if (head->next){
            printf("; ");
        }
        if (head->value>=0){
            printf("+%d", head->value);
        }
        else{
            printf("%d", head->value);
        }
    }
}


int main(){
    int tmp_command = -1;
    char value;
    list* head = nullptr;
    while (tmp_command != 0){
        std::cin >> tmp_command;
        if (tmp_command == 1){
            scanf(" %c", &value);
            ins(&head, value);
        }
        if (tmp_command == 2){
            if (head != nullptr){
                pop(&head);
            }
            else{
                printf("Stack is empty\n");
            }
        }
        if (tmp_command == 3){
            if (head != nullptr){
                printf("%c\n", head->value);
            }
            else{
                printf("Stack is empty\n");
            }
        }
        if (tmp_command == 4){
            if (head != nullptr){
                printf("0\n");
            }
            else{
                printf("1\n");
            }
        }
        if (tmp_command == 5){
            while (head != nullptr){
                list * tmp = head;
                head = head->next;
                free (tmp);
            }
        }
    }
    list* tmp = head;
    list* next;
    while (tmp){
        next = (*tmp).next;
        free(tmp);
        tmp = next;
    }
    return 0;
}