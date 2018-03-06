#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pagina.h"
#include "Editor.h"
#include "Contribuicao.h"
#include "Log.h"

struct pagina {
    char *nomePagina;
    char *nomeArquivo;
    Pagina *Prox;
};

struct listaPaginas {
    Pagina *Primeiro;
};

ListaPaginas* InicializaListaPaginas() {
    // Criando lista vazia
    ListaPaginas *lista = (ListaPaginas*) malloc(sizeof (ListaPaginas));
    lista->Primeiro = NULL;

    return lista;
}

ListaPaginas* InserePagina(char *nomePagina, char *nomeArquivo, ListaPaginas *lista) {
    if (CheckExistencia(nomePagina, lista)) {
        printLog3("ERRO:PAGINA", nomePagina, "JA EXISTE");

        return lista;
    }

    Pagina *novaPagina = (Pagina*) malloc(sizeof (Pagina));
    novaPagina->Prox = NULL;

    int tamNomePagina = strlen(nomePagina) + 1;
    int tamNomeArquivo = strlen(nomeArquivo) + 1;

    novaPagina->nomePagina = (char*) malloc(tamNomePagina * sizeof (char));
    novaPagina->nomeArquivo = (char*) malloc(tamNomeArquivo * sizeof (char));

    strcpy(novaPagina->nomePagina, nomePagina);
    strcpy(novaPagina->nomeArquivo, nomeArquivo);

    //SE A LISTA ESTIVER VAZIA
    if (lista->Primeiro == NULL)
        lista->Primeiro = novaPagina;

        //SE A LISTA JA TIVER ELEMENTOS
    else {
        novaPagina->Prox = lista->Primeiro;
        lista->Primeiro = novaPagina;
    }

    return lista;
}

ListaPaginas* RetiraPagina(char *nomePagina, ListaPaginas *lista, ListaLinks *listaLinks, ListaContribuicoes *listaContribuicoes) {
    Pagina *atual = lista->Primeiro;
    Pagina *anterior = lista->Primeiro;

    //PROCURANDO PAGINA A SER RETIRADA
    while (atual != NULL) {
        if (strcmp(atual->nomePagina, nomePagina) == 0)
            break;

        anterior = atual;
        atual = atual->Prox;
    }

    //CASO A PAGINA NAO EXISTA
    if (atual == NULL) {
        printLog2("ERRO: NAO EXISTE A PAGINA", nomePagina);
        return lista;
    }
        //PAGINA A SER RETIRADA EH A PRIMEIRA DA LISTA
    else if (atual == lista->Primeiro)
        lista->Primeiro = atual->Prox;

        //PAGINA A SER RETIRADA ESTA EM OUTRA POSICAO DA LISTA
    else
        anterior->Prox = atual->Prox;

    RetiraContribuicoesPorPagina(atual, listaContribuicoes, 1);
    RetiraLinksPorPagina(atual, listaLinks);

    free(atual->nomeArquivo);
    free(atual->nomePagina);
    free(atual);

    //printLog("Pagina", nomePagina, "retirada");

    return lista;
}

int CheckExistencia(char *nomePagina, ListaPaginas *listaPaginas) {
    Pagina *aux;

    if (listaPaginas->Primeiro == NULL)
        return 0;

    if (strcmp(listaPaginas->Primeiro->nomePagina, nomePagina) == 0)
        return 1;

    aux = listaPaginas->Primeiro;

    for (;;) {
        aux = aux->Prox;

        if (aux == NULL)
            break;

        if (strcmp(aux->nomePagina, nomePagina) == 0)
            return 1;
    }

    return 0;
}

void ImprimePagina(char *nomePagina, ListaPaginas *listaP, ListaEditores *listaE, ListaContribuicoes *listaC, ListaLinks *listaL) {
    if (CheckExistencia(nomePagina, listaP) == 0) {
        printLog3("ERRO: A PAGINA", nomePagina, "NAO EXISTE");
        return;
    }

    Pagina *pagina = RecuperaPaginaPorNome(listaP, nomePagina);

    FILE *file = fopen(pagina->nomeArquivo, "w");

    if (file) {
        fprintf(file, "%s\n\n", nomePagina);
        fprintf(file, "--> Historico de contribuicoes\n");

        ImprimeHistorico(listaC, nomePagina, file);
        ImprimeLinks(listaL, nomePagina, file);
        ImprimeTextos(listaC, nomePagina, file);

        fclose(file);
    } else {
        printLog2("ERRO AO CRIAR O ARQUIVO:", nomePagina);
    }
    return;
}

Pagina* RecuperaPaginaPorNome(ListaPaginas *listaPaginas, char *nome) {
    Pagina *pagina;

    if (listaPaginas->Primeiro == NULL)
        return NULL;

    if (strcmp(listaPaginas->Primeiro->nomePagina, nome) == 0)
        return listaPaginas->Primeiro;

    pagina = listaPaginas->Primeiro;

    do {
        pagina = pagina->Prox;

        if (pagina == NULL)
            break;

    } while ((strcmp(nome, pagina->nomePagina) != 0));

    return pagina;
}

char* RecuperaNomePagina(Pagina *pagina) {
    return (pagina->nomePagina);
}

char* RecuperaArquivoPagina(Pagina *pagina) {
    return (pagina->nomeArquivo);
}

void ImprimeWiked(ListaPaginas *listaP, ListaEditores *listaE, ListaContribuicoes *listaC, ListaLinks *listaL) {
    FILE *file = fopen("wiked.txt", "w");

    if (!file) {
        printLog2("ERRO AO ABRIR O ARQUIVO:", "'wiked.txt'");
        return;
    }

    Pagina *pagina = listaP->Primeiro;

    while (pagina != NULL) {
        fprintf(file, "%s\n\n", pagina->nomePagina);
        fprintf(file, "--> Historico de contribuicoes\n");

        ImprimeHistorico(listaC, pagina->nomePagina, file);
        ImprimeLinks(listaL, pagina->nomePagina, file);
        ImprimeTextos(listaC, pagina->nomePagina, file);

        pagina = pagina->Prox;
    }

    fclose(file);

    return;
}

void FimPaginas(ListaPaginas *lista) {
    Pagina *aux1, *aux = lista->Primeiro;

    if (aux != NULL) {
        while (aux != NULL) {
            aux1 = aux;

            free(aux1->nomeArquivo);
            free(aux1->nomePagina);

            aux = aux->Prox;

            free(aux1);
        }
    }

    free(lista);
}