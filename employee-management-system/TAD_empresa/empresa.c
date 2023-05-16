#include <stdio.h>
#include <string.h>
#include "empresa.h" 
#define TAM_LINHA 200
#define TAM_NOME 50

struct empresa {
    char CNPJ[20];
    char nome[TAM_NOME];
    char localizacao[100];
    float receita;
    float valor_de_mercado;
    CargosList *c_list;
    FuncionariosList *f_list;
    int num_funcionarios;
    int ultimo_id_funcionario;
    int num_cargos;
    int ultimo_id_cargo;
};

Empresa *empresa_cria(char *CNPJ, char *nome, char *localizacao, float receita, float valor_de_mercado) {
    Empresa* e = (Empresa*) malloc(sizeof(Empresa));
    // inserindo as informações passadas por parametro
    strcpy(e->CNPJ, CNPJ);
    strcpy(e->nome, nome);
    strcpy(e->localizacao, localizacao);
    e->receita = receita;
    e->valor_de_mercado = valor_de_mercado;

    return e;
}

Empresa *empresa_obter() {
    Empresa *empresa_arquivo;
    FILE *arquivo_origem;
    char linha[TAM_LINHA], CNPJ[20], nome_da_empresa[TAM_NOME], localizacao[100];
    float receita, valor_de_mercado;

    // lendo arquivo com as informacoes da empresa
    arquivo_origem = fopen("TAD_empresa/dados_empresa.txt", "r");
    if (arquivo_origem == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    while (fgets(linha, TAM_LINHA, arquivo_origem) != NULL) {
        sscanf(linha, " %[^;];%[^;];%[^;];%f;%f", CNPJ, nome_da_empresa, localizacao, &receita, &valor_de_mercado);
    } 

    empresa_arquivo = empresa_cria(CNPJ, nome_da_empresa, localizacao, receita, valor_de_mercado);
    fclose(arquivo_origem); // fecha o arquivo 

    return empresa_arquivo;
}

void empresa_imprime(Empresa *empresa) {
    printf("\n-------------INFORMAÇÕES DA EMPRESA-------------\n");
    printf("Nome da empresa: %s\n", empresa->nome);
    printf("CNPJ: %s\n", empresa->CNPJ);
    printf("Quantidade de funcionarios: %d\n", empresa->num_funcionarios);
    printf("Localização: %s\n", empresa->localizacao);
    printf("Receita: R$%.2f\n", empresa->receita);
    printf("Valor de mercado: R$%.2f\n\n", empresa->valor_de_mercado);
}

CargosList *solicita_informacoes_cargo(CargosList *c_list, int id, int *qtd_cargos) {
    CargosList *novo_cargo = c_list;
    char nome_cargo[TAM_NOME];
    char setor[TAM_NOME];

    printf("Digite o nome do cargo: ");
    scanf(" %[^\n]", nome_cargo);
    printf("Digite o nome do setor relacionado a este cargo: ");
    scanf(" %[^\n]", setor);

    novo_cargo = cargo_insere(novo_cargo, ++id, 0, nome_cargo, setor, qtd_cargos);

    return novo_cargo;
}

FuncionariosList *solicita_informacoes_funcionario(FuncionariosList *f_list, CargosList *c_list, int id, int *qtd_funcionarios) {
    FuncionariosList *f = f_list;
    CargosList *cargo;

    float salario;
    char nome[50], documento[20];
    Data *data = get_data();
    int jornada_de_trabalho;
    int cargo_id;

    if (cargo_lst_vazia(c_list)) {
        printf("Erro! Lista de cargos vazia.");
        printf("Primeiro crie algum cargo antes de adicinar Funcinarios.\n");
    } else {
        printf("Digite o CPF ou RG do funcionario: ");
        scanf(" %[^\n]", documento);
        printf("Digite o nome do funcionario: ");
        scanf(" %[^\n]", nome);
        printf("Digite o salario do funcionario: ");
        scanf("%f", &salario);
        printf("Digite a jornada de trabalho do funcionario: ");
        scanf("%d", &jornada_de_trabalho);
        
        f = lst_insere(f, nome, ++id, data, documento, salario, jornada_de_trabalho, qtd_funcionarios);

        cargo_imprime(c_list);

        printf("Digite o ID do cargo do Funcionario: ");
        scanf("%d", &cargo_id);
        cargo = cargo_busca(c_list, cargo_id);

        while (cargo == NULL) {
            printf("Parece que nao foi encontrado um cargo com esse ID!\n");
            printf("Tente digitar um novo ID: ");
            scanf("%d", &cargo_id);
            cargo = cargo_busca(c_list, cargo_id);
        }
        f->info.cargo = cargo->info;
        f->info.cargo_id = cargo->info->ID;
        f->info.cargo->qtd_funcionarios++;
    }   
    return f;
}

Empresa* empresa_start() {
    Empresa* empresa = empresa_obter(); // cria a empresa, com base nas informações do BD

    // pegando as informacoes dos funcionarios a partir do banco de dados
    empresa->f_list = lst_cria();
    empresa->f_list = obter_funcionarios(empresa->f_list);
    FuncionariosList* f = empresa->f_list;

    // verifica se a lista está vazia e inicializa as variaveis 'ultimo_id_funcionario' e "num_funcionarios"
    if (lst_vazia(f)) {
        empresa->ultimo_id_funcionario = 0;
        empresa->num_funcionarios = 0;
    }
    else {
        empresa->num_funcionarios = f->qtd_funcionarios;
        empresa->ultimo_id_funcionario = f->ultimo_id_cadastrado;
    }

    // pegando as informacoes dos cargos a partir do banco de dados
    empresa->c_list = cargo_cria();
    empresa->c_list = obter_cargos(empresa->c_list);
    CargosList* c = empresa->c_list;
    
    // verifica se a lista está vazia e inicializa as variaveis 'ultimo_id_cargo' e "num_cargos"
    if (cargo_lst_vazia(c)) {
        empresa->ultimo_id_cargo = 0;
        empresa->num_cargos = 0;
    }
    else {
        empresa->num_cargos = c->qtd_cargos;
        empresa->ultimo_id_cargo = c->ultimo_id_cargo_adicionado;
    }

    adiciona_cargo_a_funcionario(c, f);

    return empresa;
}

void adiciona_cargo_a_funcionario(CargosList *c_list, FuncionariosList *f_list) {
    if (cargo_lst_vazia(c_list) || lst_vazia(f_list)) {
        printf("Parece que você tem arquivos vazios, tente adicionar cargos e funcionários para começar!\n");
    } else {
        FuncionariosList *funcionario;
        CargosList *cargo;
        for (funcionario = f_list; funcionario != NULL; funcionario = funcionario->next) {
            cargo = cargo_busca(c_list, funcionario->info.cargo_id);

            if (cargo != NULL) {
                funcionario->info.cargo =  cargo->info;
            } else {
                funcionario->info.cargo =  NULL;
            }
        }
    }    
}
