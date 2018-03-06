#ifndef EDITOR_H_
#define EDITOR_H_

#include "Contribuicao.h"

// LISTA DE EDITORES
typedef struct listaEditores ListaEditores;

/* CELULA DA LISTA DE EDITORES
 * Campos:
 * - nomeEditor (char*)
 * - Prox (struct listaEditores*)
 */
typedef struct editor Editor;

/* CRIA UMA NOVA LISTA DE EDITORES
* Inputs: Nenhum
* Outputs: Lista de editores
* Pre-condicao: Nenhuma
* Pos-condicao: Lista de editor inicializada e vazia
*/
ListaEditores* InicializaListaEditores();

/* INSERE O EDITOR NO INICIO DA LISTA DE EDITORES
* Inputs: Nome do editor e lista de editores
* Outputs: Lista de editores atualizada
* Pre-condicao: Lista existe e nome do editor eh valido
* Pos-condicao: Editor inserido na lista
*/
ListaEditores* InsereEditor(char *nomeEditor, ListaEditores* lista);

/* RETIRA EDITOR DA LISTA
* Inputs: Nome do editor e Listas
* Outputs: Lista de editores atualizada
* Pre-Condicao: Listas e editor existem
* Pos-Condicao: Editor e Contribuicoes retiradas de suas respectivas listas e espaco ocupado por ele liberado
*/
ListaEditores* RetiraEditor(char *nomeEditor, ListaEditores *lista, ListaContribuicoes *listaContribuicoes);

/* LIBERA O ESPACO ALOCADO PELA LISTA DE EDITORES
* Inputs: Lista de editores
* Outputs: Lista de editores liberada
* Pre-condicao: Lista existe
* Pos-condicao: Espaco alocado pela lista liberado
*/
void FimEditores(ListaEditores* lista);

/* RETORNA O EDITOR PEDIDO
* Inputs: Nome do editor e lista de editores
* Outputs: Editor
* Pre-condicao: Lista existe e nome do editor eh valido
* Pos-condicao: Nenhuma
*/
Editor* RecuperaEditorPorNome(char *nome, ListaEditores *lista);

/* DADA A ESTRUTURA EDITOR, RETORNA O NOME
 * Inputs: Editor
 * Outputs: Nome do editor
 * Pre-condicao: Editor existe
 * Pos-condicao: Nenhuma
 */
char *RecuperaNomeEditor(Editor *editor);

/* RETORNA O TAMANHO DO NOME DO EDITOR
 * Inputs: Editor
 * Outputs: Tamanho do nome do editor
 * Pre-condicao: Editor existe
 * Pos-condicao: Nenhuma
 */
int RecuperaTamNomeEditor(Editor *editor);

#endif