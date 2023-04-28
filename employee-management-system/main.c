#include <stdio.h>
#include <stdlib.h>
#include "TAD_funcionario/funcionario.h"

int main (void) {
    FuncionariosList* f_list;
    f_list = lst_cria();
    f_list = obter_funcionarios(f_list);
    Data* data = get_data();
    f_list = lst_insere(f_list, "Victor Emanuel", 4, data);
    lst_imprime(f_list);
    return 0;
} 