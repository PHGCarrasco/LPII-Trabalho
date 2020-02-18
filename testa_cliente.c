#include <stdio.h>
#include "cliente.h"


void cadastrar_cliente(void){

	FILE * arq;
	cliente c;
	
	printf("\n\nCadastrar Cliente\n\n");
	printf(" > Nome: ");
	scanf(" %50[^\n]",c.nome_cliente);
	printf(" > Telefone: ");
	scanf(" %14[^\n]",c.telefone);



	if((arq = fopen(ARQ_CLIENTE, "ab")) == NULL){ //Teste de Abertura de Arquivo
		fprintf(stderr, "\n Erro não foi possivel abrir o arquivo %s",ARQ_CLIENTE);
		return;
	}


	fseek(arq, 0, SEEK_END);
    c.codigo_cliente = ftell(arq) / sizeof(cliente) + 1;


	printf("\n\nNovo Cliente Cadastrado\n");
	printf("\n");
	printf(" > Codigo do Cliente: %d\n", c.codigo_cliente);
	printf("\n");
	printf(" > Nome do Cliente: %s\n",c.nome_cliente);
	printf("\n");
	printf(" > Telefone do Cliente: %s\n",c.telefone);

				
	fwrite(&c, sizeof(cliente), 1,arq);


	fclose(arq);

	return;
}


void listar_clientes(){

	FILE * arq;
	cliente c;

	if((arq = fopen(ARQ_CLIENTE, "rb")) == NULL){
		fprintf(stderr, "\n Erro nao foi possivel abrir o arquivo %s ou nenhum cliente foi cadastrado\n",ARQ_CLIENTE);
		return;
	}

	printf("\n\n\t\tClientes Cadastrados\n");
	printf("--------------------------------------------------------\n");
	printf("#Codigo      Nome do Cliente         Telefone\n");
	printf("--------------------------------------------------------\n");

	while (fread(&c, sizeof(cliente), 1, arq) > 0) {
		printf("%06d   %-30.30s %-30.30s \n", c.codigo_cliente, c.nome_cliente, c.telefone);
	}
	printf("--------------------------------------------------------\n");
	fclose(arq);
}

/*
void consultar_cliente(){

	FILE * arq;
	cliente c;
	char nome[41];

	

	if((arq = fopen(ARQ_CLIENTE, "rb")) == NULL){
		fprintf(stderr, "\n Erro não foi possivel abrir o arquivo %s\n",ARQ_CLIENTE);
		return;
	}

	while (fread(&c, sizeof(cliente), 1, arq) > 0){
		qnt ++; //Quantidade de Clientes ja cadastrados
	}

	cliente vet[qnt];

	for(i = 0; i < qnt; i++){
		scanf(vet[i], sizeof(cliente), 1,arq);
	}

	printf("Cliente a ser consultado: ");
	("%40[^/n]",nome);


	//while(!(nome != ver. ))




	//while(feof()

	fclose(arq);


}*/


int main(){
int operador;

	do {
		printf("\n\nCONTROLE DE VENDAS\n");
		printf("<1> Cadastrar um cliente\n");
		printf("<2> Listar os clientes cadastrados\n");
		printf("<3> Consulta por cliente\n");
		printf("<4> Cadastar compras\n");
		printf("<5> Listar compras realizadas em um data\n");
		printf("<6> Listar compras realizadas por cliente\n");
		printf("<0> Sair do programa\n");
		printf("Opcao => ");
		scanf("%d", &operador);

			switch (operador) {
				case 1: cadastrar_cliente();
					break;
				case 2: listar_clientes();
					break;
				//case 3: consultar_cliente();
					//break;
				case 0: break;

				default: printf("\nErro: opção invalida!\n");
			}

	} while (operador != 0);

	return 0;

}


