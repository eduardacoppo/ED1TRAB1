#ifndef PAGINA_H_
#define PAGINA_H_

// LISTA DE PAGINAS
typedef struct listaPaginas ListaPaginas;

/* CELULA DA LISTA DE PAGINAS
 * Campos:
 * - nomePagina (char*)
 * - nomeArquivo (char*)
 * - Prox (struct listaPaginas*)
 */
typedef struct pagina Pagina;

#include "Link.h"
#include "Contribuicao.h"

/* CRIA UMA NOVA LISTA DE PAGINAS
* Inputs: Nenhum
* Outputs: Lista de paginas
* Pre-condicao: Nenhuma
* Pos-condicao: Lista criada, sentinela da lista de retorno existe e os campo primeiro aponta para NULL
*/
ListaPaginas* InicializaListaPaginas();

/* INSERE A PAGINA NO INICIO DA LISTA DE PAGINAS
* Inputs: Nome da pagina, o nome do arquivo da pagina e a lista de paginas
* Outputs: Lista de paginas atualizada
* Pre-condicao: Lista existe, nome da pagina e nome do arquivo validos
* Pos-condicao: Pagina criada e inserida no comeco da lista
*/
ListaPaginas* InserePagina(char *nomePagina, char *nomeArquivo, ListaPaginas* lista);

/* RETIRA PAGINA DA LISTA
* Inputs: Nome da pagina
* Outputs: Lista de paginas atualizada
* Pre-condicao: Listas e pagina a ser retirada existem
* Pos-condicao
*/
ListaPaginas* RetiraPagina(char *nomePagina, ListaPaginas *lista, ListaLinks *listaLinks, ListaContribuicoes *listaContribuicoes);

/* VERIFICA SE A PAGINA EXISTE
* Inputs: Nome da pagina e lista de paginas
* Outputs: 0 (falso) ou 1 (verdadeiro)
* Pre-condicao: Lista de paginas existe
* Pos-condicao: Nenhuma
*/
int CheckExistencia(char *nomePagina, ListaPaginas *listaPaginas);

/* CRIA UM ARQUIVO COM TODAS AS INFORMACOES DA PAGINA
* Inputs: Nome da pagina, lista de paginas, lista de editores, lista de contribuicoes e lista de links
* Outputs: Nenhum
* Pre-condicao: Listas existem
* Pos-condicao: Arquivo criado e informacoes da pagina impresas nele
*/
void ImprimePagina(char *nomePagina, ListaPaginas *listaP, ListaEditores *listaE, ListaContribuicoes *listaC, ListaLinks *listaL);

/* DADO O NOME DA PAGINA, RETORNA A ESTRUTURA
* Inputs: Lista de paginas e nome da pagina
* Outputs: Pagina
* Pre-condicao: Lista de paginas existe
* Pos-condicao: Nenhuma
*/
Pagina *RecuperaPaginaPorNome(ListaPaginas *listaPaginas, char *nomePagina);

/* DADA A ESTRUTURA PAGINA, RETORNA O NOME
* Inputs: Pagina
* Outputs: Nome da pagina
* Pre-condicao: Nenhuma
* Pos-condicao: Nenhuma
*/
char *RecuperaNomePagina(Pagina *pagina);

/* DADA A ESTRUTURA PAGINA, RETORNA O NOME DO ARQUIVO
* Inputs: Pagina
* Outputs: Nome do arquivo da pagina
* Pre-condicao: Nenhuma
* Pos-condicao: Nenhuma
*/
char *RecuperaArquivoPagina(Pagina *pagina);

/* CRIA UM ARQUIVO COM AS INFORMACOES DE TODAS AS PAGINAS
* Inputs: Lista de paginas, lista de editores, lista de contribuicoes e lista de links
* Outputs: Nenhum
* Pre-condicao: Listas existem
* Pos-condicao: Arquivo criado e informacoes de todas as paginas da wiked impresas nele
*/
void ImprimeWiked(ListaPaginas *listaP, ListaEditores *listaE, ListaContribuicoes *listaC, ListaLinks *listaL);

/* LIBERA O ESPACO ALOCADO PELA LISTA DE PAGINAS
* Inputs: Lista de paginas
* Outputs: Nenhum
* Pre-condicao: Lista existe
* Pos-condicao: Toda a memoria ocupada pela lista liberada
*/
void FimPaginas(ListaPaginas* lista);

#endif