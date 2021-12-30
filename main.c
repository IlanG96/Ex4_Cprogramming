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
    // if (str != NULL) {
    //     str[len] = '\0';
    //     printf("%s\n", str);
    //     free(str);
    // }
    for(int i=0;i<strlen(str);i=i+2)
    {
        if (str[i]=='A')
        {
            char temp=str[i+2];
            int size_of_graph=temp - '0';
            build_graphcmd(size_of_graph);
            // pnode num = head;
            // for (int i = 0; i < size_of_graph; i++)
            // {
            //     printf("%d/n", num->node_num);
            //     num = num->next;
            //} 
            continue;
        }
        if (str[i]=='n')
        {
            int j=i+2;
            char *cptr = NULL;
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
            insert_node(cptr);
            //printf("%s\n",cptr);
            free(cptr);
        }
    }
    
    

    return 0;
}