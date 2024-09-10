//
// Created by 李勃鋆 on 24-9-8.
//
#include "../week01.h"

namespace DAG {
	class Graph {
	public:
		explicit Graph(int n) :
			adjList(n), visited(n, false) {
		}

		// 添加边（有向图）
		void addEdge(int u, int v) {
			adjList[u].push_back(v); // u -> v
		}

		// 执行拓扑排序
		void topoSort() {
			std::stack<int> topoStack;

			// 遍历所有顶点
			for (int i = 0; i < adjList.size(); i++) {
				if (!visited[i]) {
					dfs(i, topoStack);
				}
			}

			// 输出拓扑排序
			std::cout << "拓扑排序: ";
			while (!topoStack.empty()) {
				std::cout << topoStack.top() << " ";
				topoStack.pop();
			}
			std::cout << std::endl;
		}

	private:
		std::vector<std::vector<int>> adjList; // 邻接列表
		std::vector<bool> visited; // 访问标记数组

		// DFS 递归函数
		void dfs(int node, std::stack<int> &topoStack) {
			visited[node] = true;

			// 递归访问所有邻居
			for (int neighbor : adjList[node]) {
				if (!visited[neighbor]) {
					dfs(neighbor, topoStack);
				}
			}

			// 当前节点访问完，加入栈
			topoStack.push(node);
		}
	};
}

int DAG_test() {
	int V = 6; // 顶点个数
	DAG::Graph graph(V);

	// 添加有向边
	graph.addEdge(5, 2);
	graph.addEdge(5, 0);
	graph.addEdge(4, 0);
	graph.addEdge(4, 1);
	graph.addEdge(2, 3);
	graph.addEdge(3, 1);

	// 执行拓扑排序
	graph.topoSort();

	return 0;
}
