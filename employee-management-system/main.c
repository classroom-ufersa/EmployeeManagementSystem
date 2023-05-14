#include "TAD_empresa/empresa.c"

FuncionariosList *solicita_informacoes_funcionario(FuncionariosList *f, CargosList *c_list, int id, int *qtd_funcionarios);
CargosList *solicita_informacoes_cargo(CargosList *c_list, int id, int *qtd_cargos);
void adiciona_cargo_a_funcionario(CargosList *c_list, FuncionariosList *f_list);

int main() {
    int opcao, ultimo_id_funcionario, ultimo_id_cargo, id_funcionario, id_cargo;
    char char_invalido;

    // cria a empresa
    Empresa *empresa;
    empresa = empresa_obter();

    // pegando as informacoes dos funcionarios a partir do banco de dados
    empresa->f_list = lst_cria();
    FuncionariosList *f = empresa->f_list; 
    f = obter_funcionarios(f);
    
    // verifica se a lista está vazia e inicializa as variaveis 'ultimo_id_funcionario' e "empresa->num_funcionarios"
    if(lst_vazia(f)) {
        ultimo_id_funcionario = 0;
        empresa->num_funcionarios = 0;
    } else {
        empresa->num_funcionarios = f->qtd_funcionarios;
        ultimo_id_funcionario = f->ultimo_id_cadastrado;
    }

    // pegando as informacoes dos cargos a partir do banco de dados
    empresa->c_list = cargo_cria();
    CargosList *c = empresa->c_list; 
    c = obter_cargos(c);

    // verifica se a lista está vazia e inicializa as variaveis 'ultimo_id_funcionario' e "empresa->num_funcionarios"
    if(cargo_lst_vazia(c)) {
        ultimo_id_cargo = 0;
        empresa->num_cargos = 0;
    } else {
        empresa->num_cargos = c->qtd_cargos;
        ultimo_id_cargo = c->ultimo_id_cargo_adicionado;
    }

    // OBS.: adicionar função que percorre o arquivo de cargos e adiciona os ponteiros ao funcinario
    adiciona_cargo_a_funcionario(c, f);

    do {
        printf("--------- MENU ---------\n");
        printf("1. Cadastrar funcionario\n");
        printf("2. Excluir funcionario\n");
        printf("3. Listar funcionarios\n");
        printf("4. Buscar funcionario\n");
        printf("5. Editar cadastro de funcionario\n");
        printf("6. Consultar receita da empresa\n");
        printf("7. Cadastrar cargo\n");
        printf("8. Ecluir cargo\n");
        printf("9. Listar cargos\n");
        printf("10. Consultar quantidade de funcionarios por cargo\n");
        printf("11. Exibe as informacoes da empresa\n");
        printf("12. Sair\n");
        printf("Escolha uma opcao: ");
        
        while (scanf("%d%c", &opcao, &char_invalido) != 2 || char_invalido != '\n' || opcao < 1 || opcao > 12) {
            printf("Opcao invalida. Digite novamente: ");

            // Limpa o buffer do teclado
            while (getchar() != '\n');
        }
        switch (opcao) {
                case 1: // cadastra funcionário
                    f = solicita_informacoes_funcionario(f, c, ultimo_id_funcionario, &empresa->num_funcionarios);
                    f->ultimo_id_cadastrado = ++ultimo_id_funcionario;
                    printf("Funcionário cadastrado com sucesso!\n");
                    printf("Funcionário de ID: %d\n", ultimo_id_funcionario);
                    printf("Quantidade de funcionários atualizado para %d\n", empresa->num_funcionarios);
                    break;
                case 2: // exclui funcionário
                    printf("Digite o ID do funcionário que deseja excluir do sistema: ");
                    scanf("%d", &id_funcionario);
                    f = lst_retira(f, id_funcionario, &empresa->num_funcionarios);
                    f->qtd_funcionarios = empresa->num_funcionarios;
                    break;
                case 3: // imprime funcionários
                    lst_ordena(f);
                    lst_imprime(f);
                    break;
                case 4: // busca funcionário
                    printf("Digite o ID do funcionário que deseja buscar: ");
                    scanf("%d",  &id_funcionario);
                    
                    FuncionariosList* funcionario_buscado;
                    funcionario_buscado = lst_busca(f, id_funcionario);

                    if (funcionario_buscado != NULL){
                        lst_imprime_um_funcionario(funcionario_buscado);
                    } else {
                        printf("Funcionário com o id %d não encontrado.\n", id_funcionario);
                    }
                    break;
                case 5: // edita funcionário
                    printf("Digite o ID do funcionário que deseja buscar: ");
                    scanf("%d",  &id_funcionario);
                    f = lst_edita(f, c, id_funcionario); 
                    break;
                case 6: // exibe receita da empresa
                    printf("Receita da empresa: R$ %.2f\n", empresa->receita);
                    break;
                case 7: // cadastra cargo
                    c = solicita_informacoes_cargo(c, ultimo_id_cargo, &empresa->num_cargos);
                    c->ultimo_id_cargo_adicionado = ++ultimo_id_cargo;
                    printf("Cargo cadastrado com sucesso!\n");
                    printf("Cargo de ID: %d\n", ultimo_id_cargo);
                    printf("Quantidade de cargos atualizado para %d\n", empresa->num_cargos);
                    break;
                case 8: // exclui cargo
                    printf("Digite o ID do cargo que deseja excluir do sistema: ");
                    scanf("%d", &id_cargo);
                    c = cargo_retira(c, id_cargo, &empresa->num_cargos);
                    c->qtd_cargos  = empresa->num_cargos;
                    adiciona_cargo_a_funcionario(c, f);
                    break;
                case 9: // lista cargos
                    cargo_imprime(c);
                    break;
                case 10: // consulta a quantidade de funcionários por cago
                    consulta_funcionarios_por_cargo(c);
                    break;
                case 11: // exibe as informações da empresa
                    empresa_imprime(empresa);
                    break;
                case 12: // sai do programa
                    lst_libera(f);
                    cargo_libera(c);
                    free(empresa);
                    printf("\nObrigado por escolher nossos serviços!\n");
                    printf("Encerrando o programa...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
    } while (opcao != 12);

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

            if (cargo != NULL) {
                funcionario->info.cargo =  cargo->info;
            } else {
                funcionario->info.cargo =  NULL;
            }
        }
    }    
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