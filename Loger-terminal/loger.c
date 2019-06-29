//Menu do programa//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

typedef struct data DATA;

struct data{
    int dia;
    int mes;
    int ano;
};

typedef struct item ITEM;

struct item{
    char codigo[10];
    char descricao[30];
    int quant_unitaria;
    DATA vencimento;
    float preco_compra;
    float preco_venda;
};

typedef struct item_hist ITEM_HIST;

struct item_hist{
	char codigo[10];
    char descricao[30];
	int quantidade;
	DATA data_venda;
};





void remover_caixa(float *valor_compra, DATA *hoje);
void verifica_caixa(void);
void remover_item(void);
void cabecalho(void);
void exibir_estoque(void);
void consultar_item(void);
void verifica_validade(void);
void inventario_inicial(void);
void grava_historico(ITEM ctt, DATA *hoje, int quant);
void checa_historico(void);
void incluir_item(void);


int main(){
	DATA *hoje;
	float *valor_compra;
    setlocale(LC_ALL, "Portuguese");
    int op;
    //Exibe o menu//
    do{
        cabecalho();
        printf("Bem-vindx ao loger!\n");
        printf("O que deseja fazer?\n");
        printf("1 - Realizar inventário inicial\n");
        printf("2 - Exibir estoque\n");
        printf("3 - Consultar item\n");
        printf("4 - Verificar a validade de itens no estoque\n");
        printf("5 - Remover item do estoque\n");
        printf("6 - Incluir item no estoque\n");
        printf("7 - Histórico\n");
		printf("8 - Dar baixa no caixa\n");
		printf("9 - Verificar valor do caixa\n");
        printf("10 - Sair do sistema\n\n");
        printf("Escolha a sua opção: ");
        scanf("%d", &op); //lê a opção selecionada pelo usuário//

        switch(op){
            case 1:
                inventario_inicial();
            break;

            case 2:
                exibir_estoque();
            break;

            case 3:
                consultar_item();
            break;

            case 4:
                verifica_validade();
            break;

            case 5:
				remover_item();

            break;

            case 6:
                incluir_item();
            break;

            case 7:
				checa_historico();
            break;

            case 8:

				hoje = malloc(sizeof(DATA));
				hoje->dia = -1;
				valor_compra = malloc(sizeof(float));
				*valor_compra = 0.0;
				remover_caixa(valor_compra, hoje);
				free(valor_compra);
				free(hoje);
            break;

            case 9:
				verifica_caixa();
            break;

            case 10:
                printf("\n\n\nObrigadx por usar o loger, até a próxima!\n");
                getch();
            break;

            default:
                printf("\n\n\nOpção inválida, tente novamente.\n");
                getch();
            break;

    }
    }while (op!=10);
}



void checa_historico(void){
	fflush(stdin);
	cabecalho();
	int escolha;
	char codigo[10];

	printf("Deseja consultar o histórico:\n");
	printf("1 - Histórico completo\n");
	printf("2 - Histórico de um produto\n");
	printf("Sua opção: ");
	scanf("%d", &escolha);

	fflush(stdin);
	cabecalho();


	FILE *hist = fopen("historico.txt", "r");
	ITEM_HIST ctt_hist;

	switch(escolha){

		case 1:
			while(fread(&ctt_hist, sizeof(ITEM_HIST), 1, hist)==1){
				printf("--------------------------------------------------------------\n");
				printf("DATA [%d/%d/%d]\n  cod: %s|nome: %s|quantidade: %d\n",ctt_hist.data_venda.dia, ctt_hist.data_venda.mes, ctt_hist.data_venda.ano, ctt_hist.codigo, ctt_hist.descricao, ctt_hist.quantidade);
				printf("--------------------------------------------------------------\n");
			}
			break;
		case 2:
			printf("Insira o código do produto: ");
			fflush(stdin);
			gets(codigo);

			while(fread(&ctt_hist, sizeof(ITEM_HIST), 1, hist)==1){
				if(strcmp(codigo, ctt_hist.codigo) == 0){
					printf("--------------------------------------------------------------\n");
					printf("DATA [%d/%d/%d]\n  cod: %s|nome: %s|quantidade: %d\n",ctt_hist.data_venda.dia, ctt_hist.data_venda.mes, ctt_hist.data_venda.ano, ctt_hist.codigo, ctt_hist.descricao, ctt_hist.quantidade);
					printf("--------------------------------------------------------------\n");
				}
			}

			break;
	}
	fclose(hist);
	getch();
}






void grava_historico(ITEM ctt, DATA *hoje, int quant){
	FILE *hist = fopen("historico.txt", "a");
	ITEM_HIST ctt_hist;

	strcpy(ctt_hist.codigo, ctt.codigo);
	strcpy(ctt_hist.descricao, ctt.descricao);
	ctt_hist.quantidade = quant;
	ctt_hist.data_venda.dia = hoje->dia;
	ctt_hist.data_venda.mes = hoje->mes;
	ctt_hist.data_venda.ano = hoje->ano;

	fwrite(&ctt_hist, sizeof(ITEM_HIST), 1, hist);

	fclose(hist);
	getch();
}




void remover_caixa(float *valor_compra, DATA *hoje){
	char codigo[10],c;
	int quant;

	fflush(stdin);
	cabecalho();
	if(hoje->dia == -1 ){
		printf("Insira a data de hoje (DD MM AAAA): ");
		scanf("%d %d %d", &hoje->dia, &hoje->mes, &hoje->ano);
		fflush(stdin);
	}
	printf("Qual produto está sendo retirado?\n");
	printf("Insira o código do produto: ");
	gets(codigo);
	printf("Insira a quantidade desejada: ");
	scanf("%d", &quant);

    FILE* arquivo;
	FILE* arquivo2;
    ITEM ctt,ctt2;
	int flag = 0;


    arquivo = fopen("estoque.txt", "r");


    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo"); //verifica se o arquivo foi aberto//
    }

    else{

        while(fread(&ctt, sizeof(ITEM),1, arquivo)==1){
            if(strcmp(codigo, ctt.codigo)==0 ){
                printf("--------------------------------------------------------------\n");
				flag = 1;
                printf("\nCódigo: %s\n", ctt.codigo);
                printf("Descrição: %s\n", ctt.descricao);
                printf("Quantidade unitária em estoque: %d\n", ctt.quant_unitaria);
				printf("Preço de venda: %.2f\n", ctt.preco_venda);
                printf("--------------------------------------------------------------\n\n");
                break;
            }



		}
		if(quant > ctt.quant_unitaria || flag == 0){
			printf("Opção inválida, produtos insuficientes.\n");
			getch();
			return ;
		}

		fclose(arquivo);

		if((flag == 1) && (quant <= ctt.quant_unitaria)){
			grava_historico(ctt, hoje, quant);

			FILE *caixa = fopen("caixa.txt", "r");
			FILE *caixa_temp = fopen("caixa_temp.txt", "w");
			if(caixa == NULL){
				printf("Problemas na abertura do arquivo de caixa\n");
				getch();
				return ;
			}
			float valor;
			fscanf(caixa, "%f", &valor);
			printf("VALOR [%.2f]\n", valor);
			valor = valor + (quant * ctt.preco_venda);
			printf("NOVO VALOR [%.2f]\n", valor);
			*valor_compra = *valor_compra + (quant * ctt.preco_venda);
			fprintf(caixa_temp, "%f", valor);
			fclose(caixa);
			fclose(caixa_temp);
			remove("caixa.txt");
			rename( "caixa_temp.txt" , "caixa.txt");

			FILE *extrato = fopen("extrato.txt", "a");
			fprintf(extrato, "%s %s %d %.2f\n", ctt.codigo, ctt.descricao, quant, (quant*ctt.preco_venda));
			fclose(extrato);


			//valor = valor + (quant * ctt.preco_venda);
			arquivo2 = fopen("temporario.txt", "w");
			arquivo = fopen("estoque.txt", "r");

			ctt.quant_unitaria =  ctt.quant_unitaria - quant;

			while(fread(&ctt2, sizeof(ITEM),1, arquivo) == 1){

				if(strcmp(codigo, ctt2.codigo)==0){
					fwrite(&ctt, sizeof(ITEM), 1, arquivo2);
					continue;
				}
				fwrite(&ctt2, sizeof(ITEM), 1, arquivo2);
			}

			fclose(arquivo);
			fclose(arquivo2);
			remove("estoque.txt");
			rename( "temporario.txt" , "estoque.txt");
		}
		printf("\n\nPassar mais algum produto nesta compra (s/n)?: ");
		if(getch()=='s'){
			return remover_caixa(valor_compra, hoje);
		}
		else{
			FILE *extrato = fopen("extrato.txt", "a");
			fprintf(extrato, "TOTAL R$ %.2f", *valor_compra);
			fclose(extrato);

		}
		getch();
	}

}





void verifica_caixa(void){
	fflush(stdin);
	cabecalho();

	FILE *caixa = fopen("caixa.txt", "r");
	if(caixa == NULL){
		printf("Problemas na abertura do arquivo");
		return ;
	}
	float valor;

	//fread(&valor, sizeof(float), 1, caixa);
	fscanf(caixa, "%f", &valor);

    printf("--------------------------------------------------------------\n");
    printf("|       R$  %.2f                         |\n", valor);
    printf("--------------------------------------------------------------\n\n");

	fclose(caixa);
	getch();
}




void remover_item(void){
    FILE* arquivo;
	FILE* arquivo2;
    ITEM ctt,ctt2;
    char descricao[30];
    char codigo[10];
	int flag = 0;
	int quant;

    arquivo = fopen("estoque.txt", "r");


    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo"); //verifica se o arquivo foi aberto//
    }

    else{
        int op;
        fflush(stdin);
        cabecalho();
        printf("Deseja consultar por:");
        printf("\n1 - Nome\n2 - Código\n");
        printf("Sua opção: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                fflush(stdin);
                cabecalho();
                printf("Digite o nome do produto que deseja consultar: ");
                strupr(gets(descricao));

                while(fread(&ctt, sizeof(ITEM),1, arquivo)==1){

                    if(strcmp(descricao, ctt.descricao)==0){
						flag = 1;
                        printf("--------------------------------------------------------------\n");
                        printf("\nCódigo: %s\n", ctt.codigo);
                        printf("Descrição: %s\n", ctt.descricao);
                        printf("Quantidade unitária em estoque: %d\n", ctt.quant_unitaria);
						break;
                        printf("--------------------------------------------------------------\n\n");
                    }
                }
            break;

            case 2:
                fflush(stdin);
                cabecalho();
                printf("Digite o código do produto que deseja consultar: ");
                gets(codigo);

                while(fread(&ctt, sizeof(ITEM),1, arquivo)==1){
                    if(strcmp(codigo, ctt.codigo)==0){
                        printf("--------------------------------------------------------------\n");
						flag = 1;
                        printf("\nCódigo: %s\n", ctt.codigo);
                        printf("Descrição: %s\n", ctt.descricao);
                        printf("Quantidade unitária em estoque: %d\n", ctt.quant_unitaria);
						break;
                        printf("--------------------------------------------------------------\n\n");
                    }
            }
            break;
            default:
                printf("Opção inválida, tente novamente.");
                getch();
            break;
        }

		fclose(arquivo);

		if(flag == 1){
			arquivo2 = fopen("temporario.txt", "w");
			arquivo = fopen("estoque.txt", "r");

			printf("Produto encontrado - Qual a quantidade a ser removida? ");
			scanf("%d", &quant);
			if(quant > ctt.quant_unitaria){
				quant = ctt.quant_unitaria;
			}
			ctt.quant_unitaria =  ctt.quant_unitaria - quant;

			while(fread(&ctt2, sizeof(ITEM),1, arquivo)==1){

				if(op == 1){

					if(strcmp(descricao, ctt2.descricao)==0){
						fwrite(&ctt, sizeof(ITEM), 1, arquivo2);
						continue;
					}
				}
				if(op == 2){

					if(strcmp(codigo, ctt2.codigo)==0){
						fwrite(&ctt, sizeof(ITEM), 1, arquivo2);
						continue;
					}
				}
				fwrite(&ctt2, sizeof(ITEM), 1, arquivo2);
			}

			fclose(arquivo);
			fclose(arquivo2);
			remove("estoque.txt");
			rename( "temporario.txt" , "estoque.txt");
		}

		getch();
	}

}


void cabecalho(void){
    system("cls");
    fflush(stdin);
    printf("--------------------------------------------------------------\n");
    printf("|                             loger                           |\n");
    printf("--------------------------------------------------------------\n\n");
}


void inventario_inicial(void){
    FILE* arquivo;

    ITEM ctt;

    arquivo = fopen("estoque.txt", "a");

    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo"); //verifica se o arquivo foi aberto//
    }

    else{
        do{
            cabecalho();
            printf("Vamos fazer o inventário inicial de seu estoque!\n\n");

            fflush(stdin);
            printf("Informe o código do produto: ");
            gets(ctt.codigo);

            fflush(stdin);
            printf("Informe a descrição do produto: ");
            strupr(gets(ctt.descricao));

            fflush(stdin);
            printf("Informe a quantidade, em unidades, do produto: ");
            scanf("%d", &ctt.quant_unitaria);

            printf("Informe a data de vencimento do produto (DD MM AAAA): ");
            scanf("%d %d %d", &ctt.vencimento.dia, &ctt.vencimento.mes, &ctt.vencimento.ano);

            printf("Informe o preço de compra do produto: ");
            scanf("%f", &ctt.preco_compra);

            fflush(stdin);
            printf("Informe o preço de venda do produto: ");
            scanf("%f", &ctt.preco_venda);

            fwrite(&ctt, sizeof(ITEM), 1, arquivo);

            printf("\nDeseja continuar (s/n)?: ");

        }while(getch()=='s');
        fclose(arquivo);
    }

}

void exibir_estoque(void){
    FILE* arquivo;

    ITEM ctt;

    arquivo = fopen("estoque.txt", "r");
    cabecalho();

    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo"); //verifica se o arquivo foi aberto//
    }

    else{
            printf("Esses são os itens que constam no seu estoque: \n\n");
            printf("--------------------------------------------------------------\n\n");
            while(fread(&ctt, sizeof(ITEM), 1, arquivo)==1){
                printf("Código: %s\n", ctt.codigo);
                printf("Descrição: %s\n", ctt.descricao);
                printf("Quantidade unitária em estoque: %d\n", ctt.quant_unitaria);
                printf("Data de valiade: %d/%d/%d\n", ctt.vencimento.dia, ctt.vencimento.mes, ctt.vencimento.ano);
                printf("Preço de compra: %.2f\n", ctt.preco_compra);
                printf("Preço de venda: %.2f\n\n", ctt.preco_venda);
                printf("--------------------------------------------------------------\n\n");
            }
        }
        fclose(arquivo);
        getch();
}

void consultar_item(void){
    FILE* arquivo;
    ITEM ctt;
    char descricao[30];
    char codigo[10];

    arquivo = fopen("estoque.txt", "r");

    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo"); //verifica se o arquivo foi aberto//
    }

    else{
        int op;
        fflush(stdin);
        cabecalho();
        printf("Deseja consultar por:");
        printf("\n1 - Nome\n2 - Código\n");
        printf("Sua opção: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                fflush(stdin);
                cabecalho();
                printf("Digite o nome do produto que deseja consultar: ");
                strupr(gets(descricao));

                while(fread(&ctt, sizeof(ITEM),1, arquivo)==1){
                    if(strcmp(descricao, ctt.descricao)==0){
                        printf("--------------------------------------------------------------\n");
                        printf("\nCódigo: %s\n", ctt.codigo);
                        printf("Descrição: %s\n", ctt.descricao);
                        printf("Quantidade unitária em estoque: %d\n", ctt.quant_unitaria);
                        printf("Data de valiade: %d/%d/%d\n", ctt.vencimento.dia, ctt.vencimento.mes, ctt.vencimento.ano);
                        printf("Preço de compra: %.2f\n", ctt.preco_compra);
                        printf("Preço de venda: %.2f\n\n", ctt.preco_venda);
                        printf("--------------------------------------------------------------\n\n");
                    }
                }
            break;

            case 2:
                fflush(stdin);
                cabecalho();
                printf("Digite o código do produto que deseja consultar: ");
                gets(codigo);

                while(fread(&ctt, sizeof(ITEM),1, arquivo)==1){
                    if(strcmp(codigo, ctt.codigo)==0){
                        printf("--------------------------------------------------------------\n");
                        printf("\nCódigo: %s\n", ctt.codigo);
                        printf("Descrição: %s\n", ctt.descricao);
                        printf("Quantidade unitária em estoque: %d\n", ctt.quant_unitaria);
                        printf("Data de valiade: %d/%d/%d\n", ctt.vencimento.dia, ctt.vencimento.mes, ctt.vencimento.ano);
                        printf("Preço de compra: %.2f\n", ctt.preco_compra);
                        printf("Preço de venda: %.2f\n\n", ctt.preco_venda);
                        printf("--------------------------------------------------------------\n\n");
                    }
            }
            break;
            default:
                printf("Opção inválida, tente novamente.");
                getch();
            break;
        }
    }
    fclose(arquivo);
    getch();
}

void verifica_validade(void){
    FILE* arquivo;
    ITEM ctt;

    cabecalho();
    arquivo = fopen("estoque.txt", "r");
    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo!\n");
    }
    else{
        int mes;
        fflush(stdin);
        printf("Digite o mês: ");
        scanf("%d", &mes);
        printf("Produtos vencendo no mês: \n");
        while(fread(&ctt, sizeof(ITEM),1, arquivo)==1){
                if(mes == ctt.vencimento.mes){
                    printf("--------------------------------------------------------------\n");
                    printf("\nCódigo: %s\n", ctt.codigo);
                    printf("Descrição: %s\n", ctt.descricao);
                    printf("Quantidade unitária em estoque: %d\n", ctt.quant_unitaria);
                    printf("Data de valiade: %d/%d/%d\n", ctt.vencimento.dia, ctt.vencimento.mes, ctt.vencimento.ano);
                    printf("Preço de compra: %.2f\n", ctt.preco_compra);
                    printf("Preço de venda: %.2f\n\n", ctt.preco_venda);
                    printf("--------------------------------------------------------------\n\n");
                    }
        }
    }
    fclose(arquivo);
    getch();
}

void incluir_item(void){
    FILE* arquivo;

    ITEM ctt;

    arquivo = fopen("estoque.txt", "a");

    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo"); //verifica se o arquivo foi aberto//
    }

    else{
        do{
            cabecalho();
            printf("Informe os seguintes dados referentes ao produto que deseja incluir no estoque:\n\n");

            fflush(stdin);
            printf("Código do produto: ");
            gets(ctt.codigo);

            fflush(stdin);
            printf("Descrição do produto: ");
            strupr(gets(ctt.descricao));

            fflush(stdin);
            printf("Quantidade unitária do produto: ");
            scanf("%d", &ctt.quant_unitaria);

            printf("Data de vencimento do produto (DD MM AAA): ");
            scanf("%d %d %d", &ctt.vencimento.dia, &ctt.vencimento.mes, &ctt.vencimento.ano);

            printf("Preço de compra do produto: ");
            scanf("%f", &ctt.preco_compra);

            fflush(stdin);
            printf("Preço de venda do produto: ");
            scanf("%f", &ctt.preco_venda);

            fwrite(&ctt, sizeof(ITEM), 1, arquivo);

            printf("\nDeseja incluir mais algum item (s/n)?: ");

        }while(getch()=='s');
        fclose(arquivo);
    }

}
