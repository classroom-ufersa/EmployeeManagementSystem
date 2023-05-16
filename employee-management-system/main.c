#include "TAD_empresa/empresa.c"

int main() {
    int opcao, id_funcionario, id_cargo;
    char char_invalido;
    Empresa* empresa = empresa_start();
    FuncionariosList* f_list = empresa->f_list;
    CargosList* c_list = empresa->c_list;

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
                    f_list = solicita_informacoes_funcionario(f_list, c_list, empresa->ultimo_id_funcionario, &empresa->num_funcionarios);
                    f_list->ultimo_id_cadastrado = ++(empresa->ultimo_id_funcionario);
                    printf("Funcionário cadastrado com sucesso!\n");
                    printf("Funcionário de ID: %d\n", empresa->ultimo_id_funcionario);
                    printf("Quantidade de funcionários atualizado para %d\n\n", empresa->num_funcionarios);
                    break;
                case 2: // exclui funcionário
                    printf("Digite o ID do funcionário que deseja excluir do sistema: ");
                    scanf("%d", &id_funcionario);
                    f_list = lst_retira(f_list, id_funcionario, &empresa->num_funcionarios);
                    f_list->qtd_funcionarios = empresa->num_funcionarios;
                    break;
                case 3: // imprime funcionários
                    lst_ordena(f_list);
                    lst_imprime(f_list);
                    break;
                case 4: // busca funcionário
                    printf("Digite o ID do funcionário que deseja buscar: ");
                    scanf("%d",  &id_funcionario);
                    
                    FuncionariosList* funcionario_buscado;
                    funcionario_buscado = lst_busca(f_list, id_funcionario);

                    if (funcionario_buscado != NULL){
                        lst_imprime_um_funcionario(funcionario_buscado);
                    } else {
                        printf("Funcionário com o id %d não encontrado.\n", id_funcionario);
                    }
                    break;
                case 5: // edita funcionário
                    printf("Digite o ID do funcionário que deseja buscar: ");
                    scanf("%d",  &id_funcionario);
                    f_list = lst_edita(f_list, c_list, id_funcionario); 
                    break;
                case 6: // exibe receita da empresa
                    printf("Receita da empresa: R$ %.2f\n", empresa->receita);
                    break;
                case 7: // cadastra cargo
                    c_list = solicita_informacoes_cargo(c_list, empresa->ultimo_id_cargo, &empresa->num_cargos);
                    c_list->ultimo_id_cargo_adicionado = ++(empresa->ultimo_id_cargo);
                    printf("Cargo cadastrado com sucesso!\n");
                    printf("Cargo de ID: %d\n", empresa->ultimo_id_cargo);
                    printf("Quantidade de cargos atualizado para %d\n\n", empresa->num_cargos);
                    break;
                case 8: // exclui cargo
                    printf("Digite o ID do cargo que deseja excluir do sistema: ");
                    scanf("%d", &id_cargo);
                    c_list = cargo_retira(c_list, id_cargo, &empresa->num_cargos);
                    c_list->qtd_cargos = empresa->num_cargos;
                    adiciona_cargo_a_funcionario(c_list, f_list);
                    break;
                case 9: // lista cargos
                    cargo_imprime(c_list);
                    break;
                case 10: // consulta a quantidade de funcionários por cago
                    consulta_funcionarios_por_cargo(c_list);
                    break;
                case 11: // exibe as informações da empresa
                    empresa_imprime(empresa);
                    break;
                case 12: // sai do programa
                    lst_libera(f_list);
                    cargo_libera(c_list);
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
