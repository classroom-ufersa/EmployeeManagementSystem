#include "TAD_empresa/empresa.c"

FuncionariosList *pedir_informacoes_funcionario(FuncionariosList *f, CargosList *c_list, int id);
void adiciona_cargo_a_funcionario(CargosList *c_list, FuncionariosList *f_list);

int main() {
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


    do {
        printf("----- MENU -----\n");
        printf("1. Cadastrar funcionario\n");
        printf("2. Excluir funcionario\n");
        printf("3. Listar funcionarios\n");
        printf("4. Buscar funcionario\n");
        printf("5. Editar cadastro de funcionario\n");
        printf("6. Consultar receita da empresa\n");
        printf("7. Consultar quantidade de funcionarios por cargo\n");
        printf("8. Exibe as informacoes da empresa\n");
        printf("9. Sair\n");
        printf("Escolha uma opcao: ");
        //scanf("%d", &opcao);
        
        if (scanf("%d", &opcao) != 1) {
            printf("Digite um valor numérico válido!\n");
            fflush(stdin); // Limpa o buffer de entrada
            opcao = 0;
            continue; // Volta para o início do laço do-while
        } else {
            switch (opcao) {
                case 1:
                    f = pedir_informacoes_funcionario(f, c, ultimo_id_cadastrado);
                    f->qtd_funcionarios = ++(empresa->num_funcionarios);
                    f->ultimo_id_cadastrado = ++ultimo_id_cadastrado;
                    printf("Funcionário cadastrado com sucesso!\n");
                    printf("Funcionário de ID: %d", ultimo_id_cadastrado);
                    printf("Quantidade de funcionários atualizado para %d\n", empresa->num_funcionarios);
                    break;
                case 2:
                    //excluir_funcionario(funcionarios, &num_funcionarios);
                    break;
                case 3:
                    lst_ordena(f);
                    lst_imprime(f);
                    break;
                case 4:
                    printf("Digite o ID do funcionário que deseja buscar: ");
                    scanf("%d",  &id_busca_funcionario);
                    
                    FuncionariosList* funcionario_buscado;
                    funcionario_buscado = lst_busca(f, id_busca_funcionario);

                    if (funcionario_buscado != NULL){
                        lst_imprime_um_funcionario(funcionario_buscado);
                    } else {
                        printf("Funcionário com o id %d não encontrado.\n", id_busca_funcionario);
                    }
                    break;
                case 5:
                    //editar_cadastro_funcionario(funcionarios, num_funcionarios);
                    break;
                case 6:
                    printf("Receita da empresa: R$ %.2f\n", empresa->receita);
                    break;
                case 7:
                    consulta_funcionarios_por_cargo(c);
                    break;
                case 8:
                    empresa_imprime(empresa);
                    break;
                case 9:
                    lst_libera(f);
                    cargo_libera(c);
                    free(empresa);
                    printf("Obrigado por escolher nossos serviços!\n");
                    printf("Encerrando o programa...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
        }
    } while (opcao != 9);

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