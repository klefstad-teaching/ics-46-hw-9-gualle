#include "dijkstras.h"
#include <algorithm>
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
	int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
	distances[source] = 0;
    previous.resize(numVertices, -1);  //in ppt said undefined ,but -1 might be more clear for me
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap; //the defalt is maxheap
    minHeap.push({0,source}); //easier to compare for pq since i don't use node
	
    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;
        for (const Edge& edge :G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
	vector<int> path;
    if (previous[destination] == -1) {
        return path;
    }
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total){
	 if (total == INF) { 
        cout << "No path found" << endl;
        return;
    }
	
	for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " "; 
    }
    cout << "\nTotal cost is " << total <<endl;
}
