//
// Created by 李勃鋆 on 24-8-27.
//
#include  "../week03.h"
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

typedef struct RssItem {
	string title;
	string link;
	string description;
	string content;
} RssItem;

class RssReader {
public:
	RssReader();
	static std::string removeHtmlTags(const std::string& html) {
		// 定义一个正则表达式来匹配 HTML 标签
		const std::regex tagRegex("<[^>]*>");
		// 使用 regex_replace 将 HTML 标签替换为空字符串
		return std::regex_replace(html, tagRegex, "");
	}
	void parseRss(); //解析
	void dump(const string &filename); //输出
	void toString() {
		int count=1;
		for (const auto &[title, link, description, content] : _rss) {
			std::cout << "<doc>"<<endl;
			std::cout << "\t<docid>"<<count++<<"</docid>"<<endl;
			std::cout << "\t<title>"<<title<<"</title>"<<endl;
			std::cout << "\t<link>"<<link<<"</link>"<<endl;
			std::cout << "\t<description>"<<description<<"</description>"<<endl;
			std::cout << "\t<content>"<<content<<"</content>"<<endl;
			std::cout << "</doc>"<<endl;
		}
	}

private:
	vector<RssItem> _rss;
};


RssReader::RssReader() = default;

void RssReader::parseRss() {
	XMLDocument doc;
	if (doc.LoadFile("/root/CLionProjects/cppDemo/week3/coolshell.xml") != XML_SUCCESS) {
		cout << "Failed to load file" << endl;
		return;
	}
	XMLElement *item = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
	if (item == nullptr) {
		cout << "No <item> element found" << endl;
		return;
	}

	while (item != nullptr) {
		RssItem rssItem;
		XMLElement *title = item->FirstChildElement("title");
		XMLElement *link = item->FirstChildElement("link");
		XMLElement *description = item->FirstChildElement("description");
		XMLElement *content = item->FirstChildElement("content:encoded"); // 使用正确的元素名
		rssItem.title = title ? title->GetText() : "";
		rssItem.link = link ? link->GetText() : "";
		rssItem.description = description ? removeHtmlTags(description->GetText()) : "";
		rssItem.content = content ? removeHtmlTags(content->GetText()) : "";

		_rss.push_back(rssItem);

		item = item->NextSiblingElement("item");
	}
}

void RssReader::dump(const string &filename) {
	ofstream fout(filename);
	if (!fout.is_open()) {
		cerr << "Failed to open file " << filename << endl;
		return;
	}
	int count=1;
	for (const auto &[title, link, description, content] : _rss) {
		fout << "<doc>"<<endl;
		fout << "\t<docid>"<<count++<<"</docid>"<<endl;
		fout << "\t<title>"<<title<<"</title>"<<endl;
		fout << "\t<link>"<<link<<"</link>"<<endl;
		fout << "\t<description>"<<description<<"</description>"<<endl;
		fout << "\t<content>"<<content<<"</content>"<<endl;
		fout << "</doc>"<<endl;
	}
	fout.close();
}

void test13_03() {
	RssReader reader;
	reader.parseRss();
	reader.toString();
	reader.dump("pagelib.txt");
}
