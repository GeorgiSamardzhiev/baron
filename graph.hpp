#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits.h>
#include <functional>
#include <stack>

namespace baron {

	using Vertex = int;
	struct Edge {
		Vertex vertex;
		int weigth;

		Edge(const Vertex& _vertex, int _weigth) :vertex(_vertex), weigth(_weigth) {};
		friend bool operator<(const Edge& e1, const Edge& e2);
		friend bool operator>(const Edge& e1, const Edge& e2);

	};
	bool operator<(const Edge& e1, const Edge& e2) {
		return e1.weigth < e2.weigth;
	}
	bool operator>(const Edge& e1, const Edge& e2) {
		return e1.weigth > e2.weigth;
	}
	using Graph = std::unordered_map<Vertex, std::vector<Edge>>;

	void setDist(std::unordered_map<Vertex, unsigned int>& dist, const Vertex& vertex) {
		try {
			dist.at(vertex);
		} catch (...) {
			dist[vertex] = UINT_MAX;
		}
	}

	void setDist2(std::unordered_map<Vertex, int>& dist, const Vertex& vertex) {
		if (dist.find(vertex) == dist.end()) {
			dist[vertex] = UINT_MAX;
		}
	}

	//returns the minumim distance between s and d
	int dijkstra(const Graph& graph, const Vertex& s, const Vertex& d) {
		std::unordered_set<Vertex> marked;
		std::unordered_map<Vertex, unsigned int> dist;
		std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> priorityQueue;
		priorityQueue.push(Edge(s, 0));
		dist[s] = 0;
		while (!priorityQueue.empty()) {
			Edge edge = priorityQueue.top();
			priorityQueue.pop();
			if (marked.count(edge.vertex) == 0) {
				marked.insert(edge.vertex);
				try {
					for (Edge e : graph.at(edge.vertex)) {
						setDist(dist, edge.vertex);
						setDist(dist, e.vertex);
						if (marked.count(e.vertex) == 0 && e.weigth + dist[edge.vertex] < dist[e.vertex]) {
							priorityQueue.push(Edge(e.vertex, dist[e.vertex] = e.weigth + dist[edge.vertex]));
						}
					}
				} catch (...) {}
			}
		}
		try {
			return dist.at(d) == INT_MAX ? -1 : dist[d];
		} catch (...) {
			return -1;
		}
	}

	//returns MST of graph
	int prim_jarnik(const Graph& graph) {
		Vertex start = graph.begin().operator*().first;
		int sum = 0;
		std::unordered_set<Vertex> marked;
		std::unordered_map<Vertex, int> dist;
		std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> priorityQueue;
		priorityQueue.push(Edge(start, 0));
		dist[start] = 0;
		while (!priorityQueue.empty()) {
			Edge edge = priorityQueue.top();
			priorityQueue.pop();
			if (marked.count(edge.vertex) == 0) {
				marked.insert(edge.vertex);
				sum += edge.weigth;
				try {
					for (Edge e : graph.at(edge.vertex)) {
						setDist2(dist, edge.vertex);
						setDist2(dist, e.vertex);
						if (marked.count(e.vertex) == 0 && e.weigth < dist[e.vertex]) {
							priorityQueue.push(Edge(e.vertex, e.weigth));
						}
					}
				} catch (...) {}
			}
		}
		return sum;
	}

	bool dfsRecursive(Graph& graph, const Vertex& start, const Vertex& end, std::unordered_set<Vertex>& visited) {
		visited.insert(start);

		Graph::iterator curNode = graph.find(start);
		for (std::vector<Edge>::iterator it = curNode->second.begin(); it != curNode->second.end(); ++it) {
			if (visited.count((*it).vertex) == 0) {
				if (start == end) {
					return true;
				}
				dfsRecursive(graph, (*it).vertex, end, visited);
			}
		}
		return false;
	}

	bool dfs(Graph& graph, const Vertex& start, const Vertex& end) {
		std::unordered_set<Vertex> visited;
		return dfsRecursive(graph, start, end, visited);
	}

	bool bfs(Graph& graph, const Vertex& start, const Vertex& end) {
		std::queue<Vertex> queue;
		std::unordered_set<Vertex> visited;

		queue.push(start);
		visited.insert(start);
		while (!queue.empty()) {
			Graph::iterator curNode = graph.find(queue.front());
			queue.pop();

			for (std::vector<Edge>::iterator it = (*curNode).second.begin(); it != (*curNode).second.end(); ++it) {
				Vertex childNode = (*it).vertex;
				if (childNode == end) {
					return true;
				}
				if (visited.count(childNode) == 0) {
					queue.push(childNode);
					visited.insert(childNode);
				}
			}
		}
		return false;
	}

	void topologicalSortRecursive(Graph& graph, const Vertex& start, std::unordered_set<Vertex>& visited, std::stack<Vertex>& sorted) {
		visited.insert(start);

		Graph::iterator curNode = graph.find(start);
		for (std::vector<Edge>::iterator it = curNode->second.begin(); it != curNode->second.end(); ++it) {
			if (visited.count((*it).vertex) == 0) {
				topologicalSortRecursive(graph, (*it).vertex, visited, sorted);
			}
		}
		sorted.push(curNode->first);
	}

	std::vector<Vertex> topologicalSort(Graph& graph) {
		std::unordered_set<Vertex> visited;
		std::stack<Vertex> sorted;
		std::vector<Vertex> res;
		for (std::pair<Vertex, std::vector<Edge>> start: graph) {
			if (visited.count(start.first) == 0) {
				topologicalSortRecursive(graph, start.first, visited, sorted);
			}
		}
		while (!sorted.empty()) {
			res.push_back(sorted.top());
			sorted.pop();
		}
		return res;
	}
}

#endif // !GRAPH_HPP