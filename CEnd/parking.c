#include <stdio.h>
#include <string.h>
#include <time.h>
int piso,linha,coluna;
int size_historico;
//STRUCT CARRO
typedef struct carro{
//ALO
//MATRICULA
char matricula[9];
//TIPO VIATURA(0 - Deficientes, 1 - Carro, 2 - Caravanas, 3- Autocarro&Camioes, 4 - Helicopteros)
int tipo_de_veiculo;
//nmr lavagens
int n_lavagens;
//pagamento
float pagamento;
}car;

typedef struct data_entrada{
    //DATA CHEGADA
 int year_chegada;
 int month_chegada;
 int day_chegada;
 int hours_chegada;
 int minutes_chegada;
 int secounds_chegada;

}data_entrada;

typedef struct data_saida{
 //DATA SAIDA
 int year_saida;
 int month_saida;
 int day_saida;
 int hours_saida;
 int minutes_saida;
 int secounds_saida;

}data_saida;

//OBJETO PARKING QUE VAI SER ARMAZENADO NUM ARRAY TRIDIMENCIONAL
typedef struct parking
{
//CARRO
 car veiculo;
 //DATA ENTRADA
 data_entrada entrada;
 //DATA SAIDA
 data_saida saida;
 //ESTADO 0=LIVRE 1=OCUPADO
 int estado;
//TIPO VIATURA(0 - Deficientes, 1 - Carro, 2 - Caravanas, 3 - Autocarro&Camioes, 4 - Helicopteros)
 int tipo;
}parking;

//DECLARAR FUNCAO QUE LEVA ARRAY
void Estacionar(int p, int l ,int c, char m[], int t, parking ***parque);
float Destacionar(int p, int l, int c,int count,parking ***parque);
void Pagamento(int p, int l ,int c,parking ***parque);
void Lavagem(int p, int l, int c, parking ***parque);
int L_livres(parking ***parque);
int L_ocupados(parking ***parque);
int Find_lugar(char m[], parking ***parque);
int Find_car(char m[], parking ***parque);
//DECLARAR O TAMANHO DO ARRAY PARQUE
void setTamanho(int p,int l,int c){
 piso=p;
 linha=l;
 coluna=c;
}

//FUNCAO PARA SETAR OS DADOS
void Estacionar(int p , int l ,int c,char m[], int t, parking ***parque){
//INICIALIZAR DADOS DE TIME
time_t now;
time(&now);
struct tm *local = localtime(&now);
//DAR ASIGN DOS VALORES COM PISO,LINHA E COLUNA FORNECIDOS CONSOANTE O QUE O UTILIZADOR CLICA NA FRONT-END

    //PEGAR NA STRING MATRICULA E COLA-LA NA POSICAO INDICADA NO PARAMETRO MATRICULA
    strcpy(parque[p][l][c].veiculo.matricula,m);
    //PEGAR NO TIPO DE VIATURA
    parque[p][l][c].veiculo.tipo_de_veiculo=t;
    //DAY GET
    parque[p][l][c].entrada.day_chegada=local->tm_mday;
    //MOUNTH GET
    parque[p][l][c].entrada.month_chegada=local->tm_mon+1;
    //YEAR GET
    parque[p][l][c].entrada.year_chegada=local->tm_year+1900;
    //HOURS GET
    parque[p][l][c].entrada.hours_chegada=local->tm_hour;
    //MINUTES GET
    parque[p][l][c].entrada.minutes_chegada=local->tm_min;
    //SECOUNDS GET
    parque[p][l][c].entrada.secounds_chegada=local->tm_sec;
    //ESTABLECER O ESTADO COMO ESTACIONADO
    parque[p][l][c].estado=1;

}



//FUNCAO PARA DETERMINAR O PAGAMENTO DO PARQUE
void Pagamento(int p , int l ,int c,parking ***parque){
    float min, horas, dia, mes, ano,sec;
    float total;
    float pagamento=2.50;

    //TOTAL DE HORAS PASSADAS
    ano = parque[p][l][c].saida.year_saida - parque[p][l][c].entrada.year_chegada;
    //TOTAL DE MESES PASSADOS
    mes = parque[p][l][c].saida.month_saida - parque[p][l][c].entrada.month_chegada;
    //TOTAL DE DIAS PASSADOS
    dia = parque[p][l][c].saida.day_saida - parque[p][l][c].entrada.day_chegada;
    //TOTAL DE HORAS PASSADOS
    horas = parque[p][l][c].saida.hours_saida - parque[p][l][c].entrada.hours_chegada;
    //TOTAL DE MINUTOS PASSADOS
    min = parque[p][l][c].saida.minutes_saida - parque[p][l][c].entrada.minutes_chegada;

    //DETERMINAMOS O NUMERO TOTAL DE HORAS E MULTIPLACAMOS PELO TOTAL A PAGAR
    total = (float)(ano * 8760) + (float)(mes * 744) + (float)(dia * 24) + (float)horas + (float)(min / 60);

    //NUMERO DE HORAS VS O PREÇO À HORA DO RESPETIVO TIPO DE VEICULO
    total = total * pagamento;
    //TOTAL A PAGAR É IGUAL AO NUMERO DE LAVAGENS X 20 (PREÇO POR LAVAGEM) + O AS HORAS
    parque[p][l][c].veiculo.pagamento = (parque[p][l][c].veiculo.n_lavagens * 20) + total;
}



//FUNCAO PARA SETAR OS DADOS
float Destacionar(int p , int l ,int c,int count, parking ***parque){
//DAR ASIGN DOS VALORES COM PISO,LINHA E COLUNA FORNECIDOS CONSOANTE O QUE O UTILIZADOR CLICA NA FRONT-END
    parque[p][l][c].veiculo.matricula[0]=0;
    //MUDAR O ESTADO SIMPLESMENTE PARA DESTACIONADO
    parque[p][l][c].estado=0;
    //INICIALIZAR DADOS DE TIME PARA SABER A DATA ATUAL
    time_t now;
    time(&now);
    struct tm *data_saida = localtime(&now);
    //DAY GET
    parque[p][l][c].saida.day_saida=data_saida->tm_mday;
    //MOUNTH GET
    parque[p][l][c].saida.month_saida=data_saida->tm_mon+1;
    //YEAR GET
    parque[p][l][c].saida.year_saida=data_saida->tm_year+1900;
    //HOURS GET
    parque[p][l][c].saida.hours_saida=data_saida->tm_hour;
    //MINUTES GET
    parque[p][l][c].saida.minutes_saida=data_saida->tm_min;
    //SECOUNDS GET
    parque[p][l][c].saida.secounds_saida=data_saida->tm_sec;

    //INICIALIZAR FUNCAO PAGAMENTO COM PARAMETROS , DATA DE CHEGADA E DATA DE SAIDA;ARMAZENAR NA ABA "PAGAMENTO"
    Pagamento(p,l,c,parque);
    //retornar o pagamento
    return parque[p][l][c].veiculo.pagamento;
}



//FUNÇÃO PARA CONTAR O NUMERO DE LAVAGENS FEITAS
void Lavagem(int p, int l, int c, parking ***parque){
    //ADICIONAMOS +1 AO CONTADOR DE LAVAGENS
    parque[p][l][c].veiculo.n_lavagens = parque[p][l][c].veiculo.n_lavagens + 1;
}



//FUNÇÃO PARA CONTAR TODOS OS LUGARES LIVRES
int L_livres(parking ***parque){
    int p = 0, l = 0, c = 0, count = 0;
    //VERIFICAMOS TODOS OS PISOS
    for (p; p <= piso; p++){
        //VERIFICAMOS TODAS AS LINHAS
        for (l; l <=linha; l++){
            //VERIFICAMOS TODAS AS COLUNAS
            for (c; c <=coluna; c++){
                //VERIFICAMOS SE O ESTADO ESTÁ LIVRE
                if (parque[p][l][c].estado == 0){
                    //RETURNAMOS O PISO-LINHA-COLUNA
                    count = count + 1;
                }
            }
        }
    }
    printf("\n%d\n", count);
}



//FUNÇÃO PARA CONTAR TODOS OS LUGARES OCUPADOS
int L_ocupados(parking ***parque){
    int p = 0, l = 0, c = 0, count = 0;
    //VERIFICAMOS TODAS OS PISOS
    for (p; p <=piso; p++){
        //VERIFICAMOS TODAS AS LINHAS
        for (l; l <=linha; l++){
            //VERIFICAMOS TODAS AS COLUNAS
            for (c; c <=coluna; c++){
                //VERIFICAMOS SE O ESTADO ESTÁ OCUPADO
                if (parque[p][l][c].estado = 1){
                    //RETURNAMOS O PISO-LINHA-COLUNA
                    count = count + 1;
                }
            }
        }
    }
    printf("\n%d\n", count);
}




//FUNÇÃO PARA PROCURAR UMA MATRICULA
int Find_car(char m[], parking ***parque){
    int valor=1;

        for (int p = 0; p <piso; p++)
{
    //QUANDO VOLTA VOLTA AQUI MUDA O PISO
    int l=0;
    for (l;l<linha;l++)
    {
    //LINHA
    int c=0;

    for (c;c<coluna;c++)
    {
     //VERIFICAR SE HÁ MATRICULAS IGUAIS
     if(strcmp(m,parque[p][l][c].veiculo.matricula)==0){
        valor=0;
        break;
     }

    }
    }
    }
    return valor;
}






//FUNCAO DE INICIALIZAR
void inicializar(int defs_number,int carv_number,int bus_number,int helicopter_number,parking ***parque){
    for (int p = 0; p <piso; p++)
{
    //QUANDO VOLTA VOLTA AQUI MUDA O PISO
    int l=0;
    for (l;l<linha;l++)
    {
    //LINHA
    int c=0;

    for (c;c<coluna;c++)
    {
    parque[p][l][c].veiculo.matricula[0]=0;
    parque[p][l][c].tipo=1;
    parque[p][l][c].veiculo.n_lavagens=0;
    parque[p][l][c].entrada.year_chegada=0;
    parque[p][l][c].entrada.month_chegada=0;
    parque[p][l][c].entrada.day_chegada=0;
    parque[p][l][c].entrada.hours_chegada=0;
    parque[p][l][c].entrada.minutes_chegada=0;
    parque[p][l][c].entrada.secounds_chegada=0;
    parque[p][l][c].saida.year_saida=0;
    parque[p][l][c].saida.month_saida=0;
    parque[p][l][c].saida.day_saida=0;
    parque[p][l][c].saida.hours_saida=0;
    parque[p][l][c].saida.minutes_saida=0;
    parque[p][l][c].saida.secounds_saida=0;
    parque[p][l][c].estado=2;
    parque[p][l][c].veiculo.pagamento=0;
}
}
}
}
