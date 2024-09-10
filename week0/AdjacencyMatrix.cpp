//
// Created by 李勃鋆 on 24-9-8.
//
#include "../week01.h"

namespace AdMatrix {
	class Graph {
	public:
		// 构造函数，n为顶点个数
		Graph(int n) :
			adjMatrix(n, std::vector<int>(n, 0)) {
		}

		// 添加边（无向图）
		void addEdge(int u, int v) {
			adjMatrix[u][v] = 1; // 如果是有权图，可以用边的权重替代1
			adjMatrix[v][u] = 1; // 无向图，u -> v 和 v -> u 都需要
		}

		// 打印邻接矩阵
		void printGraph() {
			for (const auto &row : adjMatrix) {
				for (int val : row) {
					std::cout << val << " ";
				}
				std::cout << std::endl;
			}
		}

	private:
		std::vector<std::vector<int>> adjMatrix; // 邻接矩阵
	};
}


int AdMatrix_test() {
	int V = 4; // 顶点个数
	AdMatrix::Graph graph(V);

	// 添加边
	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(1, 2);
	graph.addEdge(2, 3);

	// 打印图的邻接矩阵
	graph.printGraph();

	return 0;
}
