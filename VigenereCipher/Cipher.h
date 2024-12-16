#pragma once

#include <string>

class Cipher
{
public:
    Cipher(const std::string& charset = "0123456789abcdefghijklmnopqrstuvwxyz_.,");

    // Encrypt
    std::string Encrypt(const std::string& plaintext, const std::string& key) const;

    // Decrypt
    std::string Decrypt(const std::string& ciphertext, const std::string& key) const;

private:
    const std::string CHARSET;
    const size_t CHARSET_SIZE;

    int GetIndex(char ch) const;

    std::string FilterInput(const std::string& input) const;

    std::string Process(const std::string& input, const std::string& key, bool isEncrypt) const;
};
