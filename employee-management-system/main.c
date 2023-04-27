#include <stdio.h>
#include "funcionario.h"

int main (void) {
    FuncionariosList* f_list;
    f_list = lst_cria();
    f_list = lst_insere(f_list, "Dayvison", 1);
    f_list = lst_insere(f_list, "Marcus", 2);
    f_list = lst_insere(f_list, "Amadeus", 3);
    lst_imprime(f_list);
    lst_retira(f_list, 2);
    printf("\nRemovento funcionário...\n");
    lst_imprime(f_list);
    return 0;
} 