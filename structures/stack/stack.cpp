#include<iostream>
#include<optional>

template<typename T>
struct StackNode {
    std::optional<T> value;
    StackNode<T>* next;
    StackNode(T value, StackNode<T>* next) : value(value), next(next) {}
    StackNode(T value) : value(value), next(nullptr) {}
    StackNode() : value(std::nullopt), next(nullptr) {}
};

template<typename T>
struct Stack {
    StackNode<T>* top;
    size_t stackSize;
    Stack() : top(nullptr), stackSize(0) {}

    template<size_t N>
    Stack(const T(&elements)[N]): top(nullptr), stackSize(0) {
        for (int i = 0; i < N; i++) {
            push(elements[i]);
        }
    }

    void push(T element) {
        StackNode<T>* newNode = new StackNode<T>(element);
        if (isEmpty()) {
            top = newNode;
        } else {
            newNode->next = top;
            top = newNode;
        }
        stackSize++;
    }

    template<size_t N>
    void pushAll(const T(&elements)[N]) {
        for (int i = 0; i < N; i++) {
            push(elements[i]);
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }

    std::optional<T> pop() {
        if (isEmpty()) {
            return std::nullopt;
        }
        StackNode<T>* temp = top;
        top = top->next;
        T value = temp->value.value();
        delete temp;
        stackSize--;
        return value;
    }

    std::optional<T> peek() {
        if (isEmpty()) {
            return std::nullopt;
        }
        return top->value;
    }

    void forEach(void (*iteration)(std::optional<T>)) {
        for (StackNode<T>* current = top; current != nullptr; current = current->next) {
            iteration(current->value);
        }
    }

    void print() {
        if (top == nullptr)
            return;
        std::cout << "[";

        for (StackNode<T> *current = top; current != nullptr; current = current->next)
        {

            if (current != top)
                std::cout << ", ";
            std::cout << (current->value.has_value() ? current->value.value() : "nullopt");
        }
        std::cout << "]\n";
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};