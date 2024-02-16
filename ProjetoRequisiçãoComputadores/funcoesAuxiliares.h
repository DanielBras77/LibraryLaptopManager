#ifndef FUNCOESAUXILIARES_H_INCLUDED
#define FUNCOESAUXILIARES_H_INCLUDED

typedef struct
{
    int dia, mes, ano;
} tipoData;

#include "funcoesPrincipal.h"

tipoData calculaData7(tipoData d);
tipoData calculaData30(tipoData d);
int bissexto(int ano);
int calculaDias(tipoData d1, tipoData d2);
tipoData lerData(void);
int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo);
float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo);
void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres);
void limpaBufferStdin(void);


#endif // FUNCOESAUXILIARES_H_INCLUDED
