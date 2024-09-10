//
// Created by 李勃鋆 on 24-9-8.
//
#include "../week01.h"

namespace BFS {
	class Graph {
	public:
		// 构造函数，n为顶点个数
		Graph(int n) : adjList(n) {}

		// 添加边（无向图）
		void addEdge(int u, int v) {
			adjList[u].push_back(v);  // u -> v
			adjList[v].push_back(u);  // v -> u
		}

		// 使用广度优先搜索找到从起点到其他顶点的最短路径
		void bfs(int start) {
			std::vector<int> distance(adjList.size(), INT_MAX);  // 距离数组，初始化为无穷大
			std::vector<int> parent(adjList.size(), -1);         // 父节点数组，初始化为-1
			std::queue<int> q;

			// 起点的距离为0，加入队列
			distance[start] = 0;
			q.push(start);

			// 开始BFS
			while (!q.empty()) {
				int current = q.front();
				q.pop();

				// 遍历当前节点的所有邻居
				for (int neighbor : adjList[current]) {
					if (distance[neighbor] == INT_MAX) {  // 如果未访问
						distance[neighbor] = distance[current] + 1;  // 更新邻居的距离
						parent[neighbor] = current;  // 记录路径
						q.push(neighbor);  // 将邻居加入队列
					}
				}
			}

			// 打印结果
			for (int i = 0; i < adjList.size(); i++) {
				std::cout << "从 " << start << " 到 " << i << " 的最短距离: " << distance[i] << std::endl;
				std::cout << "路径为: ";
				printPath(i, parent);
				std::cout << std::endl;
			}
		}

	private:
		std::vector<std::vector<int>> adjList;  // 邻接列表

		// 递归打印路径
		void printPath(int node, const std::vector<int>& parent) {
			if (parent[node] == -1) {
				std::cout << node;
				return;
			}
			printPath(parent[node], parent);
			std::cout << " -> " << node;
		}
	};
}

int BFS_test() {
	int V = 6;  // 顶点个数
	BFS::Graph graph(V);

	// 添加边
	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(1, 3);
	graph.addEdge(1, 4);
	graph.addEdge(2, 4);
	graph.addEdge(3, 5);
	graph.addEdge(4, 5);

	// 从顶点0开始执行广度优先搜索
	graph.bfs(0);

	return 0;
}
