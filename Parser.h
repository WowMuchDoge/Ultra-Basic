#pragma once

#include <iostream>
#include <vector>

#include "Token.h"
#include "TokenType.h"
#include "Expr.h"
#include "Stmt.h"

class Parser {
    private:
        std::vector<Token> tokens;

        int current = 0;

        Stmt *statement() {
            if (match(TokenType::PRINT)) return printStatement();

            return expressionStatement();
        }

        Stmt *declaration() {
            if (match(TokenType::NUM)) return varStatement();

            return statement();
        }

        Stmt *printStatement() {
            match(TokenType::LEFT_PAREN);
            Expr *expr = expression();
            match(TokenType::RIGHT_PAREN);
            match(TokenType::SEMICOLON);
            return new PrintStmt(expr);
        }

        Stmt *varStatement() {
            Token token = advance();

            double iniitializer = 0;
            match(TokenType::EQUAL);

            Expr *expr = expression();

            match(TokenType::SEMICOLON);
            return new VariableStmt(expr->eval(), token, &env);
        }

        Stmt *expressionStatement() {
            Expr *expr = expression();
            match(TokenType::SEMICOLON);
            return nullptr;
        }

        Expr *expression() {
            return orExpr();
        }

        Expr *orExpr() {
            Expr *expr = andExpr();

            while (match(TokenType::OR)) {
                Token oprtr = previous();
                Expr *right = andExpr();
                expr = new Binary(expr, oprtr, right);
            }

            return expr;
        }

        Expr *andExpr() {
            Expr *expr = equality();

            while (match(TokenType::AND)) {
                Token oprtr = previous();
                Expr *right = equality();
                expr = new Binary(expr, oprtr, right);
            }

            return expr;
        }

        Expr *equality() {
            Expr *expr = comparison();

            while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
                Token oprtr = previous();
                Expr *right = term();
                expr = new Binary(expr, oprtr, right);
            }
            
            return expr;
        }

        Expr *comparison() {
            Expr *expr = term();

            while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
                Token oprtr = previous();
                Expr *right = factor();
                expr = new Binary(expr, oprtr, right);
            } 

            return expr;
        }

        Expr *term() {
            Expr *expr = factor();

            while (match(TokenType::PLUS, TokenType::MINUS)) {
                Token oprtr = previous();
                Expr *right = factor();
                expr = new Binary(expr, oprtr, right);
            }

            return expr;
        }

        Expr *factor() {
            Expr *expr = unary();

            while (match(TokenType::STAR, TokenType::SLASH)) {
                Token oprtr = previous();
                Expr *right = unary();
                expr = new Binary(expr, oprtr, right);
            }

            return expr;
        }

        Expr *unary() {
            while (match(TokenType::BANG, TokenType::MINUS)) {
                Token oprtr = previous();
                Expr *right = unary();
                return new Unary(oprtr, right);
            }

            return primary();
        }

        Expr *primary() {
            if (match(TokenType::TRUE)) return new Literal(1.0);
            if (match(TokenType::FALSE)) return new Literal(0.0);

            if (match(TokenType::LITERAL)) {
                return new Literal(previous().literal);
            }

            if (match(TokenType::LEFT_PAREN)) {
                Expr *expr = expression();
                if (match(TokenType::RIGHT_PAREN)) {
                    return new Group(expr);
                } else {
                    //Add some error handling someday...
                    return nullptr;
                }
            }

            if (match(TokenType::IDENTIFIER)) {
                return new VariableExpr(previous(), &env);
            }

            return nullptr;
        }

        bool match(TokenType t1) {
            if (check(t1)) {
                advance();
                return true;
            }
            return false;
        }

        bool match(TokenType t1, TokenType t2) {
            if (check(t1)) {
                advance();
                return true;
            } else if (check(t2)) {
                advance();
                return true;
            }
            return false;
        }

        bool match(TokenType t1, TokenType t2, TokenType t3) {
            if (check(t1)) {
                advance();
                return true;
            } else if (check(t2)) {
                advance();
                return true;
            } else if (check(t3)) {
                advance();
                return true;
            }
            return false;
        }

        bool match(TokenType t1, TokenType t2, TokenType t3, TokenType t4) {
            if (check(t1)) {
                advance();
                return true;
            } else if (check(t2)) {
                advance();
                return true;
            } else if (check(t3)) {
                advance();
                return true;
            } else if (check(t4)) {
                advance();
                return true;
            }

            return false;
        }

        bool check(TokenType type) {
            if (isAtEnd()) return false;
            return peek().type == type;
        }

        Token advance() {
            if (!isAtEnd()) current++;
            return previous();
        }

        Token peek() {
            return tokens[current];
        }

        Token previous() {
            return tokens[current - 1];
        }

        bool isAtEnd() {
            if (peek().type == TokenType::END_OF_FILE) {
                return true;
            } else {
                return false;
            }
        }

    public:
        Parser(std::vector<Token> tkns) : tokens(tkns) {}

        Environment env;

        std::vector<Stmt*> statements; 

        std::vector<Stmt*> parse() {
            while (!isAtEnd()) {
                statements.push_back(declaration());
            }
            return statements;
        }

        std::string getStr(Expr *expr) {
            return expr->printExpr(); 
        }
};