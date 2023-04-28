#include <stdio.h>
#include <stdlib.h>
#include "TAD_funcionario/funcionario.c"

int main (void) {
    FuncionariosList* f_list;
    f_list = lst_cria();
    f_list = obter_funcionarios(f_list);
    Data* data = get_data();
    f_list = lst_insere(f_list, "Joaquim Correa", 5, data);
    lst_imprime(f_list);
    lst_retira(f_list, 3);
    lst_imprime(f_list);
    atualiza_arquivo(f_list);
    return 0;
} 