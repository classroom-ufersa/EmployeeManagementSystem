#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funcionario.h"

/* estrutura do tipo Funcionario */
struct funcionario {
    char name[50];
    int id;
};

/* Struct que representa o nó da lista */
struct funcionarioslist {
    Funcionario info;
    struct list *next;
};

/* função de criação: retorna uma lista vazia */ 
FuncionariosList* lst_cria(void) {
    return NULL;
}

/* inserção no início: retorna a lista atualizada */
FuncionariosList* lst_insere(FuncionariosList* f_list, char *nome, int id) {
    FuncionariosList* novo = (FuncionariosList*) malloc(sizeof(FuncionariosList));   
    strcpy(novo->info.name, nome);
    novo->info.id = id;
    novo->next = f_list;
    return novo;
}

/* função imprime:  imprime valores dos elementos */
void lst_imprime(FuncionariosList* f_list) {
    FuncionariosList* p; /* variável auxiliar para percorrer a lista */
    for (p = f_list; p != NULL; p = p->next)
        printf("ID: %d | Nome: %s\n", p->info.id, p->info.name);    
}

/* função vazia: retorna 1 se vazia ou 0 se não vazia */
int lst_vazia(FuncionariosList* f_list) {
    if (f_list == NULL)
        return 1;
    else 
        return 0;
}

/* funcão busca: busca um elemento na lista */
FuncionariosList* lst_busca(FuncionariosList* f_list, int id) {
    FuncionariosList* p;
    for (p = f_list; p != NULL; p = p->next) {
        if(p->info.id == id)
            return p;
    }
    return NULL; /* não achou o elemento buscado */     
}

/* função retira: retira elemento da lista */
FuncionariosList* lst_retira(FuncionariosList* f_list, int id) {
    FuncionariosList* ant = NULL;
    FuncionariosList* p = f_list;

    /* procura elemento na lista, guardando anterior */
    while (p != NULL && p->info.id != id) {
        ant = p;
        p = p->next;
    }

    /* verifica se achou elemento */
    if (p == NULL) {
        return f_list; /* não achou: retorna a lista original */
    }

    /* retira elemento */
    if (ant == NULL) {
        /* retira elemento do início */
        f_list = p->next;
    } else {
        /* retira elemento do meio */
        ant->next = p->next;
    }

    free(p);
    return f_list;
}

/* função libera: libera elementos alocados */
void lst_libera(FuncionariosList* f_list) {
    FuncionariosList* p = f_list;
    while (p != NULL) {
        /* guarda referência p/ próx. elemento */
        FuncionariosList* t = p->next;
        /* libera memória apontada por p */
        free(p);
        /* faz p apontar para o próximo */
        p = t;
    }
}