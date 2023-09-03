#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 100000000

#define fim_string -1
#define AP -2 //Abre Parenteses
#define FP -3 //Fecha Parenteses
#define K -4
#define S -5
#define I -6
#define B -7
#define C -8
#define D -9
#define E -10
#define F -11
#define Y -12
#define lt -13
#define add -14
#define sub -15
#define tru -16
#define fal -17
#define mul -18

//static int entrada[N] = {lt, 8, 6, fim_string}; //  B C I K I S = S
//#include "curry.h"
//#include "DEF.h"
//#include "fat.h"
//#include "fib.h"
///*
//static int entrada[N] = {S, AP, K, AP, K, FP, FP, AP, K, S, FP, AP, S, K, FP, K, K, AP, S, K, FP, K, fim_string};
//static int entrada[N] = {B, C, I, K, I, S, fim_string}; //  B C I K I S = S
//static int entrada[N] = {D, K, I, I, S, fim_string}; //  = S
//static int entrada[N] = {E, I, I, I, S, fim_string}; //  = S
//static int entrada[N] = {F, K, I, K, Y, fim_string}; //  = Y
//static int entrada[N] = {lt, 3, 2, AP, S, K, K, I, FP, AP, sub, 1, 56, FP,fim_string}; //deve ser I se true e -55 se false
//*/

//#include "inteiro ksi.h"
#include "inteiro ksibc.h"
//#include "inteiro ksibcdef.h"
//#include "fat.h"
//#include "fib.h"
static int saida[N];

/*
verifica se dado os indices de inicio e fim de um argumento, sao iguais;
se forem iguais, sao operandos
se forem diferentes, sao expressoes de redução
*/
void checar_argumento(int entrada, int saida){
    if(entrada != saida){
        printf("Erro: argumento nao eh operando. index 1 = %i, index 2 = %i",entrada,saida);
        exit(0);
    }
}

void printar_array(unsigned int *array1) {
   int i;
   unsigned int fimString = -1;
   for(i = 0;array1[i] != fimString;i++){
       switch (array1[i]){
           case S:
               printf("S");
               break;
           case K:
               printf("K");
               break;
           case FP:
               printf(")");
               break;
           case AP:
               printf("(");
               break;
            case Y:
               printf("Y");
               break;
            case I:
               printf("I");
               break;
            case B:
               printf("B");
               break;
            case C:
               printf("C");
               break;
            case D:
               printf("D");
               break;
            case E:
               printf("E");
               break;
            case F:
               printf("F");
               break;
            case add:
               printf("+");
               break;
            case sub:
               printf("-");
               break;
            case mul:
               printf("*");
               break;
            case tru:
               printf("True");
               break;
            case fal:
               printf("False");
               break;
            case lt:
               printf("<");
               break;
           case fim_string:
                break;
           default:
               printf("%d ", array1[i]);
       }
   }
   printf("\n");
}

/*
 * Remove o parenteses da posição 0 e seu oposto
 */
void remove_parenteses(int *array1){
    int p = 0;
    int paren = 1;
    while (paren) {
        array1[p] = array1[p+1];
        p++;
        if(array1[p] == AP){
            paren++;
        }else if(array1[p] == FP){
            paren--;
        }
    }
    p--;
    while(array1[p+1] != fim_string && array1[p+2] != fim_string){
        array1[p] = array1[p+2];
        p++;
    }
    array1[p] = fim_string;
}

/*
 * Procura o fim do conjunto de inteiros
 */
void casa_parenteses(int* array1, int* p) {
    int paren = 1;
    int a = *p;
    while (paren) {
        unsigned int c  = array1[a];
        if(c == AP){
            paren++;
        }else if(c == FP){
            paren--;
        }
        a++;
    }
    *p = a;
}

/*
 * Verifica se a posicao do array é um inteiro ou um conjunto de inteiros
 */
void acha_argumento(int *array1, int *p){
    int c = (*p)++;
    if (array1[c] == AP) {
        casa_parenteses(array1,p);
    }
}

/*
 * Kab = a
 */
void reduz_K(int* array1, int* array2) {
    int A, nA;
    int n = 1;

    A = n;
    acha_argumento(array1,&n);

    nA = n-1;
    acha_argumento(array1,&n);

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * Sabc = ac(bc)
 */
void reduz_S(int *array1, int *array2) {
    int A, nA;
    int U, nU;
    int P, nP;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    U = n;
    acha_argumento(array1,&n);
    nU = n-1;
    P = n;
    acha_argumento(array1,&n);
    nP = n-1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = P; i <= nP; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = U; i <= nU; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = P; i <= nP; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = FP;
    k++;
    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * Ia = a
 */
void reduz_I(int *array1, int *array2) {
    int A, nA;
    int n = 1;

    A = n;
    acha_argumento(array1,&n);
    nA = n-1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * B a b c => a (b c)
 */
void reduz_B(int *array1, int *array2) {
    int A, nA;
    int U, nU;
    int P, nP;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    U = n;
    acha_argumento(array1,&n);
    nU = n-1;
    P = n;
    acha_argumento(array1,&n);
    nP = n-1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = U; i <= nU; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (i = P; i <= nP; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * C f g x => f x g
 */
void reduz_C(int *array1, int *array2) {
    int A, nA;
    int U, nU;
    int P, nP;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    U = n;
    acha_argumento(array1,&n);
    nU = n-1;
    P = n;
    acha_argumento(array1,&n);
    nP = n-1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (i = P; i <= nP; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (i = U; i <= nU; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * D a b c d => a (b d) (c d)
 */
void reduz_D(int *array1, int *array2) {
    int A, nA;
    int U, nU;
    int P, nP;
    int T, nT;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    U = n;
    acha_argumento(array1,&n);
    nU = n-1;
    P = n;
    acha_argumento(array1,&n);
    nP = n-1;
    T = n;
    acha_argumento(array1,&n);
    nT = n-1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = U; i <= nU; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (i = T; i <= nT; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    array2[k] = AP;
    k++;

    for (i = P; i <= nP; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (i = T; i <= nT; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * E a b c d => a b (c d)
 */
void reduz_E(int *array1, int *array2) {
    int A, nA;
    int U, nU;
    int P, nP;
    int T, nT;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    U = n;
    acha_argumento(array1,&n);
    nU = n-1;
    P = n;
    acha_argumento(array1,&n);
    nP = n-1;
    T = n;
    acha_argumento(array1,&n);
    nT = n-1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (i = U; i <= nU; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = P; i <= nP; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (i = T; i <= nT; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * F a b c d => a (b d) c
 */
void reduz_F(int *array1, int *array2) {
    int A, nA;
    int U, nU;
    int P, nP;
    int T, nT;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    U = n;
    acha_argumento(array1,&n);
    nU = n-1;
    P = n;
    acha_argumento(array1,&n);
    nP = n-1;
    T = n;
    acha_argumento(array1,&n);
    nT = n-1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = U; i <= nU; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (i = T; i <= nT; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (i = P; i <= nP; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * Ya = a(Ya)
 */
void reduz_Y(int *array1, int *array2) {
    int A, nA;
    int n = 1;

    A = n;
    acha_argumento(array1,&n);
    nA = n-1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    array2[k] = Y;
    k++;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * add a b = a + b
 */
void reduz_Add(int *array1, int *array2) {
    int A, nA;
    int U, nU;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    U = n;
    acha_argumento(array1,&n);
    nU = n-1;

    int k = 0;
    int i;

    checar_argumento(A,nA);
    checar_argumento(U,nU);
    
    int resultado = array1[A] + array1[U];

    array2[k] = resultado;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * mul a b = a * b
 */
void reduz_Mul(int *array1, int *array2) {
    int A, nA;
    int U, nU;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    U = n;
    acha_argumento(array1,&n);
    nU = n-1;

    int k = 0;
    int i;

    checar_argumento(A,nA);
    checar_argumento(U,nU);
    
    int resultado = array1[A] * array1[U];

    array2[k] = resultado;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * sub a b = a - b
 */
void reduz_Sub(int *array1, int *array2) {
    int A, nA;
    int U, nU;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    U = n;
    acha_argumento(array1,&n);
    nU = n-1;

    int k = 0;
    int i;

    checar_argumento(A,nA);
    checar_argumento(U,nU);
    
    int resultado = array1[A] - array1[U];

    array2[k] = resultado;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * tru a b = a
 */
void reduz_Tru(int *array1, int *array2) {
    int A, nA;
    int n = 1;

    A = n;
    acha_argumento(array1,&n);

    nA = n-1;
    acha_argumento(array1,&n);

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * fal a b = b
 */
void reduz_Fal(int *array1, int *array2) {
    int A, nA;
    int U, nU;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    U = n;
    acha_argumento(array1,&n);
    nU = n-1;

    int k = 0;
    int i;

    for (i = U; i <= nU; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * lt a b = a < b ? tru : fal
 */
void reduz_Lt(int *array1, int *array2) {
    int A, nA;
    int U, nU;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    U = n;
    acha_argumento(array1,&n);
    nU = n-1;

    int k = 0;
    int i;

    checar_argumento(A,nA);
    checar_argumento(U,nU);
    
    int resultado = array1[A] < array1[U] ? tru : fal;

    array2[k] = resultado;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

int main(){
    int *array1, *array2, *array3;
    array1 = entrada;
    array2 = saida;
    while(array1[1] != fim_string){
        switch (array1[0]){
            case AP:
                remove_parenteses(array1);
                array2[0] = fim_string;
                break;
            case I:
                reduz_I(array1, array2);
                break;
            case B:
                reduz_B(array1, array2);
                break;
            case D:
                reduz_D(array1, array2);
                break;
            case K:
                reduz_K(array1, array2);
                break;
            case F:
                reduz_F(array1, array2);
                break;
            case S:
                reduz_S(array1, array2);
                break;
            case Y:
                reduz_Y(array1, array2);
                break;
            case C:
                reduz_C(array1, array2);
                break;
            case E:
                reduz_E(array1, array2);
                break;
            case add:
                reduz_Add(array1, array2);
                break;
            case mul:
                reduz_Mul(array1, array2);
                break;
            case sub:
                reduz_Sub(array1, array2);
                break;
            case tru:
                reduz_Tru(array1, array2);
                break;
            case fal:
                reduz_Fal(array1, array2);
                break;
            case lt:
                reduz_Lt(array1, array2);
                break;
                
            default:
                break;
        }
        array3 = array1;
        array1 = array2;
        array2 = array3;
    }
    printar_array(array1);
    float clks = CLOCKS_PER_SEC;
    printf("\nTempo = %f", (clock()/clks));
    return 0;
}
