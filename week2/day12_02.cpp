//
// Created by 李勃鋆 on 24-8-24.
//
#include "../week02.h"

class TextQuery {
public:
	//......
	void readFile(const string &filename);

	void query(const string &word); //

	void toString() {
		for (auto &[fst,snd] : _dict) {
			cout << fst << " " << snd << endl;
		}
		std::cout << "---" << endl;
		for (const auto &_line : _lines) {
			std::cout << _line << endl;
		}
		std::cout << "---" << endl;
		for (auto &[fst,snd] : _wordNumbers) {
			std::cout << fst;
			for (auto &i : snd) {
				std::cout << i;
			}
		}
	}

private:
	//......
	vector<string> _lines; //O(1)存储该文件的内容，以便输出每个单词所在的原始行
	map<string, set<int>> _wordNumbers; //将每一行分解为各个单词，并记录每个单词所在的所有行。在输出行号时，应保证以升序输出，并且不重复。
	map<string, int> _dict; //该单词出现的次数
};

bool isTextFileByExtension(const std::string &filePath) {
	// 定义常见的文本文件扩展名
	const std::vector<std::string> textExtensions = {".txt", ".log", ".csv", ".md", ".json", ".xml", ".html", ".ini",
	                                                 ".cfg", ".cpp", ".h"};

	// 查找文件路径中最后一个 '.' 的位置
	std::size_t dotPos = filePath.find_last_of('.');
	if (dotPos == std::string::npos) {
		return false;
	}

	// 获取文件扩展名并转换为小写
	std::string fileExtension = filePath.substr(dotPos);
	std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);

	// 检查文件扩展名是否在定义的文本文件扩展名列表中
	return std::find(textExtensions.begin(), textExtensions.end(), fileExtension) != textExtensions.end();
}

void TextQuery::readFile(const string &filename) {
	ifstream stream(filename);
	if (!stream.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		return;
	}

	string line, data;
	while (getline(stream, line)) {
		_lines.push_back(line);
		istringstream buffer(line);
		while (buffer >> data) {
			string word;
			for (char &ch : data) {
				if (isalpha(ch)) {
					word += static_cast<char>(tolower(ch));
				}
			}
			// for (char &ch : data) {
			// 	if (isalpha(ch) || isdigit(ch)) {  // 处理字母和数字
			// 		word += static_cast<char>(tolower(ch));
			// 	}
			// }
			if (!word.empty()) {
				_dict[word]++;
				_wordNumbers[word].insert(static_cast<int>(_lines.size()));
			}
		}
	}
}

void TextQuery::query(const string &word) {
	if (!word.empty()) {
		std::string lowerWord;
		for (char ch : word) {
			lowerWord += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
		}

		auto search1 = _dict.find(lowerWord);
		auto search2 = _wordNumbers.find(lowerWord);
		if (search1 != _dict.end() && search2 != _wordNumbers.end()) {
			std::cout << lowerWord << " occurs " << search1->second << " times." << std::endl;
			for (const auto &lineNum : search2->second) {
				std::cout << "(line " << lineNum << ") " << _lines[lineNum - 1] << std::endl;
			}
		}
		else {
			std::cout << "Word not found." << std::endl;
		}
	}
}

void test_12_02() {
	string queryWord;
	std::cout << "Enter word: ";
	std::cin >> queryWord;
	std::string filePath;
	std::cout << "Enter the file path: ";
	std::cin >> filePath;
	TextQuery tq;
	tq.readFile(filePath);
	tq.query(queryWord);
}
