#include <iostream>
#include <fstream>

#include "Token.h"
#include "TokenType.h"
#include "Scanner.h"
#include "PrintTokens.h"
#include "Parser.h"
#include "Stmt.h"

int main() {
    std::string fileText;

    std::ifstream txtFile("code.txt");

    std::string line;
    while (std::getline(txtFile, line)) {
        fileText += line;
        fileText += '\n';
    }

    std::cout << fileText;

    Scanner scanner(fileText);

    std::vector<Token> tokens = scanner.scanTokens();

    PrintTokens pTokens(tokens);

    Parser parser(tokens);

    pTokens.printEm();

    std::vector<Stmt*> statements;
    statements = parser.parse();

    for (Stmt *statement : statements) {
        statement->execute();
    }
}