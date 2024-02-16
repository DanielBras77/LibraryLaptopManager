#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "funcoesPrincipal.h"


//Menu

char menu(int existentes, int disponiveis, int total_requisicoes, int requisicoes_ativas)
{
    char opcao;
    printf("\n\n\n************************ Menu Principal ************************");
    printf("\n\nPortáteis Existentes: %d \t\tPortáteis Disponíveis: %d", existentes, disponiveis);
    printf("\n\nTotal de Requisições Efetuadas: %d \t\tRequisições Ativas: %d", total_requisicoes, requisicoes_ativas);
    printf("\n\nA – Acrescentar um Novo Portátil");
    printf("\nB – Mostrar Portáteis");
    printf("\nC – Alterar a Localização de um Portátil");
    printf("\nD – Requisitar Portátil");
    printf("\nE – Mostrar Dados de Todas as Requisições");
    printf("\nF – Devolver Portátil");
    printf("\nG – Renovar Requisição de um Portátil");
    printf("\nH – Registar Avaria de um Portátil");
    printf("\nI – Registar Reparação de um Portátil");
    printf("\nJ – Apresentar a Informação de uma Requisição");
    printf("\nK – Apresentar Dados Estatísticos");
    printf("\nL – Listar Avarias Ocorridas");
    printf("\nS – Sair");
    printf("\n\n\t\tOpcao--> ");
    scanf(" %c", &opcao);
    opcao=toupper(opcao);
    limpaBufferStdin();

    return opcao;
}

//Funções de Pesquisa ou Inserção de Dados

int procuraPortatil(tipoPortatil vetor[], int numPortateis, int numDeProcura)
{
    int i, posicao=-1;
    for (i=0; i<numPortateis; i++)
    {
        if (vetor[i].numero_id == numDeProcura)
        {
            posicao = i;
            i = numPortateis;
        }
    }

    return posicao;
}


int procuraRequisicao(tipoRequisicao *requisicoes, int totalRequisicoes, char codigoDeProcura[MAX_STRING])
{
    int i, pos=-1, resultado=-1;
    for(i=0; i<totalRequisicoes; i++)
    {
        resultado = strcmp(requisicoes[i].codigo, codigoDeProcura);
        if(resultado == 0)
        {
            pos = i;
            i=totalRequisicoes;
        }
    }

    return pos;
}


int procuraRequisicaoAtiva(tipoRequisicao *requisicoes, int totalRequisicoes, int nrPortatil)
{
    int i, pos=-1, resultado=-1;
    for(i=0; i<totalRequisicoes; i++)
    {
        resultado = strcmp(requisicoes[i].estado_requisicao, "Ativa");
        if(resultado == 0 && requisicoes[i].numero_id==nrPortatil)
        {
            pos = i;
            i=totalRequisicoes;
        }
    }

    return pos;
}


int procuraAvariaAtiva(tipoAvaria *avarias, int totalAvarias, int numDeProcura)
{
    int i, pos=-1, resultado=-1;

    for(i=0; i<totalAvarias; i++)
    {
        if(avarias[i].tempo_avaria==0 && avarias[i].numero_id==numDeProcura)
        {
            resultado = strcmp(avarias[i].tipo_avaria, "Temporária");
            if (resultado==0)
            {
                pos = i;
                i=totalAvarias;
            }
        }
    }
    return pos;
}


int lerProcessador(void)
{
    int numero, controlo;
    do
    {
        printf("Indique o processador i(3,5,7): ");
        controlo = scanf("%d", &numero);
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Deveria inserir um número inteiro \n");
        }
        else
        {
            if(numero!= 3 && numero!= 5 && numero!= 7)
            {
                printf("Número inválido. Insira novamente!\n");
            }
        }
    }
    while((numero!=3 && numero!= 5 && numero!= 7) || (controlo ==0));

    return numero;
}


void lerTipoUtente(char vetor[])
{
    int utente;
    utente = lerInteiro("\nIndique o tipo de utente \n\n1- Estudante\n2- Docente\n3- Técnico Administrativo \n\nOpção", 1, 3);
    switch (utente)
    {
    case 1:
        strcpy(vetor, "Estudante");
        break;
    case 2:
        strcpy(vetor, "Docente");
        break;
    case 3:
        strcpy(vetor, "Técnico Administrativo");
        break;
    default:
        printf("Opção Inválida!");
    }

}


void lerEstado(char vetor[])
{
    int estado;
    estado = lerInteiro("\nIndique o estado do portátil \n\n1- Disponível\n2- Requisitado\n3- Avariado \n\nOpção", 1, 3);
    switch (estado)
    {
    case 1:
        strcpy(vetor, "Disponível");
        break;
    case 2:
        strcpy(vetor, "Requisitado");
        break;
    case 3:
        strcpy(vetor, "Avariado");
        break;
    default:
        printf("Opção Inválida!");
    }
}


void lerLocal(char vetor[])
{
    int local;
    local = lerInteiro("\nIndique a localização do portátil \n\n1- Campus1  \n2- Campus2 \n3- Campus5 \n4- Residências \n\nOpção",1,4);
    switch (local)
    {
    case 1:
        strcpy(vetor, "Campus1");
        break;
    case 2:
        strcpy(vetor, "Campus2");
        break;
    case 3:
        strcpy(vetor, "Campus5");
        break;
    case 4:
        strcpy(vetor, "Residências");
        break;
    default:
        printf("Opção Inválida!");
    }
}


void lerTipoAvaria(char vetor[])
{
    int tipo;

    tipo = lerInteiro("\nIndique o tipo da avaria do portátil \n\n1- Temporária \n2- Permanente \n\nOpção", 1, 2);
    switch (tipo)
    {
    case 1:
        strcpy(vetor, "Temporária");
        break;
    case 2:
        strcpy(vetor, "Permanente");
        break;
    default:
        printf("Opcao Inválida!");
    }
}

//Funcões Principais

int inserirInfoPortatil(tipoPortatil vetor[], int num, int *disponiveis)
{
    int pos=-1;
    do
    {
        vetor[num].numero_id = lerInteiro("\n\nIndique o número do portátil ", 1, 30);
        pos = procuraPortatil(vetor, num, vetor[num].numero_id);
        if (pos!=-1)
        {
            printf("Já existe um portátil com o número %d. Tente Novamente!", vetor[num].numero_id);
        }
    }
    while(pos!=-1);
    lerString("Indique a designação do portátil",vetor[num].designacao, MAX_STRING);
    vetor[num].processador = lerProcessador();
    vetor[num].RAM = lerInteiro("Indique a RAM do portátil",1,100);
    strcpy(vetor[num].estado, "Disponível");
    *disponiveis += 1;
    lerLocal(vetor[num].localizacao);
    printf("\nData de Aquisição");
    vetor[num].data_aquisicao = lerData();
    vetor[num].valor = lerFloat("\nIndique o valor do portátil (Euros) ", 1, 2000);
    printf("\n\nEste portátil foi inserido com sucesso e já se encontra disponível para requisição!");
    vetor[num].avarias = 0;
    vetor[num].numRequisicoesDoPc = 0;
    vetor[num].diasRequisitado = 0;
    num++;
    return num;
}


void listaPortatil(tipoPortatil vetor[], int i)
{
    printf("\n\n\nNúmero de Identificação: %d\n", vetor[i].numero_id);
    printf("\nDesignação: %s", vetor[i].designacao);
    printf("\nProcessador: Intel Core i%d", vetor[i].processador);
    printf("\nMemória RAM: %d GB", vetor[i].RAM);
    printf("\nEstado: %s", vetor[i].estado);
    printf("\nLocalização: %s", vetor[i].localizacao);
    printf("\nData de Aquisição: %d/%d/%d", vetor[i].data_aquisicao.dia, vetor[i].data_aquisicao.mes, vetor[i].data_aquisicao.ano);
    printf("\nValor do Equipamento: %.2f (Euros)", vetor[i].valor);
    printf("\nQuantidade de Avarias: %d", vetor[i].avarias);
    printf("\nQuantidade de Requisições: %d", vetor[i].numRequisicoesDoPc);
    printf("\nQuantidade Total de Dias Requisitado: %d", vetor[i].diasRequisitado);
}


void listaPortateis(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes)
{
    int i, x, cont;

    printf("\n\nLista dos Portáteis Existentes\n");
    for(i=0; i<numPortateis; i++)
    {
        listaPortatil(vetor, i);
        if (vetor[i].numRequisicoesDoPc > 0)
        {
            printf("\n\nInformação das requisições:");
            cont = 1;
            for(x=0; x<totalRequisicoes; x++)
            {
                if (requisicoes[x].numero_id == vetor[i].numero_id)
                {
                    printf("\n\nRequisição %d", cont);
                    printf("\nTipo de Utente: %s", requisicoes[x].tipo_utente);
                    printf("\nPrazo da Requisição: %d/%d/%d",requisicoes[x].prazo.dia,requisicoes[x].prazo.mes,requisicoes[x].prazo.ano);
                    cont++;
                }
            }
        }
    }
}


void alteraLocalizacao(tipoPortatil vetor[], int numPortateis)
{
    int numAlterar, pos=-1, resultado;
    char localizacao[MAX_STRING], op='s';

    do
    {
        numAlterar = lerInteiro("\n\nIndique o número do portátil a alterar localização ", 1, 30);
        pos = procuraPortatil(vetor, numPortateis, numAlterar);
        if (pos==-1)
        {
            printf("Número do portátil não existe. Tente novamente!");
        }
    }
    while(pos==-1);

    resultado = strcmp(vetor[pos].estado, "Requisitado");
    if(resultado==0)
    {
        printf("\nEste portátil encontra-se requisitado! Não é possível mudar a sua localização");
    }
    else
    {
        strcpy(localizacao, vetor[pos].localizacao);
        do
        {
            printf("\nNova Localização");
            lerLocal(vetor[pos].localizacao);
            resultado = strcmp(localizacao, vetor[pos].localizacao);
            if(resultado==0)
            {
                op = 'x';
                printf("\nLocalização selecionada é igual à anterior. Pretende continuar? \nDigite 'S' para continuar: ");
                scanf(" %c", &op);
                limpaBufferStdin();
            }
            else
            {
                op='s';
            }
        }
        while(op != 's' && op != 'S');

        printf("\nLocalização alterada com sucesso!");

    }
}


tipoRequisicao *requisitar(tipoRequisicao *requisicoes, int *totalRequisicoes, tipoPortatil vetor[], int numPortateis, int *disponiveis, int *reqAtivas)
{
    tipoRequisicao *pont;
    int i, pos, novaPos, comparacao, numRequisitar, resultado, dif=-1;
    char novoCodigo[MAX_STRING];

    pont = requisicoes;
    novaPos = *totalRequisicoes;

    requisicoes = realloc(requisicoes,(novaPos+1)*sizeof(tipoRequisicao));
    if (requisicoes == NULL)
    {
        printf ("Erro - Impossível inserir requisição");
        requisicoes = pont;
    }
    else
    {
        do
        {
            lerString("\nIndique o código da nova requisição: ", novoCodigo, MAX_STRING);
            comparacao = procuraRequisicao(requisicoes, *totalRequisicoes, novoCodigo);
            if (comparacao!=-1)
            {
                printf("Já existe uma requisição com o código indicado. Tente Novamente!\n");
            }
        }
        while(comparacao!=-1);
        pos = -1;
        strcpy(requisicoes[novaPos].codigo, novoCodigo);
        printf("\n\nLista dos Portáteis Existentes\n");
        for (i=0; i<numPortateis; i++)
        {
            listaPortatil(vetor,i);
        }

        do
        {
            numRequisitar = lerInteiro("\n\n\nIndique o número do portátil a requisitar ", 1, 30);
            pos = procuraPortatil(vetor, numPortateis, numRequisitar);
            if (pos==-1)
            {
                printf("Número do portátil não existe. Tente novamente!");
            }
            else
            {
                resultado = strcmp(vetor[pos].estado, "Disponível");
                if (resultado!=0)
                {
                    printf("Este portátil não está disponível. Tente Novamente!");
                }
            }
        }
        while(pos==-1 || resultado!=0);

        requisicoes[novaPos].numero_id = vetor[pos].numero_id;
        lerString("Indique o nome do utente",requisicoes[novaPos].nome_utente, MAX_STRING);
        lerTipoUtente(requisicoes[novaPos].tipo_utente);
        do
        {
            printf("\nData da Requisição\n");
            requisicoes[novaPos].data_requisicao = lerData();
            dif = calculaDias(vetor[pos].data_aquisicao, requisicoes[novaPos].data_requisicao);
            if (dif == -1)
            {
                printf("\nA data de requisição deveria ser depois da data de aquisição. Tente Novamente!\n");
            }
        }
        while(dif==-1);

        requisicoes[novaPos].prazo = calculaData30(requisicoes[novaPos].data_requisicao);
        strcpy(requisicoes[novaPos].estado_requisicao, "Ativa");
        requisicoes[novaPos].renovacoes = 0;
        requisicoes[novaPos].duracao = 0;
        printf("\nRequisição efetuada com sucesso!");
        printf("\n\nDados da Requisição\n");
        listaPortatil(vetor,pos);
        printf("\n\n\nO prazo de entrega expira no dia %d/%d/%d",requisicoes[novaPos].prazo.dia, requisicoes[novaPos].prazo.mes, requisicoes[novaPos].prazo.ano);
        printf("\nSe o portátil não for entregue dentro do prazo, por cada dia de atraso terá que pagar 10 euros como multa");
        strcpy(vetor[pos].estado, "Requisitado");

        (vetor[pos].numRequisicoesDoPc)++;
        (*totalRequisicoes)++;
        (*disponiveis)--;
        (*reqAtivas)++;
    }
    return requisicoes;
}


void listaDadosRequisicoes(tipoRequisicao *requisicoes, int totalRequisicoes)
{
    int i, resultado;

    for(i=0; i<totalRequisicoes; i++)
    {
        printf("\n\nRequisição: %d", i+1);
        printf("\n\nCódigo da Requisição: %s", requisicoes[i].codigo);
        printf("\nNúmero do Portátil: %d", requisicoes[i].numero_id);
        printf("\nNome do Utente: %s", requisicoes[i].nome_utente);
        printf("\nTipo de Utente: %s", requisicoes[i].tipo_utente);
        printf("\nData da Requisição: %d/%d/%d", requisicoes[i].data_requisicao.dia,requisicoes[i].data_requisicao.mes,requisicoes[i].data_requisicao.ano);
        printf("\nPrazo de Entrega: %d/%d/%d",requisicoes[i].prazo.dia, requisicoes[i].prazo.mes, requisicoes[i].prazo.ano);
        printf("\nEstado: %s", requisicoes[i].estado_requisicao);
        resultado = strcmp(requisicoes[i].estado_requisicao, "Concluída");
        if (resultado==0)
        {
            printf("\nDuração: %d Dias", requisicoes[i].duracao);
            printf("\nLocal de Devolução: %s", requisicoes[i].local_devolucao);
            if(requisicoes[i].multa>0)
            {
                printf("\nForam cobrados %d euros de multa", requisicoes[i].multa);
            }
            else
            {
                printf("\nNão foi cobrada qualquer multa");
            }
        }
    }
}


tipoRequisicao *devolver(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes)
{
    int pos=-1, pos2, resultado, dif, dif2;
    char codigo[MAX_STRING];
    do
    {
        lerString("\nIndique o código da requisição", codigo, MAX_STRING);
        pos = procuraRequisicao(requisicoes,totalRequisicoes, codigo);
        if (pos==-1)
        {
            printf("Não existe nenhuma requisição com o código indicado. Tente Novamente!\n");
        }
        else
        {
            resultado = strcmp(requisicoes[pos].estado_requisicao, "Concluída");
            if (resultado==0)
            {
                printf("Esta requisição já não está ativa. Tente Novamente!\n");
            }
        }
    }
    while(pos==-1 || resultado==0 );

    pos2 = procuraPortatil(vetor, numPortateis, requisicoes[pos].numero_id);

    do
    {
        printf("\n\nData de Devolução\n");
        requisicoes[pos].data_devolucao = lerData();
        dif = calculaDias(requisicoes[pos].data_requisicao, requisicoes[pos].data_devolucao);
        if (dif==-1)
        {
            printf("\nA data de devolução deveria ser depois da data de requisição. Tente Novamente!");
        }
    }
    while(dif==-1);

    printf("\n\nLocal de Devolução\n");
    lerLocal(requisicoes[pos].local_devolucao);
    strcpy(vetor[pos2].localizacao, requisicoes[pos].local_devolucao);

    dif2 = calculaDias(requisicoes[pos].data_requisicao, requisicoes[pos].prazo);

    if (dif > dif2)
    {
        requisicoes[pos].multa = 10*(dif - dif2);
        printf("\n\nDevido aos %d dias de atraso na entrega, serão lhe cobrados %d euros de multa",(dif-dif2),requisicoes[pos].multa);
    }
    else
    {
        requisicoes[pos].multa = 0;
        printf("\n\nRequisição entregue dentro do prazo");
    }
    requisicoes[pos].duracao = dif;
    vetor[pos2].diasRequisitado += dif;
    strcpy(vetor[pos2].estado, "Disponível");
    strcpy(requisicoes[pos].estado_requisicao, "Concluída");
    gravaFicheiroTexto(requisicoes, pos, vetor, pos2);

    return requisicoes;
}


tipoRequisicao *renovar(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes, int *disponiveis, int *reqAtivas)
{
    int resultado, pos=-1, pos2, dif, dif2;
    char codigoRenovar[MAX_STRING];
    tipoData renovacao;

    do
    {
        lerString("\nIndique o código da requisição a renovar", codigoRenovar, MAX_STRING);
        pos = procuraRequisicao(requisicoes, totalRequisicoes, codigoRenovar);
        if (pos==-1)
        {
            printf("Não existe nenhuma requisição com o código indicado. Tente Novamente!\n");
        }
        else
        {
            resultado = strcmp(requisicoes[pos].estado_requisicao, "Concluída");
            if (resultado==0)
            {
                printf("Esta requisição já não está ativa. Tente Novamente!\n");
            }
        }
    }
    while(pos==-1 || resultado==0);

    do
    {
        printf("\n\nData de Renovação\n");
        renovacao = lerData();
        dif = calculaDias(requisicoes[pos].data_requisicao, renovacao);
        if (dif==-1)
        {
            printf("\nA data de renovação deveria ser depois da data de requisição. Tente Novamente!");
        }
    }
    while(dif==-1);

    if (dif >(30 + (7*requisicoes[pos].renovacoes)))
    {
        pos2 = procuraPortatil(vetor, numPortateis, requisicoes[pos].numero_id);
        printf("\n\nRenovação fora do prazo! O portátil foi devolvido e terá que pagar multa!");
        requisicoes[pos].data_devolucao = renovacao;
        printf("\n\n\nLocal de Devolução\n");
        lerLocal(requisicoes[pos].local_devolucao);
        strcpy(vetor[pos2].localizacao, requisicoes[pos].local_devolucao);
        requisicoes[pos].duracao = dif;
        vetor[pos2].diasRequisitado += dif;
        dif2 = calculaDias(requisicoes[pos].data_requisicao, requisicoes[pos].prazo);
        requisicoes[pos].multa = 10*(dif - dif2);
        printf("\nDevido aos %d dias de atraso na entrega, serão lhe cobrados %d euros de multa",(dif-dif2),requisicoes[pos].multa);
        strcpy(requisicoes[pos].estado_requisicao, "Concluída");
        strcpy(vetor[pos2].estado, "Disponível");
        (*disponiveis)++;
        (*reqAtivas)--;
        gravaFicheiroTexto(requisicoes, pos, vetor, pos2);
        printf("\nCaso pretenda continuar com o portátil, terá de efetuar uma nova requisição");
    }
    else
    {
        requisicoes[pos].prazo = calculaData7(requisicoes[pos].prazo);
        printf("\n\n\nO novo prazo de entrega expira no dia %d/%d/%d",requisicoes[pos].prazo.dia, requisicoes[pos].prazo.mes, requisicoes[pos].prazo.ano);
        requisicoes[pos].renovacoes++;
    }

    return requisicoes;
}


tipoAvaria *registarAvaria(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes, tipoAvaria *avarias, int *totalAvarias, int *disponiveis, int *reqAtivas)
{
    int i, pos, pos2, nrPortatil, resultado, dif=-1, dif2;
    tipoAvaria *pont;


    printf("\n\nLista dos Portáteis Existentes\n");
    for (i=0; i<numPortateis; i++)
    {
        listaPortatil(vetor,i);
    }

    do
    {
        nrPortatil = lerInteiro("\n\nIndique o número do portátil a registar avaria ", 1, 30);
        pos = procuraPortatil(vetor, numPortateis, nrPortatil);
        if (pos==-1)
        {
            printf("Número do portátil não existe. Tente novamente!");
        }
    }
    while(pos==-1);

    resultado = strcmp(vetor[pos].estado, "Avariado");
    if (resultado==0)
    {
        printf("\nErro! O registo da avaria deste portátil já foi efetuado");
    }
    else
    {
        pont = avarias;

        avarias = realloc(avarias,(*totalAvarias+1)*sizeof(tipoAvaria));
        if (avarias == NULL)
        {
            printf ("\nErro - Impossível inserir avaria");
            avarias = pont;
        }
        else
        {
            avarias[*totalAvarias].numero_id = vetor[pos].numero_id;
            lerTipoAvaria(avarias[*totalAvarias].tipo_avaria);

            resultado = strcmp(vetor[pos].estado, "Disponível");
            if (resultado==0)
            {
                do
                {
                    printf("\nData de Avaria");
                    avarias[*totalAvarias].data_avaria = lerData();
                    dif = calculaDias(vetor[pos].data_aquisicao, avarias[*totalAvarias].data_avaria);
                    if (dif == -1)
                    {
                        printf("\nA data de avaria deveria ser depois da data de aquisição. Tente Novamente!\n");
                    }
                }
                while(dif==-1);
                (*disponiveis)--;
            }
            else
            {
                printf("\n\nComo o portátil se encontra requisitado será necessário efetuar a devolução\n");
                pos2 = procuraRequisicaoAtiva(requisicoes, totalRequisicoes, nrPortatil);

                do
                {
                    printf("\nData de Avaria");
                    avarias[*totalAvarias].data_avaria = lerData();
                    dif = calculaDias(requisicoes[pos2].data_requisicao, avarias[*totalAvarias].data_avaria);
                    if (dif == -1)
                    {
                        printf("\nA data de avaria deveria ser depois da data de requisição. Tente Novamente!\n");
                    }
                }
                while(dif==-1);
                requisicoes[pos2].data_devolucao = avarias[*totalAvarias].data_avaria;
                printf("\n\nLocal de Devolução\n");
                lerLocal(requisicoes[pos2].local_devolucao);
                strcpy(vetor[pos].localizacao, requisicoes[pos2].local_devolucao);
                dif = calculaDias(requisicoes[pos2].data_requisicao, requisicoes[pos2].data_devolucao);
                requisicoes[pos2].duracao = dif;
                vetor[pos].diasRequisitado += dif;
                if (dif >(30 + (7*requisicoes[pos].renovacoes)))
                {
                    dif2 = calculaDias(requisicoes[pos2].data_requisicao, requisicoes[pos2].prazo);
                    requisicoes[pos2].multa = 10*(dif - dif2);
                    printf("\nDevido aos %d dias de atraso na entrega, serão lhe cobrados %d euros de multa",(dif-dif2),requisicoes[pos2].multa);
                }
                (*reqAtivas)--;
                strcpy(requisicoes[pos2].estado_requisicao, "Concluída");
                gravaFicheiroTexto(requisicoes, pos2, vetor, pos);
            }
            strcpy(vetor[pos].estado, "Avariado");
            avarias[*totalAvarias].tempo_avaria = 0;
            vetor[pos].avarias++;
            (*totalAvarias)++;
            printf("\n\nAvaria registada com sucesso!");
        }
    }

    return avarias;
}


tipoAvaria *registarReparacao(tipoAvaria *avarias, int totalAvarias, tipoPortatil vetor[], int numPortateis, int *disponiveis)
{
    int nrPortatil, resultado, pos=-1, pos2=-1, dif, i;
    tipoData dataReparacao;

    printf("\n\nLista dos Portáteis Existentes\n");
    for (i=0; i<numPortateis; i++)
    {
        listaPortatil(vetor,i);
    }

    do
    {
        nrPortatil = lerInteiro("\n\nIndique o número do portátil a registar reparação ", 1, 30);
        pos = procuraPortatil(vetor, numPortateis, nrPortatil);
        if (pos==-1)
        {
            printf("Número do portátil não existe. Tente novamente!");
        }
    }
    while(pos==-1);

    resultado = strcmp(vetor[pos].estado, "Avariado");
    if (resultado!=0)
    {
        printf("\nErro! Este portátil não se encontra avariado");
    }
    else
    {
        pos2 = procuraAvariaAtiva(avarias, totalAvarias, nrPortatil);
        if (pos2==-1)
        {
            printf("\nErro! A avaria deste portátil é permanente, logo não pode ser reparado");
        }
        else
        {
            do
            {
                printf("\n\nData de Reparação\n");
                dataReparacao = lerData();
                dif = calculaDias(avarias[pos2].data_avaria, dataReparacao);
                if (dif==-1)
                {
                    printf("\nA data de reparação deveria ser depois da data de avaria. Tente Novamente!");
                }
            }
            while(dif==-1);
            avarias[pos2].tempo_avaria = dif;
            strcpy(vetor[pos].estado, "Disponível");
            (*disponiveis)++;
            printf("\n\nReparação registada com sucesso!");
        }
    }

    return avarias;
}


void mostrarInfoRequisicao(tipoRequisicao *requisicoes, int totalRequisicoes, tipoPortatil vetor[], int numPortateis)
{
    int pos, pos2, resultado;
    char codigo[MAX_STRING];

    pos = totalRequisicoes;
    do
    {
        lerString("\nIndique o código da requisição ", codigo, MAX_STRING);
        pos = procuraRequisicao(requisicoes, totalRequisicoes, codigo);
        if (pos==-1)
        {
            printf("Não existe nenhuma requisição com o código indicado. Tente Novamente!\n");
        }
    }
    while(pos==-1);

    pos2 = procuraPortatil(vetor, numPortateis, requisicoes[pos].numero_id);

    printf("\n\nInformação da Requisição");
    printf("\n\nCódigo da Requisição: %s", requisicoes[pos].codigo);
    printf("\nDesignação do Portátil: %s", vetor[pos2].designacao);
    printf("\nNúmero do Portátil: %d", requisicoes[pos].numero_id);
    printf("\nNome do Utente: %s", requisicoes[pos].nome_utente);
    printf("\nTipo de Utente: %s", requisicoes[pos].tipo_utente);
    printf("\nData da Requisição: %d/%d/%d", requisicoes[pos].data_requisicao.dia,requisicoes[pos].data_requisicao.mes,requisicoes[pos].data_requisicao.ano);
    printf("\nPrazo de Entrega: %d/%d/%d",requisicoes[pos].prazo.dia,requisicoes[pos].prazo.mes,requisicoes[pos].prazo.ano);
    printf("\nEstado da Requisição: %s", requisicoes[pos].estado_requisicao);
    printf("\nEstado do Portátil: %s",vetor[pos2].estado);
    printf("\nQuantidade Total de Dias Requisitado: %d", vetor[pos2].diasRequisitado);
    resultado = strcmp(requisicoes[pos].estado_requisicao, "Concluída");
    if (resultado==0)
    {
        printf("\nDuração da Requisição: %d Dias", requisicoes[pos].duracao);
        printf("\nLocal de Devolução: %s", requisicoes[pos].local_devolucao);
        if(requisicoes[pos].multa>0)
        {
            printf("\nForam cobrados %d euros de multa", requisicoes[pos].multa);
        }
        else
        {
            printf("\nNão foi cobrada qualquer multa");
        }
    }
}


void mostraDadosEstatisticos(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes)
{
    int i, somaI3=0, somaI5=0, somaI7=0;
    int estudantes=0, docentes=0, tecnicosAdmin=0, menor=0;
    int resultado=0, somaMultas=0, totalMultas=0, dif=0;
    float percI3=0.0, percI5=0.0, percI7=0.0, mediaMultas=0.0;
    tipoData maisRecente;

    maisRecente.dia = 0;
    maisRecente.mes = 0;
    maisRecente.ano = 0;

    printf("\n\nDados Estatísticos:");
    for(i=0; i<numPortateis; i++)
    {
        if(vetor[i].processador==3)
        {
            somaI3++;
        }
        else
        {
            if(vetor[i].processador==5)
            {
                somaI5++;
            }
            else
            {
                somaI7++;
            }
        }
    }
    percI3 = ((float)somaI3/numPortateis)*100;
    percI5 = ((float)somaI5/numPortateis)*100;
    percI7 = ((float)somaI7/numPortateis)*100;
    printf("\n\n%.2f %% dos processadores são i3", percI3);
    printf("\n%.2f %% dos processadores são i5", percI5);
    printf("\n%.2f %% dos processadores são i7", percI7);

    if(totalRequisicoes>0)
    {
        for(i=0; i<totalRequisicoes; i++)
        {
            resultado = strcmp(requisicoes[i].estado_requisicao, "Concluída");
            if(resultado==0 && requisicoes[i].multa != 0)
            {
                somaMultas += requisicoes[i].multa;
                totalMultas ++;
            }
        }
        if (totalMultas>0)
        {
            mediaMultas = (float)somaMultas/totalMultas;
            printf("\n\nO custo médio de cada multa paga foi de %.2f euros", mediaMultas);
        }
        else
        {
            printf("\n\nNão foi cobrada qualquer multa para apresentar média");
        }


        for(i=0; i<totalRequisicoes; i++)
        {
            resultado = strcmp(requisicoes[i].tipo_utente, "Estudante");
            if(resultado==0)
            {
                estudantes++;
            }
            else
            {
                resultado = strcmp(requisicoes[i].tipo_utente, "Docente");
                if(resultado==0)
                {
                    docentes++;
                }
                else
                {
                    tecnicosAdmin++;
                }
            }
        }
        menor = estudantes;
        if (docentes<menor)
        {
            menor = docentes;
            if(tecnicosAdmin<menor)
            {
              menor = tecnicosAdmin;
            }
        }
        else
        {
            if(tecnicosAdmin<menor)
            {
              menor = tecnicosAdmin;
            }
        }

        if (menor==estudantes)
        {
            if (estudantes==docentes)
            {
                if(estudantes==tecnicosAdmin)
                {
                    printf("\nTodos os tipos de utentes requisitaram portáteis com a mesma frequência");
                }
                else
                {
                    printf("\nOs tipos de utentes com a menor quantidade de requisições são os Estudantes e Docentes");
                }
            }
            else
            {
                if(estudantes==tecnicosAdmin)
                {
                    printf("\nOs tipos de utentes com a menor quantidade de requisições são os Estudantes e Técnicos Administrativos");
                }
                else
                {
                    printf("\nO tipo de utentes com a menor quantidade de requisições são os Estudantes");
                }
            }
        }
        else
        {
            if(menor==docentes)
            {
                if(docentes==tecnicosAdmin)
                {
                    printf("\nOs tipos de utentes com a menor quantidade de requisições são os Docentes e Técnicos Administrativos");
                }
                else
                {
                    printf("\nO tipo de utentes com a menor quantidade de requisições são os Docentes");
                }
            }
            else
            {
                printf("\nOs tipos de utentes com a menor quantidade de requisições são os Técnicos Administrativos");
            }
        }

        printf("\n\nDevolução(ões) Mais Recente(s)");
        for(i=0; i<totalRequisicoes; i++)
        {
            resultado = strcmp(requisicoes[i].estado_requisicao, "Concluída");
            if (resultado==0)
            {
                dif = calculaDias(maisRecente, requisicoes[i].data_devolucao);
                if (dif!=-1)
                {
                    maisRecente = requisicoes[i].data_devolucao;
                }
            }
        }
        for(i=0; i<totalRequisicoes; i++)
        {
            resultado = strcmp(requisicoes[i].estado_requisicao, "Concluída");
            if (resultado==0)
            {
                dif = calculaDias(maisRecente, requisicoes[i].data_devolucao);
                if (dif==0)
                {
                    printf("\n\nCódigo da Requisição: %s", requisicoes[i].codigo);
                    printf("\nNúmero do Portátil: %d", requisicoes[i].numero_id);
                    printf("\nNome do Utente: %s", requisicoes[i].nome_utente);
                    printf("\nTipo de Utente: %s", requisicoes[i].tipo_utente);
                    printf("\nData da Requisição: %d/%d/%d", requisicoes[i].data_requisicao.dia,requisicoes[i].data_requisicao.mes,requisicoes[i].data_requisicao.ano);
                    printf("\nPrazo de Entrega: %d/%d/%d",requisicoes[i].prazo.dia,requisicoes[i].prazo.mes,requisicoes[i].prazo.ano);
                    printf("\nEstado da Requisição: %s", requisicoes[i].estado_requisicao);
                    resultado = strcmp(requisicoes[i].estado_requisicao, "Concluída");
                    if (resultado==0)
                    {
                        printf("\nDuração da Requisição: %d Dias", requisicoes[i].duracao);
                        printf("\nLocal de Devolução: %s", requisicoes[i].local_devolucao);
                        if(requisicoes[i].multa>0)
                        {
                            printf("\nForam cobrados %d euros de multa", requisicoes[i].multa);
                        }
                        else
                        {
                            printf("\nNão foi cobrada qualquer multa");
                        }
                    }
                }
            }
        }
    }
    else
    {
        printf("\n\nNão existem requisições para mostrar dados estatísticos");
    }
}


void apresentarAvarias(tipoAvaria *avarias, int num_avarias, tipoPortatil vetor[], int numPortateis)
{
    int i, pos, resultado;

    for (i=0; i<num_avarias; i++)
    {
        pos = procuraPortatil(vetor, numPortateis, avarias[i].numero_id);
        listaPortatil(vetor, pos);
        printf("\n\nTipo de avaria: %s", avarias[i].tipo_avaria);
        printf("\nData da avaria: %d/%d/%d\n", avarias[i].data_avaria.dia, avarias[i].data_avaria.mes, avarias[i].data_avaria.ano);
        resultado = strcmp(avarias[i].tipo_avaria, "Permanente");
        if (resultado==0)
        {
            printf("Tempo de avaria: Permanente");
        }
        else
        {
            printf("Tempo de avaria: %d dias", avarias[i].tempo_avaria);
        }
    }
}

//Ficheiros

tipoRequisicao *lerFicheiroBinario(tipoPortatil vetor[], int *numPortateis, int *disponiveis, tipoRequisicao *requisicoes, int *totalRequisicoes, int *reqAtivas)
{
    FILE *f;
    int lido, erro;

    f=fopen("ficheiro.dat", "rb");
    if (f == NULL)
    {
        printf("\n\nErro ao abrir ficheiro!");
    }
    else
    {
        lido = fread(&(*numPortateis), sizeof(int), 1, f);
        if(lido!=1)
        {
            printf("\nErro na leitura da quantidade de portáteis!");
        }
        else
        {
            lido = fread(vetor, sizeof(tipoPortatil),(*numPortateis), f);
            if(lido != *numPortateis)
            {
                printf("\nErro na leitura da informação referente aos portáteis!");
            }
        }
        lido = fread(&(*totalRequisicoes), sizeof(int), 1, f);
        if(lido!=1)
        {
            printf("\nErro na leitura da quantidade de requisições!");
        }
        else
        {
            requisicoes = realloc(requisicoes, (*totalRequisicoes)*sizeof(tipoRequisicao));
            if (requisicoes == NULL && *totalRequisicoes != 0)
            {
                printf ("\nErro ao reservar memória!");
                (*totalRequisicoes) = 0;
            }
            else
            {
                lido = fread(requisicoes, sizeof(tipoRequisicao),(*totalRequisicoes), f);
                if(lido != *totalRequisicoes)
                {
                    printf("\nErro na leitura da informação referente às requisições!");
                }
            }
        }
        lido = fread(&(*disponiveis), sizeof(int), 1, f);
        if(lido!=1)
        {
            printf("\nErro na leitura da quantidade de portáteis disponíveis!");
        }
        lido = fread(&(*reqAtivas), sizeof(int), 1, f);
        if(lido!=1)
        {
            printf("\nErro na leitura da quantidade de requisições ativas!");
        }
        erro = fclose(f);
        if (erro != 0)
        {
            printf ("Erro %d no fecho do ficheiro", erro);
        }
    }

    return requisicoes;
}


tipoAvaria *lerFicheiroBinario2(tipoAvaria *avarias, int *totalAvarias)
{
    FILE *f;
    int lido, erro;

    f=fopen("avarias.dat", "rb");
    if (f == NULL)
    {
        printf("\n\nErro ao abrir ficheiro!");
    }
    else
    {
        lido = fread(&(*totalAvarias), sizeof(int), 1, f);
        if(lido!=1)
        {
            printf("\nErro na leitura da quantidade de avarias!");
        }
        else
        {
            avarias = realloc(avarias, (*totalAvarias)*sizeof(tipoAvaria));
            if (avarias == NULL && *totalAvarias != 0)
            {
                printf ("\nErro ao reservar memória!");
                (*totalAvarias) = 0;
            }
            else
            {
                lido = fread(avarias, sizeof(tipoAvaria),(*totalAvarias), f);
                if(lido != *totalAvarias)
                {
                    printf("\nErro na leitura da informação referente às avarias!");
                }
            }
        }
        erro = fclose(f);
        if (erro != 0)
        {
            printf ("Erro %d no fecho do ficheiro", erro);
        }
    }

    return avarias;
}


void gravaFicheiroBinario(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes, int disponiveis, int reqAtivas)
{
    FILE *f;
    int gravado, erro;

    f=fopen("ficheiro.dat", "wb");
    if (f == NULL)
    {
        printf("\n\nErro ao abrir ficheiro!");
    }
    else
    {
        gravado = fwrite(&numPortateis, sizeof(int), 1, f);
        if(gravado!=1)
        {
            printf("\nErro na escrita da quantidade de portáteis!");
        }
        else
        {
            gravado=fwrite(vetor, sizeof(tipoPortatil), numPortateis, f);
            if(gravado!=numPortateis)
            {
                printf("\nErro na escrita da informação referente aos portáteis!");
            }
        }
        gravado = fwrite(&totalRequisicoes, sizeof(int), 1, f);
        if(gravado!=1)
        {
            printf("\nErro na escrita da quantidade de requisições!");
        }
        else
        {
            gravado = fwrite(requisicoes, sizeof(tipoRequisicao), totalRequisicoes, f);
            if(gravado!=totalRequisicoes)
            {
                printf("\nErro na escrita da informação referente às requisições!");
            }

        }
        gravado = fwrite(&disponiveis, sizeof(int), 1, f);
        if(gravado!=1)
        {
            printf("\nErro na escrita da quantidade de portáteis disponíveis!");
        }
        gravado = fwrite(&reqAtivas, sizeof(int), 1, f);
        if(gravado!=1)
        {
            printf("\nErro na escrita da quantidade de portáteis disponíveis!");
        }

        erro = fclose(f);
        if (erro != 0)
        {
            printf ("Erro %d no fecho do ficheiro", erro);
        }
    }
}


void gravaFicheiroBinario2 (tipoAvaria *avarias, int totalAvarias)
{
    FILE *f;
    int gravado, erro;

    f=fopen("avarias.dat", "wb");
    if (f == NULL)
    {
        printf("\n\nErro ao abrir ficheiro!");
    }
    else
    {
        gravado = fwrite(&totalAvarias, sizeof(int), 1, f);
        if(gravado!=1)
        {
            printf("\nErro na escrita da quantidade de avarias!");
        }
        else
        {
            gravado = fwrite(avarias, sizeof(tipoAvaria), totalAvarias, f);
            if(gravado!=totalAvarias)
            {
                printf("\nErro na escrita da informação referente às avarias!");
            }
        }

        erro = fclose(f);
        if (erro != 0)
        {
            printf ("Erro %d no fecho do ficheiro", erro);
        }
    }

}


void gravaFicheiroTexto(tipoRequisicao *requisicoes, int pos, tipoPortatil vetor[], int pos2)
{
    FILE *f;
    int erro;

    f=fopen("log.txt", "a");
    if (f == NULL)
    {
        printf("\n\nErro ao abrir ficheiro!");
    }
    else
    {
        fprintf(f,"\n\nCódigo: %s",requisicoes[pos].codigo);
        fprintf(f,"\nNúmero de identificação: %d",requisicoes[pos].numero_id);
        fprintf(f,"\nProcessador: i%d", vetor[pos2].processador);
        fprintf(f,"\nRAM: %d GB", vetor[pos2].RAM);
        fprintf(f,"\nNome do Utente: %s",requisicoes[pos].nome_utente);
        fprintf(f,"\nTipo de Utente: %s",requisicoes[pos].tipo_utente);
        fprintf(f,"\nData da Requisição: %d/%d/%d",requisicoes[pos].data_requisicao.dia,requisicoes[pos].data_requisicao.mes,requisicoes[pos].data_requisicao.ano);
        fprintf(f,"\nPrazo de Entrega: %d/%d/%d",requisicoes[pos].prazo.dia, requisicoes[pos].prazo.mes, requisicoes[pos].prazo.ano);
        fprintf(f,"\nEstado: %s",requisicoes[pos].estado_requisicao);
        fprintf(f,"\nData da Devolução: %d/%d/%d", requisicoes[pos].data_devolucao.dia,requisicoes[pos].data_devolucao.mes,requisicoes[pos].data_devolucao.ano);
        fprintf(f,"\nLocal de Devolução: %s", requisicoes[pos].local_devolucao);
        fprintf(f,"\nMulta: %d", requisicoes[pos].multa);
        fprintf(f,"\nRenovações: %d", requisicoes[pos].renovacoes);
        fprintf(f,"\nDuração: %d Dias\n\n", requisicoes[pos].duracao);

        erro = fclose(f);
        if (erro != 0)
        {
            printf ("Erro %d no fecho do ficheiro", erro);
        }
    }
}
