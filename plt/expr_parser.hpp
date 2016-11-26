# ifndef EXPR_PARSER_HPP
# define EXPR_PARSER_HPP
# include "Expressions.hpp"
# include <string>
# include <vector>

enum TokenType {
    NUMBER,
    VARIABLE,
    SUM,
    SUB,
    MUL,
    DIV,
    MINUS,
    L_BRACKET,
    R_BRACKET,
    SIN,
    COS
};

struct Token {
    TokenType type;
    union {
        double number;
        char variable;
    };
    std::string str;
};

Expression * parse_expression(std::string);
# endif // EXPR_PARSER_HPP
