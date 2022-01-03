#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct g_node *pnode;
struct g_node *head;
static int Grpah_size=0;
int cost=0;
//int graph_Dist[][];


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
    Grpah_size=g_size;
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

}
//######function that find the node according to his ID######
pnode find_node(int id){
    pnode temp = head;
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
}

void remove_Edges_of(int id){
    pnode Node_iterator=head;
    pedge prevE;
    pedge Edge_Head;
    pedge Edge_iterator;
    while (Node_iterator!=NULL)
    {
        Edge_Head=(Node_iterator->edges);
        Edge_iterator=Node_iterator->edges;
        int flag=0;
        while (Edge_iterator!=NULL)
        {
            if (Edge_iterator->dest->node_num==id && flag==0)
            {
                if (Edge_iterator->next!=NULL)
                {
                    Edge_Head=Edge_iterator->next;
                    Node_iterator->edges=Edge_Head;
                }
                else
                {
                Edge_Head=NULL;
                 Node_iterator->edges=NULL;
                }
                free(Edge_iterator);
                Edge_iterator=Edge_Head;  
            }

            if (Edge_iterator->dest->node_num==id && flag!=0)
            {
                prevE->next=Edge_iterator->next;
                free(Edge_iterator);
            }
            flag++;            
            prevE=Edge_iterator;
            Edge_iterator=Edge_iterator->next;
        }
        Node_iterator=Node_iterator->next;
    }
}

void delete_node(int node_id){
    pnode iterator=head;
    pnode prev;
    // If head node itself holds the key to be deleted
    if(iterator!=NULL && iterator->node_num==node_id){
        head=iterator->next;// Changed head
        pedge prevE=iterator->edges;
        while (iterator->edges!=NULL)
            {
            prevE = iterator->edges;
            iterator->edges=iterator->edges->next;
            free(prevE);
            }
        remove_Edges_of(node_id);
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
    remove_Edges_of(node_id);
    free(iterator);
    Grpah_size--;
}

int min(int a,int b){
    if (a>b) {
        return b;}
    else {
         return a;
        }
    }
    
void Shortest_Path(int id1 ,int id2){
    int size =Grpah_size;
    int mat[size][size];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
           mat[i][j]=9999;
        } 
    }
    
    for (int src = 0; src < Grpah_size; src++)
    {
        mat[src][src]=0;
        pnode source=find_node(src);
        if(source!=NULL){
        pedge edge_iter=source->edges;
        while (edge_iter != NULL)
        {
            int dest=edge_iter->dest->node_num;
            mat[src][dest]=edge_iter->weight;
            edge_iter=edge_iter->next;
        }
    }
    }
        for(int u=0;u<Grpah_size;u++){
            for(int v=0;v<Grpah_size;v++){
                for(int k=0;k<Grpah_size;k++){
                    if(mat[v][k]!=0 && mat[v][u]!=0 && mat[u][k]!=0){
                        mat[v][k]=min(mat[v][k],mat[v][u]+mat[u][k]);

                    }
                    if(v!=k && mat[v][k]==0 && mat[v][u]!=0 && mat[u][k]!=0){
                           mat[v][k]=mat[v][u]+mat[u][k];

                }
            
            }
        }
    }

    if(mat[id1-'0'][id2-'0']>=9999)
    printf("Dijsktra shortest path: %d \n",-1);
     else
    printf("Dijsktra shortest path: %d \n",mat[id1-'0'][id2-'0']);
}


void PrintGraph(){
    pnode temp = head;
    pedge tempedge;
    while (temp!=NULL)
    {
        tempedge=temp->edges;
        printf("Node ID:%d\n",temp->node_num);
        while (tempedge!=NULL)
        {
            printf("Edge:\n Source:%d ,Dest:%d ,weight:%d\n",temp->node_num,tempedge->dest->node_num,tempedge->weight);
            tempedge=tempedge->next;
        }
        temp=temp->next;
    }
    
}

