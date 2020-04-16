#pragma once
# include <iostream>  
# include <vector>  
# include <fstream>  
# include <sstream>  
# include <string>  
# include <cstdlib>  
# include <ctime>  
# include <cmath>  
# include <climits>  

using namespace std;

/* function prototype */
void LoadGraph(vector<vector<int> >&, string);
void PrintGraph(vector<vector<int> >&);
int Karger(vector<vector<int>>&);
void RandomSelectEdge(vector<vector<int>>&, int&, int&);
void MergeVertices(vector<vector<int>>&, int&, int&);
void RemoveSelfLoops(vector<vector<int>>&, int&, int&);