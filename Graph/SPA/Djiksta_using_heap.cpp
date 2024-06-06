/*
Time Complexity: O(E * logV), Where E is the number of edges and V is the number of vertices.
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
    
    void shortestPath(int src){
        int dist[v];
        for(int i=0;i<v;i++)
            dist[i] = INT_MAX; //marking all distances as infinite initially
            
        priority_queue<iPair, vector<iPair>, greater<iPair>> pq; //min heap to maintain minimum distance node at top
        dist[src] = 0; //src->src dist = 0
        pq.push({0, src});
        
        while(!pq.empty()){
            int u = pq.top().second; //the vertex which has minimum distance from source
            pq.pop(); //removing it from heap because that it is finalised
            
            for(auto& p : adj[u]){ //traversing all adjacent nodes
                int adjNode = p.first;
                int w = p.second;
                if(dist[adjNode] > dist[u]+w){ //relaxing
                    dist[adjNode] = dist[u]+w;
                    pq.push({dist[adjNode], adjNode}); //putting them in pq because they are yet to be finalised
                }
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