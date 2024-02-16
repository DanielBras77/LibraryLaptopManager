#ifndef FUNCOESPRINCIPAL_H_INCLUDED
#define FUNCOESPRINCIPAL_H_INCLUDED


#define PORTATEIS 30
#define MAX_STRING 20

#include "funcoesAuxiliares.h"


typedef struct {
    char codigo[MAX_STRING];
    int numero_id;
    char nome_utente[MAX_STRING];
    char tipo_utente[30];
    tipoData data_requisicao;
    tipoData prazo;
    char estado_requisicao[MAX_STRING];
    tipoData data_devolucao;
    char local_devolucao[MAX_STRING];
    int multa;
    int renovacoes;
    int duracao;
} tipoRequisicao;


typedef struct {
    int numero_id;
    char designacao[MAX_STRING];
    int processador;
    int RAM;
    char estado[MAX_STRING];
    char localizacao[MAX_STRING];
    tipoData data_aquisicao;
    float valor;
    int avarias;
    int numRequisicoesDoPc;
    int diasRequisitado;
} tipoPortatil;


typedef struct {
    int numero_id;
    char tipo_avaria[MAX_STRING];
    tipoData data_avaria;
    int tempo_avaria;
} tipoAvaria;


//Menu
char menu(int existentes, int disponiveis, int total_requisicoes, int requisicoes_ativas);
//Funções de Pesquisa ou Inserção de Dados
int procuraPortatil(tipoPortatil vetor[], int numPortateis, int numDeProcura);
int procuraRequisicao(tipoRequisicao *requisicoes, int totalRequisicoes, char codigoDeProcura[MAX_STRING]);
int procuraRequisicaoAtiva(tipoRequisicao *requisicoes, int totalRequisicoes, int nrPortatil);
int procuraAvariaAtiva(tipoAvaria *avarias, int totalAvarias, int numDeProcura);
int lerProcessador(void);
void lerTipoUtente(char vetor[]);
void lerEstado(char vetor[]);
void lerLocal(char vetor[]);
void lerTipoAvaria(char vetor[]);
//Funcões Principais
int inserirInfoPortatil(tipoPortatil vetor[], int num, int *disponiveis);
void listaPortatil(tipoPortatil vetor[], int i);
void listaPortateis(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes);
void alteraLocalizacao(tipoPortatil vetor[], int numPortateis);
tipoRequisicao *requisitar(tipoRequisicao *requisicoes, int *totalRequisicoes, tipoPortatil vetor[], int numPortateis, int *disponiveis, int *reqAtivas);
void listaDadosRequisicoes(tipoRequisicao *requisicoes, int totalRequisicoes);
tipoRequisicao *devolver(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes);
tipoRequisicao *renovar(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes, int *disponiveis, int *reqAtivas);
tipoAvaria *registarAvaria(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes, tipoAvaria *avarias, int *totalAvarias, int *disponiveis, int *reqAtivas);
tipoAvaria *registarReparacao(tipoAvaria *avarias, int totalAvarias, tipoPortatil vetor[], int numPortateis, int *disponiveis);
void mostrarInfoRequisicao(tipoRequisicao *requisicoes, int totalRequisicoes, tipoPortatil vetor[], int numPortateis);
void mostraDadosEstatisticos(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes);
void apresentarAvarias(tipoAvaria *avarias, int num_avarias, tipoPortatil vetor[], int numPortateis);
//Ficheiros
tipoRequisicao *lerFicheiroBinario(tipoPortatil vetor[], int *numPortateis, int *disponiveis, tipoRequisicao *requisicoes, int *totalRequisicoes, int *reqAtivas);
tipoAvaria *lerFicheiroBinario2(tipoAvaria *avarias, int *totalAvarias);
void gravaFicheiroBinario(tipoPortatil vetor[], int numPortateis, tipoRequisicao *requisicoes, int totalRequisicoes, int disponiveis, int reqAtivas);
void gravaFicheiroBinario2 (tipoAvaria *avarias, int totalAvarias);
void gravaFicheiroTexto(tipoRequisicao *requisicoes, int pos, tipoPortatil vetor[], int pos2);

#endif // FUNCOESPRINCIPAL_H_INCLUDED
