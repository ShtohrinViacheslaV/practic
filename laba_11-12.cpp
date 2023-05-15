#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class Edge {
public:
	int m_numberOfVertex_1;
	int m_numberOfVertex_2;
	float m_weight;

public:
	Edge(int numberOfVertex_1, int numberOfVertex_2, float weight) :
		m_numberOfVertex_1(numberOfVertex_1),
		m_numberOfVertex_2(numberOfVertex_2),
		m_weight(weight) {}

	friend bool operator < (Edge& first, Edge& second) {
		if (first.m_weight < second.m_weight) {
			return true;
		}
		return false;
	}
};

class Kruskal {
protected:
	vector<Edge> m_startGraph;
	vector<Edge> m_readyTree;

	int* m_collisions;

public:
	pair<int, int> amount_op{ 0,0 };

protected:
	void initialize() {
		sort(m_startGraph.begin(), m_startGraph.end());

		m_collisions = new int[m_startGraph.size()];

		amount_op.first += 2;
		amount_op.second += 1;

		for (int i = 0; i < m_startGraph.size(); i++) {
			amount_op.second += 1;
			amount_op.first += 2;
			m_collisions[i] = i;
		}
	}

	int find_set(int position) {
		amount_op.second += 1;
		if (position == m_collisions[position]) {
			return position;
		}
		else {
			return find_set(m_collisions[position]);
		}
	}
public:
	Kruskal() {}

	void addEdge(int numberOfVertex_1, int numberOfVertex_2, float weight) {
		m_startGraph.push_back(Edge(numberOfVertex_1, numberOfVertex_2, weight));
	}

	void calculateTree() {
		int collisionNumber_1, collisionNumber_2;

		initialize();

		amount_op.first += 1;
		amount_op.second += 1;

		for (int i = 0; i < m_startGraph.size(); i++) {
			amount_op.first += 3;
			amount_op.second += 2;
			collisionNumber_1 = find_set(m_startGraph[i].m_numberOfVertex_1);
			collisionNumber_2 = find_set(m_startGraph[i].m_numberOfVertex_2);

			if (collisionNumber_1 != collisionNumber_2) {
				amount_op.first += 2;
				amount_op.second += 1;
				m_readyTree.push_back(m_startGraph[i]);

				m_collisions[collisionNumber_1] = m_collisions[collisionNumber_2];
			}
		}
	}

	void printStartGraph() {
		cout << "Start graph: " << endl;
		for (int i = 0; i < m_startGraph.size(); i++) {
			cout << "\t" << m_startGraph[i].m_numberOfVertex_1 << " " << m_startGraph[i].m_numberOfVertex_2 << " " << m_startGraph[i].m_weight << endl;
		}
		cout << endl;
	}

	void printReadyTree() {
		cout << "Ready tree: " << endl;
		for (int i = 0; i < m_readyTree.size(); i++) {
			cout << "\t" << m_readyTree[i].m_numberOfVertex_1 << " " << m_readyTree[i].m_numberOfVertex_2 << " " << m_readyTree[i].m_weight << endl;
		}
		cout << endl;
	}

	vector<Edge> getStartGraph() {
		return m_startGraph;
	}
};

class Prima {
protected:
	vector<Edge> m_startGraph;
	vector<Edge> m_readyTree;

	int m_sizeOfMAtrix;
	int** m_matrix;

public:
	pair<int, int> amount_op{ 0,0 };

protected:
	int findSizeOfMatrix() {
		int max_1 = m_startGraph[0].m_numberOfVertex_1;
		int max_2 = m_startGraph[0].m_numberOfVertex_2;

		for (int i = 1; i < m_startGraph.size(); i++) {
			if (m_startGraph[i].m_numberOfVertex_1 > max_1) {
				max_1 = m_startGraph[i].m_numberOfVertex_1;
			}
			if (m_startGraph[i].m_numberOfVertex_2 > max_2) {
				max_2 = m_startGraph[i].m_numberOfVertex_2;
			}
		}

		return max_1 > max_2 ? max_1 : max_2;
	}

	void convertGraphIntoMatrix() {
		m_sizeOfMAtrix = findSizeOfMatrix();

		m_matrix = new int* [m_sizeOfMAtrix];

		for (int i = 0; i < m_sizeOfMAtrix; i++) {
			m_matrix[i] = new int[m_sizeOfMAtrix];

			for (int j = 0; j < m_sizeOfMAtrix; j++) {
				m_matrix[i][j] = 0;
			}
		}

		for (int i = 0; i < m_startGraph.size(); i++) {
			m_matrix[m_startGraph[i].m_numberOfVertex_1 - 1][m_startGraph[i].m_numberOfVertex_2 - 1] = m_startGraph[i].m_weight;
			m_matrix[m_startGraph[i].m_numberOfVertex_2 - 1][m_startGraph[i].m_numberOfVertex_1 - 1] = m_startGraph[i].m_weight;
		}
	}

	int minKey(int* key, bool* mstSet) {
		amount_op.first += 1;
		int min = INT_MAX, min_index;

		for (int v = 0; v < m_sizeOfMAtrix; v++) {
			amount_op.first += 2;
			amount_op.second += 3;
			if (mstSet[v] == false && key[v] < min) {
				min = key[v], min_index = v;
			}
		}

		return min_index;
	}
public:
	Prima() {}

	void setStartGraph(vector<Edge> startGraph) {
		m_startGraph = startGraph;
		convertGraphIntoMatrix();
	}

	void printStartGraph() {
		cout << "Start graph: " << endl;
		for (int i = 0; i < m_startGraph.size(); i++) {
			cout << "\t" << m_startGraph[i].m_numberOfVertex_1 << " " << m_startGraph[i].m_numberOfVertex_2 << " " << m_startGraph[i].m_weight << endl;
		}
		cout << endl;
	}

	void printReadyTree() {
		cout << "Ready tree: " << endl;
		for (int i = 0; i < m_readyTree.size(); i++) {
			cout << "\t" << m_readyTree[i].m_numberOfVertex_1 << " " << m_readyTree[i].m_numberOfVertex_2 << " " << m_readyTree[i].m_weight << endl;
		}
		cout << endl;
	}

	void calculateTree() {
		amount_op.first += 5;
		int* parent = new int[m_sizeOfMAtrix];

		int* key = new int[m_sizeOfMAtrix];

		bool* mstSet = new bool[m_sizeOfMAtrix];

		for (int i = 0; i < m_sizeOfMAtrix; i++) {
			key[i] = INT_MAX;
			mstSet[i] = false;
			amount_op.first += 4;
			amount_op.second += 1;
		}

		key[0] = 0;
		parent[0] = -1;

		for (int count = 0; count < m_sizeOfMAtrix - 1; count++) {
			amount_op.first += 4;
			amount_op.second += 1;
			int u = minKey(key, mstSet);

			mstSet[u] = true;

			for (int v = 0; v < m_sizeOfMAtrix; v++) {
				amount_op.first += 2;
				amount_op.second += 3;
				if (m_matrix[u][v] and mstSet[v] == false and m_matrix[u][v] < key[v]) {
					amount_op.first += 2;
					parent[v] = u;
					key[v] = m_matrix[u][v];
				}
			}
		}

		for (int i = 1; i < m_sizeOfMAtrix; i++) {
			m_readyTree.push_back(Edge(parent[i] + 1, i + 1, m_matrix[i][parent[i]]));
		}
	}
};

int main() {
	Kruskal kruskal;
	Prima prima;

	kruskal.addEdge(1, 2, 5);
	kruskal.addEdge(1, 6, 4);
	kruskal.addEdge(1, 7, 6);
	kruskal.addEdge(2, 3, 10);
	kruskal.addEdge(2, 4, 2);
	kruskal.addEdge(3, 5, 12);
	kruskal.addEdge(4, 5, 9);
	kruskal.addEdge(4, 6, 11);
	kruskal.addEdge(4, 9, 4);
	kruskal.addEdge(5, 9, 5);
	kruskal.addEdge(6, 8, 15);
	kruskal.addEdge(6, 9, 13);
	kruskal.addEdge(7, 8, 16);
	kruskal.addEdge(7, 10, 9);
	kruskal.addEdge(8, 9, 10);
	kruskal.addEdge(8, 10, 5);
	kruskal.addEdge(9, 10, 11);

	kruskal.printStartGraph();
	cout << "Kruskal:" << endl;

	auto start_time = std::chrono::high_resolution_clock::now();
	kruskal.calculateTree();
	auto finish = std::chrono::high_resolution_clock::now();
	kruskal.printReadyTree();

	//cout << "\t-Number of assignment operations = " << amount_oper.first << ", number of comparisons operations = " << amount_oper.second << endl;
	cout << "\tKraskal time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start_time).count() << endl;
	cout << "Amount of assignments = " << kruskal.amount_op.first << ", amount of comparisons = " << kruskal.amount_op.second << endl << endl;;


	cout << "Prima:" << endl;
	prima.setStartGraph(kruskal.getStartGraph());

	start_time = std::chrono::high_resolution_clock::now();
	prima.calculateTree();
	finish = std::chrono::high_resolution_clock::now();
	prima.printReadyTree();

	cout << "\tPrima time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start_time).count() << endl << endl;
	cout << "Amount of assignments = " << prima.amount_op.first << ", amount of comparisons = " << prima.amount_op.second << endl;

	system("pause");
	return 0;
}
