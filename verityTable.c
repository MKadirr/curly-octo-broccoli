#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//chainedType
struct chainedType {
    char* id;
    int *table;
    unsigned long sizeTable;
    struct chainedType* next;
};

struct chainedType* create(char c)
{
    struct chainedType* tmp = (struct chainedType*) malloc(sizeof(struct chainedType));
    //printf("creation d'un chained type a l'adresse : %p\n", tmp);
    char tmp2[1]; tmp2[0] = c; tmp2[1] = '\0';
    tmp->id = (char*) malloc(sizeof(char[1]));
    strcpy(tmp->id, tmp2);
    tmp->sizeTable = 0;
    tmp->table = NULL;
    tmp->next = NULL;

    return tmp;
}
void allocate(struct chainedType* ct, long size)
{
    ct->sizeTable = size;

    ct->table = (int*) malloc(sizeof(int) * ct->sizeTable);
    //printf("creaton du tableau de %p à l'adresse %p de taille %d\n",ct, ct->table, ct->sizeTable);
}

void destroy(struct chainedType* ct)
{
    if(ct == NULL) return;
    destroy(ct->next);
    printf("liberation du char* : %p\n", ct->id);
    free(ct->id);
    printf("liberation du tableau : %p\n", ct->table);
    free(ct->table);
    printf("liberation de l'adresse : %p\n", ct);
    free(ct);
}

struct chainedType* find(char c, struct chainedType* ct)
{
    if(ct == NULL) 
    {
        //printf("end\n");
        return NULL;
    }
    //printf("cherche %c, a l'adresse %p d'id : %c\n",c , ct, ct->id);
    char tmp2[1]; tmp2[0] = c; tmp2[1] = '\0';
    if(strcmp(ct->id , tmp2)) return ct;
    else return find(c, ct->next);
}

void show(struct chainedType* ct)
{
    printf("%s ",ct->id);
    for(int i = 0; i<ct->sizeTable; i++) printf("| %d ", ct->table[i]);
    printf("\n");
}

long power(int nb, int expo)
{
    if(expo < 0) return -1;
    if(expo == 0) 
    {
        
        return 1;
    }
    if(expo > 0) 
    {
        //printf("%d ",expo);
        return power(nb, --expo) * nb;
    }
}


int first_of_advance(char del, char* string, int begin)
{
    for(int i = begin; i<strlen(string); i++)
    {
        if(string[i]==del) return i;
    }
    return -1;
}

int first_of(char del, char* string)
{
    return first_of_advance(del, string, 0);
}

char* substr(char* origin, int start, int end)
{
    char * tmp = (char*) malloc(sizeof(char[end-start+1]));
    for(int i = 0; i<=end-start; i++)
    {
        tmp[i] = origin[i+start];
    }
    tmp[end-start+1] = '\0';

    return tmp;
}


int* read(char* string)
{

    return NULL;
}

int* table(char* string)
{
    
    struct chainedType* first = NULL;
    struct chainedType* last = NULL;
    
    int nbProp = 0;
    for(int i = 0; i<strlen(string);i++)
    {
        //printf("%c : %d\n",string[i], string[i]);
        struct chainedType* tmp = find(string[i], first);
        //printf("tmp : %p\n",tmp);
        if(61 <= string[i] && string[i] <= (61 + 26) && tmp == NULL)
        {
            
            if(nbProp == 0) 
            {
                first = create(string[i]);
                last = first;
            }
            else 
            {
                last->next = create(string[i]);
                last = last->next;
            }
            nbProp++;
        }
    }
    

    //printf("nbProp : %d\n",nbProp);
    struct chainedType* next = first;
    unsigned long nbCase = power(2, nbProp);
    //printf("nbCase : %d\n",nbCase);
    for(int i = nbProp-1; i>=0; i--)
    {
        long distrib = power(2, i);
        allocate(next, nbCase);
        for(int j = 0; j<nbCase; j++)
        {
            next->table[j] = (((int) j / distrib) + 1) % 2;
        }
        show(next);

        next = next->next;
    }

    destroy(first);

    return NULL;
}


int main(int argc, int **argv)
{
    if(0)
    {
        struct chainedType* first = create('T');
        struct chainedType* last = first;
        
        allocate(first, 8);
        for(int j = 0; j<8; j++)
        {
            first->table[j] = ((int) j / 4) % 2;
        }
        show(first);

        destroy(first);
    }
    if(1)
    {
        char test[] = "salutation\n";
        printf("full : %s",test);
        char* sub = NULL;
        int d1 = first_of('t', test);
        int d2 = first_of_advance('t', test, 0);
        int d3 = first_of_advance('t', test, 6);

        printf("%d %d %d\n",d1, d2, d3);

        sub = substr(test, 1, d1);
        printf("%s\n",sub);

        free(sub);
    }

    //table("ABCCD");

    return 0;
}

/*
cd C:\Users\Simon\Desktop\developement\.prog\
gcc verityTable.c -o vt.exe -g -fsanitize=address
*/