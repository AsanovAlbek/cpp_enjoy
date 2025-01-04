#include<iostream>
#include "list.cpp"
#include <cstdio>

int main() {
    system("chcp 1251 > nul");
    List<int> list;
    int arr[] = { 1, 2, 3, 4, 5};
    list.add(arr, std::size(arr));
    list.print();
    int sum = list.reduce<int>(0, [](int acc, int num) { return acc + num; });
    std::cout << "Сумма чисел: " << sum << std::endl;
    List<double> mappedList = list.map<double>([](int num) {return num * 0.5;});
    std::cout << "Измененный список: " << mappedList.toString() << std::endl;
    List<int> filteredList = list.filter([](int num) {return num % 2 != 0;});
    std::cout << "Отфильтрованный список: " << filteredList.toString() << std::endl;
    list.bubbleSort();
    list.print();
    list.remove(4);
    list.print();
    list.forLoop([](int index, int num) {printf("for loop index:%d, item:%d\n", index, num);});
    list.forEach([](int num) {printf("forEach item:%d\n", num);});
    List<int> shuffledList = list.shuffle();
    std::cout << "Перемешанный список: " << shuffledList.toString() << std::endl;
    List<int> reversedList = list.reversed();
    std::cout << "Обратный список: " << reversedList.toString() << std::endl;
    shuffledList.quickSort();
    std::cout << "Отсортированный перемешанный список: " << shuffledList.toString() << std::endl;
    return 0;
}