# include "Expressions.hpp"
# include <iostream>

using namespace std;

Number::Number() {
    number = 0.0;
}

Number::Number(const double& n) {
    number = n;
}

Number::~Number() {}

Expression * Number::diff(char _) {
    return new Number(0.0);
}

void Number::print() {
    std::cout << number;
}

double Number::val() const {
    return number;
}

Expression * Number::re() { return new Number(number); };
Expression * Number::clone() { return new Number(number); }

double Number::eval(std::map<char, double> &vars) {
    return number;
}

Variable::Variable() {
    var = 'x';
}

Variable::Variable(char const var) {
    this->var = var;
}

Variable::~Variable() {}

void Variable::print() {
    std::cout << var;
}

Expression * Variable::diff(char ch) {
    if (ch == var)
        return new Number(1.);
    return new Number(0.);
}

Expression * Variable::re() { return new Variable(var); };
Expression * Variable::clone() { return new Variable(var); }

double Variable::eval(std::map<char, double> &vars) {
    return vars[var];
}

Add::Add(Expression * left, Expression * right) {
    this->left = left;
    this->right = right;
}

Add::~Add() {
    delete left;
    delete right;
}

Expression * Add::diff(char ch) {
    return new Add(left->diff(ch), right->diff(ch));
}

void Add::print() {
    std::cout << "( ";
    left->print();
    std::cout << " ) + ( ";
    right->print();
    std::cout << " )";
}

Expression * Add::re() {
    Expression * left = this->left->re();
    Expression * right = this->right->re();

    bool l0 = false, r0 = false;

    Number * l = dynamic_cast<Number*>(left);
    Number * r = dynamic_cast<Number*>(right);

    if(l) {
       if (l->val() == 0.) {
           l0 = true;
       }
    }

    if(r) {
       if (r->val() == 0.) {
           r0 = true;
       }
    }

    if (l && r) {
        Expression * expr = new Number(l->val() + r->val());
        delete left; delete right;
        return expr;
    }

    if (l0 & r0) {
        delete left; delete right;
        return new Number(0.);
    }

    if (l0) {
        delete left;
        return right;
    }

    if (r0) {
        delete right;
        return left;
    }

    return new Add(left, right);
}

Expression * Add::clone() {
    return new Add(left->clone(), right->clone());
}

double Add::eval(std::map<char, double> &vars) {
    return left->eval(vars) + right->eval(vars);
}


Sub::Sub(Expression * left, Expression * right) {
    this->left = left;
    this->right = right;
}

Sub::~Sub() {
    delete left;
    delete right;
}

Expression * Sub::diff(char ch) {
    return new Sub(left->diff(ch), right->diff(ch));
}

void Sub::print() {
    std::cout << "( ";
    left->print();
    std::cout << ") - (";
    right->print();
    std::cout << " )";
}

Expression * Sub::clone() {
    return new Sub(left->clone(), right->clone());
}

double Sub::eval(std::map<char, double> &vars) {
    return left->eval(vars) - right->eval(vars);
}

Mul::Mul(Expression * left, Expression * right) {
    this->left = left;
    this->right = right;
}

Mul::~Mul() {
    delete left;
    delete right;
}

Expression * Mul::diff(char ch) {
    return new Add(new Mul(left->diff(ch), right), new Mul(left, right->diff(ch)));
}

void Mul::print() {
    std::cout << "( ";
    left->print();
    std::cout << ") * (";
    right->print();
    std::cout << " )";
}

Expression * Mul::re() {
    Expression * left = this->left->re();
    Expression * right = this->right->re();

    bool l0 = false, r0 = false;
    bool l1 = false, r1 =  false;

    Number * l = dynamic_cast<Number*>(left);
    Number * r = dynamic_cast<Number*>(right);

    if (l && r) {
        Expression * expr  = new Number(l->val() * r->val());
        delete left; delete right;
        return expr;
    }

    if(l) {
       if (l->val() == 0.) {
           l0 = true;
       } else if (l->val() == 1.) {
           l1 = true;
       }
    }

    if(r) {
       if (r->val() == 0.) {
           r0 = true;
       } else if (r->val() == 1.) {
           r1 = true;
       }
    }

    if (l0 || r0) {
        delete left; delete right;
        return new Number(0.);
    }

    if (l1) {
        delete left;
        return right;
    }

    if (r1) {
        delete right;
        return left;
    }

    return new Mul(left, right);
}

Expression * Mul::clone() {
    return new Mul(left->clone(), right->clone());
}

double Mul::eval(std::map<char, double> &vars) {
    return left->eval(vars) * right->eval(vars);
}

Div::Div(Expression * left, Expression * right) {
    this->left = left;
    this->right = right;
}

Div::~Div() {
    delete left;
    delete right;
}

Expression * Div::diff(char ch) {
    return
        new Div(
            new Sub(new Mul(left->diff(ch), right), new Mul(left, right->diff(ch))),
            new Mul(right, right)
        );
}

void Div::print() {
    std::cout << "( ";
    left->print();
    std::cout << " ) / ( ";
    right->print();
    std::cout << " )";
}

Expression * Div::re() {
    Expression * left = this->left->re();
    Expression * right = this->right->re();

    bool l0 = false, r1 =  false;

    Number * l = dynamic_cast<Number*>(left);
    Number * r = dynamic_cast<Number*>(right);

    if (l && r) {
        Expression * expr = new Number(l->val() / r->val());
        delete left; delete right;
        return expr;
    }

    if(l) {
       if (l->val() == 0.) {
           l0 = true;
       }
    }


    if(r) {
        if (r->val() == 1.) {
           r1 = true;
       }
    }

    if (l0) {
        delete left; delete right;
        return new Number(0.);
    }
    if (r1) {
        delete right;
        return left;
    }
    return new Div(left, right);
};

Expression * Div::clone() {
    return new Div(left->clone(), right->clone());
}

double Div::eval(std::map<char, double> &vars) {
    return left->eval(vars) / right->eval(vars);
}

Minus::Minus(Expression * e) {
    val = e;
}

Minus::~Minus() {
    delete val;
}

Expression * Minus::diff(char ch) {
    return new Minus(val->diff(ch));
}

void Minus::print() {
    std::cout << '-';
    val->print();
}

Expression * Minus::re() {
    Expression * val = this->val->re();

    if(Minus * v = dynamic_cast<Minus*>(val)) {
       Expression * e = v->val->clone();
       delete val;
       return e;
    }

    if(Number * n = dynamic_cast<Number*>(val)) {
        Expression * e = new Number(-(n->val()));
        delete val;
        return e;
    }

    return new Minus(val);
};
Expression * Minus::clone() { return new Minus(val->clone()); }

double Minus::eval(std::map<char, double> &vars) {
    return -(val->eval(vars));
}

Sin::Sin(Expression * e) {
    val = e;
}

Sin::~Sin() {
    delete val;
}

void Sin::print() {
    std::cout << "sin(";
    val->print();
    std::cout << ")";
}

Expression * Sin::re() {

    Expression * v = val->re();

    if(Number * n = dynamic_cast<Number*>(v)) {
        Expression * e = new Number(sin(n->val()));
        delete v;
        return e;
    }

    return new Sin(v);
};
Expression * Sin::clone() { return new Sin(val->clone()); }

double Sin::eval(std::map<char, double> &vars) {
    return sin(val->eval(vars));
}

Cos::Cos(Expression * e) {
    val = e;
}

Cos::~Cos() {
    delete val;
}

Expression * Cos::diff(char ch) {
    return new Mul(new Minus(new Sin(val)), val->diff(ch));
}

void Cos::print() {
    std::cout << "cos(";
    val->print();
    std::cout << ")";
}

Expression * Cos::re() {
    Expression * v = val->re();

    if(Number * n = dynamic_cast<Number*>(v)) {
        Expression * e = new Number(cos(n->val()));
        delete v;
        return e;
    }

    return new Cos(v);
}
Expression * Cos::clone() { return new Cos(val->clone()); }

double Cos::eval(std::map<char, double> &vars) {
    return cos(val->eval(vars));
}

Expression * Sin::diff(char ch) {
    return new Mul(new Cos(val), val->diff(ch));
}

Expression * Sub::re() {
    Expression * left = this->left->re();
    Expression * right = this->right->re();

    bool l0 = false, r0 = false;
    Number * l = dynamic_cast<Number*>(left);
    Number * r = dynamic_cast<Number*>(right);

    if (l && r) {
        Expression * e = new Number(l->val() - r->val());
        delete left; delete right;
        return e;
    }

    if(l) {
       if (l->val() == 0.) {
           l0 = true;
       }
    }

    if(r) {
       if (r->val() == 0.) {
           r0 = true;
       }
    }

    if (l0 & r0) {
        delete left;
        delete right;
        return new Number(0.);
    }

    if (l0) {
        delete left;
        return new Minus(right);
    }

    if (r0) {
        delete right;
        return left;
    }

    return new Sub(left, right);
}
