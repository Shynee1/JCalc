#pragma once
#include <string>
#include <iostream>

enum TokenType {
    TokenType_End_Of_File,
    TokenType_Number,
    TokenType_Identifier,
    TokenType_Error,
    TokenType_Plus,
    TokenType_Minus,
    TokenType_Star,
    TokenType_Slash,
    TokenType_Caret,
    TokenType_Parentheses_Open,
    TokenType_Parentheses_Close
};

struct Token {
    TokenType type;
    std::string lexeme;
    Token(TokenType t, std::string l) : type(t), lexeme(l) {}
    Token() {}
};

class Lexer {
private:
    uint8_t start = 0;
    uint8_t current = 0;
    std::string file;
public:
    Lexer(std::string& file);
    Token handle_number();
    Token handle_identifier();
    Token next_token();
};