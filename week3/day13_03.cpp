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

	void parseRss(); //解析
	void dump(const string &filename); //输出
	void toString() {
		for (const auto &[title, link, description, content] : _rss) {
			cout << title << " " << link << " " << description << " " << content << endl;
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
		rssItem.description = description ? description->GetText() : "";
		rssItem.content = content ? content->GetText() : "";

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
	for (const auto &[title, link, description, content] : _rss) {
		fout << title << " " << link << " " << description << " " << content << endl;
	}
	fout.close();
}

void test13_03() {
	RssReader reader;
	reader.parseRss();
	reader.toString();
	reader.dump("pagelib.txt");
}
