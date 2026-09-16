#include <iostream>


struct list {
    char value;
    list *next;
};


class Stack{
private:
    list *head;
public:
    Stack();
    void ins(char value);
    int pop();
    int empty();
    char top();
    void clear();
};


Stack::Stack() : head(nullptr){}


void Stack::ins(char value){
    list* new_list = new list;
    new_list->value = value;
    new_list -> next = head;
    head = new_list;
}


int Stack::pop(){
    if (head == nullptr) {
        return -1;
    }
    list * tmp = head;
    head = head -> next;
    delete tmp;
    return 0;
}


int Stack::empty(){
    return head == nullptr;
}


char Stack::top(){
    return head -> value;
}


void Stack::clear(){
    while (head != nullptr){
        list* tmp = head;
        head = head->next;
        delete tmp;
    }
}


int main(){
    Stack stack;
    int tmp_command = -1;
    while (std::cin >> tmp_command && tmp_command != 0){
        if (tmp_command == 1){
            char value;
            std::cin >> value;
            stack.ins(value);
        }
        if (tmp_command == 2){
            if (!stack.empty()){
                stack.pop();
            }
            else{
                std::cout << "Stack is empty\n";
            }
        }
        if (tmp_command == 3){
            if (!stack.empty()){
                std::cout << stack.top() << '\n';
            }
            else{
                std::cout << "Stack is empty\n";
            }
        }
        if (tmp_command == 4){
            if (!stack.empty()){
                std::cout << "0\n";
            }
            else{
                std::cout << "1\n";
            }
        }
        if (tmp_command == 5){
            stack.clear();
        }
    }
    stack.clear();
    return 0;
}