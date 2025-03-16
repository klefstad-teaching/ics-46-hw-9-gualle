#include "dijkstras.h"

using namespace std;

int main() {
    string filename ="small.txt";
    Graph graph;
    file_to_graph(filename, graph);
    int source=0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(graph, source, previous);

    for (int i = 0; i < graph.numVertices; ++i) {
        if (distances[i] == INF) continue;
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}
