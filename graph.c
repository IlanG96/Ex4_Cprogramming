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
    for (int i =1; i < g_size; i++)
    {
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

pnode find_node(int id){
    pnode temp = head;
    if (temp->node_num==id)
    {
        return temp;
    }
    
    while (temp->next)//!=NULL)-haim wannbe IL
    {
        if(temp->node_num==id)
            return temp;
        temp=temp->next;    
    }
    return NULL;
}

void insert_node(char* cptr){
    int digit=cptr[0];
    pnode temp = head;
    while (temp->next)//!=NULL)-haim wannbe IL
    {
        if(temp->node_num==digit)
            break;
        temp=temp->next;    
    }
    // temp->edges=(pedge)malloc(sizeof(struct edge_));
    for (int i = 1; i < strlen(cptr); i=i+2)
    {
    int dest=cptr[i]-'0';
    int weight=cptr[i+1]-'0'; 
    add_edge(&(temp->edges),dest,weight);
    // temp_edge->dest=find_node((cptr[i]-'0'));
    // printf("edge point to:%d, i= %d \n",temp->edges->dest->node_num,i);
    // temp_edge->weight=cptr[i+1]-'0';
    // temp->num_of_edges++;
    // printf("First weight:%d \n",temp->edges->weight);
    // temp->edges=temp_edge;
    // // temp->edges=temp->edges->next;
    // printf("Second weight:%d \n",temp->edges->weight);
    // printf("####End####\n");
    }
    while (temp->edges!=NULL)
    {
    printf("edge point to:%d \n",temp->edges->dest->node_num);
    printf("weight:%d \n",temp->edges->weight);
    temp->edges=temp->edges->next;
    }
}

void add_edge(edge **edge_head,int dest,int weight){
    pedge new_edge=(pedge)malloc(sizeof(struct edge_));
    new_edge->dest=find_node(dest);
    new_edge->weight=weight;
    if (*edge_head==NULL)
    {
        *edge_head=new_edge;
    }
    else{
        struct edge_ *temp_edge = *edge_head;
        while (temp_edge->next!=NULL)
        {
            temp_edge=temp_edge->next;
        }
        temp_edge->next=new_edge;
    }
    

} 
//     pedge temp_edge = (pedge*)malloc(sizeof(struct edge_));
//      // declare a node

//     printf("insert_node first node data%d/n",temp->node_num);
//     pedge temp_edge = (pedge)malloc(sizeof(struct edge_));
//     if(temp->node_num==cptr[0]){
//         if(temp->edges==NULL){
//             temp->edges=
//         }
//     }
//     temp_edge->weight=info[1];
//     printf("weight of node:%d\n",temp_edge->weight);
//     printf("id of node:%d",temp_edge->id);
//     for (int i = 0; i < sizeof(info); i=+2)
//     {
//     pedge edge = temp->edges;
//     edge->num_of_edge=1;
//     int edge_size = edge->num_of_edge;
//     edge = (pedge)realloc(edge,((edge_size+1)*(sizeof(struct edge_))));
//     edge->endpoint->node_num = info[i];
//     edge->weight = info[i+1];
//     edge = edge->next; 
// }

// void delete_node(struct GRAPH_NODE_** head,int node_id){
//     struct GRAPH_NODE_ *iterator=*head;
//     struct GRAPH_NODE_ *prev;
//     // If head node itself holds the key to be deleted
//     if(iterator!=NULL && iterator->node_num==node_id){
//         *head=iterator->next;// Changed head
//         free(iterator);// free old head
//         return;
//     }
//     // Search for the node_id to be deleted, keep track of the
//     // previous node as we need to change 'prev->next'
//     while (iterator !=NULL && iterator->node_num!=node_id)
//     {
//         prev=iterator;
//         iterator=iterator->next;
//     }
//     // If key was not present in linked list
//     if(iterator==NULL)
//     return;
//     prev->next=iterator->next;
//     free(iterator->edges);
//     free(iterator);

// }

// void delete_edge();


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