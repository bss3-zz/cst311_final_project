#include <iostream>
#include <string>
#include <list>
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
        this->distance = -1;
        this->visited = false;
        this->from = NULL;
    }
    
    Node(){
        this->distance = -1;
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

void linkEdges(Edge * TempEdge, list<Node> nodes){//Count nodes from 0, this fuction will distribuite the edges
    nodes[TempEdge->from].push_back(*TempEdge);
    nodes[TempEdge->to].push_back(*TempEdge);   // Now both nodes have the edge in your knowledge
    return ;
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
    list<Node> nodes;
    
    //teste
    Node *start_node;
    
    printf("Loading nodes...\n");
    //Reading the node description from file
    for (int i = 0; i < n_nodes; i++) {
        Node *temp = new Node();
        int temp_id;
        string temp_name;
        cin >> temp_id;
        cin >> temp_name;
        
        //Init distances
        if(temp_id == s_node){ //0 of distance if the node is the start node
            temp = new Node(temp_name,temp_id,0,false);
            start_node = temp;
        }else{ //Infinite distance if the node is not the start node
            temp = new Node(temp_name,temp_id,-1,false);
        }
        
        //Inserting the nodes into the vector of nodes
        nodes.push_back(*temp);
    }
    
    printf("We have %lu nodes to work.\n", nodes.size());
    printf("Loading edges...\n");
    
    for (int i = 0; i < n_edges; i++) {
        int source, destination, weight;
        cin >> source;
        cin >> destination;
        cin >> weight;
        cout << source << " " << destination << " " << weight << endl;
        Edge *temp2 = new Edge(source,destination,weight);
        linkEdges(temp2,nodes); // distribuite the edges
        printf("%d %d %d\n", source,destination,weight);
        //Creating the node
    }
    
    
    priority_queue <Node,vector<Node>,NodeCompare> pq; //Creating a priority queue to store the nodes during the computation of the shortest path
    
    //Adding the start node
    pq.push(*start_node);
    
    cout << typeid(pq).name() << '\n';
//    Node hahaha = pq.pop();
    
    return 0;
}
