#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include "lexer.hpp"

enum ExpressionType {
	ExpressionType_Error, 
	ExpressionType_Number,
	ExpressionType_Positive,
	ExpressionType_Negative,
	ExpressionType_Add,
	ExpressionType_Sub,
	ExpressionType_Mul,
	ExpressionType_Div,
	ExpressionType_Pow
};

enum Precedence {
	Precedence_Min,    // Special
	Precedence_Term,   // + and -
	Precedence_Factor, // * and /
	Precedence_Power   // ^
};

static Precedence precedence_lookup[] = { 
	Precedence_Min,		// TokenType::End_Of_File
	Precedence_Min,		// TokenType:Number
	Precedence_Min,		// TokenType::Identifier
	Precedence_Min,		// TokenType:Error
	Precedence_Term,	// TokenType::Plus
	Precedence_Term,	// TokenType::Minus
	Precedence_Factor,	// TokenType::Star
	Precedence_Factor,	// TokenType::Slash
	Precedence_Power,	// TokenType::Caret
	Precedence_Min,		// TokenType::Parentheses_Open
	Precedence_Min		// TokenType::Parentheses_Closed
};

struct ExpressionNode {
	ExpressionType type = ExpressionType_Error;
	virtual double evaluate() = 0;
};

struct NumberNode : public ExpressionNode {
	double number;
	NumberNode(double num) : number(num) { this->type = ExpressionType_Number; };
	double evaluate() { return this->number; };
};

struct UnaryNode : public ExpressionNode {
	std::unique_ptr<ExpressionNode> operand;
	UnaryNode(std::unique_ptr<ExpressionNode> op, ExpressionType eType) { this->type = eType; this->operand = std::move(op); };
	double evaluate();
};

struct BinaryNode : public ExpressionNode {
	std::unique_ptr<ExpressionNode> left;
	std::unique_ptr<ExpressionNode> right;
	BinaryNode(ExpressionType type) { this->type = type; };
	double evaluate();
};

class Parser {
private:
	std::unique_ptr<Lexer> lexer;
	Token currentToken;
public:
	Parser(std::string expression);
	void advance_token();
	std::unique_ptr<ExpressionNode> parse_number();
	std::unique_ptr<ExpressionNode> parse_expression(Precedence prev_precedence);
	std::unique_ptr<ExpressionNode> parse_binary_expression(Token operand, std::unique_ptr<ExpressionNode> &left);
	std::unique_ptr<ExpressionNode> parse_terminal_expression();
};