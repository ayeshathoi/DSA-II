#include <bits/stdc++.h>
using namespace std;

void printSolutionMatrix(vector<vector<int>> const &weight)
{
    int n = weight.size();
    cout << "Shortest distance matrix"<<endl;
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
        {
            if (weight[i][j] != INT_MAX)
            {
                cout<<setw(7);
                cout<<weight[i][j]<<" ";
            }
            else
            {
                cout<<setw(7);
                cout<<"INF"<<" ";
            }
        }
        cout<<endl;
    }
}

void floydWarshallAlgorithm(vector<vector<int>> const &vec)
{
    int vertex_number = vec.size();

    if (vertex_number == 0)
    {
        return;
    }

    vector<vector<int>> weight(vertex_number, vector<int>(vertex_number));

    for (int i = 0; i < vertex_number; i++)
    {
        for (int j = 0; j < vertex_number; j++)
        {
            weight[i][j] = vec[i][j];
        }
    }

    for (int k = 0; k < vertex_number; k++)
    {
        for (int i = 0; i < vertex_number; i++)
        {
            for (int j = 0; j < vertex_number; j++)
            {
                if (weight[i][k] != INT_MAX && weight[k][j] != INT_MAX
                        && weight[i][k] + weight[k][j] < weight[i][j])
                {
                    weight[i][j] = weight[i][k] + weight[k][j];
                }
            }
        }
    }
    printSolutionMatrix(weight);
}

int main()
{
    ifstream in("ssp.txt");
    int vertex,edges,vertex1,vertex2,weight;
    in>>vertex>>edges;
    vector<vector<int> > vec(vertex,vector<int>(vertex));

    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            if(i==j) vec[i][j]=0;
            else vec[i][j]=INT_MAX;
        }
    }
    for (int i = 0; i < edges; i++)
    {
        in>>vertex1>>vertex2>>weight;
        vec[vertex1-1][vertex2-1] = weight;
    }

    in.close();

    floydWarshallAlgorithm(vec);
    return 0;
}
