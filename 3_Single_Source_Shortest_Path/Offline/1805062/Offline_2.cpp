#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

class Graph
{
    int vertex;
    list< pair<int, int> > *adj;
public :
    Graph(int vertex);
    void addEdge(int src,int dest,int weight);
    void Dijkstra(int s,int d);
    void BellmanFord(int s,int d);
    void printPath(int parent[], int j);
    int minDistance(int dist[], bool sptSet[]);
    int printSolution(int dist[], int n,int src,int dest,int parent[]);
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


void Graph:: printPath(int parent[], int j)
{
    int k = j;
    if (parent[j] == INF)
        return;

    printPath(parent, parent[j]);

    cout<<"->" <<j;
}

int Graph:: printSolution(int dist[], int n,int src,int dest,
                          int parent[])
{
    cout<<"Shortest path cost: "<<dist[dest]<<endl;
    cout<<src;
    printPath(parent, dest);
}
void Graph::BellmanFord(int src,int dest)
{
    set< pair<int, int> > setbellfordman;

    int dist[vertex];
    int parent[vertex];
    bool visited[vertex];

    setbellfordman.insert(make_pair(0, src));
    parent[0] = INF;
    for (int i = 0; i < vertex; i++)
    {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[src] = 0;
    while (!setbellfordman.empty())
    {

        pair<int, int> curr_element = *(setbellfordman.begin());
        setbellfordman.erase(setbellfordman.begin());

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
                    setbellfordman.erase(setbellfordman.find(make_pair(dist[v], v)));
                parent[v] = u;
                dist[v] = dist[u] + weight;
                setbellfordman.insert(make_pair(dist[v], v));
            }
        }
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight)
            {

                if (dist[v] != INF)
                    cout<<"The graph contains a negative cycle"<<endl;
                return;
            }
        }
    }
    cout<<"The graph does not contain a negative cycle"<<endl;

    printSolution(dist, vertex, src,dest, parent);
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
                setdijkstra.insert(make_pair(dist[v], v));
            }
        }
    }
    printSolution(dist, vertex, src,dest, parent);
}
int main()
{
    ifstream in("ssp.txt");
    int city, road, sr,dest,weight;
    in>>city>>road;
    Graph gr(city);
    for(int i = 0; i<road; i++)
    {
        in>>sr>>dest>>weight;
        gr.addEdge(sr,dest,weight);
    }
    int source, destination;
    in>>source>>destination;
    int choice;
    cout<<"IF YOU HAVE NEGATIVE WEIGHT, YOU MUST IMPLEMENT BELLFORD"<<endl;
    cout<<"ENTER 1 IF YOU WANT TO YOU WANT TO IMPLEMENT DIJKSTRA ALGORITHM OR 2  TO IMPLEMENT BELLFORD ALGORITHM "<<endl;
    cout<<"ENTER YOUR CHOICE: ";
    in.close();
    cin>>choice;
    if(choice==1)
        gr.Dijkstra(source,destination);
    if(choice==2)
        gr.BellmanFord(source,destination);
    return 0;

}

