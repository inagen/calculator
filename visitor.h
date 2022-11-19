#pragma once
#include "token.h"
#include <stack>
#include <stdexcept>
#include <list>
#include <vector>
#include <iostream>

struct TokenVisitor {
    virtual void visit(std::shared_ptr<Number> token) = 0;
    virtual void visit(std::shared_ptr<Bracket> token) = 0;
    virtual void visit(std::shared_ptr<Operation> token) = 0;
    virtual ~TokenVisitor() = default;
};

struct CalcVisitor : TokenVisitor {
    std::stack<int> stack{};

    virtual void visit(std::shared_ptr<Number> token) final {
        stack.push(token->getVal());
    }

    virtual void visit(std::shared_ptr<Bracket> token) final {
        throw std::logic_error("Unexcpected bracket token in CalcVisitor");
    }

    virtual void visit(std::shared_ptr<Operation> token) final {
        if (stack.size() < 2) {
            throw std::logic_error("Not enough operands");
        }
        int a = stack.top();
        stack.pop();
        int b = stack.top();
        stack.pop();
        stack.push(token->calc(b, a));
    }

    int getResult() {
        if (stack.size() != 1) {
            throw std::logic_error("Not enough operations");
        }
        int result = stack.top();
        stack.pop();
        return result;
    }
};

struct PrintVisitor : TokenVisitor {
    std::ostream& os;

    PrintVisitor(std::ostream& o) : os(o) { }

    void write(std::shared_ptr<Token> token) {
        os << token->toString() << ' ';
    }

    virtual void visit(std::shared_ptr<Number> token) final {
        write(token);
    }

    virtual void visit(std::shared_ptr<Bracket> token) final {
        write(token);
    }

    virtual void visit(std::shared_ptr<Operation> token) final {
        write(token);
    }
};

struct ParserVisitor : TokenVisitor {
    std::vector<std::shared_ptr<Token>> parsed{};
    std::stack<std::shared_ptr<Token>> operations{};

    virtual void visit(std::shared_ptr<Number> token) final {
        parsed.push_back(token);
    }

    virtual void visit(std::shared_ptr<Bracket> token) final {
        
        if (token->getType() == TokenType::OpenBracket) {
            operations.push(token);
        } else {
            while (!operations.empty() && !(operations.top()->getType() == TokenType::OpenBracket)) {
                parsed.push_back(operations.top());
                operations.pop();
            }
            if (operations.empty()) {
                throw std::logic_error("Incorrect brackets");
            }
            operations.pop();
        }
    }

    virtual void visit(std::shared_ptr<Operation> token) final {
        while (!operations.empty() && operations.top()->getType() == TokenType::Operation
                && std::dynamic_pointer_cast<Operation>(operations.top())->priority() <= token->priority()) {
            parsed.push_back(operations.top());
            operations.pop();
        }
        operations.push(token);
    }

    std::vector<std::shared_ptr<Token>> getParsed() {
        while (!operations.empty()) {
            if (operations.top()->getType() == TokenType::OpenBracket) {
                throw std::logic_error("Incorrect brackets");
            }
            parsed.push_back(operations.top());
            operations.pop();
        }
        return parsed;
    }
};