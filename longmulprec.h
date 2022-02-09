#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>

#define ELEMENTS 102                //要素数(*5で桁数)
#define INTEGER 2                   //整数部:INTEGER桁(*5で桁数)
#define DECIMAL (ELEMENTS-INTEGER)  //少数部:DECIMAL桁(*5で桁数)
#define RADIX 100000                //基数(10万)

#define LOOPNUM_PAR 1.34             //1桁のroop数

struct NUMBER{
    long n[ELEMENTS];   //数
    int sign;           //符号
};

struct timeval Time;
double ts, te, te1, te2, te3, te4;
int first_print_pi = 0;

void ClearByZero(struct NUMBER *a);
void CopyNumber(struct NUMBER *a, struct NUMBER *b);
void DispNumberDecimalNameByPi(struct NUMBER *a);
int IsZero(struct NUMBER *a);
int SetSign(struct NUMBER *a, int s);
int GetSign(struct NUMBER *a);
int SetIntNumber(struct NUMBER *a, int x);
void GetAbs(struct NUMBER *a, struct NUMBER *b);
int NumComp(struct NUMBER *a, struct NUMBER *b);
int MulBy10(struct NUMBER *a, struct NUMBER *b);
int DivBy10(struct NUMBER *a, struct NUMBER *b);
int Add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);
int Sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);
int DecimalMultiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);
int DecimalDivide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);


void ClearByZero(struct NUMBER *a){
    for(int i = 0; i < ELEMENTS; i++){
        a->n[i] = 0;
    }
    a->sign = 1;
}

void CopyNumber(struct NUMBER *a, struct NUMBER *b){
    *b = *a;
}

void DispNumberDecimalNameByPi(struct NUMBER *a){
    printf("\n pi = ");
    
    if(a->sign == 1){
        printf("+");
    } else if(a->sign == -1){
        printf("-");
    } else {
        printf("sign error ");
    }

    for(int j = 1; j <= INTEGER; j++){
        if(a->n[ELEMENTS - j] != 0){
            printf("%ld",a->n[ELEMENTS - j]);
            if(INTEGER == j){
                printf(".\n");
            }
        }
    }

    for(int i = 1; i <= DECIMAL; i++){
        printf("%05ld",a->n[DECIMAL - i]);
        if(i % 2 == 0){
            printf(" ");
            if(i % 20 == 0){
                printf("\n");
                if(i % 200 == 0){
                    printf("\n");
                }
            }
        }
    }
}

int SetSign(struct NUMBER *a, int s){
    if(s != 1 && s != -1){
        return -1;  //error
    } 
    else if(s == 1 || IsZero(a) == 0){
        a->sign = 1;
    } 
    else if(s == -1){
        a->sign = -1;
    }
    return 0;
}

int GetSign(struct NUMBER *a){
    return a->sign;
}

int SetIntNumber(struct NUMBER *a, int x){
    long maq;
    ClearByZero(a);

    if(x < 0){
        a->sign = -1;
        x = -x;
    } else if(x >= 0) {
        a->sign = 1;
    }

    for(int i = DECIMAL; i < ELEMENTS; i++){
        maq = x % RADIX;
        x = (x - maq) / RADIX;
        a->n[i] = maq;
    }

    return 0;
}

int IsZero(struct NUMBER *a){
    for(int i = 0; i < ELEMENTS; i++){
        if(a->n[i] != 0){
            return -1;
        }
    }
    return 0;
}

void GetAbs(struct NUMBER *a, struct NUMBER *b){
    CopyNumber(a, b);
    SetSign(b, 1);
}

int NumComp(struct NUMBER *a, struct NUMBER *b){
    int asign, bsign, an, bn;

    asign = GetSign(a);
    bsign = GetSign(b);

    if(asign > bsign){
        return 1;
    } 
    else if(asign < bsign){
        return -1;
    }
    else if(asign == 1 && bsign == 1){
        for(int i = 1; i <= ELEMENTS; i++){
            an = a->n[ELEMENTS - i];
            bn = b->n[ELEMENTS - i];

            if(an > bn){
                return 1;
            } else if(an < bn){
                return -1;
            }
        }
    } else if(asign == -1 && bsign == -1){
        for(int i = 1; i <= ELEMENTS; i++){
            an = a->n[ELEMENTS - i];
            bn = b->n[ELEMENTS - i];

            if(an < bn){
                return 1;
            } else if(an > bn){
                return -1;
            }
        }
    }
    return 0;
}

int MulBy10(struct NUMBER *a, struct NUMBER *b){
    long carry = 0;
    int over = 0;
    ClearByZero(b);
    SetSign(b, GetSign(a));

    if(a->n[ELEMENTS - 1] >= RADIX / 10){
        over = -1;
    }
    
    for(int i = 0; i < ELEMENTS; i++){
        b->n[i] = a->n[i] * 10 + carry;
        if(b->n[i] >= RADIX){
            b->n[i] = b->n[i] - (b->n[i] - (b->n[i] % RADIX));
        }
        carry = a->n[i] / (RADIX / 10);
    }
    return over;
}

int DivBy10(struct NUMBER *a, struct NUMBER *b){
    long borrow = 0;
    int over = 0;
    SetSign(b, GetSign(a));

    if((a->n[0] % 10) != 0){
        over = -1;
    }
    
    for(int i = ELEMENTS - 1; i >= 0; i--){
       b->n[i] = a->n[i] / 10 + (borrow * (RADIX / 10));
       borrow = a->n[i] % 10;
    }
    return over;
}

int Add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    long carry = 0, re;
    struct NUMBER absx, absy;
    ClearByZero(c);
    GetAbs(a, &absx);
    GetAbs(b, &absy);

    if(GetSign(a) == 1 && GetSign(b) == 1){
        carry = 0;

        for(int i = 0; i < ELEMENTS; i++){
            re = a->n[i] + b->n[i] + carry;
            c->n[i] = re % RADIX;
            carry = (re - c->n[i]) / RADIX;
        }
    }
    else if(GetSign(a) == 1 && GetSign(b) == -1){
        Sub(a, &absy, c);
    } 
    else if(GetSign(a) == -1 && GetSign(b) == 1){
        Sub(b, &absx, c);
    } 
    else {
        Add(&absx, &absy, c);
        SetSign(c, -1);
    }
    
    if(carry != 0){
        return -1;
    }
    return 0;
}

int Sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    long borrow = 0;
    int over = 0;
    struct NUMBER absx, absy;
    ClearByZero(c);
    GetAbs(a, &absx);
    GetAbs(b, &absy);

    if(GetSign(a) == 1 && GetSign(b) == 1){
        if(NumComp(a, b) == 1 || NumComp(a, b) == 0){
            for(int i = 0; i < ELEMENTS; i++){
                if(a->n[i] < (b->n[i] + borrow)){
                    c->n[i] = (RADIX + a->n[i]) - (b->n[i] + borrow);
                    borrow = 1;
                } else {
                    c->n[i] = a->n[i] - (b->n[i] + borrow);
                    borrow = 0;
                }
            }
        } else {
            for(int i = 0; i < ELEMENTS; i++){
                if(b->n[i] < (a->n[i] + borrow)){
                    c->n[i] = (RADIX + b->n[i]) - (a->n[i] + borrow);
                    borrow = 1;
                } else {
                    c->n[i] = b->n[i] - (a->n[i] + borrow);
                    borrow = 0;
                }
            }
            SetSign(c, -1);
        }
    }
    else if(GetSign(a) == 1 && GetSign(b) == -1){
        over = Add(a, &absy, c);
    }
    else if(GetSign(a) == -1 && GetSign(b) == 1){
        over = Add(&absx, b, c);
        SetSign(c, -1);
    }
    else {
        over = Sub(&absy, &absx, c);
    }

    if(borrow == 0 && over == 0){
        return 0;
    } else {
        return -1;
    }
}

int DecimalMultiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    struct NUMBER result, tmp, absA, absB;
    long carry, re, n = 0;
    int over;
    ClearByZero(c);
    GetAbs(a, &absA);
    GetAbs(b, &absB);

    for(int i = 0; i < ELEMENTS; i++){
        ClearByZero(&result);
        carry = 0;
        re = 0;

        if(absB.n[i] != 0){
            for(int j = 0; j < ELEMENTS; j++){
                n = (j + i) - DECIMAL;
                re = (absA.n[j] * absB.n[i]) + carry;
                if(n >= 0 && n < ELEMENTS){   
                    result.n[n] = (re % RADIX);
                    carry = (re / RADIX) % RADIX;
                } else if(n == -1){
                    carry = (re / RADIX) % RADIX; 
                }
                //DispNumberDecimalNameByPi(&);
            }
        }
        over = Add(c, &result, &tmp);
        CopyNumber(&tmp, c);
        
        if(over != 0) {
            over = -1;
        }
    }
    SetSign(c, GetSign(a) * GetSign(b));

    if(carry != 0){
        return -1;
    }
    return over;
}

int DecimalDivide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c){
    struct NUMBER one, absA, absB, tmp;
    int over = 0;

    ClearByZero(c);
    ClearByZero(&tmp);
    GetAbs(a, &absA);
    GetAbs(b, &absB);
    SetIntNumber(&one, 1);

    if(IsZero(a) == 0){
        return 0;
    }
    
    if(IsZero(b) == 0){
        printf("error\n");
        return -1;
    }

    if(NumComp(&absA, &absB) == 0){
        CopyNumber(&one, c);
        return 0;
    }

    while(1){
        MulBy10(&absB, &tmp);
        if(NumComp(&absA, &tmp) == -1){
            break;
        }
        CopyNumber(&tmp, &absB);
        MulBy10(&one, &tmp);
        CopyNumber(&tmp, &one);
    }

    while(IsZero(&absA) != 0 && IsZero(&absB) != 0){
        while(NumComp(&absA, &absB) == -1){    //a < b            
            DivBy10(&absB, &tmp);
            CopyNumber(&tmp, &absB);
            DivBy10(&one, &tmp);
            CopyNumber(&tmp, &one);
        }

        over = Sub(&absA, &absB, &tmp);
        CopyNumber(&tmp, &absA);
        over = Add(c, &one, &tmp);
        CopyNumber(&tmp, c);
    }
    SetSign(c, GetSign(a) * GetSign(b));

    return over;
}

long PAR_LOOP(long loop){
    long par;
    double tmp;

    tmp = ((double)loop / (LOOPNUM_PAR * ELEMENTS * 5)) * 100;
    par = (long)tmp;
    
    return par;
}