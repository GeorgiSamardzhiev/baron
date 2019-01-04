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

	template<typename Vertex>
	struct Edge {
		Vertex vertex;
		int weigth;

		Edge(const Vertex& _vertex, int _weigth) :vertex(_vertex), weigth(_weigth) {};

	};

	template<typename Vertex>
	bool operator<(const Edge<Vertex>& e1, const Edge<Vertex>& e2) {
		return e1.weigth < e2.weigth;
	}
	template<typename Vertex>
	bool operator>(const Edge<Vertex>& e1, const Edge<Vertex>& e2) {
		return e1.weigth > e2.weigth;
	}

	template<typename Vertex>
	class Graph : public std::unordered_map<Vertex, std::vector<Edge<Vertex>>> {
	private:
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

		bool dfsRecursive(const Vertex& start, const Vertex& end, std::unordered_set<Vertex>& visited) {
			visited.insert(start);

			typename Graph::iterator curNode = this->find(start);
			for (typename std::vector<Edge<Vertex>>::iterator it = curNode->second.begin(); it != curNode->second.end(); ++it) {
				if (visited.count((*it).vertex) == 0) {
					if (start == end) {
						return true;
					}
					return dfsRecursive((*it).vertex, end, visited);
				}
			}
			return false;
		}

		void topologicalSortRecursive(const Vertex& start, std::unordered_set<Vertex>& visited, std::stack<Vertex>& sorted) {
			visited.insert(start);

			typename Graph::iterator curNode = this->find(start);
			for (typename std::vector<Edge<Vertex>>::iterator it = curNode->second.begin(); it != curNode->second.end(); ++it) {
				if (visited.count((*it).vertex) == 0) {
					topologicalSortRecursive((*it).vertex, visited, sorted);
				}
			}
			sorted.push(curNode->first);
		}

	public:
		//returns the minumim distance between s and d
		int dijkstra(const Vertex& s, const Vertex& d) {
			std::unordered_set<Vertex> marked;
			std::unordered_map<Vertex, unsigned int> dist;
			std::priority_queue<Edge<Vertex>, std::vector<Edge<Vertex>>, std::greater<Edge<Vertex>>> priorityQueue;
			priorityQueue.push(Edge<Vertex>(s, 0));
			dist[s] = 0;
			while (!priorityQueue.empty()) {
				Edge<Vertex> edge = priorityQueue.top();
				priorityQueue.pop();
				if (marked.count(edge.vertex) == 0) {
					marked.insert(edge.vertex);
					try {
						for (Edge<Vertex> e : this->at(edge.vertex)) {
							setDist(dist, edge.vertex);
							setDist(dist, e.vertex);
							if (marked.count(e.vertex) == 0 && e.weigth + dist[edge.vertex] < dist[e.vertex]) {
								priorityQueue.push(Edge<Vertex>(e.vertex, dist[e.vertex] = e.weigth + dist[edge.vertex]));
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

		//returns sum of edge weights of MST of graph
		int prim_jarnik() {
			Vertex start = this->begin().operator*().first;
			int sum = 0;
			std::unordered_set<Vertex> marked;
			std::unordered_map<Vertex, int> dist;
			std::priority_queue<Edge<Vertex>, std::vector<Edge<Vertex>>, std::greater<Edge<Vertex>>> priorityQueue;
			priorityQueue.push(Edge<Vertex>(start, 0));
			dist[start] = 0;
			while (!priorityQueue.empty()) {
				Edge<Vertex> edge = priorityQueue.top();
				priorityQueue.pop();
				if (marked.count(edge.vertex) == 0) {
					marked.insert(edge.vertex);
					sum += edge.weigth;
					try {
						for (Edge<Vertex> e : this->at(edge.vertex)) {
							setDist2(dist, edge.vertex);
							setDist2(dist, e.vertex);
							if (marked.count(e.vertex) == 0 && e.weigth < dist[e.vertex]) {
								priorityQueue.push(Edge<Vertex>(e.vertex, e.weigth));
							}
						}
					} catch (...) {}
				}
			}
			return sum;
		}

		bool dfs(const Vertex& start, const Vertex& end) {
			std::unordered_set<Vertex> visited;
			return dfsRecursive(start, end, visited);
		}

		bool bfs(const Vertex& start, const Vertex& end) {
			std::queue<Vertex> queue;
			std::unordered_set<Vertex> visited;

			queue.push(start);
			visited.insert(start);
			while (!queue.empty()) {
				typename Graph::iterator curNode = this->find(queue.front());
				queue.pop();

				for (typename std::vector<Edge<Vertex>>::iterator it = (*curNode).second.begin(); it != (*curNode).second.end(); ++it) {
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

		std::vector<Vertex> topologicalSort() {
			std::unordered_set<Vertex> visited;
			std::stack<Vertex> sorted;
			std::vector<Vertex> res;
			for (std::pair<Vertex, std::vector<Edge<Vertex>>> start: *this) {
				if (visited.count(start.first) == 0) {
					topologicalSortRecursive(start.first, visited, sorted);
				}
			}
			while (!sorted.empty()) {
				res.push_back(sorted.top());
				sorted.pop();
			}
			return res;
		}
	};

}

#endif // !GRAPH_HPP