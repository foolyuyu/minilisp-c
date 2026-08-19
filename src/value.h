#ifndef VALUE_H
#define VALUE_H

#include <string>
#include "./token.h"

enum class ValueType {
    BOOLEAN,
    NUMERIC,
    STRING,
    NIL,
    SYMBOL,
    PAIR,
};

class Value {
private:
    ValueType type;
protected:
    Value(const ValueType& type) : type{type} {};
public:
    virtual ~Value() = default;
    ValueType getType() const {
        return type;
    }
    virtual std::string toString() const = 0;
    
};

class BooleanValue : public Value {
private:
    bool value;
public:
    BooleanValue(const bool& value) : Value(ValueType::BOOLEAN), value{value} {};
    bool getValue() const {
        return value;
    }
    std::string toString() const override;

};

class NumericValue : public Value {
private:
    double value;
public:
    NumericValue(const double& value) : Value(ValueType::NUMERIC), value{value} {}
    double getValue() const {
        return value;
    }
    std::string toString() const override;
};

class StringValue : public Value {
private:
    std::string value;
public:
    StringValue(const std::string& value) : Value(ValueType::STRING), value{value} {}
    std::string getValue() const {
        return value;
    }
    std::string toString() const override;
};

class NilValue : public Value {
public:
    NilValue() : Value(ValueType::NIL) {}
    void getValue() const {
        return;
    }
    std::string toString() const override;
};

class SymbolValue : public Value {
private:
    std::string name;
public:
    SymbolValue(const std::string& name) : Value(ValueType::SYMBOL), name{name} {}
    std::string toString() const override;
};

using ValuePtr = std::shared_ptr<Value>;

class PairValue : public Value {
private:
    ValuePtr left, right;
public:
    PairValue(const ValuePtr& left, const ValuePtr& right) : Value(ValueType::PAIR), left{left}, right{right} {}
    std::string toString() const override;
    const ValuePtr& get_left() const {
        return left;
    }
    const ValuePtr& get_right() const {
        return right;
    }
    
    friend std::string pairToList(const ValuePtr& valuep);
};



#endif