#include <iostream>
#include <string>
#include <map>
#include <list>
#include <utility>
#include <climits>
#include <queue>
#include <math.h>

//for debug purposes
#include <typeinfo>

using namespace std;

class Edge;

class Node {
public:
    string name;
    int id;
    unsigned long int distance;
    int from;
    bool visited;
    list<Edge> adjacentList;
    
    Node(string name, int id, unsigned long int distance, bool visited, int from){
        this->name = name;
        this->id = id;
        this->distance = distance;
        this->visited = visited;
        this->from = 0;
    }
    
    Node(string name, int id, unsigned long int distance, bool visited){
        this->name = name;
        this->id = id;
        this->distance = distance;
        this->visited = visited;
        this->from = 0;
    }
    
    Node(char *name, int id){
        this->name = name;
        this->id = id;
        this->distance = ULONG_MAX;
        this->visited = false;
        this->from = 0;
    }
    
    Node(){
        this->distance = ULONG_MAX;
        this->visited = false;
        this->from = 0;
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

//Operators overloads

struct NodeCompare
{
    bool operator()(const Node &n1, const Node &n2) const
    {
        return n1.distance >    n2.distance;
    }
};

ostream& operator<<(ostream& os, const Node& nd)
{
    os << "Name: " << nd.name << " ID: " << nd.id << " Distance: " << nd.distance << " From " << nd.from;
    return os;
}

ostream& operator<<(ostream& os, const Edge& edge)
{
    os << "Source: " << edge.from << " Destination: " << edge.to << " Weight: " << edge.weight;
    return os;
}


//end of Operator overloads

void print_table_line(int step, string nprime, map<int,Node> nodes, int n_nodes){
    cout << step << '\t' << '\t' << nprime;
    
    int n_tabs = (int) ceil((((n_nodes * 2.0) - nprime.length())/4.0));
    
    for (int i = 0 ; i < n_tabs ; i++ ){
        cout << '\t';
    }
    
    for( map<int,Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){ //Iterating over the neighbor list
        Node header = it->second;
        if(header.visited == true){
            cout << '\t' << '\t' << '\t';
        }else if(header.distance == -1){
            cout << "∞" << '\t' << '\t' << '\t';
        }else{
            cout << header.distance << ", " << nodes[header.from].name << '\t' << '\t';
        }
    }
    cout << endl;
}


void print_header(int n_nodes, map<int,Node> nodes){
    
    //printing output header
    cout << "step" << '\t' << "N'";
    //calculating the number of tabulations
    int n_tabs = (int) ceil((n_nodes*2)/4);
    
    for (int i = 0 ; i < n_tabs ; i++ ){
        cout << '\t';
    }
    
    for( map<int,Node>::iterator it = nodes.begin(); it != nodes.end(); ++it){ //Iterating over the neighbor list
        Node header = it->second;
        cout << "D(" << header.name << "),p(" << header.name << ")" << '\t';
    }
    
    cout << endl;
}

string concat_nprime(string old_nprime,string new_string){
    if(old_nprime.compare("") == 0){
        return new_string;
    }else{
        return old_nprime + "," + new_string;
    }
}

int main(){
    FILE *input, *output;
    
    //Redirecting the standard input from to the input file
    input = freopen("input.in","r",stdin);
    output = freopen("output.out", "w", stdout);
    
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
    
    printf("We have %d nodes with %d edges and we will start from node of id %d.\n",n_nodes,n_edges,s_node);
    
    //Creating map that will store the state of the network
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

    printf("We have %lu nodes to read.\n", nodes.size());
    printf("Loading edges...\n");
    
    for (int i = 0; i < n_edges; i++) {
        int source, destination, weight;
        cin >> source;
        cin >> destination;
        cin >> weight;
        //cout << source << " " << destination << " " << weight << endl;
        Edge *temp_edge = new Edge(source,destination,weight);
        nodes[source].adjacentList.push_back(*temp_edge);
        Edge *temp_edge2 = new Edge(destination,source,weight);
        nodes[destination].adjacentList.push_back(*temp_edge2);
    }
    
    //printing output header
    print_header(n_nodes,nodes);
    
    priority_queue <Node,vector<Node>,NodeCompare> pq; //Creating a priority queue to store the nodes during the computation of the shortest path
    
    pq.push(nodes[s_node]); //Ading the start node to the priority list;
    
    int count = 0;
    string nprime = "";
  
    while(pq.size()!= 0){ //Starting the Dijkstra algorithm
        
        Node work_node = pq.top(); //get the node that you are visiting
        pq.pop();//remove the node that you just visit
        
        if(nodes[work_node.id].visited == false){ //Check if the node was visited before
            nodes[work_node.id].visited = true; //mark the node as visited
            
            nprime = concat_nprime(nprime,nodes[work_node.id].name);
            
            //interating over the neighbor list
            list<Edge> adj = nodes[work_node.id].adjacentList;
            
            for( list<Edge>::iterator it = adj.begin(); it != adj.end(); ++it){ //Iterating over the neighbor list
                int new_distance = work_node.distance + it->weight;
                int neighbor_id = it->to;
                if((nodes[neighbor_id].distance == -1) || (new_distance < nodes[neighbor_id].distance)){ //if is cost to go to this node trought the work_node is better than what is in there
                    nodes[neighbor_id].distance = new_distance; //then update the cost
                    nodes[neighbor_id].from = work_node.id; //change the origin to this node
                    pq.push(nodes[neighbor_id]); //add this change node to the priority queue
                }
            }
            
            print_table_line(count++,nprime,nodes, n_nodes);
            
        }
//        else{
//            cout << "Previously visited node found with id " << work_node.id <<  endl;
//        }
        
        //if the node was previously visited them ignore this node
    }
    
    return 0;
}
