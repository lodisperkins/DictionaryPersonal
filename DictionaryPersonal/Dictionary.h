#pragma once

template<typename TKey, typename TValue>
class Dictionary
{
public:
	Dictionary<TKey, TValue>();
	Dictionary<TKey, TValue>(const Dictionary<TKey, TValue>& other);
	~Dictionary<TKey, TValue>();

	int getCount() const { return m_count; }

	void addItem(TKey key, TValue value);

	bool remove(TKey key);
	bool remove(TKey key, TValue& value);

	bool containsKey(TKey key) const;
	bool containsValue(TValue value) const;

	bool tryGetValue(TKey key, TValue& value);

	void clear();

	const Dictionary<TKey, TValue>& operator = (const Dictionary<TKey, TValue>& other);

	TValue operator [](TKey key);

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
inline void Dictionary<TKey, TValue>::addItem(TKey key, TValue value)
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
inline bool Dictionary<TKey, TValue>::remove(TKey key)
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
inline bool Dictionary<TKey, TValue>::remove(TKey key, TValue& value)
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
inline bool Dictionary<TKey, TValue>::containsKey(TKey key) const
{
	for (int i = 0; i < getCount(); i++)
	{
		if (m_items[i].key == key)
			return true;
	}

	return false;
}

template<typename TKey, typename TValue>
inline bool Dictionary<TKey, TValue>::containsValue(TValue value) const
{
	for (int i = 0; i < getCount(); i++)
	{
		if (m_items[i].value == value)
			return true;
	}

	return false;
}

template<typename TKey, typename TValue>
inline bool Dictionary<TKey, TValue>::tryGetValue(TKey key, TValue& value)
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
inline TValue Dictionary<TKey, TValue>::operator[](TKey key)
{
	TValue val = TValue();

	for (int i = 0; i < getCount(); i++)
	{
		if (m_items[i].key == key)
			val = m_items[i].value;
	}

	return val;
}
