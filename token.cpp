#include "token.h"
#include "visitor.h"

// Методы пришлось вынести в срр файл, так как иначе была циклическая зависимость, visitor являлся Incomplete type

// Number
Number::Number(int v) : val(v) { 

}

void Number::accept(TokenVisitor& visitor) {
    visitor.visit(shared_from_this());
}

std::string Number::toString() const noexcept {
    return std::to_string(val);
}

TokenType Number::getType() {
    return TokenType::Number;
}

int Number::getVal() const noexcept {
    return val;
}

// Brackets
void Bracket::accept(TokenVisitor& visitor) {
    visitor.visit(shared_from_this());
}

std::string OpenBracket::toString() const noexcept {
    return "(";
}

TokenType OpenBracket::getType() {
    return TokenType::OpenBracket;
}

std::string CloseBracket::toString() const noexcept {
    return ")";
}

TokenType CloseBracket::getType() {
    return TokenType::CloseBracket;
}


// Operation
void Operation::accept(TokenVisitor& visitor) {
    visitor.visit(shared_from_this());
}

TokenType Operation::getType() {
    return TokenType::Operation;
}

// Add
int Add::priority() const noexcept {
    return 1;
}

int Add::calc(int a, int b) const noexcept {
    return a + b;
}

std::string Add::toString() const noexcept {
    return "+";
}

// Subtract
int Subtract::priority() const noexcept {
    return 1;
}

int Subtract::calc(int a, int b) const noexcept {
    return a - b;
}

std::string Subtract::toString() const noexcept {
    return "-";
}

// Multiply
int Multiply::priority() const noexcept {
    return 0;
}

int Multiply::calc(int a, int b) const noexcept {
    return a * b;
}

std::string Multiply::toString() const noexcept {
    return "*";
}

// Divide
int Divide::priority() const noexcept {
    return 0;
}

int Divide::calc(int a, int b) const noexcept {
    return a / b;
}

std::string Divide::toString() const noexcept {
    return "/";
}