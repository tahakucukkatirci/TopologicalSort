#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <list>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
using namespace std;

struct Vertex{
	vector< pair<int,int> > neighbors;
	bool visited;
};

vector<Vertex> cities;
int noOfCities, noOfRoads, source, target;

void importData(char* infileName){
	fstream file(infileName);
	file >> noOfCities;
	cities.resize(noOfCities+1);
	file >> noOfRoads;
	file >> source;
	file >> target;
	for(int i=1; i<=noOfCities; i++){
		cities[i].visited = false;
	}
	for(int i=1; i<=noOfRoads; i++){
		int cityI, cityJ, distance;
		file >> cityI;
		file >> cityJ;
		file >> distance;
		pair <int,int> temp;
		temp.first = cityJ;
		temp.second = distance;
		cities[cityI].neighbors.push_back(temp);
	}
}

void sorting(int v,stack<int>* s){
	cities[v].visited=true;
	for(int i=0; i<cities[v].neighbors.size(); i++){
		if(cities[cities[v].neighbors[i].first].visited==false){
			sorting(cities[v].neighbors[i].first,s);
		}
	}
	s->push(v);
}
void topologicalSort(stack<int>* s){
	for(int i=1; i<=noOfCities; i++){
		if(cities[i].visited==false){
			sorting(i,s);
		}
	}
}

int longestPath(stack<int>* s){
	int distance[noOfCities+1];
	for(int i=1; i<=noOfCities; i++){
		distance[i] = -1;
	}
	distance[source] = 0;
	int temp=-1;
	while(temp!=target){
		temp=s->top();							
		s->pop();
		if(distance[temp] == -1)
			continue;
		if(distance[temp] != -1){
			for(int i=0; i<cities[temp].neighbors.size(); i++){
				if(distance[cities[temp].neighbors[i].first] < distance[temp] + cities[temp].neighbors[i].second){
					distance[cities[temp].neighbors[i].first] = distance[temp] + cities[temp].neighbors[i].second;
				}
			}
		}
	}
	return distance[target];

}
int main(int argc,char* argv[]){
	if(argc!=3){
		printf("Usage: ./project5 infile outfile\n");
		return 0;
	}
	importData(argv[1]);
	stack<int> s;
	topologicalSort(&s);
	int x = longestPath(&s);
	ofstream myfile(argv[2]);
	myfile << x << endl;
	//	return 0;
}


