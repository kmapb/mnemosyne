#include <openssl/sha.h>
#include <openssl/evp.h>

#include "value.hpp"

namespace mnem {

Digest Value::name() const {
    std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> mdctx(
        EVP_MD_CTX_new(), EVP_MD_CTX_free);
    if (!mdctx) {
        throw std::runtime_error("OpenSSL error: Could not create EVP_MD_CTX");
    }

    if (EVP_DigestInit_ex(mdctx.get(), EVP_sha256(), nullptr) != 1) {
        throw std::runtime_error("OpenSSL error: Could not initialize SHA256");
    }

    // Hash the type
    if (EVP_DigestUpdate(mdctx.get(), &type, sizeof(type)) != 1) {
        throw std::runtime_error(
            "OpenSSL error: Could not update digest with type");
    }

    // Hash the value based on its type
    switch (type) {
    case ValueType::INT:
        if (EVP_DigestUpdate(mdctx.get(), &int_value, sizeof(int_value)) != 1) {
            throw std::runtime_error(
                "OpenSSL error: Could not update digest with int value");
        }
        break;
    case ValueType::FLOAT:
        if (EVP_DigestUpdate(mdctx.get(), &float_value, sizeof(float_value)) !=
            1) {
            throw std::runtime_error(
                "OpenSSL error: Could not update digest with float value");
        }
        break;
    case ValueType::BOOL:
        if (EVP_DigestUpdate(mdctx.get(), &bool_value, sizeof(bool_value)) !=
            1) {
            throw std::runtime_error(
                "OpenSSL error: Could not update digest with bool value");
        }
        break;
    case ValueType::STRING:
        if (EVP_DigestUpdate(mdctx.get(), string_value->c_str(),
                             string_value->length()) != 1) {
            throw std::runtime_error(
                "OpenSSL error: Could not update digest with string value");
        }
        break;
    case ValueType::LIST:
        for (const auto &item : *list_value) {
            Digest itemDigest = item->name();
            if (EVP_DigestUpdate(mdctx.get(), itemDigest.getData().data(),
                                 Digest::SIZE) != 1) {
                throw std::runtime_error(
                    "OpenSSL error: Could not update digest with list item");
            }
        }
        break;
    case ValueType::DICT:
        for (const auto &pair : *dict_value) {
            Digest keyDigest = pair.first->name();
            Digest valueDigest = pair.second->name();
            if (EVP_DigestUpdate(mdctx.get(), keyDigest.getData().data(),
                                 Digest::SIZE) != 1 ||
                EVP_DigestUpdate(mdctx.get(), valueDigest.getData().data(),
                                 Digest::SIZE) != 1) {
                throw std::runtime_error(
                    "OpenSSL error: Could not update digest with dict item");
            }
        }
        break;
    }

    std::array<unsigned char, Digest::SIZE> hash;
    unsigned int hashLen;
    if (EVP_DigestFinal_ex(mdctx.get(), hash.data(), &hashLen) != 1) {
        throw std::runtime_error("OpenSSL error: Could not finalize digest");
    }

    return Digest(hash);
}

} // namespace mnem