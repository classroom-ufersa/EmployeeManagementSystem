#include <stdio.h>
#include <stdlib.h>
#include "TAD_empresa/empresa.c"

int main (void) {
    FuncionariosList* f_list;
    f_list = lst_cria();
    f_list = obter_funcionarios(f_list);
    Data *data = get_data();
    
    int id;



    // inserindo um novo funcionario na lista
    f_list = lst_insere(f_list, "Barbara Almeida", ++id, data, "888.888.888-88", 10000.0, 45);
    ++(f_list->qtd_funcionarios);
    lst_ordena(f_list);
    lst_imprime(f_list);

    // inserindo um novo funcionario na lista
    f_list = lst_insere(f_list, "Antonio Virgulini", ++id, data, "000.000.000-00", 4500.0, 40);
    ++(f_list->qtd_funcionarios);
    lst_ordena(f_list);
    lst_imprime(f_list);

    /*Empresa *empresa;
    empresa = empresa_obter();
    empresa_imprime(empresa);
    
    empresa->f_list = lst_cria();
    empresa->f_list = obter_funcionarios(empresa->f_list);*/

    /*CargosList *c_list;
    c_list = cargo_cria();
    c_list = obter_cargos(c_list);
    cargo_imprime(c_list);
    c_list = cargo_insere(c_list, (c_list->info->ID)+1, 0, "Gerente de Vendas", "Vendas");
    c_list = cargo_retira(c_list, 3);
    cargo_imprime(c_list);*/

    // OBS: se for criado um cargo do zero será passado como parametro 0 funcionarios
    return 0;
} 