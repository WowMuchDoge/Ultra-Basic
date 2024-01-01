#include <iostream>
#include "Token.h"
#include "TokenType.h"
#include "Scanner.h"
#include "PrintTokens.h"

int main() {
    Scanner scanner("for while if and true false print");

    std::vector<Token> tokens = scanner.scanText();

    PrintTokens pTokens(tokens);

    pTokens.printEm();
}