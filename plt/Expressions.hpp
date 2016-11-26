# ifndef EXPRESSIONS_HPP
# define EXPRESSIONS_HPP

# include <QTextStream>
# include <map>
# include <cmath>

using namespace std;

class Expression {
public:
    virtual ~Expression() {};

    virtual Expression * diff(char) = 0;
    virtual void print(QTextStream&) = 0;
    virtual Expression * re() = 0;
    virtual Expression * clone() = 0;
    virtual double eval(std::map<char, double> &) = 0;
};


class Number: public Expression {
    double number;
public:
    Number();
    Number(const double&);
    ~Number();
    Expression * diff(char);
    void print(QTextStream&);
    double val() const;
    Expression * re();
    Expression * clone();
    double eval(std::map<char, double>&);
};

class Variable: public Expression {
    char var;
public:
    Variable();
    Variable(char const) ;
    ~Variable();
    void print(QTextStream&);
    Expression * diff(char);
    Expression * re();
    Expression * clone();

    double eval(std::map<char, double>&);
};

class Add: public Expression {
    Expression * left;
    Expression * right;

public:

    Add(Expression *, Expression *);
    ~Add();
    Expression * diff(char);
    void print(QTextStream&);
    Expression * re();
    Expression * clone();
    double eval(std::map<char, double> &);
};

class Sub: public Expression {
    Expression * left;
    Expression * right;

public:

    Sub(Expression *, Expression *);
    ~Sub();
    Expression * diff(char);
    void print(QTextStream&);
    Expression * re();
    Expression * clone();
    double eval(std::map<char, double>&);
};

class Mul: public Expression {
    Expression * left;
    Expression * right;

public:
    Mul(Expression *, Expression *);
    ~Mul();
    Expression * diff(char);
    void print(QTextStream&);
    Expression * re();
    Expression * clone();
    double eval(std::map<char, double>&);
};

class Div: public Expression {
    Expression * left;
    Expression * right;

public:

    Div(Expression *, Expression *);
    ~Div();
    Expression * diff(char);
    void print(QTextStream&);
    Expression * re();
    Expression * clone();
    double eval(std::map<char, double>&);
};

class Minus: public Expression {
    Expression * val;
public:
    Minus(Expression *);
    ~Minus();
    Expression * diff(char);
    void print(QTextStream&);
    Expression * re();
    Expression * clone();
    double eval(std::map<char, double> &);
};

class Sin: public Expression {
    Expression * val;
public:
    Sin(Expression *);
    ~Sin();
    Expression * diff(char);
    void print(QTextStream&);
    Expression * re();
    Expression * clone();
    double eval(std::map<char, double> &);
};

class Cos: public Expression {
    Expression * val;
public:
    Cos(Expression *);
    ~Cos();
    Expression * diff(char);
    void print(QTextStream&);
    Expression * re();
    Expression * clone();

    double eval(std::map<char, double> &);
};

# endif // EXPRESSIONS_HPP
