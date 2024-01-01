#pragma once

#include <iostream>
#include <string>
#include <map>
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

        std::map<std::string, TokenType> keywords;

        char advance() {
            return text[current++];
        }

        bool isAtEnd() {
            return current >= text.length();
        }

        void addToken(TokenType type) {
            tokens.push_back(Token(type, 0, ""));
        }

        void addToken(TokenType type, double literal) {
            tokens.push_back(Token(type, literal, ""));
        }

        void addToken(TokenType type, std::string identifier) {
            tokens.push_back(Token(type, 0, identifier));
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

        bool isDigit(char chr) {
            return chr >= '0' && chr <= '9';
        }

        bool isAlpha(char chr) {
            return (chr >= 'A' && chr <= 'Z') ||
                   (chr >= 'a' && chr <= 'z') ||
                    chr == '_'; 
        }

        void number() {
            start = current - 1;
            while (isDigit(peek())) advance();
            if (c == '.') {
                while (isDigit(peek())) advance();
            }
            addToken(TokenType::LITERAL, std::stod(text.substr(start, current - start)));
        }

        void identifier() {
            start = current - 1;
            while (isAlpha(peek())) advance();

            std::string idtfr = text.substr(start, current - start);

            auto pos = keywords.find(idtfr);
            if (pos == keywords.end()) {
                addToken(TokenType::IDENTIFIER, idtfr);
                advance();
            } else {
                addToken(pos->second, pos->first);
                advance();
            }
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
                        if (isDigit(c)) {
                            number();
                        } else if (isAlpha(c)) {
                            identifier();
                        }
                        else {
                            advance();
                        }
                        break;
                }
            }

            return tokens;
        }

        Scanner(std::string txt) : text(txt) {
            keywords["for"] = TokenType::FOR;
            keywords["while"] = TokenType::WHILE;
            keywords["if"] = TokenType::IF;
            keywords["and"] = TokenType::AND;
            keywords["false"] = TokenType::FALSE;
            keywords["true"] = TokenType::TRUE;
            keywords["print"] = TokenType::PRINT;
        }
};