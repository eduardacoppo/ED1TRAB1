#ifndef CONTRIBUICAO_H_
#define CONTRIBUICAO_H_

// LISTA DE CONTRIBUICOES
typedef struct listaContribuicoes ListaContribuicoes;

#include "Editor.h"
#include "Pagina.h"

/* CELULA DA LISTA DE CONTRIBUICOES
 * Campos:
 * - nomeContribuicao (char*)
 * - Prox (struct listaContribuicoes*)
 * - excluida (int) - 1 = excluida, 0 = nao excluida
 * - pagina (struct listaPaginas*)
 * - editor (struct listaEditores*)
 */
typedef struct contribuicao Contribuicao;

/* CRIA UMA NOVA LISTA DE CONTRIBUICOES
* Inputs: Nenhum
* Outputs: Lista de contribuicoes
* Pre-condicao: Nenhuma
* Pos-condicao: Lista criada e vazia
*/
ListaContribuicoes* InicializaListaContribuicoes();

/* INSERE A CONTRIBUICAO NO INICIO DA LISTA DE CONTRIBUICOES DO EDITOR
* Inputs: Nome da pagina, nome do editor, nome da contribuicao e lista de editores
* Outputs: Lista de contribuicoes do editor atualizada
* Pre-condicao: Listas existem e nomes sao validos
* Pos-condicoes: Contribuicao criada e inserida na lista
*/
void InsereContribuicao(char *nomePagina, char *nomeEditor, char *nomeContribuicao, ListaEditores *listaE, ListaContribuicoes *listaC, ListaPaginas *listaP);

/* RETIRA CONTRIBUICAO DA LISTA
* Inputs: Lista de contribuicoes e nome da contribuicao
* Outputs: Nenhum
* Pre-condicao: Listas existem e nomes sao validos
* Pos-condicao: Contribuicao retirada da lista e espaco alocado por ela liberado
*/
void RetiraContribuicao(ListaContribuicoes *listaContribuicoes, ListaPaginas *listaPaginas, ListaEditores *listaEditores, char *nomePagina, char* nomeEditor, char *nomeContribuicao);

/* RETIRA TODAS AS CONTRIBUICOES DE DADA PAGINA
* Inputs: Pagina e lista de contribuicoes
* Outputs: Nenhum
* Pre-condicao: Lista e pagina existem
* Pos-condicao: Todas as contribuicoes feitas para uma pagina sinalizadas como excluidas
*/
void RetiraContribuicoesPorPagina(Pagina *pagina, ListaContribuicoes *listaContribuicoes, int paginaExcluida);

/* RETIRA TODAS AS CONTRIBUICOES DE DADO EDITOR
* Inputs: Editor e lista de contribuicoes
* Outputs: Nenhum
* Pre-condicao: Lista e editor existem
* Pos-condicao: Todas as contribuicoes feitas para um editor excluidas
*/
void RetiraContribuicoesPorEditor(Editor *editor, ListaContribuicoes *listaContribuicoes);

/* LIBERA ESPACO ALOCADO PELA LISTA DE CONTRIBUICOES
* Inputs: Nome da pagina, nome do editor, nome da contribuicao e lista de editores
* Outputs: Lista de contribuicoes do editor atualizada
* Pre-condicao: Lista existe
* Pos-condicao: Todo o espaco alocado pela lista eh liberado
*/
void FimContribuicoes(ListaContribuicoes *lista);

/* IMPRIME O HISTORICO DE CONTRIBUICOES PARA DADA PAGINA (EDITOR E RESPECTIVA CONTRIBUICAO)
* Inputs: Lista de contribuicoes, nome da pagina, arquivo onde sera imprimido o historico
* Outputs: Nenhum
* Pre-condicao: Lista, pagina e arquivo existem
* Pos-condicao: Historico de contribuicoes imprimido no arquivo
*/
void ImprimeHistorico(ListaContribuicoes *listaContribuicoes, char *nomePagina, FILE *file);

/* IMPRIME OS TEXTOS DAS CONTRIBUICOES DE UMA PAGINA
* Inputs: Lista de contribuicoes, nome da pagina e arquivo onde serao imprimidos os textos
* Outputs: Nenhum
* Pre-condicao: Lista, pagina e contribuicao existem
* Pos-condicoes: Contribuicoes imprimidas no arquivo
*/
void ImprimeTextos(ListaContribuicoes *listaContribuicoes, char *nomePagina, FILE *file);

#endif