#pragma once

#include <iostream>
#include <map>
#include <unordered_map>

#include "Stmt.h"
#include "Expr.h"
#include "Token.h"
#include "TokenType.h"

class Environment {
    private:
        std::unordered_map<std::string, double> env;

    public:
        
        void define(std::string str, double val) {
            env[str] = val;
        }

        double get(std::string str) {
            auto pos = env.find(str);
            return pos->second;
        }

        int getSize() {
            return env.size();
        }
};