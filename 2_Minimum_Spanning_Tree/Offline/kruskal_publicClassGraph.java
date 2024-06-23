import java.util.*;
import java.lang.*;
import java.io.*;
import java.io.FileNotFoundException;

class Graph {

    class kruskalEdge implements Comparable<kruskalEdge> {
        int src, dest;
        double weight;

        public int compareTo(kruskalEdge compareEdge) {
            if (Double.compare(this.weight, compareEdge.weight) < 0)
                return -1;
            if (Double.compare(this.weight, compareEdge.weight) == 0)
                return 0;
            return 1;
        }
    }

    int vertex, Edge_number;
    kruskalEdge edge[];

    Graph(int v, int e) {
        vertex = v;
        Edge_number = e;
        edge = new kruskalEdge[Edge_number];
        for (int i = 0; i < e; ++i)
            edge[i] = new kruskalEdge();

    }

    class DisjoinSet {
        int parent, rank;
    }

    class MinimumSpanningSet {
        int parent;
        double weight;
    }

    int find(DisjoinSet DisjoinSets[], int i) {

        if (DisjoinSets[i].parent != i)
            DisjoinSets[i].parent = find(DisjoinSets, DisjoinSets[i].parent);

        return DisjoinSets[i].parent;
    }

    void Union(DisjoinSet DisjoinSets[], int i, int j) {
        int iParent = find(DisjoinSets, i);
        int jParent = find(DisjoinSets, j);

        if (DisjoinSets[iParent].rank < DisjoinSets[jParent].rank)
            DisjoinSets[iParent].parent = jParent;
        else if (DisjoinSets[iParent].rank > DisjoinSets[jParent].rank)
            DisjoinSets[jParent].parent = iParent;

        else {
            DisjoinSets[jParent].parent = iParent;
            DisjoinSets[iParent].rank++;
        }
    }

    void KruskalAlgorithmImplementation() {

        kruskalEdge KruskalResult[] = new kruskalEdge[vertex];

        int e = 0;

        int i = 0;
        for (i = 0; i < vertex; ++i)
            KruskalResult[i] = new kruskalEdge();

        Arrays.sort(edge);

        DisjoinSet DisjoinSets[] = new DisjoinSet[vertex];
        for (i = 0; i < vertex; ++i)
            DisjoinSets[i] = new DisjoinSet();

        for (int v = 0; v < vertex; ++v) {
            DisjoinSets[v].parent = v;
            DisjoinSets[v].rank = 0;
        }

        i = 0;

        while (e < vertex - 1) {

            kruskalEdge next_edge = edge[i++];

            int x = find(DisjoinSets, next_edge.src);
            int y = find(DisjoinSets, next_edge.dest);

            if (x != y) {
                KruskalResult[e++] = next_edge;
                Union(DisjoinSets, x, y);
            }
        }
        System.out.println("Cost of the minimum spanning tree :  "
                + minimumCost);
        double minimumCost = 0;
        for (i = 0; i < e; ++i) {
            minimumCost += KruskalResult[i].weight;
        }
        System.out.print("List of edges selected by kruskal’s: {");
        for (i = 0; i < e; ++i) {
            if (i < e - 1) {
                System.out.print("(" + KruskalResult[i].src + ","
                        + KruskalResult[i].dest
                        + "),");
            }
            if (i == e - 1) {
                System.out.print("(" + KruskalResult[i].src + ","
                        + KruskalResult[i].dest
                        + ")}");
            }

        }
        System.out.println();

    }

    public static void main(String[] args) {
        Scanner sc;
        try {
            sc = new Scanner(new File("mst.txt"));
            int vertex = sc.nextInt();
            int E = sc.nextInt();
            Graph graph = new Graph(vertex, E);
            while (sc.hasNext()) {
                for (int i = 0; i < E; i++) {
                    graph.edge[i].src = sc.nextInt();
                    graph.edge[i].dest = sc.nextInt();
                    graph.edge[i].weight = sc.nextDouble();
                }

            }
            sc.close();
            graph.KruskalAlgorithmImplementation();
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
            e.printStackTrace();
        }

    }
}