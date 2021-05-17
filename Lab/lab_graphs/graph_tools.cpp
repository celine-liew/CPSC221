/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal. 
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    
// Vertex start = graph.getStartingVertex();
    // queue<Vertex> pq;
    
    // 1. Label all edges and vertices as unexplored. You will need 
    //    to look in graph.h for the right functions.

    vector<Vertex> vertices = graph.getVertices();
    for (size_t i = 0; i < vertices.size(); i++){
        graph.setVertexLabel(vertices[i], "UNEXPLORED");
    }

    vector<Edge> edges = graph.getEdges();
     for (size_t i = 0; i < edges.size(); i++){
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }
    
    // 2. Use the BFS function in graph_tools to find the minimum edge. 
    //    Don't forget to label it.

    Edge minEdge = BFS(graph, graph.getStartingVertex());
    graph.setEdgeLabel(minEdge.source, minEdge.dest, "MIN");
    return minEdge.weight;

    return -1;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    unordered_map<Vertex, Vertex> parent;
    
    // 1. Set all vertices as unexplored
    vector<Vertex> vertices = graph.getVertices();
    for (size_t i = 0; i < vertices.size(); ++i){
        graph.setVertexLabel(vertices[i], "UNEXPLORED");
    }
    
    // 2. Do a modified BFS. See the BFS function below as a guideline, but 
    //    your BFS here only needs to populate the "parent" map and stop once the short-
    //    est path has been found.

    queue<Vertex> q;
    graph.setVertexLabel(start, "DISCOVERY");
    q.push(start);
    bool found = false;

    while (!q.empty() && !found){
        Vertex v = q.front();
        q.pop();
        graph.setVertexLabel(v, "VISITED");
        vector<Vertex> adj = graph.getAdjacent(v);
        for (size_t i = 0; i < adj.size() && !found; i++){
            if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
                graph.setVertexLabel(adj[i], "DISCOVERY");
                parent.insert(make_pair(adj[i], v));
                q.push(adj[i]);

                if (adj[i] == end){
                    found = true;
                }
            }
        }
    }

    // 3. Use the unordered map to trace from a path from the end to the start, 
    //    counting edges. You should set edges to "minpath" here too.
    int dist = 0;
    Vertex curr = end;
    Vertex next;
    while (curr != start){
        next = parent[curr];
        graph.setEdgeLabel(curr, next, "MINPATH");
        curr = next;
        dist++;
    }
    return dist;
}

/**
 * BONUS: Finds a minimal spanning tree on a graph.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class given in dsets.cpp to help you with
 *  Kruskal's algorithm.
 *
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    // kruskal 

    // implement array-based PQ
    vector<Edge> edges = graph.getEdges();
    std::sort(edges.begin(), edges.end());

    // init. vertices
    vector<Vertex> vertices = graph.getVertices();
    int numVertices = vertices.size();
    int added = 0;
    int indx = 0;

    //create disjoint sets
    DisjointSets dsets;
    dsets.addelements(numVertices); // each vertex is its own set! 

    // add edges to MST (no cycles!)
    while( added < numVertices - 1) { // we want n-1 edges
        Edge edge = edges[indx];
        int set1 = dsets.find(edge.source);
        int set2 = dsets.find(edge.dest);
        if (set1 != set2 ){ // then you want to union them and add to MST
            graph.setEdgeLabel(edge.source, edge.dest, "MST");
            dsets.setunion(set1, set2); //smart union by size
            added++; // wanna only do it n-1 times
        }
        indx++;
    }

    /* your code here! */
}

/**
 * Does a BFS of a graph, keeping track of the minimum
 *  weight edge seen so far.
 * @param g - the graph
 * @param start - the vertex to start the BFS from
 * @return the minimum weight edge
 */
Edge GraphTools::BFS(Graph& graph, Vertex start)
{
    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    Edge min;
    min.weight = INT_MAX;

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(v);
        for (size_t i = 0; i < adj.size(); ++i) {
            if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");
                q.push(adj[i]);
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            } else if (graph.getEdgeLabel(v, adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "CROSS");
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            }
        }
    }
    return min;
}

// void GraphTools::setUnexplored(Graph& graph) {
//     Vertex start = graph.getStartingVertex();
//     queue<Vertex> pq;
//     graph.setVertexLabel(start, "UNEXPLORED");
//     pq.push(start);

//     while(!pq.empty()){
//         Vertex v = pq.front();
//         for 
//     }



// }
