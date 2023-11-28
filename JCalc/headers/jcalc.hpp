#pragma once
#include "parser.hpp"

double jcalc(std::string expression) {
    Parser parser = Parser(expression);
    auto node = parser.parse_expression(Precedence_Min);
    double eval = node->evaluate();

    return eval;
}

double jcalc(const char* expression) {
    std::string newExpr = std::string(expression);
    return jcalc(newExpr);
}