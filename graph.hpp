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

	template<typename Vertex, typename Weigth>
	struct Edge {
		Vertex vertex;
		Weigth weigth;

		Edge(const Vertex& _vertex, Weigth _weigth) :vertex(_vertex), weigth(_weigth) {};

	};

	template<typename Vertex, typename Weigth>
	bool operator<(const Edge<Vertex, Weigth>& e1, const Edge<Vertex, Weigth>& e2) {
		return e1.weigth < e2.weigth;
	}
	template<typename Vertex, typename Weigth>
	bool operator>(const Edge<Vertex, Weigth>& e1, const Edge<Vertex, Weigth>& e2) {
		return e1.weigth > e2.weigth;
	}

	template<typename Vertex, typename Weight>
	class Graph : public std::unordered_map<Vertex, std::vector<Edge<Vertex, Weight>>> {
	private:
		void setDist(std::unordered_map<Vertex, Weight>& dist, const Vertex& vertex) {
			try {
				dist.at(vertex);
			} catch (...) {
				dist[vertex] = UINT_MAX;
			}
		}

		void setDist2(std::unordered_map<Vertex, Weight>& dist, const Vertex& vertex) {
			if (dist.find(vertex) == dist.end()) {
				dist[vertex] = UINT_MAX;
			}
		}

		bool dfsRecursive(const Vertex& start, const Vertex& end, std::unordered_set<Vertex>& visited) {
			visited.insert(start);

			typename Graph::iterator curNode = this->find(start);
			for (typename std::vector<Edge<Vertex, Weight>>::iterator it = curNode->second.begin(); it != curNode->second.end(); ++it) {
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
			for (typename std::vector<Edge<Vertex, Weight>>::iterator it = curNode->second.begin(); it != curNode->second.end(); ++it) {
				if (visited.count((*it).vertex) == 0) {
					topologicalSortRecursive((*it).vertex, visited, sorted);
				}
			}
			sorted.push(curNode->first);
		}

	public:
		//returns the minumim distance between s and d
		Weight dijkstra(const Vertex& s, const Vertex& d) {
			std::unordered_set<Vertex> marked;
			std::unordered_map<Vertex, Weight> dist;
			std::priority_queue<Edge<Vertex, Weight>, std::vector<Edge<Vertex, Weight>>, std::greater<Edge<Vertex, Weight>>> priorityQueue;
			priorityQueue.push(Edge<Vertex, Weight>(s, 0));
			dist[s] = 0;
			while (!priorityQueue.empty()) {
				Edge<Vertex, Weight> edge = priorityQueue.top();
				priorityQueue.pop();
				if (marked.count(edge.vertex) == 0) {
					marked.insert(edge.vertex);
					try {
						for (Edge<Vertex, Weight> e : this->at(edge.vertex)) {
							setDist(dist, edge.vertex);
							setDist(dist, e.vertex);
							if (marked.count(e.vertex) == 0 && e.weigth + dist[edge.vertex] < dist[e.vertex]) {
								priorityQueue.push(Edge<Vertex, Weight>(e.vertex, dist[e.vertex] = e.weigth + dist[edge.vertex]));
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
		Weight prim_jarnik() {
			Vertex start = this->begin().operator*().first;
			Weight sum = 0;
			std::unordered_set<Vertex> marked;
			std::unordered_map<Vertex, Weight> dist;
			std::priority_queue<Edge<Vertex, Weight>, std::vector<Edge<Vertex, Weight>>, std::greater<Edge<Vertex, Weight>>> priorityQueue;
			priorityQueue.push(Edge<Vertex, Weight>(start, 0));
			dist[start] = 0;
			while (!priorityQueue.empty()) {
				Edge<Vertex, Weight> edge = priorityQueue.top();
				priorityQueue.pop();
				if (marked.count(edge.vertex) == 0) {
					marked.insert(edge.vertex);
					sum += edge.weigth;
					try {
						for (Edge<Vertex, Weight> e : this->at(edge.vertex)) {
							setDist2(dist, edge.vertex);
							setDist2(dist, e.vertex);
							if (marked.count(e.vertex) == 0 && e.weigth < dist[e.vertex]) {
								priorityQueue.push(Edge<Vertex, Weight>(e.vertex, e.weigth));
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

				for (typename std::vector<Edge<Vertex, Weight>>::iterator it = (*curNode).second.begin(); it != (*curNode).second.end(); ++it) {
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
			for (std::pair<Vertex, std::vector<Edge<Vertex, Weight>>> start: *this) {
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
