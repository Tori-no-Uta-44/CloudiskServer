//
// Created by 李勃鋆 on 24-8-18.
//
#include "../week02.h"

void test_07_01() {
	std::string fileName = "../func.h";
	std::ifstream ifs(fileName);
	std::string word;
	while (ifs >> word) {
		std::cout << word << std::endl;
	}
	ifs.close();
}

void test_07_02() {
	std::string fileName = "../func.h";
	std::ifstream stream(fileName);
	std::string buffer;
	while (getline(stream, buffer)) {
		std::cout << buffer << std::endl;
	}
}

void test_07_03() {
	ifstream stream("../func.h");
	stream.seekg(0, ios::end);
	long pos = stream.tellg();
	string buffer;
	buffer.resize(pos);
	stream.seekg(0);
	stream.read(&buffer[0], pos);
	std::cout << buffer << endl;
	stream.close();
}

typedef struct Record {
	string _word;
	int _frequency;
} Record;

class Dictionary {
public:
	void insert(const string& word) {
		if (_dict.empty()) {
			_dict.push_back({word, 1});
			return;
		}
		for (auto& [_word, _frequency] : _dict) {
			if (_word == word) {
				_frequency++;
				return;
			}
		}
		_dict.push_back({word, 1});
	}

	void toString() {
		for (auto& [_word, _frequency] : _dict) {
			cout << _word << " " << _frequency << endl;
		}
	}

	void read(const string& fileName);

	void store(const string& filename);

private:
	vector<Record> _dict;
};

void Dictionary::read(const string& fileName) {
	ifstream stream(fileName);
	if (!stream.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		return;
	}
	string buffer;
	string word;
	while (stream >> buffer) {
		word.clear();
		for (char& ch : buffer) {
			if (isalpha(static_cast<unsigned char>(ch))) {
				word.push_back(static_cast<char>(tolower(static_cast<unsigned char>(ch))));
			}
		}
		if (!word.empty()) {
			insert(word);
		}
	}
	stream.close();
}

void Dictionary::store(const string& filename) {
	ofstream src(filename);
	if (!src.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		return;
	}
	for (auto& [word, _frequency] : _dict) {
		src << word << ":" << _frequency << endl;
	}
	src.close();
}


void test_07_04() {
	Dictionary dict;
	dict.read("/root/download/The_Holy_Bible.txt");
	// dict.toString();
	dict.store("./dict.txt");
}
