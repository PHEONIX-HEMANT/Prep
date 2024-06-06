/*
Time Complexity: O(V2)
Auxiliary Space: O(V)
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> iPair;

class Graph{
    int v;
    vector<iPair>* adj;
    public:
    Graph(int num){
        this->v = num;
        adj = new vector<iPair>[v];
    }
    
    void addEdge(int x, int y, int w){
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }
    
    int minDistance(int dist[], bool finalized[]){ //return the vertex which is not finalised and has min distance from src
        int vertex = -1, minDist = INT_MAX;
        for(int i=0;i<v;i++){
            if(finalized[i]==false && dist[i] < minDist){
                minDist = dist[i];
                vertex = i;
            }
        }
        return vertex;
    }
    
    void shortestPath(int src){
        int dist[v];
        bool finalized[v]; //set to maintain which vertices are finalised and which ones are yet to be finalised.
        for(int i=0;i<v;i++){
            dist[i] = INT_MAX; // initially distance to all vertices = INF
            finalized[i] = false; //initially marking all as not finalised
        }
        
        dist[src] = 0; //src to src dist = 0

        //in an interation we can finalise one vertex, so need v-1 interations to finalise all (one less because dont need to finalise the last one)
        for(int i=0;i<v-1;i++){
            int u = minDistance(dist, finalized); //getting the vertex which is not finalised and has min distance from src
            finalized[u] = true; // finalising it
            for(auto& p : adj[u]){ //relaxing all the adjacents nodes which are not finalised.
                int adjNode = p.first;
                int weight = p.second; 
                if(finalized[adjNode] == false && dist[adjNode] > dist[u]+weight)
                    dist[adjNode] = dist[u]+weight;
            }
        }
        
        for(int i=0;i<v;i++)
            cout<<dist[i]<<" ";
        cout<<endl;
    }
};

int main() {
	//code
	int t;
	cin>>t;
	while(t--)
    {
        int v, e;
        cin>>v>>e;
        Graph graph(v);
        for(int i=0;i<e;i++){
            int x,y,w;
            cin>>x>>y>>w;
            graph.addEdge(x, y, w);
        }
        int src;
        cin>>src;
        graph.shortestPath(src);
    }
	return 0;
}