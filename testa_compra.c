#include <stdio.h>
#include "cliente.h"
#include "compra.h"


void cadastrar_compra(){

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


void listar_compras_data(){

	FILE * arq;
	compra c;
	data data_consulta;
	int cont = 0; //Contador de controle para as compras

	printf("\n\n\tCONSULTAR COMPRA POR DATA\n");

	printf("DATA da COMPRA \n\n");
	printf("> DIA: ");
	scanf(" %d", &data_consulta.dia);
	printf("> MES: ");
	scanf(" %d", &data_consulta.mes);
	printf("> ANO: ");
	scanf(" %d", &data_consulta.ano);


	if((arq = fopen(ARQ_COMPRA, "rb")) == NULL){
		fprintf(stderr, "\n Erro não foi possivel abrir o arquivo %s, ou nenhuma compra foi cadastrada ainda.\n",ARQ_COMPRA);
		return;
	}

			printf("\n\t\tCompras na DATA: %d / %d / %d \n", data_consulta.dia, data_consulta.mes, data_consulta.ano);
			printf("-------------------------------------------------------------------\n");
			printf("#Numero da Compra      # / Nome         Valor da Compra \n");
			printf("--------------------------------------------------------------------\n");


	while (fread(&c, sizeof(compra), 1, arq) > 0) {

		

		if(data_consulta.dia == c.dt_compra.dia && data_consulta.mes == c.dt_compra.mes && data_consulta.ano == c.dt_compra.ano){

			
			printf("%06d               %06.d                    R$ %0.2f",c.numero_compra, c.codigo_cliente, c.valor);
			
			cont ++;
		}
		
	}

	if(cont == 0)
		printf("Nehuma compra foi efetuada nesta DATA\n");

	fclose(arq);

}	




void listar_compras_cliente(void){

	FILE * arq;
	compra c;
	int id_consulta;
	int cont = 0;

	printf("\n\n\tCONSULTAR COMPRA POR CODIGO DE CLIENTE\n\n");

	printf(" > ID do cliente: ");
	scanf("%d", &id_consulta);

	if((arq = fopen(ARQ_COMPRA, "rb")) == NULL){
		fprintf(stderr, "\n Erro não foi possivel abrir o arquivo %s, ou nenhuma compra foi cadastrada ainda.\n",ARQ_COMPRA);
		return;
		}


	printf("\n\t\tCompras Efetuadas pelo Cliente #%d\n", id_consulta);
	printf("-------------------------------------------------------------------\n");
	printf("#Numero da Compra      # / Nome         Valor da Compra \n");
	printf("--------------------------------------------------------------------\n");


	while (fread(&c, sizeof(compra), 1, arq) > 0) {

		if(id_consulta == c.codigo_cliente){

			
			printf("%06d               %06.d                    R$ %0.2f \n",c.numero_compra, c.codigo_cliente, c.valor);
			
			cont ++;
		}
		
	}
	if(cont == 0)
		printf("Nehuma compra foi efetuada por este CLIENTE\n");


}





int main(){
int operador;

	do {
		printf("\n\nCONTROLE DE VENDAS\n");
		//printf("<1> Cadastrar um cliente\n");
		//printf("<2> Listar os clientes cadastrados\n");
		//printf("<3> Consulta por cliente\n");
		printf("<4> Cadastar compras\n");
		printf("<5> Listar compras realizadas em um data\n");
		printf("<6> Listar compras realizadas por cliente\n");
		printf("<0> Sair do programa\n");
		printf("Opcao => ");
		scanf("%d", &operador);

			switch (operador) {
				//case 1: cadastrar_cliente();
					//break;
				//case 2: listar_clientes();
				//	break;
				//case 3: consultar_cliente();
					//break;
				case 4: cadastrar_compra();
					break;
				case 5: listar_compras_data();
					break;
				case 6: listar_compras_cliente();
					break;
				case 0: break;
				default: printf("\nErro: opção invalida!\n");
			}

	} while (operador != 0);

	return 0;

}