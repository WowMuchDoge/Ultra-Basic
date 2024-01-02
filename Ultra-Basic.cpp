#include <iostream>
#include "Token.h"
#include "TokenType.h"
#include "Scanner.h"
#include "PrintTokens.h"
#include "Parser.h"
#include "Stmt.h"

int main() {
    Scanner scanner("num a = (1 - 10); print(1);");

    std::vector<Token> tokens = scanner.scanTokens();

    PrintTokens pTokens(tokens);

    pTokens.printEm();

    Parser parser(tokens);

    std::vector<Stmt*> statements;
    statements = parser.parse();

    for (Stmt *statement : statements) {
        statement->execute();
    }
}