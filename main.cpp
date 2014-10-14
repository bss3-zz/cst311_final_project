#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

struct edge;

struct node {
    char name;
    int id;
    bool visited;
    edge *adjacentList;
};

struct edge {
    node *from, *to;
    edge *next, *previous;
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
    int n_nodes, n_edges, start_node;
    scanf("%d %d %d", &n_nodes, &n_edges, &start_node);
    
    printf("We have %d nodes with %d edges and we will start from %d edge.\n",n_nodes,n_edges,start_node);
    
    //Creating the vector that will store the graph of the network
    vector<node> nodes;
    
    printf("Loading nodes...\n");
    //Reading the node description from file
    for (int i = 0; i < n_nodes; i++) {
        node temp;
        scanf("%d %s",&temp.id, &temp.name);
        //Inserting the nodes into the vector of nodes
        nodes.push_back(temp);
    }
    
    printf("We have %lu nodes to work.\n", nodes.size());
    printf("Loading edges...\n");
    
    for (int i = 0; i < n_edges; i++) {
        int source, destination, weight;
        scanf("%d %d %d", &source,&destination,&weight);
        printf("%d %d %d\n", source,destination,weight);
        
        //Creating the node
    }
    
    return 0;
}
