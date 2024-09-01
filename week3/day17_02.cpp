//
// Created by 李勃鋆 on 24-8-30.
//
#include "../week03.h"
struct FileCloser {
	void operator()(std::ofstream* file) {
		if(file!=nullptr) {
			file->close();
		}
	}
};
void test17_8() {
	std::unique_ptr<std::ofstream,FileCloser> fout(new std::ofstream("test.txt"));
	if (fout->is_open()) {
		// 写入内容
		*fout << "hello" << std::endl;
	} else {
		std::cerr << "Failed to open the file." << std::endl;
	}

}