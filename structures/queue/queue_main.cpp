#include <iostream>
#include "queue.cpp"

int main()
{
    Queue<std::string> queue({"a", "b", "c", "d", "e"});
    queue.print();
    std::cout << "Peek from queue: " << queue.peek().value_or("no value") << std::endl;
    queue.print();
    std::cout << "Offer from queue: " << queue.offer().value_or("no value") << std::endl;
    queue.print();
    std::cout << "Add to queue: " << std::endl;
    queue.add("f");
    queue.print();
    std::cout << "Add all to queue: " << std::endl;
    queue.addAll({"g", "h", "i"});
    queue.print();
    std::cout << "for each\n";
    queue.forEach([](std::optional<std::string> item)
                  { std::cout << "letter " << item.value_or("no val") << std::endl; });
    return 0;
}