#include <stdio.h>
#include <stdbool.h>
#include "compra.h"
#include "cliente.h"

void cadastrar_compra(void){

	FILE * arq_cliente;
	FILE * arq_compra;
	compra cm; //Estrutura compra
	cliente cl; //Estrutura cliente
	

	int codigo_cliente;

	if((arq_compra = fopen(ARQ_COMPRA, "ab")) == NULL){ //Teste de Abertura de Arquivo
		fprintf(stderr, "\n Erro não foi possivel abrir o arquivo %s\n.",ARQ_COMPRA);
		return;
	}

	if ((arq_cliente = fopen(ARQ_CLIENTE, "r+b")) == NULL) {
		printf("\nErro: não existe nenhum cliente cadastrado!\n");
		return;
	}


	fseek(arq_compra, 0, SEEK_END); //Determinar N da compra
    cm.numero_compra = ftell(arq_compra) / sizeof(compra) + 1;


	printf("\n\n\t CADASTRAR COMPRA \n");
	printf("\n Codigo da Compra: %d \n\n", cm.numero_compra);
	printf("> ID do Cliente: ");

	
	scanf("%d", &codigo_cliente);


	fseek(arq_cliente, (codigo_cliente - 1) * sizeof(cliente), SEEK_SET);
	fread(&cl, sizeof(cliente), 1, arq_cliente);

	if (codigo_cliente <= 0 || feof(arq_cliente)) { //Teste se o cliente existe
		printf("\nErro: nao existe nenhum cliente com esse codigo (%d)!\n", codigo_cliente);
		return;
	}
	else
	{

	cm.codigo_cliente = codigo_cliente;;
	printf("> Valor da compra: ");
	scanf(" %f", &cm.valor);
	printf("> Dia: ");
	scanf(" %d", &cm.dt_compra.dia);
	printf("> Mes: ");
	scanf(" %d", &cm.dt_compra.mes);
	printf("> Ano: ");
	scanf(" %d", &cm.dt_compra.ano);

	
	fwrite(&cm, sizeof(compra), 1,arq_compra);

	}

	
	fclose(arq_compra);

	fclose(arq_cliente);

}

void listar_compras_data(void){

	FILE * arq;
	FILE * arq_cl;
	compra c;
	cliente cl;

	data data_consulta;
	int cont = 0; //Contador de controle para as compras
	float total = 0;
	printf("\n\n\tCONSULTAR COMPRA POR DATA\n");

	if((arq = fopen(ARQ_COMPRA, "rb")) == NULL){
		fprintf(stderr, "\n Erro nao foi possivel abrir o arquivo %s ou nenhuma compra foi cadastrada ainda.\n",ARQ_COMPRA);
		return;
		 }

	printf("\n DATA da COMPRA \n\n");
	printf("> DIA: ");
	scanf(" %d", &data_consulta.dia);
	printf("> MES: ");
	scanf(" %d", &data_consulta.mes);
	printf("> ANO: ");
	scanf(" %d", &data_consulta.ano);

	if ((arq_cl = fopen(ARQ_CLIENTE, "r+b")) == NULL) {
		printf("\nErro: nao existe nenhum cliente cadastrado!\n");
		return;
	}


	

	

			printf("\n\t\tCompras na DATA: %d / %d / %d \n", data_consulta.dia, data_consulta.mes, data_consulta.ano);
			printf("----------------------------------------------------------------------------\n");
			printf(" #Numero da Compra      # | Nome                             Valor da Compra \n");
			printf("----------------------------------------------------------------------------\n");


	while (fread(&c, sizeof(compra), 1, arq) > 0) {

		

		if(data_consulta.dia == c.dt_compra.dia && data_consulta.mes == c.dt_compra.mes && data_consulta.ano == c.dt_compra.ano){

			fseek(arq_cl, (c.codigo_cliente - 1) * sizeof(cliente), SEEK_SET);
			fread(&cl, sizeof(cliente), 1, arq_cl);
			
			printf("%06d               #%d | %s \t\t\tR$ %0.2f \n",c.numero_compra, c.codigo_cliente, cl.nome_cliente, c.valor);
			total += c.valor;
			cont ++;
		}
		
	}

	if(cont == 0)
		printf("\tNehuma compra foi efetuada nesta DATA\n");
	else{
		printf("------------------------------------------------------------------------------\n");
		
		printf("                                         > TOTAL : R$ %.2f ",total);
	}
	fclose(arq_cl);
	fclose(arq);


}


bool datas_iguais(data d1, data d2){

	if(d1.dia == d2.dia && d1.mes && d2.mes && d1.ano == d2.ano)
		return 1;
	return 0;

}



void listar_compras_cliente(void){

	FILE * arq;
	FILE * arq_cl;
	compra c;
	cliente cl;
	int id_consulta;
	int cont = 0;

	printf("\n\n\tCONSULTAR COMPRA POR CODIGO DE CLIENTE\n");

	if((arq = fopen(ARQ_COMPRA, "rb")) == NULL){
		fprintf(stderr, "\n Erro não foi possivel abrir o arquivo %s ou nenhuma compra foi cadastrada ainda.\n",ARQ_COMPRA);
		return;
		}

	printf(" > ID do cliente: ");
	scanf("%d", &id_consulta);


	if ((arq_cl = fopen(ARQ_CLIENTE, "r+b")) == NULL) {
		printf("\nErro: não existe nenhum cliente cadastrado!\n");
		return;
	}

	


	printf("\n\t\tCompras Efetuadas pelo Cliente #%d\n", id_consulta);
	printf("-------------------------------------------------------------------\n");
	printf("#Numero da Compra      # | Nome         Valor da Compra \n");
	printf("--------------------------------------------------------------------\n");


	while (fread(&c, sizeof(compra), 1, arq) > 0) {

		if(id_consulta == c.codigo_cliente){

			fseek(arq_cl, (c.codigo_cliente - 1) * sizeof(cliente), SEEK_SET);
			fread(&cl, sizeof(cliente), 1, arq_cl);



			printf("%06d               # %d | %-30.30sR$ %0.2f \n",c.numero_compra, c.codigo_cliente,cl.nome_cliente, c.valor);
			
			cont ++;
		}
		
	}

	if(cont == 0)
		printf("Nehuma compra foi efetuada por este CLIENTE\n");


	fclose(arq);
	fclose(arq_cl);
}