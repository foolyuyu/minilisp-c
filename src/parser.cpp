#include "./parser.h"
#include "./error.h"
#include "./value.h"

#include <iostream>

ValuePtr Parser::parse() {
    auto token = std::move(tokens.front()); //目前仅支持一个队列里面最前面的词的分析
    tokens.pop_front();
    if (token->getType() == TokenType::NUMERIC_LITERAL) {
        auto value = static_cast<NumericLiteralToken&>(*token).getValue();
        return std::make_shared<NumericValue>(value);
    }
    else if (token->getType() == TokenType::BOOLEAN_LITERAL) {
        auto value = static_cast<BooleanLiteralToken&>(*token).getValue();
        return std::make_shared<BooleanValue>(value);
    }
    else if (token->getType() == TokenType::STRING_LITERAL) {
        auto value = static_cast<StringLiteralToken&>(*token).getValue();
        return std::make_shared<StringValue>(value);
    }
    else if (token->getType() == TokenType::IDENTIFIER) {
        auto value = static_cast<IdentifierToken&>(*token).getName();
        return std::make_shared<SymbolValue>(value);
    }
    else if (token->getType() == TokenType::LEFT_PAREN) {
        auto value = Parser::parseTails();
        return value;
    }

    throw SyntaxError("Unimplemented"); // 尚未实现

}

ValuePtr Parser::parseTails() {
    if (tokens.front()->getType() == TokenType::RIGHT_PAREN) {
        tokens.pop_front();
        return std::make_shared<NilValue>();
    }
    auto car = this->parse();
    if (tokens.front()->getType() == TokenType::DOT) {
        tokens.pop_front();
        auto cdr = this->parse();
        if (tokens.front()->getType() == TokenType::RIGHT_PAREN) {
            tokens.pop_front();
            return std::make_shared<PairValue>(car, cdr);
        }
    }
    else {
        auto cdr = this->parseTails();
        return std::make_shared<PairValue>(car, cdr);
    }
    
    throw SyntaxError("need a right_paren ')'\n");

}