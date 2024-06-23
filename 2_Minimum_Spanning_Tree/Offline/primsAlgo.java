import java.util.*;
import java.lang.*;
import java.io.*;
import java.io.FileNotFoundException;

public class primsAlgo {

    static class Edge {
        int source;
        int destination;
        double weight;

        public Edge(int source, int destination, double weight) {
            this.source = source;
            this.destination = destination;
            this.weight = weight;
        }

    }

    static class Graph {
        int vertices;
        LinkedList[] adjList;

        Graph(int vertices) {
            this.vertices = vertices;
            adjList = new LinkedList[vertices];
            for (int i = 0; i <vertices ; i++) {
                adjList[i] = new LinkedList<>();
            }
        }

        public void addEgde(int source, int destination, double weight) {
            Edge edge = new Edge(source, destination, weight);
            adjList[source].addFirst(edge);

            edge = new Edge(destination, source, weight);
            adjList[destination].addFirst(edge);
        }

        static class MinHeapNode{
            int vertex;
            double key;
        }
    
        static class MinimumSpanningTreeResultSet {
            int parent;
            double weight;
        }
    

        public void primsAlgorithmImplementation(){

            boolean[] PriorityQueue = new boolean[vertices];
            MinimumSpanningTreeResultSet[] MinimumSpanningTreeResultSet = new MinimumSpanningTreeResultSet[vertices];
            double [] key = new double[vertices]; 


            MinHeapNode [] MinHeapNodes = new MinHeapNode[vertices];
            for (int i = 0; i <vertices ; i++) {
                MinHeapNodes[i] = new MinHeapNode();
                MinHeapNodes[i].vertex = i;
                MinHeapNodes[i].key = Double.MAX_VALUE;
                MinimumSpanningTreeResultSet[i] = new MinimumSpanningTreeResultSet();
                MinimumSpanningTreeResultSet[i].parent = Integer.MAX_VALUE;
                PriorityQueue[i] = true;
                key[i] = Double.MAX_VALUE;
            }

          
            MinHeapNodes[0].key = 0;

    
            PriorityQueue<MinHeapNode> priqueue = new PriorityQueue<>(vertices,
                    new Comparator<MinHeapNode>() {
                        @Override
                        public int compare(MinHeapNode node_one, MinHeapNode node_two) {
                            if (Double.compare(node_one.key, node_two.key) < 0)
                                return -1;
                            if (Double.compare(node_one.key, node_two.key) == 0)
                                return 0;
                            return 1;
                        }
                    });
     
            for (int i = 0; i <vertices ; i++) {
                priqueue.offer(MinHeapNodes[i]);
            }

          
            while(!priqueue.isEmpty()){
              
                MinHeapNode extracted = priqueue.poll();

               
                int extractedVertex = extracted.vertex;
                PriorityQueue[extractedVertex] = false;

               
                LinkedList<Edge> list = (LinkedList<Edge>) adjList[extractedVertex];
                for (int i = 0; i <list.size() ; i++) {
                    Edge edge = list.get(i);

                    if(PriorityQueue[edge.destination]) {
                        int destination = edge.destination;
                        double newKey = edge.weight;
                        
                        if(key[destination]>newKey) {
                            decreaseKey(priqueue, newKey, destination);
                            MinimumSpanningTreeResultSet[destination].parent = extractedVertex;
                            MinimumSpanningTreeResultSet[destination].weight = newKey;
                            key[destination] = newKey;
                        }
                    }
                }
            }
            primsAlgorithmImplementationPrint(MinimumSpanningTreeResultSet);
        }

        public void primsAlgorithmImplementationPrint(MinimumSpanningTreeResultSet[] MinimumSpanningTreeResultSet){
            double total_min_weight = 0;
            for (int i = 1; i <vertices ; i++) {
                total_min_weight += MinimumSpanningTreeResultSet[i].weight;}
                System.out.println("Cost of the minimum spanning tree : " + total_min_weight);
                System.out.print("List of edges selected by Prim’s: {");
                 for (int i = 1; i <vertices ; i++) {
                if(i<vertices-1)
                {System.out.print("(" + i + "," + MinimumSpanningTreeResultSet[i].parent +
                        "),");}
                if(i==vertices-1)
                {System.out.print("(" + i + "," + MinimumSpanningTreeResultSet[i].parent +
                        ")}");}
            }
            System.out.println();
            
        }
        public void decreaseKey(PriorityQueue<MinHeapNode> priqueue, double newKey, int vertex){

            Iterator iteratingpriorityqueue = priqueue.iterator();

            while (iteratingpriorityqueue.hasNext()) {
                MinHeapNode MinHeapNode = (MinHeapNode) iteratingpriorityqueue.next();
                if(MinHeapNode.vertex==vertex) {
                    priqueue.remove(MinHeapNode);
                    MinHeapNode.key = newKey;
                    priqueue.offer(MinHeapNode);
                    break;
                }
            }
        }
    }
    public static void main(String[] args) {
        Scanner sc;
        try {
            sc = new Scanner(new File("mst.txt"));
            int vertex = sc.nextInt();
            int E = sc.nextInt();
            Graph graph = new Graph(vertex);
            while (sc.hasNext()) {
                for (int i = 0; i < E; i++) {
                    graph.addEdge(sc.nextInt(),sc.nextInt(),sc.nextDouble());
                }

            }
            sc.close();
            graph.PrimsAlgorithmImplementation();
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
            e.printStackTrace();
        }

    }
}
