#include <iostream>
#include <string>
#include <map>
#include <list>
#include <utility>
#include <climits>
#include <queue>

//for debug purposes
#include <typeinfo>

using namespace std;

class Edge;

class Node {
public:
    string name;
    int id;
    unsigned long int distance;
    Node *from;
    bool visited;
    list<Edge> adjacentList;
    
    Node(string name, int id, unsigned long int distance, bool visited, Node *from){
        this->name = name;
        this->id = id;
        this->distance = distance;
        this->visited = visited;
        this->from = from;
    }
    
    Node(string name, int id, unsigned long int distance, bool visited){
        this->name = name;
        this->id = id;
        this->distance = distance;
        this->visited = visited;
        this->from = NULL;
    }
    
    Node(char *name, int id){
        this->name = name;
        this->id = id;
        this->distance = ULONG_MAX;
        this->visited = false;
        this->from = NULL;
    }
    
    Node(){
        this->distance = ULONG_MAX;
        this->visited = false;
        this->from = NULL;
    }
};


struct NodeCompare
{
    bool operator()(const Node &n1, const Node &n2) const
    {
        return n1.distance < n2.distance;
    }
};

ostream& operator<<(ostream& os, const Node& nd)
{
    os << "Name: " << nd.name << " ID: " << nd.id;
    return os;
}

class Edge {
public:
    int from, to;
    int weight;
    
    Edge(int a, int b, int weight){
        this->from = a;
        this->to = b;
        this->weight = weight;
    }
};

int main(){
    FILE *input, *output;
    
    //Redirecting the standard input from to the input file
    input = freopen("input.in","r",stdin);
    
    //Checking if we have the input file
    if (input == NULL){
        perror("Problem to open the input file check if this file exists");
        exit(-1);
    }
    
    //Reading the information about the network that will be processed
    int n_nodes, n_edges, s_node;
    cin >> n_nodes;
    cin >> n_edges;
    cin >> s_node;
    
    printf("We have %d nodes with %d edges and we will start from %d edge.\n",n_nodes,n_edges,s_node);
    
    //Creating the vector that will store the graph of the network
    map<int,Node> nodes;
    
    printf("Loading nodes...\n");
    //Reading the node description from file
    for (int i = 0; i < n_nodes; i++) {
        int temp_id;
        string temp_name;
        cin >> temp_id;
        cin >> temp_name;
        
        //Init distances
        if(temp_id == s_node){ //0 of distance if the node is the start node
            nodes[temp_id].distance = 0;
        }else{ //Infinite distance if the node is not the start node
            nodes[temp_id].distance = -1;
        }
        
        nodes[temp_id].id = temp_id;
        nodes[temp_id].name = temp_name;
        nodes[temp_id].visited = false;
    }
    
    //All nodes now has been loaded into the structures
    
    printf("We have %lu nodes to work.\n", nodes.size());
    printf("Loading edges...\n");
    
    for (int i = 0; i < n_edges; i++) {
        int source, destination, weight;
        cin >> source;
        cin >> destination;
        cin >> weight;
        cout << source << " " << destination << " " << weight << endl;
        Edge *temp_edge = new Edge(source,destination,weight);
        nodes[source].adjacentList.push_back(*temp_edge);
        nodes[destination].adjacentList.push_back(*temp_edge);
    }
    
    priority_queue <Node,vector<Node>,NodeCompare> pq; //Creating a priority queue to store the nodes during the computation of the shortest path
    
    
    
    return 0;
}
