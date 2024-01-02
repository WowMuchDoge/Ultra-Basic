#pragma once

#include "TokenType.h"
#include "Token.h"
#include "Expr.h"
#include "Environment.h"

class Stmt {
    public:
        virtual ~Stmt() = default;

        virtual void execute() = 0;
};

class PrintStmt : public Stmt {
    public:
        Expr *expr;

        PrintStmt(Expr *exp) : expr(exp) {}

        void execute() {
            std::cout << expr->eval() << '\n';
        }
};

class ExprStmt : public Stmt {
    public:
        Expr *expr;

        ExprStmt(Expr *exp) : expr(exp) {}

        void execute() {
            expr->eval();
        }
};

class VariableStmt : public Stmt {
    public:
        double val;
        Token token;
        Environment *environment;

        VariableStmt(double n, Token tkn, Environment *env) : val(n), token(tkn), environment(env) {}

        void execute() {
            environment->define(token.lexeme, val);
        }
};