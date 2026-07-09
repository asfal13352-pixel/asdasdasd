#pragma once
#include <string>
#include <cstddef>

template <size_t N>
class ObfStr {
public:
    char data[N]{};

    constexpr ObfStr(const char(&str)[N]) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = str[i] ^ 0xAA;
        }
    }

    std::string Deobfuscate() const {
        std::string result;
        result.reserve(N);
        for (size_t i = 0; i < N - 1; ++i) {
            result += static_cast<char>(data[i] ^ 0xAA);
        }
        return result;
    }
};

#define OBF(str) (ObfStr<sizeof(str)>(str).Deobfuscate().c_str())