#include <stdio.h>
#include <stdlib.h>
//#include "TAD_funcionario/funcionario.c"
#include "TAD_empresa/empresa.c"

int main() {
    int opcao;
    Empresa *empresa;
    empresa = empresa_obter();

    empresa->f_list = lst_cria();
    empresa->f_list = obter_funcionarios(empresa->f_list);
    empresa->num_funcionarios = lst_quantidade(empresa->f_list);
    lst_ordena(empresa->f_list);

    do {
        printf("\n----- MENU -----\n");
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
            printf("\n");
            switch (opcao) {
                case 1:
                    //cadastrar_funcionario(funcionarios, &num_funcionarios);
                    break;
                case 2:
                    //excluir_funcionario(funcionarios, &num_funcionarios);
                    break;
                case 3:
                    lst_imprime(empresa->f_list);
                    break;
                case 4:
                    //buscar_funcionario(funcionarios, num_funcionarios);
                    break;
                case 5:
                    //editar_cadastro_funcionario(funcionarios, num_funcionarios);
                    break;
                case 6:
                    printf("Receita da empresa: R$ %.2f\n", empresa->receita);
                    break;
                case 7:
                    //consultar_quantidade_funcionarios_por_cargo(funcionarios, num_funcionarios);
                    break;
                case 8:
                    empresa_imprime(empresa);
                    break;
                case 9:
                    lst_libera(empresa->f_list);
                    free(empresa);
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