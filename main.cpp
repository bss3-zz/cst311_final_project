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
        this->distance = -1;
        this->visited = false;
        this->from = 0;
    }
    
    Node(){
        this->distance = -1;
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

string zCase(string name, int position){// Z treatment
    
//    if(position == name.length()-1){
//        return zCase((name+"a"),position);
//    }else if(name[position] == 'z'){
//        name[position] = 'a';
//        return zCase(name, position-1);
//    }else{
//        name[position]++;
//        return name;
//    }
    
    if(position == 0){
        name[position] = 'a';
        return "a" + name;
    }
    name[position] = 'a';
    if( name[position - 1] == 'z'){
         return zCase(name, position - 1);
    }
    name[position - 1]++;
    return name;
    
}


string nameUpadate(string name){ //fuction to give a unique name to each node
    int length = name.length() - 1;
    if(name[length] == 'z'){
        zCase(name,length);
    }else{
        name[length]++;
    }
    
    return name;
}




int main(){
    FILE *input, *output;
    int l,row;
    
    //Redirecting the standard input from to the input file
    input = freopen("input.in","r",stdin);
    output = freopen("output.out", "w", stdout);
    
    //Checking if we have the input file
    if (input == NULL){
        perror("Problem to open the input file check if this file exists");
        exit(-1);
    }
    
    //Reading the information about the network that will be processed
    int n_nodes, s_node;
    cin >> n_nodes;
    cin >> s_node;
    
    printf("We have %d nodes starting from node of id %d.\n",n_nodes,s_node);
    
    //Creating map that will store the state of the network
    map<int,Node> nodes;
    
    printf("Loading nodes...\n");
    //Reading the node description from file

    string name = "`";
    for (int i = 0; i < n_nodes; i++) {
        
        if(i == s_node){
            nodes[i].distance = 0;
        }else{
            nodes[i].distance = -1;
        }
        
        
        if(name.size() == 0 ){
            name = 'a';
            nodes[i].id = i;
            nodes[i].name = 'a';
            nodes[i].visited = false;
        }else{
            if(i == s_node){ //0 of distance if the node is the start node
                nodes[i].distance = 0;
            }else{ //Infinite distance if the node is not the start node
                nodes[i].distance = -1;
            }
            nodes[i].id = i;
            name = nameUpadate(name);
            nodes[i].name = name;
            nodes[i].visited = false;
        }
        
    }

    int weight;
    for (l = 0; l < n_nodes; l++) {
        for (row = 0; row < n_nodes; row++) {
            if(row != l){
                cin >> weight;
                if(weight != -1){
                    Edge *temp_edge = new Edge(row,l, weight);
                    nodes[row].adjacentList.push_back(*temp_edge);
                }
            }else{
            }
        }
    }
    
    //All nodes now has been loaded into the structures

    
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
