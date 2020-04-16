#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
#include "RandomizedContraction.h"

using namespace std;

/* Load the graph */
void LoadGraph(vector<vector<int> >& graph, string filename) {
    ifstream infile;
    infile.open(filename, ios::in);
    string line;
    while (getline(infile, line)) {
        vector<int> tmp_list;
        istringstream istr(line);
        int tmp=0;
        while (istr >> tmp)
            tmp_list.push_back(tmp);
        graph.push_back(tmp_list);
    }
    infile.close();
}

/* Print the graph in adjacency list representation*/
void PrintGraph(vector<vector<int> >& graph) {
    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = 0; j < graph[i].size(); ++j)
            cout << graph[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

/* Perform Karger Contraction */
int Karger(vector<vector<int>>& graph) {
    while (graph.size() > 2) {
        int index_u = 0;
        int index_v = 0;
        RandomSelectEdge(graph, index_u, index_v);
        MergeVertices(graph, index_u, index_v);
        RemoveSelfLoops(graph, index_u, index_v);
    }
    return graph[0].size() - 1;
}

/* Randomly select edge u-v */
void RandomSelectEdge(vector<vector<int>>& graph, int& index_u, int& index_v) {

    index_u = rand() % graph.size();
    int tmp_v = (rand() % (graph[index_u].size() - 1)) + 1;
    for (size_t i = 0; i < graph.size(); ++i)
        if (graph[i][0] == graph[index_u][tmp_v]) {
            index_v = i;
            break;
        }
}
/* Merge vertices u and v, keep u, delete v */
void MergeVertices(vector<vector<int>>& graph, int& index_u, int& index_v) {
    for (size_t i = 0; i < graph.size(); ++i) {
        if (i != index_v) {
            for (size_t j = 1; j < graph[i].size(); ++j) {
                if (graph[i][j] == graph[index_v][0])
                    graph[i][j] = graph[index_u][0];
            }
        }
    }
    for (size_t i = 1; i < graph[index_v].size(); ++i)
        graph[index_u].push_back(graph[index_v][i]);
}

/* Remove self-loopS */
void RemoveSelfLoops(vector<vector<int>>& graph, int& index_u, int& index_v) {
    for (size_t i = 1; i < graph[index_u].size(); ++i)
        if (graph[index_u][i] == graph[index_u][0]) {
            graph[index_u].erase(graph[index_u].begin() + i);
            --i;
        }
    graph.erase(graph.begin() + index_v);
}

int main(int argc, char** argv) {

    vector<vector<int> > graph;
    /* store the elements in txt file into adjacency list */
    LoadGraph(graph, "kargerMinCut.txt");
    vector<vector<int>> original_graph = graph;
    PrintGraph(graph);
    srand((unsigned)time(NULL));

    /* karger contraction */
    int min_cut = INT_MAX;
    double trials = pow(graph.size(), 2) * log10(graph.size());     
    for (double i = 0; i < trials; ++i) {
        graph = original_graph;
        int inter_val = Karger(graph);
        min_cut = std::min(inter_val, min_cut);        
    }
    cout << "Karger's Minimum Cut: " << min_cut << endl;

    return 0;
}