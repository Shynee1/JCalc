#pragma once
#include "parser.hpp"

double jcalc(std::string expression) {
    Parser parser = Parser(expression);
    ExpressionNode* node = parser.parse_expression(Precedence_Min);
    double eval = node->evaluate();
    delete node;
    return eval;
}

double jcalc(const char* expression) {
    std::string newExpr = std::string(expression);
    return jcalc(newExpr);
}