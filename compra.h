/*  Cabeçalho compra.h */

#ifndef _COMPRA_H
#define _COMPRA_H
#include <stdbool.h>

/* Nome do arquivo aonde as compras são cadastradas */
#define ARQ_COMPRA "compras.dat"
#define ARQ_CLIENTE "clientes.dat"


/* Estrutura que representa uma data */
typedef struct {

	int dia;
	int mes;
	int ano;

} data;

/* Estrutura que representa uma compra */
typedef struct {

	int numero_compra;
	int codigo_cliente; // código do cliente que realizou a compra
	float valor;
	data dt_compra;

} compra;

/* função que cadastra uma nova compra no arquivo */
void cadastrar_compra(void);

/* função que lista todas as compras feitas em uma data */
void listar_compras_data(void);

/* função que devolve verdadeiro se as duas datas passadas
* como argumentos são iguais, ou falso, caso contrário.
* Usada na função listar_compras_data() */
bool datas_iguais(data, data);

/* função que lista todas as compras feitas por um cliente */
void listar_compras_cliente(void);


#endif