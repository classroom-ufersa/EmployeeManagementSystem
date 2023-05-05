#include <stdio.h>
#include <stdlib.h>
#include "TAD_empresa/empresa.c"

int main (void) {
    FuncionariosList* f_list;
    f_list = lst_cria();
    f_list = obter_funcionarios(f_list);
    Data *data = get_data();
    
    //colocar essa verificacao no main.c
    int id;
    if(lst_vazia(f_list)){
        id = 1;
    } else {
        id = ++(*(f_list->ultimo_id_cadastrado));
    }
    
    f_list = lst_insere(f_list, "Patricia Almeida", id, data, "888.888.888-88", 10000.0, 45);
    
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