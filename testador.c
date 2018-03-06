#include <stdio.h>
#include <string.h>
#include "Pagina.h"
#include "Editor.h"
#include "Contribuicao.h"
#include "Link.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Modelo: %s nome_do_arquivo.txt\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == 0) {
        printf("Arquivo nao existe!\n");
        return 2;
    }


    ListaPaginas* listaPaginas = InicializaListaPaginas();
    ListaEditores* listaEditores = InicializaListaEditores();
    ListaContribuicoes* listaContribuicoes = InicializaListaContribuicoes();
    ListaLinks* listaLinks = InicializaListaLinks();

    char funcao[20], nomePagina[20], nomePagina2[20], nomeArquivo[20], nomeEditor[20], nomeContribuicao[20];

    do {
        fscanf(file, "%s", funcao);

        if (strcmp(funcao, "INSEREPAGINA") == 0) {
            fscanf(file, "%s %s", nomePagina, nomeArquivo);
            listaPaginas = InserePagina(nomePagina, nomeArquivo, listaPaginas);
        }

        if (strcmp(funcao, "RETIRAPAGINA") == 0) {
            fscanf(file, "%s", nomePagina);
            listaPaginas = RetiraPagina(nomePagina, listaPaginas, listaLinks, listaContribuicoes);
        }

        if (strcmp(funcao, "INSEREEDITOR") == 0) {
            fscanf(file, "%s", nomeEditor);
            listaEditores = InsereEditor(nomeEditor, listaEditores);
        }

        if (strcmp(funcao, "RETIRAEDITOR") == 0) {
            fscanf(file, "%s", nomeEditor);
            listaEditores = RetiraEditor(nomeEditor, listaEditores, listaContribuicoes);
        }

        if (strcmp(funcao, "INSERECONTRIBUICAO") == 0) {
            fscanf(file, "%s %s %s", nomePagina, nomeEditor, nomeContribuicao);
            InsereContribuicao(nomePagina, nomeEditor, nomeContribuicao, listaEditores, listaContribuicoes, listaPaginas);
        }

        if (strcmp(funcao, "INSERELINK") == 0) {
            fscanf(file, "%s %s", nomePagina, nomePagina2);
            InsereLink(listaLinks, listaPaginas, nomePagina, nomePagina2);
        }

        if (strcmp(funcao, "RETIRALINK") == 0) {
            fscanf(file, "%s %s", nomePagina, nomePagina2);
            RetiraLink(listaLinks, listaPaginas, nomePagina, nomePagina2);
        }

        if (strcmp(funcao, "IMPRIMEPAGINA") == 0) {
            fscanf(file, "%s", nomePagina);
            ImprimePagina(nomePagina, listaPaginas, listaEditores, listaContribuicoes, listaLinks);
        }

        if (strcmp(funcao, "RETIRACONTRIBUICAO") == 0) {
            fscanf(file, "%s %s %s", nomePagina, nomeEditor, nomeContribuicao);
            RetiraContribuicao(listaContribuicoes, listaPaginas, listaEditores, nomePagina, nomeEditor, nomeContribuicao);
        }

        if (strcmp(funcao, "CAMINHO") == 0) {
            fscanf(file, "%s %s", nomePagina, nomePagina2);
            CheckLink(listaLinks, listaPaginas, nomePagina, nomePagina2);
        }

        if (strcmp(funcao, "IMPRIMEWIKED") == 0) {
            ImprimeWiked(listaPaginas, listaEditores, listaContribuicoes, listaLinks);
        }
    }    while (strcmp(funcao, "FIM") != 0);

    FimPaginas(listaPaginas);
    FimEditores(listaEditores);
    FimContribuicoes(listaContribuicoes);
    FimLinks(listaLinks);

    fclose(file);

    return 0;
}