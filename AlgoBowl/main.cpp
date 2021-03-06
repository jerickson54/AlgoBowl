#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <set>
#include <time.h>

using namespace std;


struct algoBowl {

	int vertices;
	int edge;
	int weight;

	algoBowl(int v, int e, int w) {
		vertices = v;
		edge = e;
		weight = w;

	}

	friend bool operator <(const algoBowl& x, const algoBowl& y) {
		return x.weight < y.weight;
	}
};



 

vector<vector<int>> loadPoints( int  &n, int  &m, vector<algoBowl> &allNodes);
void printMatrix(vector<vector<int>> adjMatrix, int n);
void chronicStupididty(vector<vector<int>> adjMatrix, set<int>& firstContainer, set<int>& secondContainer, vector< algoBowl> allNodes, int& finalWeight);
void printAllNodes(vector < algoBowl> allNodes);
void makeOutput(int totalWeight, set<int> firstContainer, set<int> secondContainer);
void inputGeneratorAllNodesTouching();
void inputGeneratorTouchingOne();


int main() {

	
	//vector<Graph> allNodes;
	vector<algoBowl> allNodes;
	vector <vector<int>> adjMatrix;
	int numVertices;
	int numEdges;
	int totalWeight = 0;

	//final containers
	set<int> firstContainer;
	set<int> secondContainer;


	adjMatrix = loadPoints( numVertices, numEdges,allNodes);
	//printAllNodes(allNodes);
	chronicStupididty(adjMatrix, firstContainer, secondContainer,allNodes,totalWeight);
	//printMatrix(adjMatrix, numVertices);
	makeOutput(totalWeight, firstContainer, secondContainer);

	//inputGeneratorAllNodesTouching();
	//inputGeneratorTouchingOne();




	system("pause");



	

	



}

void printAllNodes(vector < algoBowl> allNodes) {

	for (auto n : allNodes) {
		cout << n.vertices << " " << n.edge << " " << n.weight << endl;
	}
}

void chronicStupididty(vector<vector<int>> adjMatrix, set<int>& firstContainer, set<int>& secondContainer, vector<algoBowl> allNodes, int& finalWeight) {

	std::priority_queue <algoBowl> dp;
	int maxSize = adjMatrix.size()/ 2;


	for (auto p : allNodes)
		dp.push(p);

	//cout << dp.top().weight << endl;

	while (!dp.empty()) {

		//cout << dp.top().weight << endl;
		


		algoBowl temp = dp.top();
		dp.pop();

		
	
		// if vertices already in first container, we need to add the edge to a contianer
		if (firstContainer.find(temp.vertices) != firstContainer.end()) {
			// if the first container isn't already full add to first container, otherwise add to second container
			if (firstContainer.size() < maxSize) {
				if(secondContainer.find(temp.edge) == secondContainer.end())
				firstContainer.insert(temp.edge);
			}
			else {
				if(firstContainer.find(temp.edge) == firstContainer.end())
				secondContainer.insert(temp.edge);
			}
			
		}

		// if edge alread in first container
		else if (firstContainer.find(temp.edge) != firstContainer.end()) {
			// if the first container isn't already full add to first container, otherwise add to second container
			if (firstContainer.size() < maxSize) {
				if (secondContainer.find(temp.vertices) == secondContainer.end())
				firstContainer.insert(temp.vertices);
			}
			else {
				if (firstContainer.find(temp.vertices) == firstContainer.end())
				secondContainer.insert(temp.vertices);
			}
		}

		// if vertices in second container
		else if (secondContainer.find(temp.vertices) != secondContainer.end()) {
			// if the second container isn't already full add to second container, otherwise add to first container
			if (secondContainer.size() < maxSize) {
				if (firstContainer.find(temp.edge) == firstContainer.end())
				secondContainer.insert(temp.edge);
			}
			else {
				if (secondContainer.find(temp.edge) == secondContainer.end())
				firstContainer.insert(temp.edge);
			}
		}
		
		// if edge in second container
		else if (secondContainer.find(temp.edge) != secondContainer.end()) {
			// if the second container isn't already full add to second container, otherwise add to first container
			if (secondContainer.size() < maxSize) {
				if (firstContainer.find(temp.vertices) == firstContainer.end())
				secondContainer.insert(temp.vertices);
			}
			else {
				if (secondContainer.find(temp.vertices) == secondContainer.end())
				firstContainer.insert(temp.vertices);
			}
		}

		// if neither nodes are in either container yet, add them to the smaller container
		else {
			//cout << "inside the else" << endl;
			if (firstContainer.size() < secondContainer.size()) {
				if (secondContainer.find(temp.vertices) == secondContainer.end())
				firstContainer.insert(temp.vertices);
			}
			else {
				if (firstContainer.find(temp.vertices) == firstContainer.end())
				secondContainer.insert(temp.vertices);
			}

			if (firstContainer.size() < secondContainer.size()) {
				if (secondContainer.find(temp.edge) == secondContainer.end())
				firstContainer.insert(temp.edge);
			}
			else {
				if (firstContainer.find(temp.edge) == firstContainer.end())
				secondContainer.insert(temp.edge);
			}

		}

		

		
	}


	// Unconnected nodes, add to smaller container
	for (int i = 1; i < adjMatrix.size(); i++) {
		if (secondContainer.find(i) == secondContainer.end() && firstContainer.find(i) == firstContainer.end()) {
			if (firstContainer.size() < secondContainer.size()) {
				firstContainer.insert(i);
			}
			else {
				secondContainer.insert(i);
			}
		}
	}


	set<int>::iterator it;
	set<int>::iterator it2;
	for (it = firstContainer.begin(); it != firstContainer.end();++it) {
		for (it2 = secondContainer.begin(); it2 != secondContainer.end();++it2) {
			finalWeight += adjMatrix[*it - 1][*it2 - 1];
			//cout << *it << " " << *it2 << endl;
		}

	}



}

vector<vector<int>> loadPoints( int  &n, int  &m, vector <algoBowl>& allNodes) {

	int node;
	int adj;
	int weight;


		

	ifstream file("input.txt");

	if (file.fail()) {
		cerr << "You goofed";
		exit(1);
	}

	file >> n >> m;

	vector<vector <int>> adjMat(n,vector<int> (n));


	while (file >> node >> adj >> weight) {

		if (weight >= 1 && weight <= 50) {

			algoBowl temp(node, adj, weight);
			allNodes.push_back(temp);
			adjMat[node - 1][adj - 1] = weight;
			adjMat[adj - 1][node - 1] = weight;
		}

		else
			cout << "One of the weights in the input file is invalid." << endl;
		

	

	}

	file.close();



	return adjMat;



}
void printMatrix(vector<vector<int>> adjMatrix, int n){

	
	for (int i = 0; i < n;++i) {
		for (int j = 0; j < n; ++j) {
			cout << adjMatrix.at(i).at(j) << " ";
		}
		cout << endl;
	}
	

	
}

void makeOutput(int totalWeight, set<int> firstContainer, set<int> secondContainer) {

	ofstream output("output.txt");

	if (output.is_open()) {

		output << totalWeight << endl;

		for (auto i : firstContainer)
			output << i << " ";

			output << endl;

	
		for (auto i : secondContainer)
			output << i << " " ;

		output << endl;

	}

	output.close();

}

void inputGeneratorAllNodesTouching() {


	ofstream output("genInput12.txt");

	int numNodes = 12;
	//assuming every node is touching every other node
	int numEdges = (((numNodes-1) * (numNodes-1))+(numNodes-1)) / 2;
	srand(time(NULL));
	
	if (output.is_open()) {

		output << numNodes << " " << numEdges << endl;

		for (int i = 1; i <= numNodes; ++i) {
			for (int j = i+1; j <= numNodes; ++j) {
				output << i << " " << j << " " << rand() % 49 + 1 <<endl;
			}
		}


	}

	output.close();

}

void inputGeneratorTouchingOne() {


	ofstream output("genInputTouch10.txt");

	int numNodes = 10;
	//assuming every node is touching one other node
	int numEdges = numNodes;
	srand(time(NULL));

	//keep set to keep track of which nodes are touching
	vector<int> randomizeInt;
	//keep track so we dont get reverse of itself
	vector<int> dontAllowSelf(numNodes);

	for (int i = 1; i <= numNodes; ++i)
		randomizeInt.push_back(i);
	std::random_shuffle(randomizeInt.begin(), randomizeInt.end());

	

	if (output.is_open()) {

		output << numNodes << " " << numEdges << endl;

		for (int i = 1; i <= numNodes; ++i) {
			
			while (true) {
				if (randomizeInt.at(0) != i) {
					output << i << " " << randomizeInt.at(0) << " " << rand() % 49 + 1 << endl;
					//dontAllowSelf.at(randomizeInt.at(0)) = i;
					randomizeInt.erase(randomizeInt.begin(), randomizeInt.begin() + 1);
					break;
				}
				else
					std::random_shuffle(randomizeInt.begin(), randomizeInt.end());

			}
			
		}


	}

	output.close();

}




