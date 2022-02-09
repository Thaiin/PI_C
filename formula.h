#include "longmulprec.h"

int ArcTan(struct NUMBER *a, struct NUMBER *b);
void DF(struct NUMBER *a);
long PAR_LOOP(long loop);

int DasesFormula(struct NUMBER *a);
int VegasFormula(struct NUMBER *a);
int MachinsFormula(struct NUMBER *a);
int GausssFormula(struct NUMBER *a);
int StellmersFormula(struct NUMBER *a);
int TakanosFormula(struct NUMBER *a);


//b = arctan(1/a)
int ArcTan(struct NUMBER *a, struct NUMBER *b){
    struct NUMBER one, tmpA, re, tmp, powA;
    long n = 2, i = 1;

    SetIntNumber(&one, 1);
    SetIntNumber(&re, 1);
    ClearByZero(b);

    DecimalDivide(&one, a, &tmpA);  //aの逆数
    CopyNumber(&tmpA, &tmp);
    DecimalMultiple(&tmpA, &tmp, &powA); // aの逆数の二乗

    while(IsZero(&re) != 0){
        n = i * 2 - 1;

        if(n % 2 == 1 && i % 2 == 1){
            SetIntNumber(&re, n);
        }else{
            SetIntNumber(&re, -n);
        }
        DecimalDivide(&one, &re, &tmp);    //1/(-1^n)n
        DecimalMultiple(&tmp, &tmpA, &re); //(1/a)^n * (1/(-1^n)n)

        Add(b, &re, &tmp);
        CopyNumber(&tmp, b);
        i++;

        DecimalMultiple(&tmpA, &powA, &tmp); //(a^2*i+1)*a^2
        CopyNumber(&tmp, &tmpA);
    }
    return 0;
}

//a = 4*(arctan(1/2) + arctan(1/5) + arctan(1/8))
void DF(struct NUMBER *a){
    struct NUMBER arctan1, arctan2, arctan3, tmp, re, t;
    struct NUMBER two, five, eight, four, one;
    struct NUMBER tmpA, reA, powA;
    struct NUMBER tmpB, reB, powB;
    struct NUMBER tmpC, reC, powC;
    long n, i = 1;

    ClearByZero(&arctan1);
    ClearByZero(&arctan2);
    ClearByZero(&arctan3);
    SetIntNumber(&two, 2);
    SetIntNumber(&five, 5);
    SetIntNumber(&eight, 8);
    SetIntNumber(&four, 4);
    SetIntNumber(&one, 1);

    SetIntNumber(&reA, 1);
    SetIntNumber(&reB, 1);
    SetIntNumber(&reC, 1);

    DecimalDivide(&one, &two, &tmpA);  //aの逆数
    DecimalMultiple(&tmpA, &tmpA, &powA); // aの逆数の二乗
    DecimalDivide(&one, &five, &tmpB);  //bの逆数
    DecimalMultiple(&tmpB, &tmpB, &powB); // bの逆数の二乗
    DecimalDivide(&one, &eight, &tmpC);  //cの逆数
    DecimalMultiple(&tmpC, &tmpC, &powC); // cの逆数の二乗

    while(IsZero(&reA) != 0){
        n = i * 2 - 1;

        if(n % 2 == 1 && i % 2 == 1){
            SetIntNumber(&re, n);
        }else{
            SetIntNumber(&re, -n);
        }
        DecimalDivide(&one, &re, &tmp);    //1/(-1^n)n
        CopyNumber(&tmp, &t);
        DecimalMultiple(&tmp, &tmpA, &reA); //(1/a) * (1/(-1^n)n)
        
        Add(&arctan1, &reA, &tmp);
        CopyNumber(&tmp, &arctan1);
        
        DecimalMultiple(&tmpA, &powA, &tmp);
        CopyNumber(&tmp, &tmpA);

        if(IsZero(&reB) != 0){
            DecimalMultiple(&t, &tmpB, &reB);
            
            Add(&arctan2, &reB, &tmp);
            CopyNumber(&tmp, &arctan2);

            DecimalMultiple(&tmpB, &powB, &tmp);
            CopyNumber(&tmp, &tmpB);
        }

        if(IsZero(&reC) != 0){
            DecimalMultiple(&t, &tmpC, &reC);

            Add(&arctan3, &reC, &tmp);
            CopyNumber(&tmp, &arctan3);
            
            DecimalMultiple(&tmpC, &powC, &tmp);
            CopyNumber(&tmp, &tmpC);
        }

        //printf("roop:%ld%%\n", PAR_LOOP(i));
        i++;
    }
    Add(&arctan1, &arctan2, &tmp);
    Add(&tmp, &arctan3, a);
    DecimalMultiple(a, &four, &tmp);
    CopyNumber(&tmp, a);
}

// a = 4*(arctan(1/2) + arctan(1/5) + arctan(1/8))
int DasesFormula(struct NUMBER *a){
    struct NUMBER arctan1, arctan2, arctan3, tmp;
    struct NUMBER two, five, eight, four;
    int r1, r2, r3, r4, over = 0;

    ClearByZero(&arctan1);
    ClearByZero(&arctan2);
    ClearByZero(&arctan3);
    SetIntNumber(&two, 2);
    SetIntNumber(&five, 5);
    SetIntNumber(&eight, 8);
    SetIntNumber(&four, 4);

    r1 = ArcTan(&two, &arctan1);
    gettimeofday(&Time, NULL);
    te1 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("first : %06.6f[s]\n", te1 - ts);
    
    r2 = ArcTan(&five, &arctan2);
    gettimeofday(&Time, NULL);
    te2 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("second: %06.6f[s]\n", te2 - te1);

    r3 = ArcTan(&eight, &arctan3);
    gettimeofday(&Time, NULL);
    te3 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("third : %06.6f[s]\n", te3 - te2);

    Add(&arctan1, &arctan2, &tmp);
    Add(&tmp, &arctan3, a);

    r4 = DecimalMultiple(a, &four, &tmp);
    CopyNumber(&tmp, a);

    if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0){
        over = -1;
    }
    return over;
}

// a = 4*(2*arctan(1/2) - arctan(1/7))
int VegasFormula(struct NUMBER *a){
    struct NUMBER arctan1, arctan2, tmp;
    struct NUMBER two, seven, four;
    int r1, r2, r3, r4, r5, over = 0;

    ClearByZero(&arctan1);
    ClearByZero(&arctan2);
    SetIntNumber(&two, 2);
    SetIntNumber(&seven, 7);
    SetIntNumber(&four, 4);

    r1 = ArcTan(&two, &arctan1);
    gettimeofday(&Time, NULL);
    te1 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("first : %06.6f[s]\n", te1 - ts);

    r2 = ArcTan(&seven, &arctan2);
    gettimeofday(&Time, NULL);
    te2 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("second: %06.6f[s]\n", te2 - te1);

    r3 = DecimalMultiple(&arctan1, &two, &tmp);
    CopyNumber(&tmp, &arctan1);

    r4 = Sub(&arctan1, &arctan2, &tmp);
    r5 = DecimalMultiple(&tmp, &four, a);
    
    if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0 || r5 != 0){
        over = -1;
    }
    return over;
}

// a = 4*(4*arctan(1/5) - arctan(1/239))
int MachinsFormula(struct NUMBER *a){
    struct NUMBER arctan1, arctan2, tmp;
    struct NUMBER four, re1, re2;
    int r1, r2, r3, r4, r5, over = 0;

    ClearByZero(&arctan1);
    ClearByZero(&arctan2);
    SetIntNumber(&re1, 5);
    SetIntNumber(&re2, 239);
    SetIntNumber(&four, 4);

    r1 = ArcTan(&re1, &arctan1);
    gettimeofday(&Time, NULL);
    te1 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("first : %06.6f[s]\n", te1 - ts);

    r2 = ArcTan(&re2, &arctan2);
    gettimeofday(&Time, NULL);
    te2 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("second: %06.6f[s]\n", te2 - te1);

    r3 = DecimalMultiple(&arctan1, &four, &tmp);
    CopyNumber(&tmp, &arctan1);

    r4 = Sub(&arctan1, &arctan2, &tmp);
    r5 = DecimalMultiple(&tmp, &four, a);
    
    if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0 || r5 != 0){
        over = -1;
    }
    return over;
}

// a = 4*(12*arctan(1/18) + 8*arctan(1/57) - 5*arctan(1/239))
int GausssFormula(struct NUMBER *a){
    struct NUMBER arctan1, arctan2, arctan3, tmp;
    struct NUMBER five, eight, four, twelve;
    struct NUMBER re1, re2, re3;
    int r1, r2, r3, over = 0;

    ClearByZero(&arctan1);
    ClearByZero(&arctan2);
    ClearByZero(&arctan3);

    SetIntNumber(&re1, 18);
    SetIntNumber(&re2, 57);
    SetIntNumber(&re3, 239);

    SetIntNumber(&four, 4);
    SetIntNumber(&five, -5);
    SetIntNumber(&eight, 8);
    SetIntNumber(&twelve, 12);

    r1 = ArcTan(&re1, &arctan1);
    gettimeofday(&Time, NULL);
    te1 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("first : %06.6f[s]\n", te1 - ts);
    
    r2 = ArcTan(&re2, &arctan2);
    gettimeofday(&Time, NULL);
    te2 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("second: %06.6f[s]\n", te2 - te1);

    r3 = ArcTan(&re3, &arctan3);
    gettimeofday(&Time, NULL);
    te3 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("third : %06.6f[s]\n", te3 - te2);

    if(r1 != 0 || r2 != 0 || r3 != 0){
        over = -1;
    }

    r1 = DecimalMultiple(&arctan1, &twelve, &tmp);
    CopyNumber(&tmp, &arctan1);

    r2 = DecimalMultiple(&arctan2, &eight, &tmp);
    CopyNumber(&tmp, &arctan2);

    r3 = DecimalMultiple(&arctan3, &five, &tmp);
    CopyNumber(&tmp, &arctan3);

    if(r1 != 0 || r2 != 0 || r3 != 0){
        over = -1;
    }

    r1 = Add(&arctan1, &arctan2, &tmp);
    r2 = Add(&tmp, &arctan3, a);
    r3 = DecimalMultiple(a, &four, &tmp);
    CopyNumber(&tmp, a);

    if(r1 != 0 || r2 != 0 || r3 != 0){
        over = -1;
    }

    return over;
}

// a = 4*(44*arctan(1/57) + 7*arctan(1/239) - 12*arctan(1/682) + 24*arctan(1/12943))
int StellmersFormula(struct NUMBER *a){
    struct NUMBER arctan1, arctan2, arctan3, arctan4;
    struct NUMBER re1, re2, re3, re4;
    struct NUMBER at1, at2, at3, at4, four;
    struct NUMBER tmp, arc1, arc2, arctan;
    int r1, r2, r3, r4, over = 0;

    ClearByZero(&arctan1);
    ClearByZero(&arctan2);
    ClearByZero(&arctan3);
    ClearByZero(&arctan4);
    SetIntNumber(&four, 4);
    SetIntNumber(&re1, 57);
    SetIntNumber(&re2, 239);
    SetIntNumber(&re3, 682);
    SetIntNumber(&re4, 12943);

    SetIntNumber(&at1,  44);
    SetIntNumber(&at2,   7);
    SetIntNumber(&at3, -12);
    SetIntNumber(&at4,  24);

    r1 = ArcTan(&re1, &arctan1);
    gettimeofday(&Time, NULL);
    te1 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("first : %06.6f[s]\n", te1 - ts);

    r2 = ArcTan(&re2, &arctan2);
    gettimeofday(&Time, NULL);
    te2 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("second: %06.6f[s]\n", te2 - te1);

    r3 = ArcTan(&re3, &arctan3);
    gettimeofday(&Time, NULL);
    te3 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("three : %06.6f[s]\n", te3 - te2);

    r4 = ArcTan(&re4, &arctan4);
    gettimeofday(&Time, NULL);
    te4 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("four  : %06.6f[s]\n", te4 - te3);

    if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0){
        over = -1;
    }

    r1 = DecimalMultiple(&at1, &arctan1, &tmp);
    CopyNumber(&tmp, &arctan1);

    r2 = DecimalMultiple(&at2, &arctan2, &tmp);
    CopyNumber(&tmp, &arctan2);

    r3 = DecimalMultiple(&at3, &arctan3, &tmp);
    CopyNumber(&tmp, &arctan3);

    r4 = DecimalMultiple(&at4, &arctan4, &tmp);
    CopyNumber(&tmp, &arctan4);

    if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0){
        over = -1;
    }

    r1 = Add(&arctan1, &arctan2, &arc1);
    r2 = Add(&arctan3, &arctan4, &arc2);
    r3 = Add(&arc1, &arc2, &arctan);
    
    r4 = DecimalMultiple(&arctan, &four, a);

    if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0){
        over = -1;
    }
    return over;
}

// a = 4*(12*arctan(1/49) + 32*arctan(1/57) - 5*arctan(1/239) + 12*arctan(1/110443))
int TakanosFormula(struct NUMBER *a){
    struct NUMBER arctan1, arctan2, arctan3, arctan4;
    struct NUMBER re1, re2, re3, re4;
    struct NUMBER at1, at2, at3;
    struct NUMBER tmp, arc1, arc2, four;
    int r1, r2, r3, r4, over = 0;

    ClearByZero(&arctan1);
    ClearByZero(&arctan2);
    ClearByZero(&arctan3);
    ClearByZero(&arctan4);
    SetIntNumber(&re1, 49);
    SetIntNumber(&re2, 57);
    SetIntNumber(&re3, 239);
    SetIntNumber(&re4, 110443);

    SetIntNumber(&at1, 12);
    SetIntNumber(&at2, 32);
    SetIntNumber(&at3, -5);
    SetIntNumber(&four, 4);

    r1 = ArcTan(&re1, &arctan1);
    gettimeofday(&Time, NULL);
    te1 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("first : %06.6f[s]\n", te1 - ts);

    r2 = ArcTan(&re2, &arctan2);
    gettimeofday(&Time, NULL);
    te2 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("second: %06.6f[s]\n", te2 - te1);

    r3 = ArcTan(&re3, &arctan3);
    gettimeofday(&Time, NULL);
    te3 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("three : %06.6f[s]\n", te3 - te2);

    r4 = ArcTan(&re4, &arctan4);
    gettimeofday(&Time, NULL);
    te4 = (double)Time.tv_sec + (double)Time.tv_usec * 1.0E-6;
    printf("four  : %06.6f[s]\n", te4 - te3);

    if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0){
        over = -1;
    }

    r1 = DecimalMultiple(&at1, &arctan1, &tmp);
    CopyNumber(&tmp, &arctan1);

    r2 = DecimalMultiple(&at2, &arctan2, &tmp);
    CopyNumber(&tmp, &arctan2);

    r3 = DecimalMultiple(&at3, &arctan3, &tmp);
    CopyNumber(&tmp, &arctan3);

    r4 = DecimalMultiple(&at1, &arctan4, &tmp);
    CopyNumber(&tmp, &arctan4);

    if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0){
        over = -1;
    }

    r1 = Add(&arctan1, &arctan2, &arc1);
    r2 = Add(&arctan3, &arctan4, &arc2);
    r3 = Add(&arc1, &arc2, &tmp);
    r4 = DecimalMultiple(&tmp, &four, a);

    if(r1 != 0 || r2 != 0 || r3 != 0 || r4 != 0){
        over = -1;
    }

    return over;
}