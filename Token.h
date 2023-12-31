#pragma once

#include "TokenType.h"
#include <string>

class Token {
    public:
        const TokenType type;
        const double literal;
        const std::string lexeme;

        Token(TokenType tp, double ltrl, std::string lxme) : type(tp), literal(ltrl), lexeme(lxme) {}
};