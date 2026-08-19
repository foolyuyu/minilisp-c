#include "./value.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

std::string BooleanValue::toString() const {
    if(BooleanValue::value) {
        return "#t";
    }
    else {
        return "#f";
    }
}

std::string NumericValue::toString() const {
    std::ostringstream oss;
    if (value == std::floor(value)) {
        oss << value;
    }
    else {
        oss << std::fixed << std::setprecision(6) << value;
    }
    return oss.str();
    
}
// 暂未实现区分int和double

std::string StringValue::toString() const {
    std::ostringstream oss;
    oss << std::quoted(StringValue::value);
    return oss.str();
}

std::string NilValue::toString() const {
    return "()";
}

std::string SymbolValue::toString() const {
    return name;
}

std::string cdrToString(const ValuePtr& rightp) {
    if (rightp->getType() == ValueType::NIL) {
        return ")";
    }
    else if (rightp->getType() == ValueType::PAIR) {
        std::ostringstream oss;
        auto& pair = static_cast<const PairValue&>(*rightp);
        oss << " " << (pair.get_left())->toString() << cdrToString(pair.get_right());
        return oss.str();
    }
    else {
        return " . " + rightp->toString() + ")";
    }
}

std::string PairValue::toString() const {
    std::ostringstream oss;
    oss << '(' << left->toString() << cdrToString(right);

    /* 下面这个是不做右侧括号省略的版本
    if (right->getType() == ValueType::NIL) {
        oss << ')';
    }
    else if (right->getType() == ValueType::PAIR) {
        oss << right->toString() << ')';
    }
    else {
        oss << " . " << right->toString() << ')';
    }*/

    return oss.str();
}

std::ostream& operator<< (std::ostream& os, const ValuePtr& valuep) {
    os << valuep->toString() << std::endl;
    return os;
}