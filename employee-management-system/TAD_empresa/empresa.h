/* TAD: empresa */

#ifndef EMPRESA_H
#define EMPRESA_H

// Struct do tipo Empresa
typedef struct empresa Empresa;

// Função que cria uma empresa
Empresa *empresa_cria(char *CNPJ, char *nome, char *localizacao, float receita, float valor_de_mercado);

// Função que pega os dados do banco de dados da empresa e retorna um ponteiro para Empresa
Empresa *obter_empresa();

// Função imprime: imprime os dados da empresa
void empresa_imprime(Empresa *empresa);

#endif
