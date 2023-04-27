/* TAD: funcionario */

#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct funcionario Funcionario;
typedef struct funcionarioslist FuncionariosList;

/* funções de criação e liberação */
FuncionariosList* lst_cria(void);
void lst_libera(FuncionariosList* l);

/* funções de manipulação */
FuncionariosList* lst_insere(FuncionariosList* f_list, char *nome, int id);
FuncionariosList* lst_retira(FuncionariosList* f_list, int id);
FuncionariosList* lst_busca(FuncionariosList* f_list, int id) ;
void lst_imprime(FuncionariosList* f_list);
int lst_vazia(FuncionariosList* f_list);

#endif