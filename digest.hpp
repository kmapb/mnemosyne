#pragma once

#include <array>
#include <string>
#include <openssl/sha.h>

namespace mnem {

class Digest {
public:
    static constexpr size_t SIZE = SHA256_DIGEST_LENGTH;

    Digest() : data_() {}
    explicit Digest(const std::array<unsigned char, SIZE>& data) : data_(data) {}

    const std::array<unsigned char, SIZE>& getData() const { return data_; }

    std::string toString() const {
        static const char hex_digits[] = "0123456789abcdef";
        std::string result(SIZE * 2, ' ');
        for (size_t i = 0; i < SIZE; ++i) {
            result[2 * i] = hex_digits[data_[i] >> 4];
            result[2 * i + 1] = hex_digits[data_[i] & 0xF];
        }
        return result;
    }

    bool operator==(const Digest& other) const {
        return data_ == other.data_;
    }

    bool operator!=(const Digest& other) const {
        return !(*this == other);
    }

private:
    std::array<unsigned char, SIZE> data_;
};

} // namespace mnem