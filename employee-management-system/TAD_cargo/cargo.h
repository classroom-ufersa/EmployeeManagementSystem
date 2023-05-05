/* TAD: cargo */

#ifndef CARGO_H
#define CARGO_H

// TIPOS ESTRUTURADOS:
// Struct do tipo Funcionario
typedef struct cargo Cargo;

// Struct para o nó da lista
typedef struct cargoslist CargosList;

CargosList* cargo_cria(void);
CargosList* cargo_insere(CargosList* c_list, int ID, int qtd_funcionarios, char *nome_cargo, char *setor);
CargosList* obter_cargos(CargosList *c_list);
int cargo_lst_vazia(CargosList* c_list);
void cargo_imprime(CargosList *c_list);
Cargo* cargo_busca(CargosList* c_list, int ID);
CargosList* cargo_retira(CargosList* c_list, int ID);
void cargo_libera(CargosList* f_list);
void cargo_atualiza_arquivo(CargosList* c_list);


#endif