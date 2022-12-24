#pragma once
#include<string>
#include<iostream>
#include <vector>

using namespace std;

enum STATE
{
	EXIST,
	DELETE,
	EMPTY
};

//哈希表：线性探测解决哈希冲突
template<class K, class V>
struct HashNode
{
	pair <K, V> _kv;//数据
	STATE _state = EMPTY;//状态
};

//顺序表实现哈希
template<class K, class V>
class HashTable
{
public:
	typedef HashNode<K, V> Node;

	HashTable(size_t n = 779)
		:_hTable(n)
		, _size(0)
	{}

	bool insert(const pair<K, V>& kv)
	{
		//0.检查容量
		checkCapacity();

		//1.当前元素的哈希位置
		int idx = kv.first % _hTable.size();

		//2.判断key是否存在
		while (_hTable[idx]._state != EMPTY)//当前位置已有数据或者为删除位置，都不能存放
		{
			//当前位置存在数据且key相同，则不能插入
			if (_hTable[idx]._state == EXIST
				&& _hTable[idx]._kv.first == kv.first)
			{
				return false;
			}
			//继续往后搜索空位置
			++idx;
			//走到末尾，需要从头开始找
			if (idx == _hTable.size())
				idx = 0;
		}

		_hTable[idx]._kv = kv;
		_hTable[idx]._state = EXIST;
		++_size;

		return true;
	}

	void checkCapacity()
	{
		//负载因子[0, 1],这里定负载因子为0.7
		if (_hTable.size() == 0 || _size * 10 / _hTable.size() >= 7)
		{
			//创建新表
			int newC = _hTable.size() == 0 ? 10 : 2 * _hTable.size();
			HashTable<K, V> newHt(newC);

			for (size_t i = 0; i < _hTable.size(); ++i)
			{
				//将原先的表的数据插入到新的表中，
				if (_hTable[i]._state == EXIST)
				{
					newHt.insert(_hTable[i]._kv);
				}
			}
			//交换两个表的内容
			Swap(newHt);
		}
	}

	void Swap(HashTable<K, V>& Ht)
	{
		swap(_hTable, Ht._hTable);
		swap(_size, Ht._size);
	}

	Node* find(const K& key)
	{
		//计算位置
		int idx = key % _hTable.size();
		while (_hTable[idx]._state != EMPTY)
		{
			//找到
			if (_hTable[idx]._state == EXIST
				&& key == _hTable[idx]._kv.first)
			{
				return &_hTable[idx];
			}
			++idx;
			if (idx == _hTable.size())
				idx = 0;
		}
		//如果遇到空格则表示没找到，返回空
		return NULL;
	}

	bool erase(const K& key)
	{
		Node* node = find(key);
		if (node)
		{
			//伪删除
			--_size;
			node->_state = DELETE;
			return true;
		}
		return false;
	}

private:
	vector<Node> _hTable;//表
	size_t _size;//有效元素个数
};

