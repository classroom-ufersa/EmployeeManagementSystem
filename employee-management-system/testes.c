#include <stdio.h>
#include <stdlib.h>
//#include "TAD_funcionario/funcionario.c"
#include "TAD_empresa/empresa.c"

int main (void) {
    /*FuncionariosList* f_list;
    f_list = lst_cria();
    f_list = obter_funcionarios(f_list);
    lst_imprime(f_list);
    lst_ordena(f_list);
    Data *data = get_data();
    f_list = lst_insere(f_list, "Pedro", 3, data, "123.123.123-01", "Gerente", "RH", 8000.0, 40);
    
    printf("----------------------------\n");
    lst_ordena(f_list);
    lst_imprime(f_list);*/

    Empresa *empresa;
    empresa = empresa_obter();
    empresa_imprime(empresa);
    
    empresa->f_list = lst_cria();
    empresa->f_list = obter_funcionarios(empresa->f_list);
    return 0;
} 