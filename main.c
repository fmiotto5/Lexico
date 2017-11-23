#define TKId 1

//PALAVRAS RESERVADAS
#define TKVoid 2
#define TKShort 3
#define TKInt 4
#define TKLong 5
#define TKFloat 6
#define TKDouble 7
#define TKChar 69
#define TKAsm 8
#define TKAuto 9
#define TKBreak 10
#define TKIf 11
#define TKElse 12
#define TKWhile 13
#define TKDo 14
#define TKFor 15
#define TKSwitch 16
#define TKCase 17
#define TKContinue 18
#define TKDefault 19
#define TKConst 20
#define TKEnum 21
#define TKExtern 22
#define TKGoto 23
#define TKRegister 24
#define TKReturn 25
#define TKSigned 26
#define TKUnsigned 27
#define TKSizeof 28
#define TKStatic 29
#define TKStruct 30
#define TKTypedef 31
#define TKUnion 32
#define TKVolatile 33

//CARACTERES EPSECIAIS //OPERADORES
#define TKAbrePar 34        /* ( */
#define TKFechaPar 35       /* ) */
#define TKAbreChave 36      /* [ */
#define TKFechaChave 37     /* ] */
#define TKAbreColchete 38   /* { */
#define TKFechaColchete 39  /* } */
#define TKPontoeVirg 40     /* ; */
#define TKDoisPontos 41     /* : */
#define TKVirgula 42        /* , */
#define TKAtrib 43          /* = */
#define TKMais 44           /* + */
#define TKMenos 45          /* - */
#define TKMultiplicacao 46  /* * */
#define TKDivisao 47        /* / */
#define TKRestoDivisao 48   /* % */
#define TKMaior 49          /* > */
#define TKMenor 50          /* < */
#define TKHashtag 51        /* # */

//OPERADORES REDUZIDOS
#define TKMenosIgual 52             /* -= */
#define TKMaisIgual 53              /* += */
#define TKMultiplicacaoIgual 54     /* *= */
#define TKDivisaoIgual 55           /* /= */
#define TKRestoDivisaoIgual 56      /* %= */
#define TKComparadorMaiorIgual 57   /* >= */
#define TKComparadorMenorIgual 58   /* <= */
#define TKMenosMenos 59             /* -- */
#define TKMaisMais 60               /* ++ */
#define TKComparadorIgual 61        /* == */
#define TKComparadorDiferente 62    /* != */
#define TKNegacao 63                /* ! */
#define TKTernario 64               /* ? */
#define TKShiftLeft 65              /* << */
#define TKShiftRight 66             /* >> */
#define TKOU 67                     /* || */
#define TKAND 68                    /* && */


//CONSTANTES
#define TKConstInt 80
#define TKConstFloat 81
#define TKConstOctal 82
#define TKConstHexa 83

//Erros
#define TKErroE 100
#define TKErroConstFloat 101
#define TKErroOU 102
#define TKErroAND 103
#define TKErroConstHexa 104

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
        int pos = 0;
int estado_anterior = 0;
int posColuna = 0;
int subColuna = 0;
int linha = 0;
int coluna = 0;
int tab = 0;

struct pal_res{char palavra[20]; int tk;};
struct pal_res lista_pal[]={  {"void",TKVoid},
                              {"short",TKShort},
                              {"int",TKInt},
                              {"long",TKLong},
                              {"float",TKFloat},
                              {"double",TKDouble},
                              {"asm",TKAsm},
                              {"auto",TKAuto},
                              {"break",TKBreak},
                              {"if",TKIf},
                              {"else",TKElse},
                              {"while",TKWhile},
                              {"do",TKDo},
                              {"for",TKFor},
                              {"switch",TKSwitch},
                              {"case",TKCase},
                              {"continue",TKContinue},
                              {"default",TKDefault},
                              {"const",TKConst},
                              {"enum",TKEnum},
                              {"extern",TKExtern},
                              {"goto",TKGoto},
                              {"register",TKRegister},
                              {"return",TKReturn},
                              {"signed",TKSigned},
                              {"unsigned",TKUnsigned},
                              {"sizeof",TKSizeof},
                              {"static",TKStatic},
                              {"struct",TKStruct},
                              {"typedef",TKTypedef},
                              {"union",TKUnion},
                              {"volatile",TKVolatile},
                              {"fimtabela",TKId}
};

int palavra_reservada(char lex[])
{
    int postab=0;
    while (strcmp("fimtabela",lista_pal[postab].palavra)!=0)
    {
        if (strcmp(lex,lista_pal[postab].palavra)==0)
            return lista_pal[postab].tk;
        postab++;
    }
    return TKId;
}


int le_token(char st[],char lex[])
{
    int estado=0, fim=0, posl=0;
    posColuna = pos;
//estado_anterior = 0;
    while (!fim)
    {
        char c=st[pos];

        lex[posl++]=c;
        switch(estado){
            case 0:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_'){
                    pos++;
                    estado=1;
                    estado_anterior = 0;
                    break;
                }
                if (c>='0' && c<='9'){
                    if (c == '0'){
                        pos++;
                        estado = 8;
                        estado_anterior = 0;
                        break;
                    }
                    pos++;
                    estado=2;
                    estado_anterior = 0;
                    break;
                }
                if (c=='.'){
                    pos++;
                    estado=3;
                    estado_anterior = 0;
                    break;
                }
                if (c=='='){
                    c = st[++pos];
                    if (c == '=') {
                        lex[posl++] = '=';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKComparadorIgual;
                    }
                    else {
                        lex[posl] = '\0';
                        return TKAtrib;
                    }
                }
                if (c=='!'){
                    c = st[++pos];
                    if (c == '=') {
                        lex[posl++] = '=';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKComparadorDiferente;
                    }
                    else {
                        lex[posl] = '\0';
                        return TKNegacao;
                    }
                }
                if (c=='?'){
                    lex[posl]='\0';
                    pos++;
                    estado_anterior = 0;
                    return TKTernario;
                }
                if (c=='+'){
                    c = st[++pos];
                    if (c == '+') {
                        lex[posl++] = '+';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKMaisMais;
                    }
                    else if (c == '=') {
                        lex[posl++] = '=';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKMaisIgual;
                    }
                    else {
                        lex[posl] = '\0';
                        return TKMais;
                    }

                }
                if (c=='-'){
                    c = st[++pos];
                    if (c == '-') {
                        lex[posl++] = '-';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKMenosMenos;
                    }
                    else if (c == '=') {
                        lex[posl++] = '=';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKMenosIgual;
                    }
                    else {
                        lex[posl] = '\0';
                        return TKMenos;
                    }
                }
                if (c=='*'){
                    c = st[++pos];
                    if (c == '=') {
                        lex[posl++] = '=';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKMultiplicacaoIgual;
                    }
                    else {
                        lex[posl] = '\0';
                        return TKMultiplicacao;
                    }
                }
                if (c=='/'){
                    c = st[++pos];
                    if (c == '=') {
                        lex[posl++] = '=';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKDivisaoIgual;
                    }
                    else {
                        lex[posl] = '\0';
                        return TKDivisao;
                    }
                }
                if (c=='%'){
                    c = st[++pos];
                    if (c == '=') {
                        lex[posl++] = '=';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKRestoDivisaoIgual;
                    }
                    else {
                        lex[posl] = '\0';
                        return TKRestoDivisao;
                    }
                }
                if (c=='|'){
                    c = st[++pos];
                    if (c == '|') {
                        lex[posl++] = '|';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKOU;
                    }
                    return TKErroOU;
                }
                if (c=='&'){
                    c = st[++pos];
                    if (c == '&') {
                        lex[posl++] = '&';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKAND;
                    }
                    return TKErroAND;
                }
                if (c=='>'){
                    c = st[++pos];
                    if (c == '=') {
                        lex[posl++] = '=';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKComparadorMaiorIgual;
                    }
                    else if (c == '>') {
                        lex[posl++] = '>';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKShiftRight;
                    }
                    else {
                        lex[posl] = '\0';
                        return TKMaior;
                    }
                }
                if (c=='<'){
                    c = st[++pos];
                    if (c == '=') {
                        lex[posl++] = '=';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKComparadorMenorIgual;
                    }
                    else if (c == '<') {
                        lex[posl++] = '<';
                        lex[posl] = '\0';
                        pos++;
                        estado_anterior = 0;
                        return TKShiftLeft;
                    }
                    else {
                        lex[posl] = '\0';
                        return TKMenor;
                    }
                }
                if (c=='('){
                    lex[posl]='\0';
                    pos++;
                    estado_anterior = 0;
                    return TKAbrePar;
                }
                if (c==')'){
                    lex[posl]='\0';
                    pos++;
                    estado_anterior = 0;
                    return TKFechaPar;
                }
                if (c=='{'){
                    lex[posl]='\0';
                    pos++;
                    estado_anterior = 0;
                    return TKAbreChave;
                }
                if (c=='}'){
                    lex[posl]='\0';
                    pos++;
                    estado_anterior = 0;
                    return TKFechaChave;
                }
                if (c==','){
                    lex[posl]='\0';
                    pos++;
                    estado_anterior = 0;
                    return TKVirgula;
                }
                if (c==';'){
                    lex[posl]='\0';
                    pos++;
                    estado_anterior = 0;
                    return TKPontoeVirg;
                }
                if (c==':'){
                    lex[posl]='\0';
                    pos++;
                    estado_anterior = 0;
                    return TKDoisPontos;
                }
                if (c==' ' || c=='\n') {
                    pos++;
                    posl--;
                    posColuna = pos;
                }
                if (c==127) {
                    pos++;
                    posl--;
                    linha++;
                    subColuna = pos;
                    posColuna = pos;
                }
                if (c==9) {
                    tab ++;
                    pos++;
                    posColuna = pos;
                    posl--;
                    subColuna -= 3;

                }
                if (c=='\0') return -1;

                break;
            case 1:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_' || c>='0' && c<='9') {
                    pos++;
                    break;
                }
                lex[--posl]='\0';
                estado_anterior = 1;
                return palavra_reservada(lex);

            case 2:
                if (c>='0' && c<='9'){ //JA FOI LIDO UM NUMERO ANTERIORMENTE OU UM SINAL
                    pos++;
                    break;
                }

                if (c=='.') {
                    pos++;
                    estado=3;
                    estado_anterior = 2;
                    break;
                }
                if (c=='E') {
                    pos++;
                    estado=4;
                    estado_anterior = 2;
                    break;
                }
                lex[--posl]='\0';
                estado_anterior = 2;
                return TKConstInt;
            case 3:if (c>='0' && c<='9'){
                    pos++;
                    estado=7;
                    break;
                }
                else{
                    return TKErroConstFloat;
                }

            case 4: if (c>='0' && c<='9'){
                    pos++;
                    estado=6;
                    break;
                }
                else if (c=='-' || c=='+'){
                    pos++;
                    estado=5;
                    break;
                }
                return TKErroE;

            case 5: if (c>='0' && c<='9'){
                    pos++;
                    estado=6;
                    break;
                }
                return TKErroE;

            case 6: if (c>='0' && c<='9'){
                    pos++;
                    break;
                }
                if (estado_anterior = 2){
                    lex[--posl]='\0';
                    estado_anterior = 6;
                    return TKConstInt;
                }
                else{
                    lex[--posl]='\0';
                    estado_anterior = 6;
                    return TKConstFloat;
                }
            case 7:if (c>='0' && c<='9'){
                    pos++;
                    break;
                }
                if (c=='E') {
                    pos++;
                    estado=4;
                    estado_anterior = 7;
                    break;
                }
                lex[--posl]='\0';
                estado_anterior = 7;
                return TKConstFloat;
            case 8:
                if (c>='0' && c<='9'){
                    pos++;
                    break;
                }
                if (c == 'x' || c == 'X'){
                    pos++;
                    estado = 9;
                    estado_anterior = 8;
                    break;
                }
                lex[--posl]='\0';
                return TKConstOctal;
            case 9:
                if (c>='0' && c<='9'){
                    pos++;
                    estado_anterior = 9;
                    break;
                }
                else{
                    if (estado_anterior == 8)
                        return TKErroConstHexa;
                }
                lex[--posl]='\0';
                return TKConstHexa;
        }
    }
}

int main()
{
    int tk;
    char exp1[20000],lex[20], c;
    setbuf(stdout, NULL);
    FILE *entrada, *saida;

    int i = 0;

                               /* /home/felipe/Área de Trabalho/entrada/entrada */
    if ((entrada = fopen("/home/canu/carvi/cent/csin/fmiotto5/Área de Trabalho/entrada", "r")) == NULL) {
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }

    while(1){ // passa todo o conteudo do arquivo pra um string
        c = fgetc(entrada);
        if (feof(entrada))
            break;
        if(c != 9 && c != 10 && c !=13){
            exp1[i++] = c;
        }
        else if(c ==10){
            exp1[i++] = 127;
        }
        else if(c ==9){
            exp1[i++] = 9;
        }
    }
    exp1[i] = '\0';

    if ((saida = fopen("/home/canu/carvi/cent/csin/fmiotto5/Área de Trabalho/saida", "w")) == NULL) {
        printf("Arquivo  dest não pode ser aberto\n");
        exit(1);
    }



    while ((tk=le_token(exp1,lex))!=-1){
        /*printf("posColuna: %d\n", posColuna);
        printf("subColuna: %d\n", subColuna);
        printf("pos: %d\n", pos);*/

        coluna = posColuna - subColuna;
        char linhaSt[3];
        char colunaSt[3];
        snprintf(linhaSt, sizeof(linhaSt), "%d", linha);			// converto int para string
        snprintf(colunaSt, sizeof(colunaSt), "%d", coluna);


        if(tk == 100){
            fputs("TKErroE: Erro no uso da exponenciacao na Linha: ",saida);
            for (i = 0;i < strlen(linhaSt);i++) {
                fputc(linhaSt[i], saida);
            }
            fputs(" Coluna: ",saida);
            for (i = 0;i < strlen(colunaSt);i++) {
                fputc(colunaSt[i],saida);
            }
            fputs(" !!!",saida);
            break;
        }
        if(tk == 101){
            fputs("TKErroConstFloat: Erro no uso do '.' na Linha: ",saida);
            for (i = 0;i < strlen(linhaSt);i++) {
                fputc(linhaSt[i], saida);
            }
            fputs(" Coluna: ",saida);
            for (i = 0;i < strlen(colunaSt);i++) {
                fputc(colunaSt[i],saida);
            }
            fputs(" !!!",saida);
            break;
        }
        if(tk == 104){
            fputs("TKErroConstHexa: Erro no uso da variável hexadecimal na Linha: ",saida);
            for (i = 0;i < strlen(linhaSt);i++) {
                fputc(linhaSt[i], saida);
            }
            fputs(" Coluna: ",saida);
            for (i = 0;i < strlen(colunaSt);i++) {
                fputc(colunaSt[i],saida);
            }
            fputs(" !!!",saida);
            break;
        }


        char token[3];                                // converte o numero de int tk
        snprintf(token, sizeof(token), "%d", tk);     // para string token, pra poder escrever no arquivo
        int i;
        fputs("Tipo: ",saida);
        for (i = 0; i < strlen(token); i++) {
            fputc(token[i],saida); // escreve token[3] no arquivo de saida
        }
        fputc(' ',saida);
        fputc(9,saida);
        fputs("Lexema: ",saida);
        for(i = 0; i < strlen(lex);i++){
            fputc(lex[i],saida); // escreve o lex
        }
        fputc(' ',saida);
        fputc(9,saida);
        fputs("Linha: ",saida);


        for (i = 0;i < strlen(linhaSt);i++) {
            fputc(linhaSt[i], saida);
        }
        fputc(' ',saida);
        fputc(9,saida);
        fputs("Coluna: ",saida);

        for (i = 0;i < strlen(colunaSt);i++) {
            fputc(colunaSt[i],saida);
        }

        fputc(10,saida);
    }


    fclose(entrada);
    fclose(saida);
    system("pause");
}