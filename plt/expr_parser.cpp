# include "expr_parser.hpp"
# include <vector>
# include <cctype>
# include <exception>
# include <cstdio>
# include <QDebug>

using namespace std;

double stod ( string &num){
      return QString(num.c_str()).toDouble();
}


inline bool is_operator(Token token) {
    return token.type == SUM || token.type == SUB || token.type == MUL || token.type == DIV
        || token.type == MINUS || token.type == L_BRACKET || token.type == R_BRACKET;
}

inline int get_precendence(Token t) {
    if (t.type == NUMBER) return 0;
    if (t.type == VARIABLE) return 0;
    if (t.type == L_BRACKET) return 1;
    if (t.type == R_BRACKET) return 1;
    if (t.type == COS) return 1;
    if (t.type == SIN) return 1;
    if (t.type == SUM) return 3;
    if (t.type == SUB) return 3;
    if (t.type == MUL) return 2;
    return 2;
}

void skip_whitespace(string &str, int &pos) {
    while (isspace(str[pos]) && pos < str.length()) ++pos;
}

std::vector<Token> tokenize(string& str) {
    vector<Token> tokens;
    int pos = 0;
    int const length = str.length();
    while (pos < length) {
        skip_whitespace(str, pos);

        Token token;

        if (isalpha(str[pos])) {
            char var = str[pos];

            if (pos + 1 == length || !isalpha(str[pos + 1])) {
                token.type = VARIABLE;
                token.variable = var;
                token.str = var;
                tokens.push_back(token);
                ++pos;
            } else {
                string func = "";
                func += var;
                while (++pos < length && isalpha(str[pos])) {
                    func += str[pos];
                }
                token.str = func;
                if (!func.compare("cos")) {
                    token.type = COS;
                }
                else if (!func.compare("sin")) {
                    token.type = SIN;
                }
                else throw string("Unknown name: \"") + func + "\"";
                tokens.push_back(token);
            }
        } else if (isdigit(str[pos]) || (str[pos] == '.' && pos + 1 < length && isdigit(str[pos + 1]))) {
            string num = "";
            num += str[pos++];
            bool point_found = false;
            while (isdigit(str[pos]) || str[pos] == '.') {
                if (str[pos] == '.') {
                    if (!point_found) {
                        point_found = true;
                    } else throw string("Too many points in number");
                }
                num += str[pos++];
            }
            token.type = NUMBER;
            token.number = stod(num);
            token.str = num;
            tokens.push_back(token);
        } else {
            switch (str[pos]) {
                case '+': {
                    token.type = SUM;
                    token.str = "+";
                    break;
                }
                case '-': {
                    token.type = SUB;
                    token.str = "-";
                    break;
                }
                case '*': {
                    token.type = MUL;
                    token.str = "*";
                    break;
                }
                case '/': {
                    token.type = DIV;
                    token.str = "/";
                    break;
                }
                case '(': {
                    token.type = L_BRACKET;
                    token.str = "(";
                    break;
                }
                case ')': {
                    token.type = R_BRACKET;
                    token.str = ")";
                    break;
                }
                default: throw string("Unexppected character: ") + str[pos];
            }
            tokens.push_back(token);
            ++pos;
        }
    }
    return tokens;
}

int get_token_with_highest_precendence(vector<Token> &tokens, int start, int stop) {
    int prec = -1;
    int index = 0;
    int brackets = 0;
    //cout << "get_token_with_highest_precendence: ";
    for (int i = start; i < stop; ++i) {
        //cout << tokens[i].str << " ("<< i << ") ";
        int p = get_precendence(tokens[i]);
        if (p > prec || (p == prec && p > 1)) {
            prec = p;
            index = i;
        }
        if (tokens[i].type == L_BRACKET) {
            brackets = 1; ++i;
            while (brackets > 0 && i < stop) {
                if (tokens[i].type == L_BRACKET) ++brackets;
                if (tokens[i].type == R_BRACKET) --brackets;
                ++i;
            }
            if (brackets > 0) throw string("Unbalanced brackets");
            --i;
        }
    }
    //cout << endl;
    return index;
}

int find_close_bracket(vector<Token>& tokens, int start, int stop) {
    int pos = start + 1;
    int brackets = 1;
    while (brackets > 0 && pos < stop) {
        if (tokens[pos].type == L_BRACKET) ++brackets;
        if (tokens[pos].type == R_BRACKET) --brackets;
        ++pos;
    }
    if (brackets > 0) throw string("Unbalanced brackets");
    --pos;
    return pos;
}

Expression * build_expression(vector<Token>& tokens, int start, int stop) {

    if (start - stop == 0)
        throw string("Trying to parse empty expression");

    //std::cout << start << " " << stop << std::endl;

    if (stop - start == 1) {
        Token &token = tokens[start];
        if (token.type == VARIABLE) {
            return new Variable(token.variable);
        }
        if (token.type == NUMBER) {
            return new Number(token.number);
        }

        throw string("Unexpected single token: ") + token.str;
    }

    int index = get_token_with_highest_precendence(tokens, start, stop);
    Token &token = tokens[index];
    //cout << get_precendence(token) << " " << token.str << " " << index << endl;

    if (index == start) {
        if (token.type == SUB) {
            return new Minus(build_expression(tokens, start + 1, stop));
        }

        else if (token.type == COS) {
            if (tokens[index + 1].type != L_BRACKET) throw string("Expect open bracket after COS but ") + token.str + " given";
            int close_bracket = find_close_bracket(tokens, index + 1, stop);
            if (close_bracket != stop - 1) {
                throw string("Cos brackets parsing error");
            }
            return new Cos(build_expression(tokens, index + 2, close_bracket));
        }

        else if (token.type == SIN) {
            if (tokens[index + 1].type != L_BRACKET) throw string("Expect open bracket after sin but ") + token.str + " given";
            int close_bracket = find_close_bracket(tokens, index + 1, stop);
            if (close_bracket != stop - 1) {
                throw string("Sin brackets parsing error");
            }
            return new Sin(build_expression(tokens, index + 2, close_bracket));
        }

        else if (token.type == L_BRACKET) {
            int close_bracket = find_close_bracket(tokens, index, stop);
            //cout << "close_bracket = " << close_bracket << endl;
            if (close_bracket != stop - 1) throw string("Unbalansed brackets");
            return build_expression(tokens, index + 1, close_bracket);
        }

        throw string("Unexpected token with start index: ") + token.str;
    }

    Expression * left = build_expression(tokens, start, index);
    Expression * right = build_expression(tokens, index + 1, stop);

    if (token.type == SUM) return new Add(left, right);
    if (token.type == SUB) return new Sub(left, right);
    if (token.type == MUL) return new Mul(left, right);
    if (token.type == DIV) return new Div(left, right);

    throw string("Unexpected token ") + token.str;
}

Expression * build_expression(vector<Token> tokens) {
    return build_expression(tokens, 0, tokens.size());
}

Expression * parse_expression(string str) {
    return build_expression(tokenize(str));
}
