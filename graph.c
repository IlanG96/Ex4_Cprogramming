#include "graph.h"
#include <stdio.h>

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

void build_graph_cmd(pnode *head){
    pnode curr_node=head;
    
    return 0;
}

void insert_node(struct GRAPH_NODE_** head,int info[]){
    pnode temp; // declare a node
    pedge temp_edge;
    temp = (pnode)malloc(sizeof(struct GRAPH_NODE_)); // allocate memory using malloc()
    temp->next = NULL;// make next point to NULL
    temp->node_num=info[0];
    temp->edges=NULL;
    for (int i = 1; i < sizeof(info); i=i+2)
    {
    temp_edge = (pedge)malloc(sizeof(struct edge_)); // allocate memory using malloc()
    temp_edge->weight=info[i];
    temp_edge->endpoint=info[i+1];//need to check how to do this!!
    if (temp->edges==NULL)
    {
    }
        while (temp->edges->next==NULL)
        {
            /* code */
        }
        
    }
    
    struct GRAPH_NODE_ *iterator=*head;
    while (iterator->next!=NULL)
    {
        iterator=iterator->next;
    }
    iterator->next=temp;
    
    return temp;//return the new node 
}
void delete_node(struct GRAPH_NODE_** head,int node_id){
    struct GRAPH_NODE_ *iterator=*head;
    struct GRAPH_NODE_ *prev;
    // If head node itself holds the key to be deleted
    if(iterator!=NULL && iterator->node_num==node_id){
        *head=iterator->next;// Changed head
        free(iterator);// free old head
        return;
    }
    // Search for the node_id to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (iterator !=NULL && iterator->node_num!=node_id)
    {
        prev=iterator;
        iterator=iterator->next;
    }
    // If key was not present in linked list
    if(iterator==NULL)
    return;
    prev->next=iterator->next;
    free(iterator->edges);
    free(iterator);

}

void delete_edge()

// void insert_edge(struct GRAPH_NODE_** head,struct edge_** Edge_Head,int weight,int src,int dest){
//     pedge curr_edge;
//     curr_edge= (pedge)malloc(sizeof(struct edge_)); // allocate memory using malloc()
//     curr_edge->weight=weight;

//     while ((*head)->node_num!=src)
//     {
//         /* code */
//     }
    

// }


// pnode insert_node_cmd(pnode *head, int id){
//     pnode temp,p;// declare two nodes temp and p
//     temp = createNode();//createNode will return a new node with data = value and next pointing to NULL.
//     temp->node_num = id; // add element's value to data part of node
//     if(head == NULL){
//         head = temp;     //when linked list is empty
//     }
//     else{
//         p  = head;//assign head to p 
//         while(p->next != NULL){
//             p = p->next;//traverse the list until p is the last node.The last node always points to NULL.
//         }
//         p->next = temp;//Point the previous last node to the new node created.
//     }
//     return head;
// }