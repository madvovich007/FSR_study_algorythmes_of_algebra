#include <iostream>


class Stack{
private:
    char * arr;
    int size;
    int capacity;
public:
    Stack();
    Stack(int begin_capacity);
    Stack(Stack & stack2);
    Stack(Stack && stack2);
    Stack(int n, char * value);
    void ins(char value);
    int pop();
    int empty();
    char top();
    void clear();
    ~Stack();
};


Stack::Stack() : arr(nullptr), size(0), capacity(0){}

Stack::Stack(int initial_capacity){
    if (initial_capacity <= 0){
        arr = nullptr;
        size = 0;
        capacity = 0;
    }
    else{
        capacity = initial_capacity;
        size = 0;
        arr = new char[capacity];
    }
}

Stack::Stack(Stack&& stack2){
    arr = stack2.arr;
    size = stack2.size;
    capacity = stack2.capacity;

    stack2.arr = nullptr;
    stack2.size = 0;
    stack2.capacity = 0;
}

Stack::Stack(Stack & stack2){
    size = stack2.size;
    capacity = stack2.capacity;

    arr = new char[capacity];
    if (capacity > 0) {
        for (int i = 0; i < size; i++) {
            arr[i] = stack2.arr[i];
        }
    }
    else{
        arr = nullptr;
    }
}

Stack::Stack(int n, char* value){
    if (n <= 0){
        arr = nullptr;
        size = 0;
        capacity = 0;
    }
    else{
        size = n;
        capacity = n + 1;
        arr = new char[capacity];
        for (int i = 0; i < size; i++){
            arr[i] = value[i];
        }
    }
}

Stack::~Stack(){
    delete[] arr;
    arr = nullptr;
    size = 0;
    capacity = 0;
}


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
    return 0;
}