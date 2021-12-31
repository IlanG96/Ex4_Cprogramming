#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct g_node *pnode;
struct g_node *head;

typedef struct edge_ {
    int weight;
    pnode dest;
    struct edge_ *next;
} edge, *pedge;

typedef struct g_node {
    int node_num;
    int num_of_edges; 
    pedge edges;
    struct g_node *next;
} node, *pnode;

void  build_graphcmd(int g_size){
    free(head);
    head = NULL;
    head=(pnode)malloc(sizeof(struct g_node));
    head->node_num=0;
    head->num_of_edges=1;
    head->next=NULL;
    pnode temp = head;
    //Check why +1
    for (int i =1; i < g_size+1; i++)
    {
        if (i==g_size)
        {
            break;
        }
        
        pnode next_Node=(pnode)malloc(sizeof(struct g_node));
        next_Node->node_num=i;
        next_Node->num_of_edges=1;
        temp->next=next_Node;
        temp=temp->next;
    }
//   printf("%d\n",head->node_num);
//   printf("%d\n",head->next->node_num);
//   printf("%d\n",head->next->next->node_num);
//   printf("%d\n",head->next->next->next->node_num);


}
//######function that find the node according to his ID######
pnode find_node(int id){
    pnode temp = head;
    //printf("Start at: %d\n",temp->node_num);
    //if the node we are looking for is the head
    //return him
    if ((temp->node_num)==id)
    {
        //printf("first if enter: %d\n",temp->node_num);
        return temp;
    }
    //else go over all the nodes and try to find the node
    while (temp!=NULL)
    {
        //printf("now at: %d\n",temp->node_num);
        if((temp->node_num)==id)
            return temp;
        temp=temp->next;    
    }
    return NULL;
}

void insert_node(char* cptr){
    int digit=cptr[0]-'0';// Node number
    pnode temp = head;
    temp=find_node(digit);//find the node
    for (int i = 1; i < strlen(cptr); i=i+2)
    {
    int dest=cptr[i]-'0';
    int weight=cptr[i+1]-'0'; 
    add_edge(&(temp->edges),dest,weight);
    }
    //### Edge Print Test###
    while (temp->edges!=NULL)
    {
    printf("Edge:\n Source:%d ,Dest:%d ,weight:%d\n",temp->node_num,temp->edges->dest->node_num,temp->edges->weight);
    temp->edges=temp->edges->next;
    }
}

void add_edge(edge **edge_head,int dest,int weight){
    pedge new_edge=(pedge)malloc(sizeof(struct edge_));//Create new edge
    //##Fill the edge info##
    new_edge->dest=find_node(dest);
    new_edge->weight=weight;
    //###################
    //if this is the first Edge of this node
    if (*edge_head==NULL)
    {
        //make him the new head
        *edge_head=new_edge;
    }
    else{
        //Start going over the edges until you find the last edge in the list
        struct edge_ *temp_edge = *edge_head;
        while (temp_edge->next!=NULL)
        {
            temp_edge=temp_edge->next;
        }
        //when you find the last edge make him point to the new edge.
        temp_edge->next=new_edge;
    }
} 

void delete_node(int node_id){
    pnode iterator=head;
    pnode prev;
    // If head node itself holds the key to be deleted
    if(iterator!=NULL && iterator->node_num==node_id){
        head=iterator->next;// Changed head
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
    //pnode iterator2=iterator;
    prev->next=iterator->next;
    pedge prevE=iterator->edges;
    //######Delete Edges in the node we delete####
    while (iterator->edges!=NULL)
    {
    prevE = iterator->edges;
    iterator->edges=iterator->edges->next;
    free(prevE);
    }
    //###########
    free(iterator);
}
void remove_Edges_of(int id){
    pnode Node_iterator=head;
    pedge prevE;
    pedge Edge_Head;
    pedge Edge_iterator;
    while (Node_iterator!=NULL)
    {
        Edge_Head=Node_iterator->edges;
        Edge_iterator=Node_iterator->edges;
        int flag=0;
        while (Edge_iterator!=NULL)
        {
            if (Edge_iterator->dest->node_num==id && flag==0)
            {
                Edge_Head=Edge_iterator->next;
                free(Edge_iterator);
            }
            if (Edge_iterator->dest->node_num==id && flag!=0)
            {
                prevE->next=Edge_iterator->next;
                free(Edge_iterator);
                Edge_iterator=prevE;
            }
            flag++;            
            prevE=Edge_iterator;
            Edge_iterator=Edge_iterator->next;
        }
    }
}

void PrintGraph(){
    pnode temp = head;
    while (temp!=NULL)
    {
        printf("Node ID:%d\n",temp->node_num);
        temp=temp->next;
    }
    
}

