package com.company;
import java.lang.*;
import java.util.*;
import java.util.LinkedList;

public class Main {
    static class Edge {
        int source;
        int destination;
        int weight;

        public Edge(int source, int destination, int weight) {
            this.source = source;
            this.destination = destination;
            this.weight = weight;
        }
    }

    static class Graph {
        int vertex;
        LinkedList<Edge> [] adj;

        Graph(int vertices) {
            this.vertex = vertices;
            adj = new LinkedList[vertices];

            for (int i = 0; i <vertex ; i++) {
                adj[i] = new LinkedList<>();
            }
        }

        public void addEgde(int source, int destination, int weight) {
            Edge edge = new Edge(source, destination, weight);
            adj[source].addFirst(edge);
        }
        boolean bfs(int ResidualGraph[][],int source, int tank, int parent[]) {

            boolean visited[] = new boolean[vertex];
            for (int i = 0; i < vertex; ++i)
                visited[i] = false;

            LinkedList<Integer> queue = new LinkedList<Integer>();
            queue.add(source);
            visited[source] = true;
            parent[source] = -1;

            while (queue.size() != 0) {
                int u = queue.poll();

                for (Edge x : adj[u]) {
                    int v = x.destination;
                    if (visited[v] == false && ResidualGraph[u][v] > 0) {
                        if (v == tank) {
                            parent[v] = u;
                            return true;
                        }
                        queue.add(v);
                        parent[v] = u;
                        visited[v] = true;
                    }
                }
            }
            return false;
        }

        int FordFulkerson(int source, int tank) {
            int u, v;

            int ResidualGraph[][] = new int[vertex][vertex];

            for (u = 0; u < vertex; u++){
                for(Edge x : adj[u])
                {
                    ResidualGraph[u][x.destination] = x.weight;
                }
            }


            int parent[] = new int[vertex];

            int max_flow = 0;

            while (bfs(ResidualGraph, source, tank, parent)) {
                int path_flow = Integer.MAX_VALUE;
                for (v = tank; v != source; v = parent[v]) {
                    u = parent[v];
                    path_flow = Math.min(path_flow, ResidualGraph[u][v]);
                }

                for (v = tank; v != source; v = parent[v]) {
                    u = parent[v];
                    ResidualGraph[u][v] -= path_flow;
                    ResidualGraph[v][u] += path_flow;
                }

                max_flow += path_flow;
            }
            return max_flow;
        }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int ver = sc.nextInt();

        int nodes = (ver*(ver-1))/2+2;
        int num_edges = 3*(ver-1)*(ver-2)/2+(ver-1);

        int I = Integer.MAX_VALUE;

        String name[] = new String[ver];
        int win[] = new int[ver];
        int loss[] = new int[ver];
        int left[] = new int[ver];
        int capacity[][]=new int[ver][ver];
        int game[][] = new int[ver][ver];

        for (int i = 0; i < ver; i++) {
            name[i] = sc.next();
            win[i] = sc.nextInt();
            loss[i] = sc.nextInt();
            sc.nextInt();
            left[i] = sc.nextInt();
            for (int j = 0; j < ver; j++) {
                if(i==j)
                {
                    game[i][j]=0;
                    continue;
                }
                game[i][j] = sc.nextInt();

            }
        }
        for (int i = 0; i < ver; i++) {
            for (int j = 0; j < ver; j++) {
                capacity[i][j] = win[i] + left[i] - win[j];

            }
        }

        for(int i = 0; i < ver; i++){
            Graph g = new Graph(nodes);
            int teamInd[] = new int[ver];
            int curNode = (ver - 1) * (ver - 2) / 2 + 1;
            for(int j = 0; j < ver; j++){
                if(i == j)continue;
                teamInd[j] = curNode;
                g.addEgde(curNode, nodes - 1, capacity[i][j]);
                curNode++;
            }
            curNode = 1;
            int total = 0;
            for(int j = 0; j < ver; j++){
                if(i == j)continue;
                for(int k = j + 1; k < ver; k++){
                    if(i == k)continue;
                    total += game[j][k];
                    g.addEgde(0, curNode, game[j][k]);
                    g.addEgde(curNode, teamInd[j], I);
                    g.addEgde(curNode, teamInd[k], I);
                    curNode++;
                }
            }
            if(g.FordFulkerson(0, nodes - 1) != total){
                System.out.println(name[i] + "  is eliminated.");
            }
        }
        sc.close();
    }
}
