#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
    int f, c, i;
       int vistos[10];

       for (f = 0; f < 9; f++) 
       {
           for (i = 0; i < 10; i++) vistos[i] = 0; 
           for (c = 0; c < 9; c++) 
           {
               int num = n->sudo[f][c];
               if (num != 0) 
               {
                   if (vistos[num]) return 0; 
                   vistos[num] = 1; 
               }
           }
       }

       for (c = 0; c < 9; c++) 
       {
           for (i = 0; i < 10; i++) vistos[i] = 0; 
           for (f = 0; f < 9; f++) 
           {
               int num = n->sudo[f][c];
               if (num != 0) 
               {
                   if (vistos[num]) return 0; 
                   vistos[num] = 1; 
               }
           }
       }

       for (int f_inicial = 0; f_inicial < 9; f_inicial += 3) {
           for (int c_inicial = 0; c_inicial < 9; c_inicial += 3) {
               for (i = 0; i < 10; i++) vistos[i] = 0;
               for (f = f_inicial; f < f_inicial + 3; f++) 
               {
                   for (c = c_inicial; c < c_inicial + 3; c++) 
                   {
                       int num = n->sudo[f][c];
                       if (num != 0) {
                           if (vistos[num]) return 0;
                           vistos[num] = 1; 
                       }
                   }
               }
           }
       }

       return 1; 
   }


List* get_adj_nodes(Node* n)
{
   List* list = createList();
       int f, c;


       for (f = 0; f < 9; f++) {
           for (c = 0; c < 9; c++) {
               if (n->sudo[f][c] == 0) 
               {
                   
                   for (int num = 1; num <= 9; num++) 
                   {
                       Node* nuevo_nodo = copy(n);
                       nuevo_nodo->sudo[f][c] = num;
                       if (is_valid(nuevo_nodo)) {
                           pushBack(list, nuevo_nodo);
                       } else 
                       {
                           free(nuevo_nodo);
                       }
                   }
                   return list;
               }
           }
       }

       return list;
   }
      
int is_final(Node* n)
{
    int f, c;
    for (f = 0; f < 9; f++)
    {
        for (c = 0; c < 9; c++)
        {
            if (n->sudo[f][c] == 0)
            {
                return 0;
            }   
        }   
    }
    return 1;
    
}

Node* DFS(Node* initial, int* cont)
{
    Stack* S = createStack();
    push(S, initial);
    while (get_size(S) != 0)
    {
        Node* n = top(S);
        pop(S);
        if (is_final(n))
        {
            return n;
        }
        List* list = get_adj_nodes(n);
        Node* aux = first(list);

        while (aux)
        {
            push(S, aux);
            aux = next(list);
        }
        free(n);
        (*cont)++;
        
            
    }
  return NULL;
}



/*
int main( int argc, char *argv[] )
{

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/