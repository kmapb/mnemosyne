#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include <new>

#include "digest.hpp"

namespace mnem {

// Define the possible types
enum class ValueType { INT, FLOAT, STRING, BOOL, LIST, DICT };

class Value {
  public:
    // Named constructor functions
    static Value Int(int64_t v) { return Value(ValueType::INT, v); }
    static Value Float(double v) { return Value(ValueType::FLOAT, v); }
    static Value String(const std::string &v) {
        return Value(ValueType::STRING, v);
    }
    static Value Bool(bool v) { return Value(ValueType::BOOL, v); }
    static Value List(const std::vector<std::shared_ptr<Value>> &v) {
        return Value(ValueType::LIST, v);
    }
    static Value Dict(const std::unordered_map<std::shared_ptr<Value>,
                                               std::shared_ptr<Value>> &v) {
        return Value(ValueType::DICT, v);
    }

    // Destructor
    ~Value() {
        switch (type) {
        case ValueType::STRING:
            delete string_value;
            break;
        case ValueType::LIST:
            delete list_value;
            break;
        case ValueType::DICT:
            delete dict_value;
            break;
        default:
            break;
        }
    }

    // Copy constructor
    Value(const Value &other) : type(other.type) { copyFrom(other); }

    // Move constructor
    Value(Value &&other) noexcept : type(other.type) {
        moveFrom(std::move(other));
    }

    // Copy assignment operator
    Value &operator=(const Value &other) {
        if (this != &other) {
            this->~Value();
            type = other.type;
            copyFrom(other);
        }
        return *this;
    }

    // Move assignment operator
    Value &operator=(Value &&other) noexcept {
        if (this != &other) {
            this->~Value();
            type = other.type;
            moveFrom(std::move(other));
        }
        return *this;
    }

    ValueType getType() const { return type; }

    // Getter methods (add appropriate error handling)
    int64_t asInt() const { return int_value; }
    double asFloat() const { return float_value; }
    bool asBool() const { return bool_value; }
    const std::string &asString() const { return *string_value; }
    const std::vector<std::shared_ptr<Value>> &asList() const {
        return *list_value;
    }
    const std::unordered_map<std::shared_ptr<Value>, std::shared_ptr<Value>> &
    asDict() const {
        return *dict_value;
    }

    Digest name() const;

  private:
    ValueType type;

    union {
        int64_t int_value;
        double float_value;
        bool bool_value;
        std::string *string_value;
        std::vector<std::shared_ptr<Value>> *list_value;
        std::unordered_map<std::shared_ptr<Value>, std::shared_ptr<Value>>
            *dict_value;
    };

    // Private constructors
    Value(ValueType t, int64_t v) : type(t), int_value(v) {}
    Value(ValueType t, double v) : type(t), float_value(v) {}
    Value(ValueType t, bool v) : type(t), bool_value(v) {}
    Value(ValueType t, const std::string &v)
        : type(t), string_value(new std::string(v)) {}
    Value(ValueType t, const std::vector<std::shared_ptr<Value>> &v)
        : type(t), list_value(new std::vector<std::shared_ptr<Value>>(v)) {}
    Value(ValueType t, const std::unordered_map<std::shared_ptr<Value>,
                                                std::shared_ptr<Value>> &v)
        : type(t),
          dict_value(new std::unordered_map<std::shared_ptr<Value>,
                                            std::shared_ptr<Value>>(v)) {}

    void copyFrom(const Value &other) {
        switch (type) {
        case ValueType::INT:
            int_value = other.int_value;
            break;
        case ValueType::FLOAT:
            float_value = other.float_value;
            break;
        case ValueType::BOOL:
            bool_value = other.bool_value;
            break;
        case ValueType::STRING:
            string_value = new std::string(*other.string_value);
            break;
        case ValueType::LIST:
            list_value =
                new std::vector<std::shared_ptr<Value>>(*other.list_value);
            break;
        case ValueType::DICT:
            dict_value = new std::unordered_map<std::shared_ptr<Value>,
                                                std::shared_ptr<Value>>(
                *other.dict_value);
            break;
        }
    }

    void moveFrom(Value &&other) {
        switch (type) {
        case ValueType::INT:
            int_value = other.int_value;
            break;
        case ValueType::FLOAT:
            float_value = other.float_value;
            break;
        case ValueType::BOOL:
            bool_value = other.bool_value;
            break;
        case ValueType::STRING:
            string_value = other.string_value;
            other.string_value = nullptr;
            break;
        case ValueType::LIST:
            list_value = other.list_value;
            other.list_value = nullptr;
            break;
        case ValueType::DICT:
            dict_value = other.dict_value;
            other.dict_value = nullptr;
            break;
        }
    }
};

} // namespace mnem