#include <stdio.h>
#include <stdlib.h>
//#include "TAD_funcionario/funcionario.c"
#include "TAD_empresa/empresa.c"

int main() {
    int opcao;
    do {
        printf("\n----- MENU -----\n");
        printf("1. Cadastrar funcionario\n");
        printf("2. Excluir funcionario\n");
        printf("3. Listar funcionarios\n");
        printf("4. Buscar funcionario\n");
        printf("5. Editar cadastro de funcionario\n");
        printf("6. Consultar receita da empresa\n");
        printf("7. Consultar quantidade de funcionarios por cargo\n");
        printf("8. Sair\n");
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
                    //listar_funcionarios(funcionarios, num_funcionarios);
                    break;
                case 4:
                    //buscar_funcionario(funcionarios, num_funcionarios);
                    break;
                case 5:
                    //editar_cadastro_funcionario(funcionarios, num_funcionarios);
                    break;
                case 6:
                    //consultar_receita_empresa(empresa);
                    break;
                case 7:
                    //consultar_quantidade_funcionarios_por_cargo(funcionarios, num_funcionarios);
                    break;
                case 8:
                    printf("Encerrando o programa...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
        }
    } while (opcao != 8);

    return 0;
}