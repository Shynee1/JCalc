#include "parser.hpp"

using namespace std;

double UnaryNode::evaluate() {
	switch (this->type) {
		case ExpressionType_Positive: return operand->evaluate();
		case ExpressionType_Negative: return -operand->evaluate();
		default: return 0;
	}
}

double BinaryNode::evaluate() {
	switch (this->type) {
		case ExpressionType_Add: return left->evaluate() + right->evaluate();
		case ExpressionType_Sub: return left->evaluate() - right->evaluate();
		case ExpressionType_Mul: return left->evaluate() * right->evaluate();
		case ExpressionType_Div: return left->evaluate() / right->evaluate();
		case ExpressionType_Pow: return pow(left->evaluate(), right->evaluate());
		default: return 0;
	}
}

Parser::Parser(std::string expression) {
	this->lexer = new Lexer(expression);
	this->currentToken = lexer->next_token();
}

Parser::~Parser() {
	delete lexer;
}

ExpressionNode* Parser::parse_expression(Precedence prev_prec) {
	// Read first operand / advance parser
	ExpressionNode* left = parse_terminal_expression();
	// Read operator and get precendce
	Token curr_op = currentToken;
	Precedence curr_prec = precedence_lookup[currentToken.type];

	while (curr_prec != Precedence_Min) {
		if (prev_prec >= curr_prec) break;

		advance_token();
		// Recursively parse new expression
		left = parse_binary_expression(curr_op, left);
		curr_op = currentToken;
		curr_prec = precedence_lookup[curr_op.type];
	}
	return left;
}

ExpressionNode* Parser::parse_binary_expression(Token op, ExpressionNode* left) {
	BinaryNode* ret = nullptr;
	
	switch (op.type) {
		case TokenType_Plus: ret = new BinaryNode(ExpressionType_Add); break;
		case TokenType_Minus: ret = new BinaryNode(ExpressionType_Sub); break;
		case TokenType_Star: ret = new BinaryNode(ExpressionType_Mul); break;
		case TokenType_Slash: ret = new BinaryNode(ExpressionType_Div); break;
		case TokenType_Caret: ret = new BinaryNode(ExpressionType_Pow); break;
		default: { throw std::invalid_argument("ERROR: Invalid operator '" + op.lexeme + "'"); }
	}
	
	ret->left = left;
	ret->right = parse_expression(precedence_lookup[op.type]);
	return ret;
}

ExpressionNode* Parser::parse_terminal_expression() {
	ExpressionNode* ret = nullptr;

	if (currentToken.type == TokenType_Number) {
		ret = parse_number();
	}
	else if (currentToken.type == TokenType_Parentheses_Open) {
		advance_token();
		ret = parse_expression(Precedence_Min);
		if (currentToken.type == TokenType_Parentheses_Close) advance_token();
	}
	else if (currentToken.type == TokenType_Plus) {
		advance_token();
		ret = new UnaryNode(parse_terminal_expression(), ExpressionType_Positive);
	}
	else if (currentToken.type == TokenType_Minus) {
		advance_token();
		ret = new UnaryNode(parse_terminal_expression(), ExpressionType_Negative);
	}

	// Handle implicit multplication
	if (currentToken.type == TokenType_Number || currentToken.type == TokenType_Parentheses_Open) {
		BinaryNode* new_ret = new BinaryNode(ExpressionType_Mul);
		new_ret->left = ret;
		new_ret->right = parse_expression(Precedence_Factor);
		ret = new_ret;
	}


	return ret;
}

void Parser::advance_token() {
	this->currentToken = lexer->next_token();
}

ExpressionNode* Parser::parse_number() {
	double num = stod(currentToken.lexeme);
	advance_token();
	return new NumberNode(num);
}