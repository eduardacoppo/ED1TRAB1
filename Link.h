#ifndef LINK_H_
#define LINK_H_

/* CELULA DA LISTA DE LINKS
 * Campos:
 * - de (struct listaPagina*)
 * - para (struct listaPaginas*)
 * - Prox (struct listaLinks*)
 */
typedef struct link Link;

// LISTA DE LINKS
typedef struct listaLinks ListaLinks;

#include "Pagina.h"
#include "Link.h"

/* INICIALIZA A LISTA DE LINKS
 * Inputs: Nenhum
 * Outputs: Lista inicializada e vazia
 * Pre-condicao: Nenhuma
 * Pos-condicao: Lista criada e vazia
 */
ListaLinks *InicializaListaLinks();

/* INSERE LINK NA LISTA
 * Inputs: Lista de links, lista de paginas e nome das paginas
 * Outputs: Nenhum
 * Pre-condicao: Listas existem, nomes das paginas validos e respecivas paginas existem
 * Pos-condicao: Link inserido na lista de links
 */
void InsereLink(ListaLinks *listaLinks, ListaPaginas *listaPaginas, char *deNome, char *paraNome);

/* REMOVE LINK DA LISTA
 * Inputs: Lista de links e link a ser retirado
 * Outputs: Nenhum
 * Pre-condicao: Lista e link existem
 * Pos-condicao: Link removido
 */
void RemoverLink(ListaLinks *lista, Link *l);

/* RETIRA LINK DA PAGINA
 * Inputs: Pagina e lista de links
 * Outputs: Nenhum
 * Pre-condicao: Lista e pagina existem
 * Pos-condicao: Link retirado da lista
 */
void RetiraLink(ListaLinks *listaLinks,ListaPaginas *listaPaginas, char *deNome, char *paraNome);

/* RETIRA LINK DA PAGINA
 * Inputs: Pagina e lista de links
 * Outputs: Nenhum
 * Pre-condicao: Lista e pagina existem
 * Pos-condicao: Todos os links daquela pagina sao retirados
 */
void RetiraLinksPorPagina(Pagina *pagina, ListaLinks *listaLinks);

/* LIBERA ESPACO ALOCADO PELA LISTA DE LINKS
 * Inputs: Lista de links
 * Outputs: Nenhum
 * Pre-condicao: Lista existe
 * Pos-condicao: Espaco alocado para a lista liberado
 */
void FimLinks(ListaLinks *lista);

/* VERIFICA SE EXISTE LINK ENTRE DUAS PAGINAS
 * Inputs: Lista de links, lista de paginas, nome das paginas
 * Outputs: Nenhum
 * Pre-condicao: Listas existem e nomes das paginas sao validos
 * Pos-condicao: Nenhuma
 */
void CheckLink(ListaLinks *listaLinks, ListaPaginas *listaPaginas, char *nomeDe, char *nomePara);

/* IMPRIME OS LINKS PARA CERTA PAGINA EM UM ARQUIVO
 * Inputs: Lista de links, nome da pagina e arquivo
 * Outputs: Nenhum
 * Pre-condicao: Lista e arquivo existem, nome da pagina valido
 * Pos-condicao: Lista de links da pagina imprimida no arquivo
 */
void ImprimeLinks(ListaLinks *listaLinks, char *nomePagina, FILE *file);

#endif