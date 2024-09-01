//
// Created by 李勃鋆 on 24-8-28.
//
#include "../week03.h"

class Query_base {
protected:
	virtual ~Query_base()=default;
};

class TextQuery01 {
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

bool isTextFileByExtension15_1(const std::string &filePath) {
	// 定义常见的文本文件扩展名
	const std::vector<std::string> textExtensions = {".txt", ".log", ".csv", ".md", ".json", ".xml", ".html",
													 ".ini",
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

string dealLine15_1(string &line) {
	// 正则表达式匹配合法单词部分
	const regex words_regex("([A-Za-z]+(-[A-Za-z]+|'[A-Za-z]+)?)");
	string result;
	result.reserve(line.size()); // 预分配内存
	for (auto it = std::sregex_iterator(line.begin(), line.end(), words_regex); it != std::sregex_iterator(); ++it) {
		string word = it->str();
		// -后全为大写字母，将-替换为空格，分为两个单词
		const size_t hyphenPos = word.find('-');
		if (hyphenPos != string::npos && std::all_of(word.begin() + static_cast<std::string::difference_type>(hyphenPos) + 1, word.end(), ::isupper)) {
			word[hyphenPos] = ' ';
		}
		// 单引号在开头或结尾
		const size_t apostrophePos = word.find('\'');
		if (apostrophePos != string::npos && (word.back() == '\'' || word.front() == '\'')) {
			word[apostrophePos] = ' ';
		}
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		if (!result.empty()) {
			result += ' ';
		}
		result += word;
	}
	return result;
}

void TextQuery01::readFile(const string &filename) {
	ifstream stream(filename);
	if (!stream.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		return;
	}
	if (!isTextFileByExtension15_1(filename)) {
		std::cout << filename << " is not a text file." << std::endl;
	}
	string line, data;
	while (getline(stream, line)) {
		_lines.push_back(line);
		istringstream buffer(line);
		while (buffer >> data) {
			string word;
			memset(word.data(), 0, word.size());
			word=dealLine15_1(data);
			if (!word.empty()) {
				_dict[word]++;
				_wordNumbers[word].insert(static_cast<int>(_lines.size()));
			}
		}
	}
}

void TextQuery01::query(const string &word) {
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

void test15_01() {
	// /root/download/china_daily.txt
	string queryWord;
	std::cout << "Enter word: ";
	std::cin >> queryWord;
	std::string filePath;
	std::cout << "Enter the file path: ";
	std::cin >> filePath;
	TextQuery01 tq;
	tq.readFile(filePath);
	// tq.toString();
	tq.query(queryWord);
}
