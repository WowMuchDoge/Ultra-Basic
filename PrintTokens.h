#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Token.h"
#include "TokenType.h"

class PrintTokens {
    private:
        std::vector<Token> tokens;
    public:
        PrintTokens(std::vector<Token> tkns) : tokens(tkns) {}

        void printEm() {
            for (Token token : tokens) {
                switch(token.type) {
                    case TokenType::FOR:
                        std::cout << "for\n";
                        break;
                    case TokenType::WHILE:
                        std::cout << "while\n";
                        break;
                    case TokenType::IF:
                        std::cout << "if\n";
                        break;
                    case TokenType::AND:
                        std::cout << "and\n";
                        break;
                    case TokenType::RIGHT_BRACE:
                        std::cout << "}\n";
                        break;
                    case TokenType::LEFT_BRACE:
                        std::cout << "{\n";
                        break;
                    case TokenType::MINUS:
                        std::cout << "-\n";
                        break;
                    case TokenType::PLUS:
                        std::cout << "+\n";
                        break;
                    case TokenType::STAR:
                        std::cout << "*\n";
                        break;
                    case TokenType::SLASH:
                        std::cout << "/\n";
                        break;
                    case TokenType::MOD:
                        std::cout << "%\n";
                        break;
                    case TokenType::IDENTIFIER:
                        std::cout << token.lexeme << '\n';
                        break;
                    case TokenType::LITERAL:
                        std::cout << token.literal << '\n';
                        break;
                    case TokenType::SEMICOLON:
                        std::cout << ";\n";
                        break;
                    case TokenType::BANG:
                        std::cout << "!";
                        break;
                    case TokenType::BANG_EQUAL:
                        std::cout << "!=\n";
                        break;
                    case TokenType::EQUAL:
                        std::cout << "=\n";
                        break;
                    case TokenType::EQUAL_EQUAL:
                        std::cout << "==\n";
                        break;
                    case TokenType::GREATER:
                        std::cout << ">\n";
                        break;
                    case TokenType::GREATER_EQUAL:
                        std::cout << ">=\n";
                        break;
                    case TokenType::LESS:
                        std::cout << "<\n";
                        break;
                    case TokenType::LESS_EQUAL:
                        std::cout << "<=\n";
                        break;
                    case TokenType::LEFT_PAREN:
                        std::cout << "(\n";
                        break;
                    case TokenType::RIGHT_PAREN:
                        std::cout << ")\n";
                        break;
                    case TokenType::FALSE:
                        std::cout << "false\n";
                        break;
                    case TokenType::TRUE:
                        std::cout << "true\n";
                        break;
                    case TokenType::END_OF_FILE:
                        std::cout << "eof\n";
                        break;
                }
            }
        }
};