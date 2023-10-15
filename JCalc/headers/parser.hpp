#pragma once
#include <iostream>
#include <string>
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
	ExpressionType type;
	virtual double evaluate() = 0;
};

struct NumberNode : public ExpressionNode {
	double number;
	NumberNode(double num) : number(num) { this->type = ExpressionType_Number; };
	double evaluate() { return this->number; };
};

struct UnaryNode : public ExpressionNode {
	ExpressionNode* operand;
	UnaryNode(ExpressionNode* op, ExpressionType eType) : operand(op) { this->type = eType; };
	double evaluate();
};

struct BinaryNode : public ExpressionNode {
	ExpressionNode* right;
	ExpressionNode* left;
	BinaryNode(ExpressionType type) { this->type = type; };
	double evaluate();
};

class Parser {
private:
	Lexer* lexer;
	Token currentToken;
public:
	Parser(std::string expression);
	~Parser();
	void advance_token();
	ExpressionNode* parse_number();
	ExpressionNode* parse_expression(Precedence prev_precedence);
	ExpressionNode* parse_infix_expression(Token operand, ExpressionNode* left);
	ExpressionNode* parse_terminal_expression();
};