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
        LinkedList<Edge>[] adj;

        Graph(int vertices) {
            this.vertex = vertices;
            adj = new LinkedList[vertices];

            for (int i = 0; i < vertex; i++) {
                adj[i] = new LinkedList<>();
            }
        }

        public void addEgde(int source, int destination, int weight) {
            Edge edge = new Edge(source, destination, weight);
            adj[source].addFirst(edge);
        }

        boolean bfs(int ResidualGraph[][], int source, int tank, int parent[]) {
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
            return (visited[tank] == true);
        }

        void dfs(int rGraph[][], int s, boolean visited[]) {
            visited[s] = true;
            for (int i = 0; i < vertex; i++)
                if (rGraph[s][i] > 0) {
                    if (!visited[i]) {
                        dfs(rGraph, i, visited);
                    }
                }
        }


        void minCut(int source, int tank) {
            int u, v;

            int ResidualGraph[][] = new int[vertex][vertex];

            for (u = 0; u < vertex; u++) {
                for (Edge x : adj[u]) {
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


                boolean visited[] = new boolean[vertex];

                dfs(ResidualGraph, source, visited);


                for (int i = 0; i < vertex; i++)
                    for (int j = 0; j < vertex; j++)
                        if (visited[i]) {
                            if (!visited[j])
                                if (adj != null)
                                    System.out.println(i + "->" + j);

                            return;
                        }
            }
        }

        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            int ver = sc.nextInt();
            int I = Integer.MAX_VALUE;
            Graph g = new Graph(ver);

            for (int i = 0; i < ver; i++) {
                    g.addEgde(sc.nextInt(), sc.nextInt(), sc.nextInt());
            }

            g.minCut(sc.nextInt(),sc.nextInt() );
            sc.close();
        }
    }
}

