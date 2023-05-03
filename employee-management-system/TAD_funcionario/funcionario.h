/* TAD: funcionario */

#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

// --- TIPOS ESTRUTURADOS ---
// Struct do tipo union para o Documento (RG/CPF)
typedef union documento Documento;

// Struct do tipo Funcionario
typedef struct funcionario Funcionario;

// Struct para o nó da lista
typedef struct funcionarioslist FuncionariosList;

// --- FUNÇÕES DE CRIAÇÃO E LIBERAÇÃO --- 
// Função de criação: retorna uma lista vazia 
FuncionariosList* lst_cria(void);

// Função libera: libera elementos alocados
void lst_libera(FuncionariosList* l);

// --- FUNÇÕES DE MANIPULAÇÃO --- 
// Inserção no início: retorna a lista atualizada
FuncionariosList* lst_insere(FuncionariosList* f_list, char *nome, int id, Data *data, char *documento, 
char *cargo, char *setor, float salario, int jornada_trabalho);

// Função que resgata os funcionários arquivados e salva na lista
FuncionariosList* obter_funcionarios(FuncionariosList *f_list);

// Função retira: retira elemento da lista
FuncionariosList* lst_retira(FuncionariosList* f_list, int id);

// Funcão busca: busca um elemento na lista 
FuncionariosList* lst_busca(FuncionariosList* f_list, int id) ;

// Função imprime:  imprime valores dos elementos
void lst_imprime(FuncionariosList* f_list);

// Função vazia: retorna 1 se vazia ou 0 se não vazia
int lst_vazia(FuncionariosList* f_list);

// Função atualiza arquivo: resgata informações do banco de dados
void atualiza_arquivo(FuncionariosList* f_list);

// Função que troca os valores de dois nós
void swapNodes(FuncionariosList *f_list_1, FuncionariosList *f_list_2);

// Função que ordena a lista em ordem alfabetica
void lst_ordena(FuncionariosList *f_list);

// Função edita: altera o cadastro do funcionário
FuncionariosList *lst_edita(FuncionariosList *f_list, int id);

// Função que retorna a quantidade de elementos da lista
int lst_quantidade(FuncionariosList *f_list);

#endif