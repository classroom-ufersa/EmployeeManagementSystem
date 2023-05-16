/* TAD: empresa */

#ifndef EMPRESA_H
#define EMPRESA_H

#include "../TAD_funcionario/funcionario.c"

// Struct do tipo Empresa
typedef struct empresa Empresa;

// Função que cria uma empresa
Empresa *empresa_cria(char *CNPJ, char *nome, char *localizacao, float receita, float valor_de_mercado);

// Resgata os dados do banco de dados da empresa e retorna um ponteiro para Empresa
Empresa *obter_empresa();

// Função imprime: imprime os dados da empresa
void empresa_imprime(Empresa *empresa);

// Solicita ao usuário as informações necessárias para preencher o cadastro de um cargo
CargosList *solicita_informacoes_cargo(CargosList *c_list, int id, int *qtd_cargos);

// Solicita ao usuário as informações necessárias para preencher o cadastro de um funcionario
FuncionariosList *solicita_informacoes_funcionario(FuncionariosList *f, CargosList *c_list, int id, int *qtd_funcionarios);

// Inicializa a empresa, com todas as informações necessárias
Empresa* empresa_start();

// Atribui os cargos a cada funcionário
void adiciona_cargo_a_funcionario(CargosList *c_list, FuncionariosList *f_list);

#endif
