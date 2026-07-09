#pragma once
#include <cstdint>
#include <string_view>

// Compile-time XOR string obfuscation macro
#define OBFUSCATE(str) ([]() {
    constexpr auto len = std::char_traits<char>::length(str);
    constexpr char key = static_cast<char>((len * 0x5A) ^ 0xA5);
    char obf[len + 1] = {};
    for (size_t i = 0; i < len; ++i) obf[i] = str[i] ^ key;
    obf[len] = '\0';
    struct { char data[len + 1]; constexpr operator const char*() const { return data; } } s{obf};
    return s;
}())

// Runtime deobfuscation
inline std::string Deobfuscate(const char* obf, size_t len) {
    char key = static_cast<char>((len * 0x5A) ^ 0xA5);
    std::string out(len, '\0');
    for (size_t i = 0; i < len; ++i) out[i] = obf[i] ^ key;
    return out;
}
