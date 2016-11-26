# include <iostream>

# include "Expressions.hpp"
# include "expr_parser.hpp"
# include <string>
# include <vector>
# include <cstdlib>

int main(int argc, char** argv) {

    system("clear");

    std::string str;

    while (true) {
        std::cout << ">> Enter expression (empty string for exit)" << std::endl << "<< ";
        std::getline(std::cin, str);
        if (!str.length()) break;

        for (int i = 0; i < 30; ++i) std::cout << '-';
        std::cout <<std::endl;

        try {
            Expression * expr = parse_expression(str);
            std::cout << ">> Expr: ";
            expr->print();
            Expression * re = expr->re();
            std::cout << std::endl << ">> Expr re: ";
            re->print();
            std::cout << std::endl << ">> Diff(x): ";
            re->diff('x')->print();
            std::cout << std::endl << ">> Diff(x) re: ";
            re->diff('x')->re()->print();
            std::cout << std::endl;

            delete expr;
            delete re;
        } catch (std::string err) {
            std::cerr << "Error: " << err << std::endl;
        }

        for (int i = 0; i < 30; ++i) std::cout << '-';
        std::cout <<std::endl;
    }

    return 0;
}
