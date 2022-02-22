#include <iostream>
#include "Dictionary.h"
#include <Windows.h>
#include <excpt.h>
#include <vector>
#include <string>

const char* numStrings[] = { "one", "two", "three", "four", "five" };



bool checkOrder(Dictionary<int, const char*>& dictionary)
{
	if (dictionary.getCount() != 5)
		return false;
	const char* currentString = nullptr;

	for (int i = 0; i < dictionary.getCount(); i++)
	{
		if (!dictionary.tryGetValue(i + 1, currentString))
			return false;

		if (strcmp(currentString, numStrings[i]) != 0)
			return false;
	}

	return true;
}

int allocationAndDeallocation()
{
	try
	{
		Dictionary<int, const char*>* dictionary = new Dictionary<int, const char*>();
		dictionary->addItem(1, "one");
		dictionary->addItem(2, "two");
		dictionary->clear();
		dictionary->clear();

		if (dictionary->containsKey(1) || dictionary->containsKey(2) || dictionary->containsValue("one") || dictionary->containsValue("two"))
		{
			std::cout << "Still contains values after cleared" << std::endl;
			return 0;
		}

		dictionary->addItem(3, "three");
		dictionary->remove(1);

		if (!dictionary->containsKey(3))
		{
			std::cout << "Removes the wrong values if given a non-matching key" << std::endl;
			return 0;
		}

		delete dictionary;
	}
	catch (...)
	{
		return 0;
	}


	return 1;
}

int addingItems()
{
	try
	{
		Dictionary<int, const char*> dictionary = Dictionary<int, const char*>();

		dictionary.addItem(1, "one");
		dictionary.addItem(2, "two");
		dictionary.addItem(3, "three");
		dictionary.addItem(4, "four");
		dictionary.addItem(5, "five");

		if (!checkOrder(dictionary))
		{
			std::cout << "Dictionary doesn't contain all items added" << std::endl;
			return 0;
		}

		if (!dictionary.containsValue("one"))
		{
			std::cout << "Dictionary doesn't contain all items added" << std::endl;
			return 0;
		}

		if (!dictionary.containsValue("two"))
		{
			std::cout << "Dictionary doesn't contain all items added" << std::endl;
			return 0;
		}

		if (!dictionary.containsValue("three"))
		{
			std::cout << "Dictionary doesn't contain all items added" << std::endl;
			return 0;
		}

		if (!dictionary.containsValue("four"))
		{
			std::cout << "Dictionary doesn't contain all items added" << std::endl;
			return 0;
		}

		if (!dictionary.containsValue("five"))
		{
			std::cout << "Dictionary doesn't contain all items added" << std::endl;
			return 0;
		}

		dictionary.addItem(2, "six");

		if (dictionary.containsValue("six"))
		{
			std::cout << "Dictionary allows duplicates" << std::endl;
			return 0;
		}
	}
	catch (...)
	{
		return 0;
	}

	return 1;
}

int removingItems()
{
	try
	{
		Dictionary<int, const char*> dictionary = Dictionary<int, const char*>();

		dictionary.addItem(1, "one");
		dictionary.addItem(2, "two");
		dictionary.addItem(3, "three");
		dictionary.addItem(4, "four");
		dictionary.addItem(5, "five");

		const char* val = nullptr;

		dictionary.remove(1);

		if (dictionary.containsValue("one"))
		{
			std::cout << "Dictionary doesn't remove items based on key" << std::endl;
			return 0;
		}

		dictionary.remove(2, val);

		if (dictionary.containsValue("two") || strcmp(val, "two") != 0)
		{
			std::cout << "Dictionary doesn't remove items based on key or doesnt assign the removed value correctly" << std::endl;
			return 0;
		}


		dictionary.remove(3);

		if (dictionary.containsValue("three"))
		{
			std::cout << "Dictionary doesn't remove items based on key" << std::endl;
			return 0;
		}

		dictionary.remove(4, val);

		if (dictionary.containsValue("four") || strcmp(val, "four") != 0)
		{
			std::cout << "Dictionary doesn't remove items based on key or doesnt assign the removed value correctly" << std::endl;
			return 0;
		}


		dictionary.remove(5);

		if (dictionary.containsValue("five"))
		{
			std::cout << "Dictionary doesn't remove items based on key" << std::endl;
			return 0;
		}

		dictionary.addItem(2, "six");

		if (!dictionary.containsValue("six"))
		{
			std::cout << "Dictionary doesn't add items after all have been removed" << std::endl;
			return 0;
		}
	}
	catch (...)
	{
		return 0;
	}

	return 1;
}

int assignment()
{
	try
	{
		Dictionary<int, const char*> dictionary = Dictionary<int, const char*>();
		Dictionary<int, const char*> dictionary2 = Dictionary<int, const char*>(dictionary);

		dictionary.addItem(1, "one");
		dictionary.addItem(2, "two");
		dictionary.addItem(3, "three");
		dictionary.addItem(4, "four");
		dictionary.addItem(5, "five");

		if (checkOrder(dictionary2))
		{
			std::cout << "Dictionary values aren't copied when assigned to another" << std::endl;
			return 0;
		}

		dictionary2 = dictionary;

		if (!checkOrder(dictionary2))
		{
			std::cout << "Dictionary values aren't copied when assigned to another" << std::endl;
			return 0;
		}

		dictionary.clear();
		if (!checkOrder(dictionary2))
		{
			std::cout << "Dictionary values aren't copied when assigned to another" << std::endl;
			return 0;
		}
	}
	catch (...)
	{
		return 0;
	}

	return 1;
}

int main()
{
	int score = allocationAndDeallocation();
	score += addingItems();
	score += removingItems();
	score += assignment();
	std::cout << "Score: " << score;

	std::vector<int> test = std::vector<int>();

	return 0;
}