#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funcionario.h"
#define TAM_LINHA 200
#define TAM_NOME 50

union documento {
  char CPF[20];
  char RG[20];
};

struct funcionario {
    Documento cpf_rg;
    Data *data_de_contratacao;
    char name[TAM_NOME];
    int id;
    Cargo *cargo;
    float salario;
    int jornada_trabalho;
    int cargo_id;
};

struct funcionarioslist {
    Funcionario info;
    int ultimo_id_cadastrado;
    int qtd_funcionarios;
    struct funcionarioslist *next;
    struct funcionarioslist *prev;
};

FuncionariosList* lst_cria(void) {
    return NULL;
}

FuncionariosList* lst_insere(FuncionariosList* f_list, char *nome, int id, Data *data, char *documento, 
float salario, int jornada_trabalho, int *qtd_funcionarios) {
    FuncionariosList* novo = (FuncionariosList*) malloc(sizeof(FuncionariosList));   

    // inserindo as informações passadas pelo usuário
    strcpy(novo->info.name, nome);
    novo->info.id = id;
    novo->info.data_de_contratacao = data;
    strcpy(novo->info.cpf_rg.CPF, documento);
    novo->info.salario = salario;
    novo->info.jornada_trabalho = jornada_trabalho;
    novo->qtd_funcionarios = ++(*qtd_funcionarios);

    // adicionando de fato o nó na lista
    novo->next = f_list;
    novo->prev = NULL;
    // verifica se a lista não está vazia
    if (f_list != NULL)
        f_list->prev = novo;
    
    // atualiza_arquivo(novo);
    return novo;
}

FuncionariosList*  obter_funcionarios(FuncionariosList *f_list){
    FILE *arquivo_origem;
    FuncionariosList *new_list = f_list;
    char linha[TAM_LINHA], nome[TAM_NOME], documento[20];
    int id, dia, mes , ano, cargo_id = 0, maior_id = 0, qtd_funcionarios = 0;
    float salario;
    int jornada_trabalho;

    // lendo arquivo com as informacoes dos funcionarios
    arquivo_origem = fopen("TAD_funcionario/dados_funcionarios.txt", "r"); // abre o arquivo_origem para leitura
    if (arquivo_origem == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fseek(arquivo_origem, 0, SEEK_END); // posiciona o cursor no final do arquivo
    if (ftell(arquivo_origem) == 0) { // verifica a posição atual do cursor
        printf("Arquivo 'dados_funcionarios.txt' está vazio.\n");
        return NULL;
    }else{
        rewind(arquivo_origem); // recoloca o cursor no inicio do arquivo
    }

    while (fgets(linha, TAM_LINHA, arquivo_origem) != NULL) { 
        sscanf(linha, " %[^;];%d;%d/%d/%d;%[^;];%f;%d;%d", nome, &id, &dia, &mes, &ano, documento, &salario, &jornada_trabalho, &cargo_id);
        Data *data_contratacao = (Data*) malloc(sizeof(Data)); 
        data_contratacao->dia = dia;
        data_contratacao->mes = mes;
        data_contratacao->ano = ano;

        new_list = lst_insere(new_list, nome, id, data_contratacao, documento, salario, jornada_trabalho, &qtd_funcionarios);
        new_list->info.cargo_id = cargo_id;
        
        if (id > maior_id)
            maior_id = id;
        
        new_list->ultimo_id_cadastrado = maior_id; // aloca o id (o maior atual), o último id alocado ao último nó será o maior do arquivo
    }

    fclose(arquivo_origem); // fecha o arquivo
    return new_list;
}

void lst_imprime(FuncionariosList* f_list) {
    if (lst_vazia(f_list)) {
        printf("Nenhum funcionário encontrado no Sistema!\n");
        printf("Por favor, tente adicionar algum funcionário antes de exibi-los.\n\n");
    } else{
        FuncionariosList* p;
        printf("\n------------LISTA DE FUNCIONARIOS------------\n");
        for (p = f_list; p != NULL; p = p->next) {
            printf("Nome do Funcionario: %s\nID: %d\n", p->info.name, p->info.id);    
            printf("Data da contratacao: %d/", p->info.data_de_contratacao->dia); // imprime dia
            printf("%d/", p->info.data_de_contratacao->mes); // imprime mês
            printf("%d\n", p->info.data_de_contratacao->ano); // imprime ano
            printf("RG/CPF: %s\n", p->info.cpf_rg.CPF); // imprime Documento
            printf("Salario: %.2f \nJornada de Trabalho: %d\n", p->info.salario, p->info.jornada_trabalho);
            if (p->info.cargo != NULL) {
                printf("Cargo: %s\nSetor: %s\n\n", p->info.cargo->nome_cargo, p->info.cargo->setor);
            } else {
                printf("Ops! Cargo inexistente, tente editar o funcionario.\n\n");
            }
        }
    }
}

int lst_vazia(FuncionariosList* f_list) {
    if (f_list == NULL)
        return 1;
    else 
        return 0;
}

FuncionariosList* lst_busca(FuncionariosList* f_list, int id) {
    FuncionariosList* p;
    if (lst_vazia(f_list)) {
        printf("ERRO: lista vazia!\n");
        return NULL;
    } else {
        for (p = f_list; p != NULL; p = p->next) {
            if(p->info.id == id) {
                return p;
            }
        }
    }
    return NULL; // não achou o elemento buscado     
}

FuncionariosList* lst_retira(FuncionariosList* f_list, int id, int *qtd_funcionarios_ptr) {
    FuncionariosList* p = lst_busca(f_list, id);

    // verifica se achou elemento
    if (p == NULL) {
        printf("Funcionário com ID %d não foi encontrado no sistema. Por favor, tente novamente.\n\n", id);
        return f_list; 
    }

    // retira elemento do encadeamento
    if (f_list == p) // testa se é o primeiro elemento
        f_list = p->next;
    else 
        p->prev->next = p->next;
    
    if (p->next != NULL) // testa se é o último elemento
        p->next->prev = p->prev; 
    
    
    (p->info.cargo->qtd_funcionarios)--;
    (*qtd_funcionarios_ptr)--; // atualiza a quantidade de funcionarios
    free(p);

    printf("O funcionário de ID %d foi excluído do sistema.\n", id);
    printf("Quantidade de funcionários atualizado para %d.\n\n", *qtd_funcionarios_ptr);
    return f_list;
}

void lst_libera(FuncionariosList* f_list) {
    FuncionariosList* p = f_list;
    while (p != NULL) {
        /* guarda referência p/ próx. elemento */
        FuncionariosList* t = p->next;
        /* libera memória apontada por p */
        free(p->info.data_de_contratacao); // libera memória alocada para data
        free(p);
        /* faz p apontar para o próximo */
        p = t;
    }
}

void lst_atualiza_arquivo(FuncionariosList* f_list) {
    FuncionariosList* p; /* variável auxiliar para percorrer a lista */
    FILE *arquivo;
    arquivo = fopen("TAD_funcionario/dados_funcionarios.txt", "w"); // Abre o arquivo para escrita

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    lst_ordena(f_list);   
    for (p = f_list; p != NULL; p = p->next) {
        fprintf(arquivo, "%s;", p->info.name); // nome
        fprintf(arquivo, "%d;", p->info.id); // id
        fprintf(arquivo, "%d/", p->info.data_de_contratacao->dia); // data
        fprintf(arquivo, "%d/", p->info.data_de_contratacao->mes);
        fprintf(arquivo, "%d;", p->info.data_de_contratacao->ano);
        fprintf(arquivo, "%s;", p->info.cpf_rg.CPF); // documento
        fprintf(arquivo, "%.2f;", p->info.salario); // salario
        fprintf(arquivo, "%d;", p->info.jornada_trabalho); // jornada de trabalho
        fprintf(arquivo, "%d\n", p->info.cargo_id); // id do cargo
    }
    
    fclose(arquivo); // Fecha o arquivo
    printf("Arquivo funcionarios atualizado com sucesso!\n");
}

void swapNodes(FuncionariosList *f_list_1, FuncionariosList *f_list_2) {
    Funcionario temp = f_list_1->info;
    f_list_1->info = f_list_2->info;
    f_list_2->info = temp;
}

void lst_ordena(FuncionariosList *f_list) {
    FuncionariosList *i;
    FuncionariosList *j;
    // ordena os nomes usando bubble sort
    for (i = f_list; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->info.name, j->info.name) > 0) {
                swapNodes(i, j);
            }
        }
    }
}

FuncionariosList *lst_edita(FuncionariosList *f_list, CargosList *c_list, int id) {
    FuncionariosList* p = lst_busca(f_list, id);

    // verifica se achou o elemento
    if (p == NULL) {
        printf("Funcionário com ID %d não encontrado no sistema. Por favor, tente novamente.\n", id);
        return f_list; 
    } else {
        char resposta;
            printf("Deseja editar o nome (s/n)? ");
            scanf(" %c", &resposta);
            if (resposta == 's') {
                printf("Digite o novo nome: ");
                scanf(" %[^\n]", p->info.name);
            }
            printf("Deseja editar o CPF (s/n)? ");
            scanf(" %c", &resposta);
            if (resposta == 's') {
                printf("Digite o novo CPF: ");
                scanf(" %[^\n]", p->info.cpf_rg.CPF);
            }
            printf("Deseja editar o cargo (s/n)? ");
            scanf(" %c", &resposta);
            if (cargo_lst_vazia(c_list)) {
                printf("Erro! Lista de cargos vazia.");
                printf("Primeiro crie algum cargo antes de adicinar Funcinarios.\n");
                
            } else if(resposta == 's') {
                // Edita o cargo
                int cargo_id;
                CargosList *cargo;

                cargo_imprime(c_list);
                printf("Digite o ID do novo cargo: ");
                scanf("%d", &cargo_id);
                cargo = cargo_busca(c_list, cargo_id);

                while (cargo == NULL) {
                    printf("Parece que nao foi encontrado um cargo com esse ID!\n");
                    printf("Tente digitar um novo ID: ");
                    scanf("%d", &cargo_id);
                    cargo = cargo_busca(c_list, cargo_id);
                }

                if (p->info.cargo != NULL)
                    p->info.cargo->qtd_funcionarios--; // Diminui a quantidade de funcionários no cargo anterior
            
                p->info.cargo = cargo->info;
                p->info.cargo_id = cargo->info->ID;
                p->info.cargo->qtd_funcionarios++; // Aumenta a quantidade de funcionários no cargo atual
            }
            printf("Deseja editar o salário (s/n)? ");
            scanf(" %c", &resposta);
            if (resposta == 's') {
                printf("Digite o novo salário: ");
                scanf("%f", &p->info.salario);
            }
            printf("Deseja editar a jornada de trabalho (s/n)? ");
            scanf(" %c", &resposta);
            if (resposta == 's') {
                printf("Digite a nova jornada de trabalho: ");
                scanf("%d", &p->info.jornada_trabalho);
            }
            printf("Funcionário atualizado com sucesso!\n\n");
    }

    return f_list;
}

void lst_imprime_um_funcionario(FuncionariosList* f_list) {
    printf("Nome do Funcionario: %s\n", f_list->info.name);
    printf("ID: %d\n", f_list->info.id);    
    printf("Data da contratacao: %d/", f_list->info.data_de_contratacao->dia); // imprime dia
    printf("%d/", f_list->info.data_de_contratacao->mes); // imprime mês
    printf("%d\n", f_list->info.data_de_contratacao->ano); // imprime ano
    printf("RG/CPF: %s\n", f_list->info.cpf_rg.CPF); // imprime Documento
    printf("Salario: %.2f \nJornada de Trabalho: %d\n", f_list->info.salario, f_list->info.jornada_trabalho);
     if (f_list->info.cargo != NULL) {
        printf("Cargo: %s\nSetor: %s\n\n", f_list->info.cargo->nome_cargo, f_list->info.cargo->setor);
    } else {
        printf("Ops! Cargo inexistente, tente editar o funcionario.\n\n");
    }
}
