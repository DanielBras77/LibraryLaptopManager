#include <stdio.h>
#include <string.h>

#include "funcoesAuxiliares.h"


tipoData calculaData7(tipoData d)
{
    int meses[12]  = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(d.dia>24)
    {
        if (d.mes==12)
        {
            d.dia -= 24;
            d.mes = 1;
            d.ano += 1;
        }
        else
        {
            if(meses[d.mes-1]==31)
            {
                d.dia -= 24;
                d.mes += 1;
            }
            else
            {
                if(meses[d.mes-1]==28)
                {
                    if(bissexto(d.ano)==1)
                    {
                        d.dia -= 22;
                        d.mes += 1;
                    }
                    else
                    {
                        d.dia -= 21;
                        d.mes += 1;
                    }
                }
                else
                {
                    d.dia -= 23;
                    d.mes += 1;
                }
            }
        }
    }
    else
    {
       d.dia += 7;
    }

    return d;
}


tipoData calculaData30(tipoData d)
{
    int meses[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if(meses[d.mes-1]==31)
    {
        if (d.dia>1)
        {
            d.dia -= 1;
            if(d.mes==12)
            {
                d.mes = 1;
                d.ano += 1;
            }
            else
            {
                d.mes += 1;
            }
        }
        else
        {
            d.dia = 31;
        }
    }
    else
    {
        if(meses[d.mes-1]==28)
        {
            if(bissexto(d.ano)==1)
            {
                d.dia += 1;
            }
            else
            {
                d.dia += 2;
            }
        }
        d.mes++;
    }

    return d;
}


int bissexto(int ano)
{
    if (((ano % 4 == 0) && (ano % 100!= 0)) || (ano%400 == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int calculaDias(tipoData d1, tipoData d2)
{
    int meses[12]  = {31,28,31,30,31,30,31,31,30,31,30,31};
    int diferenca=0;

    if (d2.ano > d1.ano)
    {
        if(d1.mes==2)
        {
            if(bissexto(d1.ano)==1)
            {
                diferenca += 29 - d1.dia;
            }
            else
            {
                diferenca += 28 - d1.dia;
            }
        }
        else
        {
            diferenca = meses[d1.mes-1] - d1.dia;
        }
        d1.mes++;

        for(int i=d1.mes; i<=12; i++)
        {
            if(i==2)
            {
                if(bissexto(d1.ano)==1)
                {
                    diferenca += 29;
                }
                else
                {
                    diferenca += 28;
                }
            }
            else
            {
                diferenca += meses[i-1];
            }
        }
        d1.ano++;


        for(int i=d1.ano; i<d2.ano; i++)
        {
            if(bissexto(i)==1)
            {
                diferenca += 366;
            }
            else
            {
                diferenca += 365;
            }
        }
        for(int i=1; i<d2.mes; i++)
        {
            if(i==2)
            {
                if(bissexto(d2.ano)==1)
                {
                    diferenca += 29;
                }
                else
                {
                    diferenca += 28;
                }
            }
            else
            {
                diferenca += meses[i-1];
            }
        }

        diferenca += d2.dia;
    }
    else
    {
        if (d2.ano == d1.ano)
        {
            if(d2.mes>d1.mes)
            {
                if(d1.mes==2)
                {
                    if(bissexto(d1.ano)==1)
                    {

                        diferenca += 29 - d1.dia;
                    }
                    else
                    {
                        diferenca += 28 - d1.dia;
                    }
                }
                else
                {
                    diferenca = meses[d1.mes-1] - d1.dia;
                }
                d1.mes++;
                for(int i=d1.mes; i<d2.mes; i++)
                {
                    if(i==2)
                    {
                        if(bissexto(d1.ano)==1)
                        {
                            diferenca += 29;
                        }
                        else
                        {
                            diferenca += 28;
                        }
                    }
                    else
                    {
                        diferenca += meses[i-1];
                    }
                }
                diferenca += d2.dia;
            }
            else
            {
                if(d2.mes==d1.mes)
                {
                    if(d2.dia>d1.dia)
                    {
                        diferenca =  d2.dia - d1.dia;
                    }
                    else
                    {
                        if(d2.dia==d1.dia)
                        {
                            diferenca = 0;
                        }
                        else
                        {
                            diferenca = -1;
                        }
                    }
                }
                else
                {
                    diferenca = -1;
                }
            }
        }
        else
        {
            diferenca = -1;
        }
    }

    return diferenca;
}


tipoData lerData(void)
{
    tipoData nova;
    int limite;
    nova.ano = lerInteiro("\nIndique o ano ", 2000, 2023);
    nova.mes = lerInteiro("Indique o mês ", 1, 12);

    switch(nova.mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        limite = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        limite = 30;
        break;
    case 2:
        if (((nova.ano % 4 == 0) && (nova.ano % 100!= 0)) || (nova.ano%400 == 0))
        {
            limite = 29;
        }
        else
        {
            limite = 28;
        }
    }
    nova.dia = lerInteiro("Indique o dia ", 1, limite);

    return nova;
}


int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo)
{
    int numero, controlo;
    do
    {
        printf("%s (%d a %d) : ", mensagem, minimo, maximo);
        controlo = scanf ("%d", &numero);
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Erro! Deveria inserir um número inteiro \n");
        }
        else
        {
            if(numero<minimo || numero>maximo)
            {
                printf("Número inválido. Insira novamente!\n");
            }
        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}


float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo)
{
    float numero;
    int controlo;
    do
    {
        printf("%s (%.2f a %.2f) : ", mensagem, minimo, maximo);
        controlo = scanf ("%f", &numero);
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Erro! Devera inserir um número decimal (float) \n");
        }
        else
        {
            if(numero<minimo || numero>maximo)
            {
                printf("Número inválido. Insira novamente!\n");
            }
        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}


void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres)
{
    int tamanhoString;

    do
    {
        printf("%s: ", mensagem);
        fgets(vetorCaracteres, maximoCaracteres, stdin);

        tamanhoString = strlen(vetorCaracteres);

        if (tamanhoString == 1)
        {
            printf("Erro! Não foram introduzidos caracteres! Apenas clicou na tecla ENTER \n\n");
        }

    }
    while (tamanhoString == 1);

    if(vetorCaracteres[tamanhoString-1] != '\n')
    {
        limpaBufferStdin();
    }
    else
    {
        vetorCaracteres[tamanhoString-1] = '\0';
    }

}


void limpaBufferStdin(void)
{
    char chr;
    do
    {
        chr = getchar();
    }
    while (chr != '\n' && chr != EOF);
}
