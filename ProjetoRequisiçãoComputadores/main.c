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
            //Inserir a informa��o referente a todos os port�teis
            if (pcsExistentes<PORTATEIS)
            {
                pcsExistentes = inserirInfoPortatil(computadores, pcsExistentes, &pcsDisponiveis);
            }
            else
            {
                printf("\n\nErro! Apenas podem ser registados 30 port�teis!\n");
            }
            break;
        case 'B':
            //Listar a informa��o referente a todos os port�teis
            if (pcsExistentes>0)
            {
                listaPortateis(computadores, pcsExistentes, requisicoes, totalRequisicoes);
            }
            else
            {
                printf("\n\nN�o existe nenhum port�til para mostrar");
            }
            break;
        case 'C':
            //Registar a altera��o da localiza��o de um computador port�til
            if (pcsExistentes>0)
            {
                alteraLocalizacao(computadores, pcsExistentes);
            }
            else
            {
                printf("\n\nN�o existe nenhum port�til para alterar a localiza��o");
            }
            break;
        case 'D':
            //Registar a requisi��o de um computador port�til
            if (pcsExistentes>0)
            {
                if (pcsDisponiveis>0)
                {
                    requisicoes = requisitar(requisicoes,&totalRequisicoes,computadores,pcsExistentes, &pcsDisponiveis, &requisicoesAtivas);
                }
                else
                {
                    printf("\n\nNenhum dos nosso port�teis se encontra dispon�vel para requisi��o");
                }
            }
            else
            {
                printf("\n\nErro! N�o existem port�teis para requisitar");
            }
            break;
        case 'E':
            //Listar os dados de todas as requisi��es
            if(totalRequisicoes==0)
            {
                printf("\n\nErro! N�o foi efetuada nenhuma requisi��o at� ao momento");
            }
            else
            {
                listaDadosRequisicoes(requisicoes, totalRequisicoes);
            }
            break;
        case 'F':
            //Registar a devolu��o de um computador port�til previamente requisitado
            if(totalRequisicoes==0)
            {
                printf("\n\nErro! N�o foi efetuada nenhuma requisi��o at� ao momento");
            }
            else
            {
                if (requisicoesAtivas>0)
                {
                    requisicoes = devolver(computadores, pcsExistentes, requisicoes, totalRequisicoes);
                    pcsDisponiveis++;
                    requisicoesAtivas--;
                    printf("\n\nDevolu��o efetuada com sucesso!");
                }
                else
                {
                    printf("\n\nErro! N�o existem requisi��es ativas");
                }
            }
            break;
        case 'G':
            //Renovar a requisi��o de um computador port�til
            if(totalRequisicoes==0)
            {
                printf("\n\nErro! N�o foi efetuada nenhuma requisi��o at� ao momento");
            }
            else
            {
                if (requisicoesAtivas>0)
                {
                    requisicoes = renovar(computadores, pcsExistentes, requisicoes, totalRequisicoes, &pcsDisponiveis, &requisicoesAtivas);
                }
                else
                {
                    printf("\n\nErro! N�o existem requisi��es ativas");
                }
            }
            break;
        case 'H':
            //Registar a avaria de um computador port�til
            if (pcsExistentes>0)
            {
                avarias = registarAvaria(computadores, pcsExistentes, requisicoes, totalRequisicoes, avarias, &totalAvarias, &pcsDisponiveis, &requisicoesAtivas);
            }
            else
            {
                printf("\n\nErro! N�o existem port�teis para registar avarias");
            }
            break;
        case 'I':
            //Registar a repara��o de um computador port�til
            if (pcsExistentes>0)
            {
                avarias = registarReparacao(avarias, totalAvarias, computadores, pcsExistentes, &pcsDisponiveis);
            }
            else
            {
                printf("\n\nErro! N�o existem port�teis para registar repara��o");
            }
            break;
        case 'J':
            //Apresentar a informa��o de uma requisi��o
            if(totalRequisicoes==0)
            {
                printf("\n\nErro! N�o foi efetuada nenhuma requisi��o at� ao momento");
            }
            else
            {
                mostrarInfoRequisicao(requisicoes, totalRequisicoes, computadores, pcsExistentes);
            }
            break;
        case 'K':
            //Apresentar dados estat�sticos
            if (pcsExistentes==0)
            {
                printf("\n\nN�o existem port�teis para mostrar dados estat�sticos");
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
                printf("\n\nErro! N�o foi registada nenhuma avaria at� ao momento");
            }
            break;
        case 'S':
            printf("\n\nFim do programa!\n\n");
            break;

        default:
            printf("\n\nOp��o inv�lida!\n");
        }
        gravaFicheiroBinario(computadores, pcsExistentes, requisicoes, totalRequisicoes, pcsDisponiveis, requisicoesAtivas);
        gravaFicheiroBinario2(avarias, totalAvarias);
    }
    while (op != 'S');

    free(requisicoes);
    free(avarias);

    return 0;
}
