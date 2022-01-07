#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct g_node *pnode;
struct g_node *head;
static int Grpah_size=0;
int cost=0;

typedef struct edge_ {
    int weight;
    pnode dest;
    struct edge_ *next;
} edge, *pedge;

typedef struct g_node {
    int node_num;
    pedge edges;
    struct g_node *next;
} node, *pnode;

void free_graph();
void delete_node(int node_id);
void remove_Edges_of(int id);

void  build_graphcmd(int g_size){
    Grpah_size=g_size;
    //printf("Grpah_size: %d\n",Grpah_size);
    head = NULL;
    head=(pnode)malloc(sizeof(struct g_node));
    head->node_num=0;
    head->next=NULL;
    pnode temp = head;
    for (int i =1; i < g_size+1; i++)
    {
        if (i==g_size)
        {
            break;
        }
        pnode next_Node=(pnode)malloc(sizeof(struct g_node));
        next_Node->node_num=i;
        //printf("Next node:: %d is connecting to %d\n",next_Node->node_num,temp->node_num);
        temp->next=next_Node;
        temp=temp->next;
    }
    temp->next=NULL;
}

void free_graph(){
    int size=Grpah_size;
    pnode Iterator = head;
    while (head!=NULL)
    {
        pnode Iterator=head;
        //printf("Iterator:%d\n",Iterator->node_num);
        head=head->next;// Changed head
        //printf("Head: %d\n",head->node_num);
        pedge prevE=Iterator->edges;
        while (Iterator->edges!=NULL)
            {
            prevE = Iterator->edges;
            Iterator->edges=Iterator->edges->next;
            free(prevE);
            }
        //printf("Iterator FREE:%d\n",Iterator->node_num);           
        free(Iterator);// free old head
    }
    //printf("Finished\n");
    free(head);
    head=NULL;
}

//######function that find the node according to his ID######
pnode find_node(int id){
    pnode temp = head;
    //if the node we are looking for is the head
    //return him
    if ((temp->node_num)==id)
    {
        return temp;
    }
    //else go over all the nodes and try to find the node
    while (temp!=NULL)
    {
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
    new_edge->next=NULL;
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
/*
Update or create a node according to the "type" recieved
'n'-update an exist node
'B'-Create a new node
*/
void insert_node(char* cptr,char type){
    if(type=='n'){
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
    if(type=='B'){
        int digit=cptr[0]-'0';// Node number
        pnode temp = head;
        temp=find_node(digit);//find the node
        if (temp==NULL)
        {
        pnode temp = head;
        pnode new_Node=(pnode)malloc(sizeof(struct g_node));
        new_Node->node_num=digit;
        new_Node->next=NULL;
            while (temp->next!=NULL)
            {
                temp=temp->next;
            }
            temp->next=new_Node;
        for (int i = 1; i < strlen(cptr); i=i+2)
        {
        int dest=cptr[i]-'0';
        int weight=cptr[i+1]-'0'; 
        add_edge(&(new_Node->edges),dest,weight);
        }
        Grpah_size++;
        }
        else{
        pedge prevE=temp->edges;
        while (temp->edges!=NULL)
    {
        prevE = temp->edges;
        temp->edges=temp->edges->next;
        free(prevE);
    }
        temp=find_node(digit);//find the node
        for (int i = 1; i < strlen(cptr); i=i+2)
        {
        int dest=cptr[i]-'0';
        int weight=cptr[i+1]-'0'; 
        add_edge(&(temp->edges),dest,weight);
    }
    }
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

/*
Return the shortest path form id1 to id2 using a matrix
if type = 0 id1 and id2 are integers
if type = 1 id1 and id2 are integers from a string
*/    
int Shortest_Path(int id1 ,int id2,int type){
    int size =Grpah_size+2;
    int mat[size][size];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
           mat[i][j]=9999;
        } 
    }
    for (int src = 0; src <= Grpah_size+1; src++)
    {
        mat[src][src]=0;
        pnode source=find_node(src);
        if(source!=NULL){
        pedge edge_iter=source->edges;
        while (edge_iter != NULL)
        {
            int dest=edge_iter->dest->node_num;
            if(dest>=size){
            dest=dest-1;
            }
            mat[src][dest]=edge_iter->weight;
            edge_iter=edge_iter->next;
        }
    }
    }
        for(int u=0;u<=Grpah_size+1;u++){
            for(int v=0;v<=Grpah_size+1;v++){
                for(int k=0;k<=Grpah_size+1;k++){
                    if(mat[v][k]!=0 && mat[v][u]!=0 && mat[u][k]!=0){
                        mat[v][k]=min(mat[v][k],mat[v][u]+mat[u][k]);

                    }
                    if(v!=k && mat[v][k]==0 && mat[v][u]!=0 && mat[u][k]!=0){
                           mat[v][k]=mat[v][u]+mat[u][k];

                }
            
            }
        }
    }
    if (type==0){
    if(mat[id1][id2]>=9999)
    return -1;
     else
    return mat[id1][id2];
    }
    else{
        //to recieve the actual number from a string we must do -'0' 
        if(mat[id1-'0'][id2-'0']>=9999)
            return -1;
        else
            return mat[id1-'0'][id2-'0'];
    }
}


/*
Swap function for permute
*/
void swap(int *x, int *y){
    int temp = 0;
    temp = *x;
    *x = *y;
    *y = temp;
}

/*
Get an Array and a length of the array and calculate the dist of the nodes in the array
 */
int TSP_Shortest_Path(int TSP[], int Tsp_len){
    int cost = 0;
    for (int i = 0; i < Tsp_len-1; i++)
    {
        if (cost <= -1)
        {
            return 99999;
        }
        int add=Shortest_Path(TSP[i], TSP[i+1],0);
        if(add!=-1){
        cost += add;
        }
        else
            return 99999;
    }
    return cost;
}

/* Function to print permutations of an Array 
This function takes three parameters: 
1. TSP Array 
2. Starting index of the array 
3. Ending index of the string.
4. Size of the array */
void permute(int TSP[], int s, int e, int size, int* Min_cost){
    if (s == e)//End of the recursion
    {
        int cost = TSP_Shortest_Path(TSP, size);
        if (min(cost, *Min_cost) == cost)
        {
            *Min_cost = cost;
        }
    }
    else{
        for (int i = s; i <= e; i++)
        {
            swap((TSP+s), (TSP+i));
            permute(TSP, s+1, e, size, Min_cost);
            swap((TSP+s), (TSP+i));
        }
    }
}
    

/*
TSP function that receive a string from the user that include how many "destination" and the id of the "destination"
that the user wish to check.
The function return the min cost of the most efficient road.
*/
void TSP_cmd(char* cptr){
    int arr_size = cptr[0]-'0'; //Arr_size
    int Nodes[arr_size];  
    for (int i = 0; i < strlen(cptr)-1; i++)
    {
        int city = cptr[i+1]-'0';
        Nodes[i] = city;
    } 
    int Min_cost = 99999;
    permute(Nodes, 0, arr_size-1, arr_size, &Min_cost);
    if ((Min_cost <= 0) || (Min_cost >= 99999))
    {
        Min_cost = -1;
    }
    printf("TSP shortest path: %d \n", Min_cost);
}

/*
Print the nodes and the edges in the graph
*/
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
