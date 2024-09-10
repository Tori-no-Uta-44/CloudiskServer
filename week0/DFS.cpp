//
// Created by 李勃鋆 on 24-9-8.
//
#include "../week01.h"

namespace DFS {
	class Graph {
	public:
		explicit Graph(int n) :
			adjList(n), visited(n, false) {
		}

		void addEdge(int u, int v) {
			adjList[u].push_back(v);
			adjList[v].push_back(u);
		}

		void dfsIterative(int startNode) {
			std::fill(visited.begin(), visited.end(), false); // 重置访问数组
			std::stack<int> s;
			s.push(startNode);
			visited[startNode] = true;

			std::cout << "深度优先搜索的顺序: ";

			while (!s.empty()) {
				int node = s.top();
				s.pop();
				std::cout << node << " ";

				// 遍历节点的邻居，未访问的节点压入栈中
				for (int neighbor : adjList[node]) {
					if (!visited[neighbor]) {
						s.push(neighbor);
						visited[neighbor] = true;
					}
				}
			}
			std::cout << std::endl;
		}

	private:
		std::vector<std::vector<int>> adjList;
		std::vector<bool> visited;
	};
}

int DFS_test() {
	int V = 5;
	DFS::Graph graph(V);

	graph.addEdge(0, 1);
	graph.addEdge(0, 3);
	graph.addEdge(1, 2);
	graph.addEdge(1, 4);
	graph.addEdge(3, 4);

	graph.dfsIterative(0);

	return 0;
}
