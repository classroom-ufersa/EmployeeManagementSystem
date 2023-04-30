/* TAD: funcionario */

#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

// --- TIPOS ESTRUTURADOS ---
// Struct do tipo union para o Documento (RG/CPF)
typedef union documento Documento;

// Struct do tipo Data
typedef struct data Data;

// Struct do tipo Funcionario
typedef struct funcionario Funcionario;

// Struct para o nó da lista
typedef struct funcionarioslist FuncionariosList;

// --- FUNÇÕES DE CRIAÇÃO E LIBERAÇÃO --- 
// Função de criação: retorna uma lista vazia 
FuncionariosList* lst_cria(void);

// Função libera: libera elementos alocados
void lst_libera(FuncionariosList* l);

// FUNÇÕES DE MANIPULAÇÃO
FuncionariosList* lst_insere(FuncionariosList* f_list, char *nome, int id, Data *data, char *documento);
FuncionariosList* obter_funcionarios(FuncionariosList *f_list);
FuncionariosList* lst_retira(FuncionariosList* f_list, int id);
FuncionariosList* lst_busca(FuncionariosList* f_list, int id) ;
void lst_imprime(FuncionariosList* f_list);
int lst_vazia(FuncionariosList* f_list);
Data *get_data(void);
void atualiza_arquivo(FuncionariosList* f_list);

// Função que troca os valores de dois nós
void swapNodes(FuncionariosList *f_list_1, FuncionariosList *f_list_2);

// Função que ordena a lista em ordem alfabetica
void lst_ordena(FuncionariosList *f_list);

#endif