#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pagina.h"
#include "Editor.h"
#include "Contribuicao.h"
#include "Log.h"

struct editor {
    char *nomeEditor;
    Editor *Prox;
};

struct listaEditores {
    Editor *Primeiro;
    Editor *Ultimo;
};

ListaEditores* InicializaListaEditores() {
    ListaEditores *lista = (ListaEditores*) malloc(sizeof (ListaEditores));
    lista->Primeiro = lista->Ultimo = NULL;

    return lista;
}

ListaEditores* InsereEditor(char *nomeEditor, ListaEditores *lista) {
    Editor *aux;


    //Verifica se o editor já existe
    if (lista->Primeiro != NULL) {
        if (strcmp(lista->Primeiro->nomeEditor, nomeEditor) == 0) {
            printLog3("ERRO: EDITOR", nomeEditor, "JA EXISTE");
            return lista;
        }

        aux = lista->Primeiro;

        for (;;) {
            aux = aux->Prox;

            if (aux == NULL)
                break;

            if (strcmp(aux->nomeEditor, nomeEditor) == 0)
                break;
        }

        if (aux != NULL) {
            printLog3("ERRO: EDITOR", nomeEditor, "JA EXISTE");
            return lista;
        }
    }

    Editor *novoEditor = (Editor*) malloc(sizeof (Editor));
    novoEditor->Prox = NULL;

    novoEditor->nomeEditor = (char*) malloc(sizeof (char)*(strlen(nomeEditor) + 1));
    strcpy(novoEditor->nomeEditor, nomeEditor);

    //SE A LISTA ESTIVER VAZIA
    if (lista->Primeiro == NULL)
        lista->Primeiro = novoEditor;

        //SE A LISTA JA TIVER ELEMENTOS
    else {
        novoEditor->Prox = lista->Primeiro;
        lista->Primeiro = novoEditor;
    }

    return lista;
}

ListaEditores* RetiraEditor(char *nomeEditor, ListaEditores *lista, ListaContribuicoes *listaContribuicoes) {
    Editor *atual = lista->Primeiro;
    Editor *anterior = lista->Primeiro;

    //PROCURANDO EDITOR A SER RETIRADO
    while (atual != NULL) {
        if (strcmp(atual->nomeEditor, nomeEditor) == 0)
            break;

        anterior = atual;
        atual = atual->Prox;
    }

    //CASO O EDITOR NAO EXISTA
    if (atual == NULL) {
        printLog3("ERRO: EDITOR", nomeEditor, "NAO EXISTE");
    }
        //EDITOR A SER RETIRADO EH O PRIMEIRO DA LISTA
    else if (atual == lista->Primeiro) {
        lista->Primeiro = atual->Prox;
        RetiraContribuicoesPorEditor(atual, listaContribuicoes);

        free(atual->nomeEditor);
        free(atual);
    }
        //EDITOR A SER RETIRADO ESTA EM OUTRA POSICAO DA LISTA
    else {
        anterior->Prox = atual->Prox;
        RetiraContribuicoesPorEditor(atual, listaContribuicoes);

        free(atual->nomeEditor);
        free(atual);
    }

    return lista;
}

char* RecuperaNomeEditor(Editor *editor) {
    return (editor->nomeEditor);
}

int RecuperaTamNomeEditor(Editor *editor) {
    int tam = strlen(editor->nomeEditor);

    return tam;
}

Editor* RecuperaEditorPorNome(char *nome, ListaEditores *lista) {
    Editor *aux;

    if (lista->Primeiro == NULL)
        return NULL;

    if (strcmp(lista->Primeiro->nomeEditor, nome) == 0)
        return lista->Primeiro;

    aux = lista->Primeiro;

    for (;;) {
        aux = aux->Prox;

        if (aux == NULL)
            break;

        if (strcmp(aux->nomeEditor, nome) == 0)
            break;
    }

    if (aux == NULL) {
        printLog3("ERRO: EDITOR", nome, "NAO EXISTE");
    }
    return aux;
}

void FimEditores(ListaEditores *lista) {
    Editor *aux = lista->Primeiro;
    Editor *aux1;

    if (aux != NULL) {
        while (aux != NULL) {
            aux1 = aux;

            free(aux1->nomeEditor);

            aux = aux->Prox;

            free(aux1);
        }
    }

    free(lista);

    return;
}