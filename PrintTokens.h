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
                        std::cout << "for " << '\n';
                        break;
                    case TokenType::WHILE:
                        std::cout << "while " << '\n';
                        break;
                    case TokenType::IF:
                        std::cout << "if " << '\n';
                        break;
                    case TokenType::AND:
                        std::cout << "and " << '\n';
                        break;
                    case TokenType::RIGHT_BRACE:
                        std::cout << "} " << "right brace" << '\n';
                        break;
                    case TokenType::LEFT_BRACE:
                        std::cout << "{ " << "left brace" << '\n';
                        break;
                    case TokenType::MINUS:
                        std::cout << "- " << "minus" << '\n';
                        break;
                    case TokenType::PLUS:
                        std::cout << "+ " << "plus" << '\n';
                        break;
                    case TokenType::STAR:
                        std::cout << "* " << "star" << '\n';
                        break;
                    case TokenType::SLASH:
                        std::cout << "/ " << "slash" << '\n';
                        break;
                    case TokenType::MOD:
                        std::cout << "% " << "modulo" << '\n';
                        break;
                    case TokenType::IDENTIFIER:
                        std::cout << token.lexeme << " identifier\n";
                        break;
                    case TokenType::LITERAL:
                        std::cout << token.literal << " literal\n";  
                        break;
                    case TokenType::SEMICOLON:
                        std::cout << "; " << "semicolon" << '\n';
                        break;
                    case TokenType::BANG:
                        std::cout << "! " << "bang" << '\n';
                        break;
                    case TokenType::BANG_EQUAL:
                        std::cout << "!= " << "bang equal" << '\n';
                        break;
                    case TokenType::EQUAL:
                        std::cout << "= " << "equal" << '\n';
                        break;
                    case TokenType::EQUAL_EQUAL:
                        std::cout << "== " << "equal equal" << '\n';
                        break;
                    case TokenType::GREATER:
                        std::cout << "> " << "greater" << '\n';
                        break;
                    case TokenType::GREATER_EQUAL:
                        std::cout << ">= " << "greater eqqual" << '\n';
                        break;
                    case TokenType::LESS:
                        std::cout << "< " << "less" << '\n';
                        break;
                    case TokenType::LESS_EQUAL:
                        std::cout << "<= " << "less equal" << '\n';
                        break;
                    case TokenType::LEFT_PAREN:
                        std::cout << "( " << "left paren" << '\n';
                        break;
                    case TokenType::RIGHT_PAREN:
                        std::cout << ") " << "right paren" << '\n';
                        break;
                    case TokenType::END_OF_FILE:
                        std::cout << "eof " << '\n';
                        break;
                    case TokenType::PRINT:
                        std::cout << "print " << '\n';
                        break;
                    case TokenType::OR:
                        std::cout << "or\n";
                        break;
                    case TokenType::NUM:
                        std::cout << "num\n";
                }
            }
        }
};