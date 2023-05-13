#include "TAD_empresa/empresa.c"

FuncionariosList *pedir_informacoes_funcionario(FuncionariosList *f, CargosList *c_list, int id);
void adiciona_cargo_a_funcionario(CargosList *c_list, FuncionariosList *f_list);

int main (void) {
    int opcao, ultimo_id_cadastrado, id_busca_funcionario;

    // cria a empresa
    Empresa *empresa;
    empresa = empresa_obter();

    // pegando as informacoes dos funcionarios a partir do banco de dados
    empresa->f_list = lst_cria();
    FuncionariosList *f = empresa->f_list; 
    f = obter_funcionarios(f);
    
    // verifica se a lista está vazia e inicializa as variaveis 'ultimo_id_cadastrado' e "empresa->num_funcionarios"
    if(lst_vazia(f)) {
        ultimo_id_cadastrado = 0;
        empresa->num_funcionarios = 0;
    } else {
        empresa->num_funcionarios = f->qtd_funcionarios;
        ultimo_id_cadastrado = f->ultimo_id_cadastrado;
    }

    // pegando as informacoes dos cargos a partir do banco de dados
    empresa->c_list = cargo_cria();
    CargosList *c = empresa->c_list; 
    c = obter_cargos(c);

    // OBS.: adicionar função que percorre o arquivo de cargos e adiciona os ponteiros ao funcinario
    adiciona_cargo_a_funcionario(c, f);

    // verificando se a tratativa de id e quantidade de funcionários estão corretas
    printf("o ultimo id cadastrado no sistema foi: %d\n", ultimo_id_cadastrado);
    printf("Quantidade atual de funcionarios cadastrados: %d\n", empresa->num_funcionarios);

    lst_imprime(f);
    f = lst_retira(f, 12, &empresa->num_funcionarios);
    return 0;
} 

void adiciona_cargo_a_funcionario(CargosList *c_list, FuncionariosList *f_list) {
    if (cargo_lst_vazia(c_list) || lst_vazia(f_list)) {
        printf("Parece que você tem arquivos vazios, tente adicionar cargos e funcionários para começar!\n");
    } else {
        FuncionariosList *funcionario;
        CargosList *cargo;
        for (funcionario = f_list; funcionario != NULL; funcionario = funcionario->next) {
            cargo = cargo_busca(c_list, funcionario->info.cargo_id);
            funcionario->info.cargo =  cargo->info;
        }
    }    
}

FuncionariosList *pedir_informacoes_funcionario(FuncionariosList *f_list, CargosList *c_list, int id) {
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
        
        f = lst_insere(f, nome, ++id, data, documento, salario, jornada_de_trabalho);

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