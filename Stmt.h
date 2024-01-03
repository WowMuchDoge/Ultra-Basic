#pragma once

#include <vector>

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

        void execute() override {
            std::cout << expr->eval() << '\n';
        }
};

class ExprStmt : public Stmt {
    public:
        Expr *expr;

        ExprStmt(Expr *exp) : expr(exp) {}

        void execute() override {
            expr->eval();
        }
};

class VariableStmt : public Stmt {
    public:
        Expr *val;
        Token token;
        Environment *environment;

        VariableStmt(Expr *n, Token tkn, Environment *env) : val(n), token(tkn), environment(env) {}

        void execute() override {
            environment->define(token.lexeme, val->eval());
        }
};

class Block : public Stmt {
    public:
        std::vector<Stmt*> statements;

        Block(std::vector<Stmt*> stmts) : statements(stmts) {}

        void execute() override {
            for (Stmt* statement : statements) {
                statement->execute();
            }
        }
};

class WhileStatement : public Stmt {
    public:
        Expr *expr;
        Stmt *stmt;

        WhileStatement(Expr *exp, Stmt *stm) : expr(exp) {}

        void execute() override {
            while (expr->eval() >= 1) {
                stmt->execute();
            }
        }
};

class IfStatement : public Stmt {
    public:
        Expr *expr;
        Stmt *stmt;

        IfStatement(Expr *exp, Stmt *stm) : expr(exp), stmt(stm) {}

        void execute() override {
            if (expr->eval() >= 1) {
                stmt->execute();
            }
        }
};