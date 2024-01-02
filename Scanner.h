#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "Token.h"
#include "TokenType.h"

class Scanner {
    private:
        std::string source;

        int current = 0;
        int start = 0;

        std::vector<Token> tokens;

        std::map<std::string, TokenType> keywords;

        void addToken(TokenType type) {
            tokens.push_back(Token(type, 0, ""));
            current++;
        }

        void addToken(TokenType type, double val) {
            tokens.push_back(Token(type, val, ""));
        }

        void addToken(TokenType type, std::string identifier) {
            tokens.push_back(Token(type, 0, identifier));
        }

        bool isAlpha(char c) {
            return (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '_';
        }

        bool isDigit(char c) {
            return c >= '0' && c <= '9';
        }

    public:
        std::vector<Token> scanTokens() {
            while (source[current] != '\0') {
                char c = source[current];

                switch (c) {
                    case '+': addToken(TokenType::PLUS); break;
                    case '-': addToken(TokenType::MINUS); break;
                    case '*': addToken(TokenType::STAR); break;
                    case '%': addToken(TokenType::MOD); break;
                    case '(': addToken(TokenType::LEFT_PAREN); break;
                    case '{': addToken(TokenType::LEFT_BRACE); break;
                    case '}': addToken(TokenType::RIGHT_BRACE); break;
                    case ')': addToken(TokenType::RIGHT_PAREN); break;
                    case ';': addToken(TokenType::SEMICOLON); break;
                    case '=':
                        if (source[current + 1] == '=') {
                            addToken(TokenType::EQUAL_EQUAL);
                            current++;
                        } else {
                            addToken(TokenType::EQUAL);
                        } break;
                    case '!':
                        if (source[current + 1] == '=') {
                            addToken(TokenType::BANG_EQUAL);
                            current++;
                        } else {
                            addToken(TokenType::BANG);
                        } break;
                    case '>':
                        if (source[current + 1] == '=') {
                            addToken(TokenType::GREATER_EQUAL);
                            current++;
                        } else {
                            addToken(TokenType::GREATER);
                        } break;
                    case '<':
                        if (source[current + 1] == '=') {
                            addToken(TokenType::LESS_EQUAL);
                            current++;
                        } else {
                            addToken(TokenType::LESS);
                        } break;
                    case '/':
                        if (source[current + 1] == '/') {
                            while (source[current] != '\n' && source[current] != '\0') {
                                current++;
                            }
                            current++;
                        } else {
                            addToken(TokenType::SLASH);
                        }
                        break;
                    default:
                        if (isDigit(c)) {
                            start = current;
                            while (isDigit(source[++current]));
                            if (source[current] == '.' && isDigit(source[current + 1])) {
                                current++;
                                while (isDigit(source[++current])); 
                            }
                            addToken(TokenType::LITERAL, std::stod(source.substr(start, current - start)));
                        } else if (isAlpha(source[current])) {
                            start = current;
                            while (isAlpha(source[++current]));
                            std::string txt = source.substr(start, current - start);
                            auto pos = keywords.find(txt);
                            if (pos == keywords.end()) {
                                addToken(TokenType::IDENTIFIER, txt);
                            } else {
                                addToken(pos->second);
                                current--;
                            }
                        } else {
                            current++;
                        }
                        break;
                }
            }

            tokens.push_back(Token(TokenType::END_OF_FILE, 0, ""));
            return tokens;
        }

        Scanner(std::string text) : source(text) {
            keywords["for"] = TokenType::FOR;
            keywords["while"] = TokenType::WHILE;
            keywords["if"] = TokenType::IF;
            keywords["and"] = TokenType::AND;
            keywords["or"] = TokenType::OR;
            keywords["print"] = TokenType::PRINT;
            keywords["num"] = TokenType::NUM;
            keywords["true"] = TokenType::TRUE;
            keywords["false"] = TokenType::FALSE;
        };
};