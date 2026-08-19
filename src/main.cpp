#include <iostream>
#include <string>

#include "./tokenizer.h"
#include "./value.h"
#include "./parser.h"

using ValuePtr = std::shared_ptr<Value>;

int main() {
    while (true) {
        try {
            std::cout << ">>> " ;
            std::string line;
            std::getline(std::cin, line);
            if (std::cin.eof()) {
                std::exit(0);
            }

            // 词法分析器
            auto tokens = Tokenizer::tokenize(line);
            for (auto& token : tokens) {
                std::cout << *token << std::endl;
            }

            // 语法分析器
            Parser parser(std::move(tokens));
            auto value = parser.parse();
            std::cout << value->toString() << std::endl;

        }
        catch (std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
