#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "funcoesPrincipal.h"


int main()
{
    int pcsExistentes=0, pcsDisponiveis=0, totalRequisicoes=0, requisicoesAtivas=0, totalAvarias=0;
    char op='x';

    tipoPortatil computadores[PORTATEIS];
    tipoRequisicao *requisicoes=NULL;
    tipoAvaria *avarias=NULL;

    setlocale(LC_ALL, "Portuguese");

    requisicoes = lerFicheiroBinario(computadores, &pcsExistentes, &pcsDisponiveis, requisicoes, &totalRequisicoes, &requisicoesAtivas);
    avarias = lerFicheiroBinario2(avarias, &totalAvarias);

    do
    {
        op = toupper(menu(pcsExistentes,pcsDisponiveis,totalRequisicoes,requisicoesAtivas));
        switch(op)
        {
        case 'A':
            //Inserir a informação referente a todos os portáteis
            if (pcsExistentes<PORTATEIS)
            {
                pcsExistentes = inserirInfoPortatil(computadores, pcsExistentes, &pcsDisponiveis);
            }
            else
            {
                printf("\n\nErro! Apenas podem ser registados 30 portáteis!\n");
            }
            break;
        case 'B':
            //Listar a informação referente a todos os portáteis
            if (pcsExistentes>0)
            {
                listaPortateis(computadores, pcsExistentes, requisicoes, totalRequisicoes);
            }
            else
            {
                printf("\n\nNão existe nenhum portátil para mostrar");
            }
            break;
        case 'C':
            //Registar a alteração da localização de um computador portátil
            if (pcsExistentes>0)
            {
                alteraLocalizacao(computadores, pcsExistentes);
            }
            else
            {
                printf("\n\nNão existe nenhum portátil para alterar a localização");
            }
            break;
        case 'D':
            //Registar a requisição de um computador portátil
            if (pcsExistentes>0)
            {
                if (pcsDisponiveis>0)
                {
                    requisicoes = requisitar(requisicoes,&totalRequisicoes,computadores,pcsExistentes, &pcsDisponiveis, &requisicoesAtivas);
                }
                else
                {
                    printf("\n\nNenhum dos nosso portáteis se encontra disponível para requisição");
                }
            }
            else
            {
                printf("\n\nErro! Não existem portáteis para requisitar");
            }
            break;
        case 'E':
            //Listar os dados de todas as requisições
            if(totalRequisicoes==0)
            {
                printf("\n\nErro! Não foi efetuada nenhuma requisição até ao momento");
            }
            else
            {
                listaDadosRequisicoes(requisicoes, totalRequisicoes);
            }
            break;
        case 'F':
            //Registar a devolução de um computador portátil previamente requisitado
            if(totalRequisicoes==0)
            {
                printf("\n\nErro! Não foi efetuada nenhuma requisição até ao momento");
            }
            else
            {
                if (requisicoesAtivas>0)
                {
                    requisicoes = devolver(computadores, pcsExistentes, requisicoes, totalRequisicoes);
                    pcsDisponiveis++;
                    requisicoesAtivas--;
                    printf("\n\nDevolução efetuada com sucesso!");
                }
                else
                {
                    printf("\n\nErro! Não existem requisições ativas");
                }
            }
            break;
        case 'G':
            //Renovar a requisição de um computador portátil
            if(totalRequisicoes==0)
            {
                printf("\n\nErro! Não foi efetuada nenhuma requisição até ao momento");
            }
            else
            {
                if (requisicoesAtivas>0)
                {
                    requisicoes = renovar(computadores, pcsExistentes, requisicoes, totalRequisicoes, &pcsDisponiveis, &requisicoesAtivas);
                }
                else
                {
                    printf("\n\nErro! Não existem requisições ativas");
                }
            }
            break;
        case 'H':
            //Registar a avaria de um computador portátil
            if (pcsExistentes>0)
            {
                avarias = registarAvaria(computadores, pcsExistentes, requisicoes, totalRequisicoes, avarias, &totalAvarias, &pcsDisponiveis, &requisicoesAtivas);
            }
            else
            {
                printf("\n\nErro! Não existem portáteis para registar avarias");
            }
            break;
        case 'I':
            //Registar a reparação de um computador portátil
            if (pcsExistentes>0)
            {
                avarias = registarReparacao(avarias, totalAvarias, computadores, pcsExistentes, &pcsDisponiveis);
            }
            else
            {
                printf("\n\nErro! Não existem portáteis para registar reparação");
            }
            break;
        case 'J':
            //Apresentar a informação de uma requisição
            if(totalRequisicoes==0)
            {
                printf("\n\nErro! Não foi efetuada nenhuma requisição até ao momento");
            }
            else
            {
                mostrarInfoRequisicao(requisicoes, totalRequisicoes, computadores, pcsExistentes);
            }
            break;
        case 'K':
            //Apresentar dados estatísticos
            if (pcsExistentes==0)
            {
                printf("\n\nNão existem portáteis para mostrar dados estatísticos");
            }
            else
            {
                mostraDadosEstatisticos(computadores, pcsExistentes, requisicoes, totalRequisicoes);
            }
            break;
        case 'L':
            //Apresentar uma listagem de todas as avarias ocorridas
            if (totalAvarias>0)
            {
                apresentarAvarias(avarias, totalAvarias, computadores, pcsExistentes);
            }
            else
            {
                printf("\n\nErro! Não foi registada nenhuma avaria até ao momento");
            }
            break;
        case 'S':
            printf("\n\nFim do programa!\n\n");
            break;

        default:
            printf("\n\nOpção inválida!\n");
        }
        gravaFicheiroBinario(computadores, pcsExistentes, requisicoes, totalRequisicoes, pcsDisponiveis, requisicoesAtivas);
        gravaFicheiroBinario2(avarias, totalAvarias);
    }
    while (op != 'S');

    free(requisicoes);
    free(avarias);

    return 0;
}
