//
// Created by 李勃鋆 on 24-9-8.
//
#include "../week01.h"

namespace ConnectedComponents {
	class Graph {
	public:
		Graph(int n) :
			adjList(n), visited(n, false) {
		}

		// 添加边
		void addEdge(int u, int v) {
			adjList[u].push_back(v);
			adjList[v].push_back(u); // 无向图
		}

		// 查找连通分量
		void findConnectedComponents() {
			int componentCount = 0;
			for (int i = 0; i < adjList.size(); i++) {
				if (!visited[i]) {
					std::cout << "连通分量 " << componentCount + 1 << ": ";
					dfs(i);
					std::cout << std::endl;
					componentCount++;
				}
			}
			std::cout << "总共连通分量数: " << componentCount << std::endl;
		}

	private:
		std::vector<std::vector<int>> adjList; // 邻接列表
		std::vector<bool> visited; // 访问标记数组

		// 深度优先搜索
		void dfs(int node) {
			visited[node] = true;
			std::cout << node << " "; // 输出当前节点
			for (int neighbor : adjList[node]) {
				if (!visited[neighbor]) {
					dfs(neighbor);
				}
			}
		}
	};
}


int ConnectedComponents_test() {
	int V = 5; // 顶点个数
	ConnectedComponents::Graph graph(V);

	// 添加边
	graph.addEdge(0, 1);
	graph.addEdge(1, 2);
	graph.addEdge(3, 4);

	// 查找并打印连通分量
	graph.findConnectedComponents();

	return 0;
}
