package com.company;

import java.util.*;

class Graph
{
    private int V;
    private LinkedList<Integer> adj[];

    Graph(int v)
    {
        V = v;
        adj = new LinkedList[v];
        for (int i = 0; i < v; ++i)
            adj[i] = new LinkedList();
    }

    void addEdge(int v, int w)
    {
        adj[v].add(w);
    }

    private boolean checkCycle(int i, boolean[] visited,
                                 boolean[] recheck)
    {

        if (recheck[i])
            return true;

        if (visited[i])
            return false;

        visited[i] = true;

        recheck[i] = true;
        LinkedList<Integer> dependencies = adj[i];

        for (Integer c: dependencies)
            if (checkCycle(c, visited, recheck))
                return true;

        recheck[i] = false;

        return false;
    }


    private boolean isCyclic()
    {

        boolean[] visited = new boolean[V];
        boolean[] recheck = new boolean[V];

        for (int i = 0; i < V; i++)
            if (checkCycle(i, visited, recheck))
                return true;

        return false;
    }


    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        int num_loopholes = sc.nextInt();

        Graph graph = new Graph(num_loopholes);

        int number_dependencies = sc.nextInt();

        for(int i = 0;i<number_dependencies;i++)
            graph.addEdge(sc.nextInt(), sc.nextInt());

        if(graph.isCyclic())
            System.out.println("NO");
        else
            System.out.println("YES");
        sc.close();
    }
}
