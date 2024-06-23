#include <iostream> 
#include <iomanip> 
#include <vector>
#include <queue>
using namespace std;

struct edge{
    int cap, flow, dest;
    edge(int d, int c){
        cap = c;
        dest = d;
        flow = 0;
    }
};

struct MaxFlow{
    int n, s, t;
    vector<vector<int>> adj;
    vector<edge> ed;
    
    MaxFlow(int _n, int _s, int _t){
        n = _n;
        s = _s;
        t = _t;
        adj.resize(n);
    }
    
    void addEdge(int u, int v, int cap){
        adj[u].push_back(ed.size());
        ed.push_back(edge(v, cap));
        
        adj[v].push_back(ed.size());
        ed.push_back(edge(u, 0));
    }
    int bfs(){
        queue<int> q;
        q.push(s);
        vector<int> par(n, -2);
        par[s] = -1;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int x : adj[u]){
                if(ed[x].cap > ed[x].flow && par[ed[x].dest] == -2){
                    q.push(ed[x].dest);
                    par[ed[x].dest] = x;
                }
            }
        }
        
        if(par[t] == -2)return 0;
        
        int fl = 1e9;
        int p = t;
        while(par[p] != -1){
            int l = par[p];
            fl = min(ed[l].cap - ed[l].flow, fl);
            p = ed[l ^ 1].dest;
        }
        
        
        p = t;
        while(par[p] != -1){
            int l = par[p];
            ed[l].flow += fl;
            ed[l ^ 1].flow -= fl;
            p = ed[l ^ 1].dest;
        }
        
        return fl;
        
    }
    int maxFlow(){
        int ans = 0, f;
        while(f = bfs())
            ans += f;
        return ans;
    }
    void dfs(int ind, vector<int> &vis){
        vis[ind] = 1;
        for(auto x : adj[ind]){
            if(ed[x].cap > ed[x].flow && !vis[ed[x].dest])dfs(ed[x].dest, vis);
        }
    }
    void mincut(){
        maxFlow();
        vector<int> vis(n, 0);
        dfs(s, vis);
        for(int i = 0; i < n; i++){
            if(vis[i] == 0)continue;
            for(auto x : adj[i]){
                if(vis[ed[x].dest] || ed[x].cap == 0)continue;
                cout << i << " --> " << ed[x].dest << endl;
            }
        }
    }
};

int main(){
    int n, m, s, t;
    //Enter Nodes, Edge, Source, Sink // 0 indexed
    cin >> n >> m >> s >> t;
    MaxFlow fl(n, s, t);
    
    for(int i = 0; i < m; i++){
        //Enter Edges u v w
        int u, v, w;
        cin >> u >> v >> w;
        fl.addEdge(u, v, w);
    }
    
    cout << fl.maxFlow() << endl;
    fl.mincut();
}
