//
// Created by 李勃鋆 on 24-9-8.
//
// 图类表示使用邻接列表表示的图
#include "../week01.h"

namespace adList {
	class Graph {
	public:
		// 构造函数，n为顶点的个数
		Graph(int n) :
			adjList(n) {
		}

		// 添加边
		void addEdge(int u, int v) {
			adjList[u].push_back(v); // 对于无向图，u -> v 和 v -> u 都需要
			adjList[v].push_back(u); // 如果是有向图，可以省略这一行
		}

		// 打印邻接列表表示的图
		void printGraph() {
			for (int i = 0; i < adjList.size(); i++) {
				std::cout << i << ": ";
				for (int neighbor : adjList[i]) {
					std::cout << neighbor << " ";
				}
				std::cout << std::endl;
			}
		}

	private:
		std::vector<std::vector<int>> adjList; // 邻接列表
	};
}


int adList_test() {
	int V = 5; // 顶点个数
	adList::Graph graph(V);

	// 添加边
	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(1, 2);
	graph.addEdge(1, 3);
	graph.addEdge(2, 3);
	graph.addEdge(3, 4);

	// 打印图的邻接列表
	graph.printGraph();

	return 0;
}
