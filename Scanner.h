#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Token.h"
#include "TokenType.h"

class Scanner {
    private:

        int current = 0;
        int start = 0;

        std::string text;

        std::vector<Token> tokens;

        char c = text[current];

        char advance() {
            return text[current++];
        }

        bool isAtEnd() {
            return current >= text.length();
        }

        void addToken(TokenType type) {
            tokens.push_back(Token(type, 0, ""));
        }

        char peek() {
            return text[current];
        }

        bool match(char exp) {
            if (check(exp)) {
                advance();
                return true;
            }
            return false;
        }

        bool check(char exp) {
            if (isAtEnd()) return false;
            if (peek() == exp) {
                return true;
            }
            return false;
        }

    public:

        std::vector<Token> scanText() {
            while (!isAtEnd()) {
                c = advance();
                switch(c) {
                    case '(': addToken(TokenType::LEFT_PAREN); break;
                    case ')': addToken(TokenType::RIGHT_PAREN); break;
                    case '{': addToken(TokenType::LEFT_BRACE); break;
                    case '}': addToken(TokenType::RIGHT_BRACE); break;                    
                    case '+': addToken(TokenType::PLUS); break;
                    case '-': addToken(TokenType::MINUS); break;
                    case '*': addToken(TokenType::STAR); break;
                    case '%': addToken(TokenType::MOD); break;
                    case '=':
                        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
                    case '!':
                        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
                    case '>':
                        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
                    case '<':
                        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
                    case '/':
                        if (match('/')) {
                            while (peek() != '\n' && !isAtEnd()) advance();
                            break;    
                        } else {
                            addToken(TokenType::SLASH); break;
                            break;
                        }
                        break;
                    default:
                        advance();
                        break;
                }
            }

            return tokens;
        }

        Scanner(std::string txt) : text(txt) {}
};