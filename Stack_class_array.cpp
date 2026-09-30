#include <iostream>


class Stack{
private:
    char * arr;
    int size;
    int capacity;
public:
    Stack();
    void ins(char value);
    int pop();
    int empty();
    char top();
    void clear();
};


Stack::Stack() : arr(nullptr), size(0), capacity(0){}


void Stack::ins(char value){
    if (size == capacity){
        int new_capacity;
        if (capacity == 0){
            new_capacity = 1;
        }
        else{
            new_capacity = capacity * 2;
        }
        char * new_arr = new char[new_capacity];
        for (int i = 0; i < size; i++){
            new_arr[i] = arr[i];
        }
        delete [] arr;
        arr = new_arr;
        capacity = new_capacity;
    }
    arr[size++] = value;
}


int Stack::pop(){
    if (size == 0) {
        return -1;
    }
    size--;
    return 0;
}


int Stack::empty(){
    return size == 0;
}


char Stack::top(){
    return arr[size - 1];
}


void Stack::clear(){
    delete[] arr;
    arr = nullptr;
    size = 0;
    capacity = 0;
}


int main(){
    int tmp_command = -1;
    char value;
    Stack stack;
    while (std::cin >> tmp_command && tmp_command != 0){
        switch (tmp_command){
            case 1:
                std::cin >> value;
                stack.ins(value);
                break;
            case 2:
                if (!stack.empty()){
                    stack.pop();
                }
                else{
                    std::cout << "Stack is empty\n";
                }
                break;
            case 3:
                if (!stack.empty()){
                    std::cout << stack.top() << '\n';
                }
                else{
                    std::cout << "Stack is empty\n";
                }
                break;
            case 4:
                if (!stack.empty()){
                    std::cout << "0\n";
                }
                else{
                    std::cout << "1\n";
                }
                break;
            case 5:
                stack.clear();
                break;
            default:
                break;
        }
    }
    stack.clear();
    return 0;
}