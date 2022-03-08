#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

class Graph
{
    int vertex;
    list< pair<int, int> > *adj;
    int cost[1000];
public :
    Graph(int vertex);
    void addEdge(int src,int dest,int weight);
    void Dijkstra(int s,int d);
    void addCost(int origin,int cost);
    void printPath(int parent[], int j,int dist[]);
    int minDistance(int dist[], bool sptSet[]);
    int printSolution(int dist[], int n,int src,int dest,int parent[]);
    int printSol(int dist[], int n,int src,int dest,int parent[]);
};
Graph :: Graph(int V)
{
    this->vertex = V;
    adj = new list< pair<int, int> > [vertex];


}
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));

}
void Graph ::addCost(int u,int c)
{
    cost[u] = c;
}
int Graph:: minDistance(int dist[],
                        bool sptSet[])
{
    int min1 = INT_MAX, min_index;

    for (int v = 0; v < vertex; v++)
        if (sptSet[v] == false &&
                dist[v] <= min1)
            min1 = dist[v], min_index = v;

    return min_index;
}


void Graph:: printPath(int parent[], int j,int dist[])
{
    int k = j;
    if (parent[j] == INF)
        return;


    printPath(parent, parent[j],dist);

    cout<<"->" <<j;
}

int Graph:: printSol(int dist[], int n,int src,int dest,
                          int parent[])
{

    cout<<"Shortest path cost: "<<dist[dest]<<endl;
    cout<<src;
    dist[dest]+=cost[src];
    printPath(parent, dest,dist);
}
int Graph:: printSolution(int dist[], int n,int src,int dest,
                          int parent[])
{

    dist[dest]+=cost[src];
    printPath(parent, dest,dist);
}

void Graph::Dijkstra(int src,int dest)
{
    set< pair<int, int> > setdijkstra;

    int dist[vertex];
    int parent[vertex];
    bool visited[vertex];

    setdijkstra.insert(make_pair(0, src));
    parent[0] = INF;
    for (int i = 0; i < vertex; i++)
    {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[src] = 0;
    while (!setdijkstra.empty())
    {

        pair<int, int> curr_element = *(setdijkstra.begin());
        setdijkstra.erase(setdijkstra.begin());

        int u = curr_element.second;
        int min_distance = minDistance(dist, visited);
        visited[min_distance] = true;
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;

            if (!visited[v] && dist[v] > dist[u] + weight)
            {

                if (dist[v] != INF)
                    setdijkstra.erase(setdijkstra.find(make_pair(dist[v], v)));
                parent[v] = u;
                dist[v] = dist[u] + weight;
                dist[v]+=cost[v];
                setdijkstra.insert(make_pair(dist[v], v));
            }
        }
    }
    printSolution(dist, vertex, src,dest, parent);
    printPath(parent, dest,dist);
    printSol(dist, vertex, src,dest, parent);
}
int main()
{
    ifstream in("ssp.txt");
    int city, road, src,dest,weight,cost,vertex;
    in>>city>>road;
    Graph gr(city);
    for(int i = 0; i<city; i++)
    {
        in>>vertex>>cost;
        gr.addCost(vertex,cost);
    }
    for(int i = 0; i<road; i++)
    {
        in>>src>>dest>>weight;
        gr.addEdge(src,dest,weight);
    }
    int source, destination;
    in>>source>>destination;
    int choice;
    in.close();
    gr.Dijkstra(source,destination);
    return 0;

}
