#include <iostream>
#include <string>

int main() {
    std::string seasons[] = {"winter", "spring", "summer", "autumn"};
    std::string text;
    std::cout << "Введите текст:" << std::endl;
    std::getline(std::cin, text);
    for (int i = 0; i < size(seasons); i++) {
        if (text.find(seasons[i]) != std::string::npos) {
            std::cout << "season " << seasons[i] << " found" << std::endl;
        }
    }
    return 0;
}