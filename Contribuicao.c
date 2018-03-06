#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Pagina.h"
#include "Editor.h"
#include "Contribuicao.h"
#include "Log.h"

struct contribuicao {
    char *nomeContribuicao;
    Contribuicao *Prox;
    int excluida;
    Pagina *pagina;
    char *nomePagina;
    Editor *editor;
};

struct listaContribuicoes {
    Contribuicao *Primeiro;
    Contribuicao *Ultimo;
};

ListaContribuicoes* InicializaListaContribuicoes() {
    ListaContribuicoes *lista = (ListaContribuicoes*) malloc(sizeof (ListaContribuicoes));
    lista->Primeiro = lista->Ultimo = NULL;

    return lista;
}

void InsereContribuicao(char *nomePagina, char *nomeEditor, char *nomeContribuicao, ListaEditores *listaE, ListaContribuicoes *listaC, ListaPaginas *listaP) {
    Editor *editor = RecuperaEditorPorNome(nomeEditor, listaE);
    Pagina *pagina = RecuperaPaginaPorNome(listaP, nomePagina);

    if (editor == NULL) {
        printLog3("ERRO: EDITOR ", nomeEditor, " NAO EXISTE!");
        return;
    }

    if (pagina == NULL) {
        printLog3("ERRO: PAGINA", nomePagina, " NAO EXISTE!");
        return;
    }


    //Verifica se a contribuição ja existe
    if (listaC->Primeiro != NULL) {
        Contribuicao *aux;

        aux = listaC->Primeiro;
        //Verifica se ela é a primeira da lista
        if (strcmp(aux->nomeContribuicao, nomeContribuicao) == 0) {
            printLog3("ERRO: CONTRIBUICAO", nomeContribuicao, "JA EXISTE!");
            return;
        } else {
            //varre a lista procurando
            for (;;) {

                if (aux == NULL) break;

                if (strcmp(aux->nomeContribuicao, nomeContribuicao) == 0) break;

                aux = aux->Prox;
            }

            if (aux != NULL) {
                printLog3("ERRO: CONTRIBUICAO", nomeContribuicao, "JA EXISTE!");
                return;
            }
        }
    }



    Contribuicao *c = (Contribuicao*) malloc(sizeof (Contribuicao));

    c->editor = editor;
    c->excluida = 0;

    c->nomeContribuicao = (char*) malloc(sizeof (char)*(strlen(nomeContribuicao) + 1));
    strcpy(c->nomeContribuicao, nomeContribuicao);

    c->nomePagina = (char*) malloc(sizeof (char)*(strlen(nomePagina) + 1));
    strcpy(c->nomePagina, nomePagina);

    c->Prox = NULL;
    c->pagina = pagina;

    if (listaC->Primeiro == NULL) {
        listaC->Primeiro = listaC->Ultimo = c;
        return;
    }

    listaC->Ultimo->Prox = c;
    listaC->Ultimo = c;

    return;
}

void RetiraContribuicao(ListaContribuicoes *listaContribuicoes, ListaPaginas *listaPaginas, ListaEditores *listaEditores, char *nomePagina, char* nomeEditor, char *nomeContribuicao) {
    Contribuicao *aux;
    Editor *editor = RecuperaEditorPorNome(nomeEditor, listaEditores);
    aux = listaContribuicoes->Primeiro;

    if (editor == NULL) {
        printLog3("ERRO: EDITOR", nomeEditor, "NAO EXISTE");
        return;
    }

    while (aux != NULL) {
        if (strcmp(aux->nomeContribuicao, nomeContribuicao) == 0) {
            if (editor == aux->editor) {
                aux->excluida = 1;
            }
            else {
                printLog4("ERRO: EDITOR", RecuperaNomeEditor(editor), "NAO PODE RETIRAR A CONTRIBUICAO", aux->nomeContribuicao);
            }
            break;
        }

        aux = aux->Prox;
    }

    if (aux == NULL) {
        printLog3("ERRO: CONTRIBUICAO", nomeContribuicao, " NAO EXISTE!");
    }

    return;
}

void ImprimeTextos(ListaContribuicoes *listaContribuicoes, char *nomePagina, FILE *file) {
    Contribuicao *contribuicao = listaContribuicoes->Primeiro;
    int c;

    fprintf(file, "--> Textos\n\n");

    while (contribuicao != NULL) {
        if ((strcmp(RecuperaNomePagina(contribuicao->pagina), nomePagina) == 0)&& !contribuicao->excluida) {
            FILE *arquivo = fopen(contribuicao->nomeContribuicao, "r");

            if (arquivo) {
                fprintf(file, "-------- %s (%s) --------\n\n", contribuicao->nomeContribuicao, RecuperaNomeEditor(contribuicao->editor));

                while ((c = getc(arquivo)) != EOF)
                    fprintf(file, "%c", c);

                fprintf(file, "\n\n");

                fclose(arquivo);
            } else {
                printLog3("ERRO: O ARQUIVO DA CONTRIBUICAO", contribuicao->nomeContribuicao, "NAO FOI ENCONTRADO!");
            }
        }

        contribuicao = contribuicao->Prox;
    }
}

void ImprimeHistorico(ListaContribuicoes *listaContribuicoes, char *nomePagina, FILE *file) {
    Contribuicao *contribuicao = listaContribuicoes->Primeiro;

    while (contribuicao != NULL) {
        if (strcmp(RecuperaNomePagina(contribuicao->pagina), nomePagina) == 0) {
            if (!contribuicao->excluida) {
                fprintf(file, "%s %s\n", RecuperaNomeEditor(contribuicao->editor), contribuicao->nomeContribuicao);
            } else {
                fprintf(file, "%s %s(EXCLUIDA)\n", RecuperaNomeEditor(contribuicao->editor), contribuicao->nomeContribuicao);
            }
        }

        contribuicao = contribuicao->Prox;
    }

    fprintf(file, "\n");

    return;
}

void RetiraContribuicoesPorPagina(Pagina *pagina, ListaContribuicoes *listaContribuicoes, int paginaExcluida) {
    Contribuicao *aux;

    aux = listaContribuicoes->Primeiro;

    while (aux != NULL) {
        if (aux->pagina == pagina) {
            aux->excluida = 1;

            if (paginaExcluida) {
                aux->pagina = NULL;
            }
        }
        aux = aux->Prox;
    }

    return;
}

void RetiraContribuicoesPorEditor(Editor *editor, ListaContribuicoes *listaContribuicoes) {

    Contribuicao *aux;
    Contribuicao *aux2;
    Contribuicao *ant;

    aux = listaContribuicoes->Primeiro;
    ant = NULL;

    while (aux != NULL) {
        if (aux->editor == editor) {
            /*Verifica se a contribuição é a primeira da lista, essa função esta
             dentro do loop pois se c1 e c2 devem ser retiradas e for retirada c1
             c2 sera primeira da lista.
             */
            if (aux == listaContribuicoes->Primeiro) {
                listaContribuicoes->Primeiro = aux->Prox;
                aux2 = aux;
                aux = aux->Prox;
                free(aux2->nomeContribuicao);
                free(aux2->nomePagina);
                free(aux2);
                continue;
            } else {
                ant->Prox = aux->Prox;
                aux2 = aux;
                aux = aux->Prox;
                free(aux2->nomeContribuicao);
                free(aux2->nomePagina);
                free(aux2);
                continue;
            }
        }
        ant = aux;
        aux = aux->Prox;
    }

    return;
}

void FimContribuicoes(ListaContribuicoes * lista) {
    Contribuicao *aux;
    Contribuicao *prox;

    aux = lista->Primeiro;

    if (aux != NULL) {
        do {
            prox = aux->Prox;

            free(aux->nomeContribuicao);
            free(aux->nomePagina);
            free(aux);
            aux = prox;
        } while (prox != NULL);
    }
    free(lista);
}