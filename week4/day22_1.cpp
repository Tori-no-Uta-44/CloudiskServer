//
// Created by 李勃鋆 on 24-9-5.
//
#include <utility>

#include "../week04.h"

class Dictionary22 {
public:
	void toString() {
		for (auto &[fst, snd] : _dict) {
			std::cout << fst << "--" << snd << std::endl;
		}
	}

	void read(const string &fileName);

	void store(const string &filename);

private:
	unordered_map<string, int> _dict;
};

void Dictionary22::read(const string &fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Can't open file " << fileName << std::endl;
		return;
	}
	string line, data;
	while (getline(file, line)) {
		istringstream buffer(line);
		while (buffer >> data) {
			string word;
			for (auto &ch : data) {
				if (isalpha(ch)) {
					word += static_cast<char>(toupper(ch));
				}
			}
			if (!word.empty()) {
				_dict[word]++;
			}
		}
	}
	file.close();
}

void Dictionary22::store(const string &filename) {
	ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Can't open file " << filename << std::endl;
	}
	for (auto &[fst,snd] : _dict) {
		file << fst << "--" << snd << endl;
	}
	file.close();
}

void test22_1() {
	Dictionary22 dict;
	dict.read("/root/download/The_Holy_Bible.txt");
	dict.store("./dict.txt");
}

void test22_2() {
	ifstream file("/root/download/file.txt"); //配对的
	ifstream maps("/root/download/map.txt"); //键值
	if (!file.is_open()) {
		std::cerr << "Can't open file " << std::endl;
	}
	if (!maps.is_open()) {
		std::cerr << "Can't open map " << std::endl;
	}
	std::map<string, string> file_data;
	std::map<string, string> maps_data;
	string line, data;
	while (getline(maps, line)) {
		istringstream buffer(line);
		vector<string> words;
		while (buffer >> data) {
			words.push_back(data);
		}
		string k = words.at(0);
		string v;
		for (int i = 1; i < words.size(); i++) {
			v += words.at(i) + " ";
		}
		maps_data.insert(pair<string, string>(k, v));
	}
	maps.close();
	string ch;
	while (getline(file, ch)) {
		istringstream buffer(ch);
		while (buffer >> ch) {
			if (auto search = maps_data.find(ch); search != maps_data.end()) {
				cout << search->second << " ";
			}
			else {
				std::cout << ch << " ";
			}
		}
		cout << endl;
	}
	file.close();
}

struct ListNode146 {
	int _key, _value;
	ListNode146 *_next;
	ListNode146 *_prev;

	ListNode146() = default;

	ListNode146(int key, int value):
		_key(key), _value(value), _next(nullptr), _prev(nullptr) {
	}
};

struct Node146 {
	int _key;
	ListNode146 *_value;
	Node146 *_next;

	Node146() = default;

	explicit Node146(int key):
		_key(key), _value(nullptr), _next(nullptr) {

	}
};

struct HaspMap146 {
	int _size = 0;
	int _capacity = 0;
	long _hashSeed = 0;
	Node146 **_table{};

	HaspMap146() = default;

	explicit HaspMap146(int size, int capacity, long hashSeed):
		_size(size), _capacity(capacity), _hashSeed(hashSeed) {
		_table = new Node146 *[capacity];
		for (int i = 0; i < capacity; i++) {
			_table[i] = nullptr;
		}
	}

	~HaspMap146() {
		for (int i = 0; i < _capacity; i++) {
			delete _table[i];
		}
		delete[] _table;
	}

	[[nodiscard]] long hash(const long key) const {
		return (key ^ _hashSeed) % _capacity;
	}

	void put(const int key, ListNode146 *value) {
		const long idx = hash(key);
		auto *node = new Node146(key);
		node->_value = value;
		node->_next = _table[idx];
		_table[idx] = node;
		_size++;
	}

	[[nodiscard]] ListNode146 *get(const int key) const {
		const long idx = hash(key);
		const Node146 *current = _table[idx];
		while (current) {
			if (current->_key == key) {
				return current->_value;
			}
			current = current->_next;
		}
		return nullptr;
	}

	void remove(const int key) {
		const long idx = hash(key);
		Node146 *current = _table[idx];
		Node146 *prev = nullptr;
		while (current) {
			if (current->_key == key) {
				if (prev) {
					prev->_next = current->_next;
				}
				else {
					_table[idx] = current->_next;
				}
				delete current;
				_size--;
				return;
			}
			prev = current;
			current = current->_next;
		}
	}
};

class LRUCache {
private:
	int _capacity;
	int _size;
	ListNode146 *_head;
	ListNode146 *_tail;
	HaspMap146 *_hashMap;
	// unique_ptr<ListNode146> _head;
	// unique_ptr<ListNode146> _tail;
	// unique_ptr<HaspMap146> _hashMap;
	// shared_ptr<ListNode146> _head;
	// shared_ptr<ListNode146> _tail;
	// shared_ptr<HaspMap146> _hashMap;

public:
	explicit LRUCache(int capacity):
		_capacity(capacity), _size(0) {
		_hashMap = new HaspMap146(0, capacity, time(nullptr)); // 初始化哈希表
		_head = new ListNode146(); // 哨兵节点
		_tail = new ListNode146();
		_head->_next = _tail;
		_tail->_prev = _head;
	}

	~LRUCache() {
		delete _hashMap;
		delete _head;
		delete _tail;
	}

	int get(int key) {
		ListNode146 *node = _hashMap->get(key);
		if (!node) {
			return -1; // 缓存未命中
		}
		moveToTail(node); // 将访问的节点移动到链表尾部
		return node->_value;
	}

	void put(int key, int value) {
		if (ListNode146 *node = _hashMap->get(key)) {
			// 如果节点存在，更新值并移动到尾部
			node->_value = value;
			moveToTail(node);
		}
		else {
			// 如果不存在，创建新节点
			auto *newNode = new ListNode146(key, value);
			_hashMap->put(key, newNode); // 加入哈希表
			addToTail(newNode); // 加入链表尾部
			_size++;
			// 如果超出容量，移除最久未使用的节点
			if (_size > _capacity) {
				const ListNode146 *oldNode = _head->_next; // 链表头部的节点即为最久未使用
				removeNode(oldNode);
				_hashMap->remove(oldNode->_key); // 从哈希表中移除
				delete oldNode;
				_size--;
			}
		}
	}

private:
	// 将节点移动到链表尾部
	void moveToTail(ListNode146 *node) {
		removeNode(node);
		addToTail(node);
	}

	// 将节点从链表中移除
	void removeNode(const ListNode146 *node) {
		node->_prev->_next = node->_next;
		node->_next->_prev = node->_prev;
	}

	// 将节点加入到链表尾部
	void addToTail(ListNode146 *node) const {
		node->_prev = _tail->_prev;
		node->_next = _tail;
		_tail->_prev->_next = node;
		_tail->_prev = node;
	}
};

void test22_3() {
	LRUCache cache(2);
	cache.put(1, 1);
	cache.put(2, 2);
	std::cout << cache.get(1) << std::endl; // 返回 1
	cache.put(3, 3); // 该操作会使得关键字 2 作废
	std::cout << cache.get(2) << std::endl; // 返回 -1 (未找到)
	cache.put(4, 4); // 该操作会使得关键字 1 作废
	std::cout << cache.get(1) << std::endl; // 返回 -1 (未找到)
	std::cout << cache.get(3) << std::endl; // 返回 3
	std::cout << cache.get(4) << std::endl; // 返回 4
}

namespace test_22_4 {
	// 定义双向链表节点，使用智能指针
	struct ListNode {
		int _key = 0, _value = 0;
		std::shared_ptr<ListNode> _next;
		std::weak_ptr<ListNode> _prev; // 为防止循环引用，前指针使用 weak_ptr
		ListNode() = default;

		ListNode(int key, int value) :
			_key(key), _value(value), _next(nullptr) {
		}
	};

	// 定义哈希表的节点，使用智能指针
	struct Node {
		int _key = 0;
		std::shared_ptr<ListNode> _value; // 指向链表节点
		std::shared_ptr<Node> _next;

		Node() = default;

		explicit Node(int key) :
			_key(key), _value(nullptr), _next(nullptr) {
		}
	};

	// 定义自制哈希表，使用智能指针
	struct HaspMap {
		int _size;
		int _capacity;
		int _hashSeed;
		std::shared_ptr<Node> *_table;

		HaspMap() = default;

		explicit HaspMap(int size, int capacity, int hashSeed) :
			_size(size), _capacity(capacity), _hashSeed(hashSeed) {
			_table = new std::shared_ptr<Node>[capacity];
			for (int i = 0; i < capacity; ++i) {
				_table[i] = nullptr;
			}
		}

		~HaspMap() {
			delete[] _table;
		}

		// 哈希函数
		[[nodiscard]] int hash(const int key) const {
			return (key ^ _hashSeed) % _capacity;
		}

		// 插入 key 和节点到哈希表中
		void put(int key, std::shared_ptr<ListNode> value) {
			const int idx = hash(key);
			const auto newNode = std::make_shared<Node>(key);
			newNode->_value = std::move(value);
			newNode->_next = _table[idx];
			_table[idx] = newNode;
			_size++;
		}

		// 获取 key 对应的节点
		[[nodiscard]] std::shared_ptr<ListNode> get(const int key) const {
			const int idx = hash(key);
			auto current = _table[idx];
			while (current) {
				if (current->_key == key) {
					return current->_value;
				}
				current = current->_next;
			}
			return nullptr;
		}

		// 移除 key
		void remove(const int key) {
			const int idx = hash(key);
			auto current = _table[idx];
			std::shared_ptr<Node> prev = nullptr;
			while (current) {
				if (current->_key == key) {
					if (prev) {
						prev->_next = current->_next;
					}
					else {
						_table[idx] = current->_next;
					}
					_size--;
					return;
				}
				prev = current;
				current = current->_next;
			}
		}
	};

	class LRUCache {
	public:
		explicit LRUCache(int capacity) :
			_capacity(capacity), _size(0) {
			_hashMap = std::make_unique<HaspMap>(0, capacity, 123456); // 初始化哈希表
			_head = std::make_shared<ListNode>(); // 哨兵节点
			_tail = std::make_shared<ListNode>();
			_head->_next = _tail;
			_tail->_prev = _head;
		}

		int get(int key) {
			const auto node = _hashMap->get(key);
			if (!node) {
				return -1; // 缓存未命中
			}
			moveToTail(node); // 将访问的节点移动到链表尾部
			return node->_value;
		}

		void put(int key, int value) {
			if (const auto node = _hashMap->get(key)) {
				// 如果节点存在，更新值并移动到尾部
				node->_value = value;
				moveToTail(node);
			}
			else {
				// 如果不存在，创建新节点
				const auto newNode = std::make_shared<ListNode>(key, value);
				_hashMap->put(key, newNode); // 加入哈希表
				addToTail(newNode); // 加入链表尾部
				_size++;
				// 如果超出容量，移除最久未使用的节点
				if (_size > _capacity) {
					const auto oldNode = _head->_next; // 链表头部的节点即为最久未使用
					removeNode(oldNode);
					_hashMap->remove(oldNode->_key); // 从哈希表中移除
					_size--;
				}
			}
		}

	private:
		int _capacity;
		int _size;
		std::shared_ptr<ListNode> _head;
		std::shared_ptr<ListNode> _tail;
		std::unique_ptr<HaspMap> _hashMap;

		// 将节点移动到链表尾部
		void moveToTail(const std::shared_ptr<ListNode> &node) {
			removeNode(node);
			addToTail(node);
		}

		// 将节点从链表中移除
		void removeNode(const std::shared_ptr<ListNode> &node) {
			const auto prevNode = node->_prev.lock(); // 使用 weak_ptr.lock() 获取 shared_ptr
			prevNode->_next = node->_next;
			node->_next->_prev = prevNode;
		}

		// 将节点加入到链表尾部
		void addToTail(const std::shared_ptr<ListNode> &node) const {
			node->_prev = _tail->_prev;
			node->_next = _tail;
			const auto prevNode = _tail->_prev.lock();
			prevNode->_next = node;
			_tail->_prev = node;
		}
	};
}

void test22_4() {
	test_22_4::LRUCache cache(2);
	cache.put(1, 1);
	cache.put(2, 2);
	std::cout << cache.get(1) << std::endl; // 返回 1
	cache.put(3, 3); // 该操作会使得关键字 2 作废
	std::cout << cache.get(2) << std::endl; // 返回 -1 (未找到)
	cache.put(4, 4); // 该操作会使得关键字 1 作废
	std::cout << cache.get(1) << std::endl; // 返回 -1 (未找到)
	std::cout << cache.get(3) << std::endl; // 返回 3
	std::cout << cache.get(4) << std::endl; // 返回 4
}

namespace test_22_3 {
	struct ListNode22_3 {
		int _key = 0;
		int _value = 0;
		ListNode22_3 *_next = nullptr;
		ListNode22_3 *_prev = nullptr;

		ListNode22_3() = default;

		ListNode22_3(int key, int value):
			_key(key), _value(value) {

		}
	};

	class LRUCache22_3 {
		int _capacity = 0;
		ListNode22_3 *_head = nullptr;
		ListNode22_3 *_tail = nullptr;
		unordered_map<int, ListNode22_3*> _data;

	public:
		LRUCache22_3() = default;

		explicit LRUCache22_3(int capacity):
			_capacity(capacity), _head(new ListNode22_3()), _tail(new ListNode22_3()) {
			_head->_next = _tail;
			_tail->_prev = _head;
		}

		int get(int key) {
			if(_data.find(key)!=_data.end()) {
				ListNode22_3* node=_data[key];
				removeNode(node);
				addToHead(node);
				return node->_value;
			}
			return -1;
		}

		void put(int key, int value) {
			if(_data.find(key)!=_data.end()) {
				ListNode22_3 *node=_data[key];
				node->_value=value;
				removeNode(node);
				addToHead(node);
			}else {
				if(_data.size()>=_capacity) {
					ListNode22_3 *tail=_tail->_prev;
					_data.erase(tail->_key);
					removeNode(tail);
					delete tail;
				}
				auto *node=new ListNode22_3(key,value);
				_data[key]=node;
				addToHead(node);
			}
		}

	private:
		void removeNode(ListNode22_3 *node) {
			node->_prev->_next=node->_next;
			node->_next->_prev=node->_prev;
		}
		void addToHead(ListNode22_3 *node) const {
			node->_next=_head->_next;
			node->_prev=_head;
			_head->_next->_prev=node;
			_head->_next=node;
		}
	};
}
