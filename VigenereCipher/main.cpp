#include <iostream>
#include <algorithm>
#include <cctype>
#include "Cipher.h"

int main(void)
{
	Cipher cipher;

	while (true)
	{
		int mode{};
		std::string inputText, key;

		std::cout << "Mode Select(0: Encrypt, 1: Decrypt): ";
		std::cin >> mode;
		std::cin.ignore(); // Clear input buffer

		if (mode != 0 && mode != 1)
		{
			std::cerr << "ERROR::Mode undefined." << std::endl;
			system("pause");
			return 1;
		}

		if (mode == 0)
		{
			std::cout << "Enter Plain Text: ";
		}
		else
		{
			std::cout << "Enter Code: ";
		}
		
		std::getline(std::cin, inputText);

		std::cout << "Key: ";
		std::getline(std::cin, key);

		try
		{
			std::string result;
			if (mode == 0)
			{
				result = cipher.Encrypt(inputText, key);
				std::cout << "Cipher Text: " << result << std::endl;
			}
			else
			{
				result = cipher.Decrypt(inputText, key);
				std::cout << "Decrypted Text: " << result << std::endl;
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << "ERROR::" << e.what() << std::endl;
			system("pause");
			return 1;
		}

		std::cout << std::endl;
	}

	return 0;
}
