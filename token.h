#pragma once
#include <string>
#include <memory>

struct TokenVisitor;

enum class TokenType {
    Number,
    Operation,
    OpenBracket,
    CloseBracket
};


struct Token {
    virtual void accept(TokenVisitor& visitor) = 0;
    virtual std::string toString() const noexcept = 0;
    virtual TokenType getType() = 0;
    virtual ~Token() = default;
};


struct Number : Token, std::enable_shared_from_this<Number> {
    const int val;
    Number(int v);
    void accept(TokenVisitor& visitor) final;
    std::string toString() const noexcept final;
    TokenType getType() final;
    int getVal() const noexcept;
};

struct Bracket : Token, std::enable_shared_from_this<Bracket> {
    void accept(TokenVisitor& visitor);
};

struct OpenBracket : Bracket {
    std::string toString() const noexcept final;
    TokenType getType() final;
};

struct CloseBracket : Bracket {
    std::string toString() const noexcept final;
    TokenType getType() final;
};

struct Operation : Token, std::enable_shared_from_this<Operation> {
    void accept(TokenVisitor& visitor);
    TokenType getType() final;
    virtual int priority() const noexcept = 0;
    virtual int calc(int a, int b) const noexcept = 0;
    virtual ~Operation() = default;
};


struct Add : Operation {
    int priority() const noexcept final;
    int calc(int a, int b) const noexcept final;
    std::string toString() const noexcept final;
};

struct Subtract : Operation {
    int priority() const noexcept final;
    int calc(int a, int b) const noexcept final;
    std::string toString() const noexcept final;
};

struct Multiply : Operation {
    int priority() const noexcept final;
    int calc(int a, int b) const noexcept final;
    std::string toString() const noexcept final;
};

struct Divide : Operation {
    int priority() const noexcept final;
    int calc(int a, int b) const noexcept final;
    std::string toString() const noexcept final;
};