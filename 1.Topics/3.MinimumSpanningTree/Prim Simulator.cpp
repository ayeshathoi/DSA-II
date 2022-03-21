
#include <cstring>
#include <iostream>
using namespace std;

#define INF 9999999

int main()
{
    int no_edge;

    int V;
    cin>>V;
    int G[V][V];
    for(int i=0; i<V; i++)
        for(int j=0; j<V; j++)
            cin>>G[i][j];
    int selected[V];

    memset(selected, false, sizeof(selected));

    no_edge = 0;
    selected[0] = true;

    int x;
    int y;

    cout << "Edge"
         << " : "
         << "Weight";
    cout << endl;
    while (no_edge < V - 1)
    {
        int min = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < V; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < V; j++)
                {
                    if (!selected[j] && G[i][j])    // not in selected and there is an edge
                    {
                        if (min > G[i][j])
                        {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        cout << x << " - " << y << " :  " << G[x][y];
        cout << endl;
        selected[y] = true;
        no_edge++;
    }

    return 0;
}
