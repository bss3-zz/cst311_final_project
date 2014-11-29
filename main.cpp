#include <iostream>
#include <string>
#include <map>
#include <list>
#include <utility>
#include <climits>
#include <queue>


void update(edge.weight,)

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

void linkEdges(Edge * TempEdge, list<Node> nodes){//Count nodes from 0, this fuction will distribuite the edges
    nodes[TempEdge->from].push_back(*TempEdge);
    nodes[TempEdge->to].push_back(*TempEdge);   // Now both nodes have the edge in your knowledge
    return ;
};



String nameUpadate(String name){ //fuction to give a unique name to each node
    int size = name.size() - 1;
    if(name[size] == 'z'){
        zCase(name,size);
    }else{
        name[size]++;
    }
    return name;
}

void zCase(String name, int size){// Z treatment
    if(size == 0){
        name[size] = 'a';
        name =  name + "a";
    }else{
        name[size] = 'a';
        if(name[size-1] == 'z'){
            zCase(name,size-1);
        }else{
            name[size-1]++;        }
    }
}


int main(){
    FILE *input, *output;
    int l,row
    
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

    string name;
    for (int i = 0; i < n_nodes; i++) {
        if(name.size == 0 ){
            name = 'a';
            odes[temp_id].id = i;
            nodes[temp_id].name = 'a';
            nodes[temp_id].visited = false;
        }else{
            if(i == s_node){ //0 of distance if the node is the start node
                nodes[i].distance = 0;
            }else{ //Infinite distance if the node is not the start node
                nodes[temp_id].distance = -1;
            }
            nodes[temp_id].id = i;
            nodes[temp_id].name = nameUpadate(name);
            nodes[temp_id].visited = false;
        }
        
    }
    
    
    
    for (l = 0; l < n_nodes; l++) {
        for (row = 0; row < n_nodes; row++) {
            if(row != l){
                cin >> weight;
                Edge *temp_edge = new Edge(row,l, weight);
                Edge *temp_edge2 = new Edge(l,row, weight);
                nodes[row].adjacentList.push_back(*temp_edge);
                nodes[l].adjacentList.push_back(*temp_edge2);
            }
        }
    }
    //All nodes now has been loaded into the structures
    
    printf("We have %lu nodes to work.\n", nodes.size());
    printf("Loading edges...\n")
    
    priority_queue <Node,vector<Node>,NodeCompare> pq; //Creating a priority queue to store the nodes during the computation of the shortest path
    
    
    
    return 0;
}
