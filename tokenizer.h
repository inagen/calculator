#pragma once
#include "token.h"
#include <istream>
#include <list>
#include <memory>
#include <vector>
#include <iostream>

struct IStreamWrapper {
    std::istream& is;
    bool needBack = false;
    char current = 0;

    IStreamWrapper(std::istream& i) : is(i) { }

    char getCurrent() const noexcept {
        return current;
    }

    char getNext() {
        if (needBack) {
            needBack = false;
        } else {
            is.get(current);
            if (is.eof()) {
                current = 0;
            }
        }
        
        return current;
    }

    void back() {
        needBack = true;
    }

};

struct Tokenizer {
    enum class State {
        Start,
        Number,
        Error,
        End
    };

    State state;
    IStreamWrapper is;

    Tokenizer (std::istream& i) : is(i) {}

    std::shared_ptr<Token> nextToken() {
        switch (state) {
            case State::Start: {
                char symbol = is.getNext();
                switch (symbol) {
                    case '(':
                        return std::make_shared<OpenBracket>();
                    case ')':
                        return std::make_shared<CloseBracket>();
                    case '+':
                        return std::make_shared<Add>();
                    case '-':
                        return std::make_shared<Subtract>();
                    case '*':
                        return std::make_shared<Multiply>();
                    case '/':
                        return std::make_shared<Divide>();
                    default:
                        if (symbol == 0) {
                            state = State::End;
                            return nextToken();
                        }
                        if (std::isspace(symbol)) {
                            return nextToken();
                        }
                        if (std::isdigit(symbol)) {
                            state = State::Number;
                            return nextToken();
                        }
                        state = State::Error;
                        return nextToken();
                }
            }
            case State::Number: {
                int number = is.getCurrent() - '0';
                while (std::isdigit(is.getNext())) {
                    number = number * 10 + is.getCurrent() - '0';
                }
                is.back();
                state = State::Start;
                return std::make_shared<Number>(number);
            }
            case State::Error: {
                throw std::logic_error("Parsing error");
            }
            case State::End: {
                return nullptr;
            }
            default: {
                throw new std::logic_error("Unknown state");
            }
        }
    }

    std::vector<std::shared_ptr<Token>> tokenize() {
        std::vector<std::shared_ptr<Token>> res;
        while (true) {
            std::shared_ptr<Token> token = nextToken();
            if (token == nullptr) {
                return res;
            } else {
                res.push_back(token);
            }
        }
    }

};