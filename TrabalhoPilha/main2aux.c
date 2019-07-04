#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N (1 << 6)

typedef struct elem
{
    char dado;
    struct elem *anterior;
} celula;

celula *pilha = NULL;


char posfixa[N], sinal_de_associacao[] = { '}', ']', ')', '{', '[', '(' };

void limpapilha();
int empilha(char x);
int desempilha(char *y);
int posfixafuncao(char *f);
int prioridade(char c);

int main()
{
    int eposfixa;
    char funcao[N];
    scanf("%s", funcao);
    eposfixa = posfixafuncao(funcao);
    if (eposfixa == 1)
    {
        printf("%s\n", posfixa);
    }
    else if (eposfixa == -1)
    {
        puts("Erro em alocação");
    }
    else
    {
        puts("incorretamente parentizada");
    }

    if(pilha != NULL)
    {
        limpapilha();
    }
    else
    {
        free(pilha);
    }
    return 0;
}

int empilha(char x)
{
    celula *nova = malloc(sizeof(celula));
    if (nova == NULL)
    {
        return 0;
    }
    nova->dado = x;
    nova->anterior = pilha;
    pilha = nova;
    return 1;
}

int desempilha(char *y)
{
    celula *lixo = pilha;
    if (pilha == NULL)
    {
        return 0;
    }
    pilha = lixo->anterior;
    *y = lixo->dado;
    free(lixo);
    return 1;
}

void limpapilha()
{
    char donny;
    while (pilha->anterior != NULL)
    {
        desempilha(&donny);
    }
    free(pilha);
}

int prioridade(char c)
{
    switch (c)
    {
        case '^':
            return 3;
        case '*':
            return 2;
        case '/':
            return 2;
        case '+':
            return 1;
        case '-':
            return 1;
        default:
            return 0;
    }
}

int posfixafuncao(char *f)
{
    int j = 0;
    for(int i = 0; i < strlen(f); i++)
    {
        char c = f[i], op, t;
        printf("%s\n", posfixa);
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            posfixa[j] = c; 
            j++;
        }
        else
        {
            if(c == '(')
            {
                if(!empilha(c))
                {
                    return -1;
                }
            }
            else
            {
                if(c == ')')
                {
                    if(!desempilha(&op))
                    {
                        return 0;
                    }
                    while(op != '(')
                    {
                        posfixa[j] = op;
                        j++;
                        if(!desempilha(&op))
                        {
                            return 0;
                        }
                    }
                }
                else
                {
                    desempilha(&t);
                    if(prioridade(c) > prioridade(t))
                    {
                        if(!empilha(t))
                        {
                            return -1;
                        }
                        if(!empilha(c))
                        {
                            return -1;
                        }
                    }
                    else
                    {
                        while(prioridade(c) <= prioridade(t))
                        {
                            posfixa[j] = t;
                            j++;
                            desempilha(&t);
                        }
                        if(!empilha(t))
                        {
                            return -1;
                        }
                        if(!empilha(c))
                        {
                            return -1;
                        }
                    }
                }
            }
        }
    }
    while(pilha != NULL)
    {
        desempilha(&posfixa[j]);
        j++;
    }
    return 1;
}