#include "lexer.hpp"

using namespace std;

Lexer::Lexer(string& file) {
    this->file = file;
}

Token Lexer::next_token() {
    // Remove leading whitespace
    while (current <= file.length() && isspace(file[current])) current++;
    // Check index bounds
    if (current >= file.length()) return Token(TokenType_End_Of_File, "");

    start = current;
    string lexeme(1, file[start]);
    current++;

    // Tokenize file
    switch (file[start]) {
    case '(': return Token(TokenType_Parentheses_Open, lexeme);
    case ')': return Token(TokenType_Parentheses_Close, lexeme);
    case '+': return Token(TokenType_Plus, lexeme);
    case '-': return Token(TokenType_Minus, lexeme);
    case '*': return Token(TokenType_Star, lexeme);
    case '/': return Token(TokenType_Slash, lexeme);
    case '^': return Token(TokenType_Caret, lexeme);
    default: {
        current--;
        if (isalpha(file[start])) return handle_identifier();
        else if (isdigit(file[start])) return handle_number();
        else return Token(TokenType_Error, "");
    }
    }
}

Token Lexer::handle_number() {
    // Read full digit
    while (isdigit(file[current]) || file[current] == '.') current++;
    return Token(TokenType_Number, file.substr(start, current - start));
}

Token Lexer::handle_identifier() {
    // Read full identifier
    while (isdigit(file[current]) || isalpha(file[current])) current++;
    return Token(TokenType_Identifier, file.substr(start, current - start));
}