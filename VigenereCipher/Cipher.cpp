#include <stdexcept>
#include "Cipher.h"

Cipher::Cipher(const std::string& charset) : CHARSET(charset), CHARSET_SIZE(charset.size())
{
}

std::string Cipher::Encrypt(const std::string& plaintext, const std::string& key) const
{
	return Process(plaintext, key, true);
}

std::string Cipher::Decrypt(const std::string& ciphertext, const std::string& key) const
{
	return Process(ciphertext, key, false);
}

int Cipher::GetIndex(char ch) const
{
	ch = std::tolower(ch);
	if (ch == 'Å@' || ch == ' ') ch = '_';
	auto pos = CHARSET.find(ch);
	return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

std::string Cipher::FilterInput(const std::string& input) const
{
	std::string filtered{};
	for (char ch : input)
	{
		if (GetIndex(ch) != -1)
		{
			filtered += ch;
		}
	}
	return filtered;
}

std::string Cipher::Process(const std::string& input, const std::string& key, bool isEncrypt) const
{
	std::string output;
	std::string filteredKey = FilterInput(key);
	if (filteredKey.empty())
	{
		throw std::invalid_argument("Key contains no valid characters.");
	}

	std::size_t keyLength = filteredKey.length();
	for (std::size_t i = 0; i < input.length(); ++i)
	{
		int inputIndex = GetIndex(input[i]);
		if (inputIndex != -1)
		{
			int keyIndex = GetIndex(filteredKey[i % keyLength]);
			if (keyIndex == -1) continue;

			std::size_t resultIndex;
			if (isEncrypt)
			{
				resultIndex = (static_cast<std::size_t>(inputIndex) + keyIndex) % CHARSET_SIZE;
			}
			else
			{
				resultIndex = (static_cast<std::size_t>(inputIndex) + CHARSET_SIZE - keyIndex) % CHARSET_SIZE;
			}

			output += isEncrypt ? std::toupper(CHARSET[resultIndex]) : CHARSET[resultIndex];
		}
	}
	return output;
}