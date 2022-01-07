#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "graph.c"

int main(){
    char *str = NULL;
    int ch;
    size_t size = 0, len = 0;
    pnode head;
    while ((ch=getchar()) != EOF && ch != '\n') {
        if (len + 1 >= size)
        {
            size = size * 2 + 1;
            str = realloc(str, sizeof(char)*size);
        }
        str[len++] = ch;
    }
    for(int i=0;i<strlen(str);i=i+2)
    {
         if (str[i]=='A')
        {
            free_graph();
            i=i+2;
            char temp=str[i];
            int size_of_graph=temp - '0';
            build_graphcmd(size_of_graph);
        }
        else if (str[i]=='n')
        {
            int j=i+2;
            char *cptr = NULL;
            cptr = (char*)malloc(sizeof(char));
            *cptr = NULL;
            if(cptr == NULL){
                return 0;
            }
            while (isdigit(str[j])!=0)
            {         
            cptr = realloc(cptr,((strlen(cptr)+1)*sizeof(char)));
            strncat(cptr, &str[j], 1);
            j=j+2;
            }
            i=j-2;
            char end='\0';
            strncat(cptr, &end, 1);

            insert_node(cptr,'n');
            free(cptr);
        }
        else if (str[i]=='B')
        {
            int j=i+2;
            char *cptr;
            cptr = (char*)malloc(sizeof(char));
            if(cptr == NULL){
                return 0;
            }
            while (isdigit(str[j])!=0)
            {         
            cptr = realloc(cptr,((strlen(cptr)+1)*sizeof(char)));
            strncat(cptr, &str[j], 1);
            j=j+2;
            }
            i=j-2;
            insert_node(cptr,'B');
            //printf("%s\n",cptr);
            free(cptr);
        }
        
        else if (str[i]=='D')
        {
            i=i+2;
            char temp=str[i];
            int Node_id=temp - '0';
            delete_node(Node_id);
        }
        else if(str[i] == 'S'){
            i=i+2;
            int src= str[i];
            i=i+2;
            int dest = str[i];
            int ans=Shortest_Path(src,dest,1);
             printf("Dijsktra shortest path: %d\n",ans);
        }
        else if(str[i]=='T'){
            int j=i+2;
            char *cptr = NULL;
            cptr = (char*)malloc(sizeof(char));
            *cptr = NULL;
            if(cptr == NULL){
                return 0;
            }
            while (isdigit(str[j])!=0)
            {         
            cptr = realloc(cptr,((strlen(cptr)+1)*sizeof(char)));
            strncat(cptr, &str[j], 1);
            j=j+2;
            }
            i=j-2;
            TSP_cmd(cptr);
        }   
    }
    
    
    //PrintGraph();
    return 0;
}