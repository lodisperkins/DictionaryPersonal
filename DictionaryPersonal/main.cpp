#include <iostream>
#include "Dictionary.h"

void printDictionary(Dictionary<int, const char*> dictionary)
{
	const char* value = nullptr;
	for (int i = 0; i < dictionary.getCount(); i++)
		if (dictionary.tryGetValue(i + 1, value))
			std::cout << value << std::endl;
}

int main()
{
	Dictionary<int, const char*> names = Dictionary<int, const char*>();
	names.addItem(1, "Lodis1");
	names.addItem(2, "Lodis2");
	names.addItem(8, "Lodis3");
	names.addItem(3, "Lodis4");
	const char* value = names[8];
	if (names.tryGetValue(1, value))
		printDictionary(names);

	std::cout << value << std::endl;
	return 0;
}