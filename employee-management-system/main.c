#include <stdio.h>
#include <stdlib.h>
#include "TAD_funcionario/funcionario.c"

int main (void) {
    /*FuncionariosList* f_list;
    f_list = lst_cria();
    f_list = obter_funcionarios(f_list);
    Data* data = get_data();
    f_list = lst_insere(f_list, "Claudio Caueh", 5, data, "062.757.660-50");
    lst_imprime(f_list);
    lst_retira(f_list, 2);
    lst_imprime(f_list);
    atualiza_arquivo(f_list);*/

    FuncionariosList* f_list;
    f_list = lst_cria();
    Data* data = get_data();
    f_list = lst_insere(f_list, "A S", 1, data, "000.000.000-00");
    f_list = lst_insere(f_list, "B S", 2, data, "111.111.111-11");
    f_list = lst_insere(f_list, "D S", 3, data, "222.222.222-22");
    
    printf("++++++++\n");
    lst_imprime(f_list);

    printf("++++++++\n");
    f_list = lst_retira(f_list, 2);
    lst_imprime(f_list);

    return 0;
} 