
#define DEBUG_PRINTS

#include "visitor.h"
#include "token.h"
#include "tokenizer.h"
#include <sstream>
#include <iostream>

int main() {
    
    std::cout << "Enter expression: ";
    std::string input;
    std::getline(std::cin, input);
    
    std::istringstream iss(input);

    Tokenizer tokenizer(iss);
    auto tokens = tokenizer.tokenize();


    ParserVisitor parserVisitor;
    for (auto& token : tokens) {
        token->accept(parserVisitor);
    }

    auto parsed = parserVisitor.getParsed();
    PrintVisitor printVisitor(std::cout);
    
    std::cout << "Polish notation: ";
    for (auto& token : parsed) {
        token->accept(printVisitor);
    }
    std::cout << std::endl;

    CalcVisitor calcVisitor;
    for (auto& token : parsed) {
        token->accept(calcVisitor);
    }
    std::cout << "Expression result: " << calcVisitor.getResult() << std::endl;
}