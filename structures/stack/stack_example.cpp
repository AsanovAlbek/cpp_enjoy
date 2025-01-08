#include<iostream>
#include "stack.cpp"

int main() {
    Stack<std::string> stack({"first", "second", "third"});
    stack.print();
    std::cout << "Peek top element:" << stack.peek().value_or("no element") << std::endl;
    std::cout << "Pop top element:" << stack.pop().value_or("no element") << std::endl;
    std::cout << "push element" << std::endl;
    stack.push("fourth");
    stack.print();
    stack.forEach([](std::optional<std::string> item) {
        std::cout << item.value_or("no element") << std::endl;
    });
    return 0;
}