#pragma once

template<typename TKey, typename TValue>
class Dictionary
{
public:
	Dictionary<TKey, TValue>();
	Dictionary<TKey, TValue>(const Dictionary<TKey, TValue>& other);
	~Dictionary<TKey, TValue>();

	/// <summary>
	/// Gets the number of items in the dictionary
	/// </summary>
	int getCount() const { return m_count; }

	/// <summary>
	/// Creates a new item with the given key and value and adds it to the dictionary
	/// </summary>
	/// <param name="key">The key of the new item</param>
	/// <param name="value">The value of the new item</param>
	void addItem(const TKey& key, const TValue& value);

	/// <summary>
	/// Removes the item that matches the given key from the dictionary
	/// </summary>
	/// <param name="key">The key of the item to search for</param>
	/// <returns>Whether or not the removal was successful. Returns false if the item isn't in the dictionary</returns>
	bool remove(const TKey& key);
	/// <summary>
	/// Removes the item that matches the given key from the dictionary
	/// </summary>
	/// <param name="key">The key of the item to search for</param>
	/// <param name="value">The variable to use to store the value that was removed</param>
	/// <returns>Whether or not the removal was successful. Returns false if the item isn't in the dictionary</returns>
	bool remove(const TKey& key, TValue& value);

	/// <summary>
	/// Checks to see if an item that has the given key is in the dictionary
	/// </summary>
	/// <param name="key">The key of the item to search for</param>
	/// <returns>Returns false if the item wasn't in the dictionary</returns>
	bool containsKey(const TKey& key) const;
	/// <summary>
	/// Checks to see if an item that has the given value is in the dictionary
	/// </summary>
	/// <param name="value">The key of the item to search for</param>
	/// <returns>Returns false if the item wasn't in the dictionary</returns>
	bool containsValue(const TValue& value) const;

	/// <summary>
	/// Tries to find the item that matches the given key
	/// </summary>
	/// <param name="key">The key of the item to search for</param>
	/// <param name="value">The variable to use to store the value that was found</param>
	/// <returns></returns>
	bool tryGetValue(const TKey& key, TValue& value) const;

	/// <summary>
	/// Deletes all items in dictionary
	/// </summary>
	void clear();

	const Dictionary<TKey, TValue>& operator = (const Dictionary<TKey, TValue>& other);

	TValue operator [](const TKey key);

private:
	template <typename TItemKey, typename TItemValue>
	struct Item
	{
		TKey key;
		TValue value;
	};

private:
	int m_count = 0;
	Item<TKey, TValue>* m_items = nullptr;
};

template<typename TKey, typename TValue>
inline Dictionary<TKey, TValue>::Dictionary()
{
	m_count = 0;
	m_items = nullptr;
}

template<typename TKey, typename TValue>
inline Dictionary<TKey, TValue>::Dictionary(const Dictionary<TKey, TValue>& other)
{
	*this = other;
}

template<typename TKey, typename TValue>
inline Dictionary<TKey, TValue>::~Dictionary()
{
	clear();
}

template<typename TKey, typename TValue>
inline void Dictionary<TKey, TValue>::addItem(const TKey& key, const TValue& value)
{
	Item<TKey, TValue>* temp = new Item<TKey, TValue>[getCount() + 1];

	for (int i = 0; i < getCount(); i++)
	{
		if (m_items[i].key == key)
			return;

		temp[i] = m_items[i];
	}

	temp[getCount()] = { key, value };
	//delete m_items;
	m_items = temp;

	m_count++;
}

template<typename TKey, typename TValue>
inline bool Dictionary<TKey, TValue>::remove(const TKey& key)
{
	if (getCount() <= 0)
		return false;

	bool itemRemoved = false;

	Item<TKey, TValue>* temp = new Item<TKey, TValue>[getCount() - 1];
	int j = 0;
	for (int i = 0; i < getCount(); i++)
	{
		if (m_items[i].key == key)
			itemRemoved = true;
		else
		{
			temp[j] = m_items[i];
			j++;
		}
	}

	if (itemRemoved)
	{
		m_count--;
		delete m_items;
		m_items = temp;
	}

	return itemRemoved;
}

template<typename TKey, typename TValue>
inline bool Dictionary<TKey, TValue>::remove(const TKey& key, TValue& value)
{
	if (getCount() <= 0)
		return false;

	bool itemRemoved = false;

	Item<TKey, TValue>* temp = new Item<TKey, TValue>[getCount() - 1];
	int j = 0;
	for (int i = 0; i < getCount(); i++)
	{
		if (m_items[i].key == key)
		{
			itemRemoved = true;
			value = m_items[i].value;
		}
		else
		{
			temp[j] = m_items[i];
			j++;
		}
	}

	if (itemRemoved)
	{
		m_count--;
		delete m_items;
		m_items = temp;
	}

	return itemRemoved;
}

template<typename TKey, typename TValue>
inline bool Dictionary<TKey, TValue>::containsKey(const TKey& key) const
{
	for (int i = 0; i < getCount(); i++)
	{
		if (m_items[i].key == key)
			return true;
	}

	return false;
}

template<typename TKey, typename TValue>
inline bool Dictionary<TKey, TValue>::containsValue(const TValue& value) const
{
	for (int i = 0; i < getCount(); i++)
	{
		if (m_items[i].value == value)
			return true;
	}

	return false;
}

template<typename TKey, typename TValue>
inline bool Dictionary<TKey, TValue>::tryGetValue(const TKey& key, TValue& value) const
{
	for (int i = 0; i < getCount(); i++)
	{
		if (m_items[i].key == key)
		{
			value = m_items[i].value;
			return true;
		}
	}

	return false;
}

template<typename TKey, typename TValue>
inline void Dictionary<TKey, TValue>::clear()
{
	if (m_count <= 0)
		return;

	delete m_items;
	m_items = nullptr;

	m_count = 0;
}

template<typename TKey, typename TValue>
inline const Dictionary<TKey, TValue>& Dictionary<TKey, TValue>::operator=(const Dictionary<TKey, TValue>& other)
{
	clear();
	m_items = new Item<TKey, TValue>[other.getCount()];
	m_count = other.getCount();

	for (int i = 0; i < other.getCount(); i++)
		m_items[i] = other.m_items[i];

	return *this;
}

template<typename TKey, typename TValue>
inline TValue Dictionary<TKey, TValue>::operator[](const TKey key)
{
	TValue val = TValue();

	for (int i = 0; i < getCount(); i++)
	{
		if (m_items[i].key == key)
			val = m_items[i].value;
	}

	return val;
}
