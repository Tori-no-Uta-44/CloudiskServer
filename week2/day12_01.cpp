//
// Created by 李勃鋆 on 24-8-24.
//词频统计的作业再用map容器去实现一次，体验一下使用vector/map时程序执行的速度
// 提示：++dict [word];
#include "../week02.h"

class Dictionary_test_12_01 {
public:
	void toString() {
		for (auto &[fst, snd] : _dict) {
			std::cout << fst << "--" << snd << std::endl;
		}
	}

	void read(const string &fileName);

	void store(const string &filename);

private:
	map<string, int> _dict;
};

void Dictionary_test_12_01::read(const string &fileName) {
	ifstream stream(fileName);
	if (!stream.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		return;
	}
	string line, data;
	while (getline(stream, line)) {
		istringstream buffer(line);
		while (buffer >> data) {
			string word;
			for (char &ch : data) {
				if (isalpha(ch)) {
					word += static_cast<char>(tolower(ch));
				}
			}
			if (!word.empty()) {
				_dict[word]++;
			}
		}
	}
	stream.close();
}

void Dictionary_test_12_01::store(const string &filename) {
	ofstream src(filename);
	if (!src.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		return;
	}
	for (auto &[fst,snd] : _dict) {
		src << fst << "--" << snd << endl;
	}
	src.close();
}

void test_12_01() {
	Dictionary_test_12_01 dict;
	dict.read("/root/download/The_Holy_Bible.txt");
	dict.store("./dict.txt");
}
