#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "Token.h"
#include "TokenType.h"
#include "Environment.h"

class Expr {
    public:
        virtual std::string printExpr() = 0;
        virtual double eval() = 0;
        virtual ~Expr() = default;
};

class Binary : public Expr {
    public:
        Expr *left;
        Expr *right;
        Token oprtr;

        Binary(Expr *l, Token op ,Expr *r) : left(l), oprtr(op), right(r) {}

        std::string printExpr() override {
            return "Binary";
        }

        double eval() override {
            switch(oprtr.type) {
                case TokenType::PLUS:
                    return left->eval() + right->eval();
                case TokenType::MINUS:
                    return left->eval() - right->eval();
                case TokenType::STAR:
                    return left->eval() * right->eval();
                case TokenType::SLASH:
                    return left->eval() / right->eval();
                case TokenType::MOD:
                    return (int)left->eval() % (int)right->eval();
                case TokenType::EQUAL_EQUAL:
                    return (double) (left->eval() == right->eval());
                case TokenType::BANG_EQUAL:
                    return (double) (left->eval() != right->eval());
                case TokenType::GREATER:
                    return (double) (left->eval() > right->eval());
                case TokenType::GREATER_EQUAL:
                    return (double) (left->eval() >= right->eval());
                case TokenType::LESS:
                    return (double) (left->eval() < right->eval());
                case TokenType::LESS_EQUAL:
                    return (double) (left->eval() <= right->eval());
                case TokenType::AND:
                    return (double) ((bool)left->eval() && (bool)right->eval());
                case TokenType::OR:
                    return (double) ((bool)left->eval() || (bool)right->eval());
            }
        }
};

class Unary : public Expr {
    public:
        Expr *right;
        Token oprtr;

        Unary(Token op, Expr *r) : oprtr(op), right(r) {}

        std::string printExpr() override {
            return "Unary";
        }

        double eval() override {
            return -(right->eval());
        }
};

class Group : public Expr {
    public:
        Expr *expr;

        Group(Expr *exp) : expr(exp) {}

        std::string printExpr() override {
            return "Group";
        }

        double eval() override {
            return expr->eval();
        }
        
};

class Literal : public Expr {
    public:
        double value;

        Literal(double val) : value(val) {}

        std::string printExpr() override {
            return "Literal";
        }

        double eval() override {
            return value;
        }
};

class VariableExpr : public Expr {
    public:
        Token token;
        Environment *env;

        VariableExpr(Token tkn, Environment *e) : token(tkn), env(e) {}

        std::string printExpr() {
            return "Variable Expression";
        }

        double eval() override {
            return env->get(token.lexeme);
        }
};