#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <dir.h>

const int shuffleN = 100000;
const int aloc = 50;

typedef struct{
    char username[50+1];
    int cardN;
    char status;
    int timer;
    int total;
}Igraci;

typedef struct{
    char c;
    int n;
    int p;
}Igra;

typedef struct{
    int n;
    char naziv[10+1];
    char broj[10+1];

}Karte;

typedef struct{
    char matrica[7][10];
    char dmatrica[7][10];

}VisualKarte;

typedef struct{
    int n;
    char naziv[10+1];
    char broj[10+1];

}NewKarte;

typedef struct{
    char matrica[7][10];
    char dmatrica[7][10];

}VisualNewKarte;

typedef struct{
    int n;
    char naziv[10+1];
    char broj[10+1];

}MemoryKarte;

typedef struct{
    char matrica[7][10];
    char dmatrica[7][10];
    char negmatrica[7][10];
    int check;
    int open;

}VisualMemoryKarte;

void shuffleDeck(Karte *scards,int a){

    int i,j,x,y;

    srand(time(NULL));

    for(i=0;i<shuffleN;i++){

        x=rand()%104;
        y=rand()%104;

        Karte z=scards[x];
        scards[x]=scards[y];
        scards[y]=z;
    }
}

void shuffleNewDeck(NewKarte *scards,int a){

    int i,j,x,y;

    srand(time(NULL));

    for(i=0;i<shuffleN;i++){

        x=rand()%52;
        y=rand()%52;

        NewKarte z=scards[x];
        scards[x]=scards[y];
        scards[y]=z;
    }
}

void shuffleMemDeck(MemoryKarte *scards,int a){

    int i,j,x,y;

    srand(time(NULL));

    for(i=0;i<shuffleN;i++){

        x=rand()%24;
        y=rand()%24;

        MemoryKarte z=scards[x];
        scards[x]=scards[y];
        scards[y]=z;
    }
}

void SetColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){

          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }


 int display(Igraci *igraci,VisualKarte *vkarte,int br_igraca,int i,int j, int f,int d,int row,int column,int m,int n,int *niz){

 	int deckp,h,check=0,cardcounter=0;

 	f=0;
    for(i=0;i<br_igraca;i++){
        printf("%s:\n",igraci[i].username);
        d=0;
        for(row=0;row<m;row++){

            j=f;
            d=0;
            cardcounter=0;
            while(d<5){
                for(column=0;column<n;column++){
                        if(vkarte[j].matrica[3][2]=='C' || vkarte[j].matrica[3][2]=='S'){
                            SetColor(1);
                        }
                        else{
                            SetColor(4);
                        }
                        check=0;
                        for(h=0;h<50;h++){
                            if(j+1==niz[h]){
                                check=1;
                            }
                        }
                        if(check!=1){
                            //printf("%d,%d",row,column);
                            printf("%c",vkarte[j].matrica[row][column]);
                        }

                }
                if(check==0){
                    cardcounter++;
                }
                d++;
                j++;
            }
            printf("\n");
        }
        SetColor(15);
        printf("\n");
        f=f+5;

        igraci[i].cardN=cardcounter;
    }
    deckp=j;
    return deckp;
 }

 void matrix(int b,int a,Karte *karte,VisualKarte *vkarte,int m,int n){

    int row,column,i;
    char string1[10]="dijamant";
    char string2[10]="zir";
    char string3[10]="srce";
    char string4[10]="pik";

    //matrice0
    i=0;
    while(i<a){
        for(row=0;row<m;row++){
            for(column=0;column<n;column++){
                vkarte[i].matrica[row][column]=' ';
            }
        }
        i++;
    }
    //matrice1
    i=0;
    while(i<a){
        for(row=0;row<m;row++){
            for(column=0;column<n;column++){
                if(row==0 || row==m-1){
                    vkarte[i].matrica[row][column]=196;
                }
                else if(column==0 || column==n-1){
                    vkarte[i].matrica[row][column]=179;
                }
            }
        }
        vkarte[i].matrica[0][0]=218;
        vkarte[i].matrica[0][n-1]=191;
        vkarte[i].matrica[m-1][0]=192;
        vkarte[i].matrica[m-1][n-1]=217;
        i++;
    }
    //matrice2
    i=0;
    while(i<a){

        b=(karte[i].n)%13;
        if(b>=2 && b<=9){
            vkarte[i].matrica[1][1]=b+48;
            vkarte[i].matrica[m-2][n-2]=b+48;
        }
        else if(b==10){
                vkarte[i].matrica[1][1]=49;
                vkarte[i].matrica[1][2]=48;
                vkarte[i].matrica[m-2][n-3]=49;
                vkarte[i].matrica[m-2][n-2]=48;
        }
        else if(b==11){
                vkarte[i].matrica[1][1]=74;
                vkarte[i].matrica[m-2][n-2]=74;
        }
        else if(b==12){
                vkarte[i].matrica[1][1]=81;
                vkarte[i].matrica[m-2][n-2]=81;
        }
        else if(b==0){
                vkarte[i].matrica[1][1]=75;
                vkarte[i].matrica[m-2][n-2]=75;
        }
        else if(b==1){
                vkarte[i].matrica[1][1]=65;
                vkarte[i].matrica[m-2][n-2]=65;
        }
        i++;
    }
    //matrice3
    i=0;
    while(i<a){
        if(strcmp(karte[i].naziv,string1)==0){
            vkarte[i].matrica[3][1]='D';
            vkarte[i].matrica[3][2]='i';
            vkarte[i].matrica[3][3]='a';
            vkarte[i].matrica[3][4]='m';
            vkarte[i].matrica[3][5]='o';
            vkarte[i].matrica[3][6]='n';
            vkarte[i].matrica[3][7]='d';
            vkarte[i].matrica[3][8]='s';

        }
        else if(strcmp(karte[i].naziv,string2)==0){
            vkarte[i].matrica[3][2]='C';
            vkarte[i].matrica[3][3]='l';
            vkarte[i].matrica[3][4]='u';
            vkarte[i].matrica[3][5]='b';
            vkarte[i].matrica[3][6]='s';
        }
        else if(strcmp(karte[i].naziv,string3)==0){
            vkarte[i].matrica[3][2]='H';
            vkarte[i].matrica[3][3]='e';
            vkarte[i].matrica[3][4]='a';
            vkarte[i].matrica[3][5]='r';
            vkarte[i].matrica[3][6]='t';
            vkarte[i].matrica[3][7]='s';
        }
        else if(strcmp(karte[i].naziv,string4)==0){
            vkarte[i].matrica[3][2]='S';
            vkarte[i].matrica[3][3]='p';
            vkarte[i].matrica[3][4]='a';
            vkarte[i].matrica[3][5]='d';
            vkarte[i].matrica[3][6]='e';
            vkarte[i].matrica[3][7]='s';
        }
        i++;
    }


 }

 void newmatrix(int b,int a,NewKarte *karte,VisualNewKarte *vkarte,int m,int n){

    int row,column,i;
    char string1[10]="dijamant";
    char string2[10]="zir";
    char string3[10]="srce";
    char string4[10]="pik";

    //matrice0
    i=0;
    while(i<a){
        for(row=0;row<m;row++){
            for(column=0;column<n;column++){
                vkarte[i].matrica[row][column]=' ';
            }
        }
        i++;
    }
    //matrice1
    i=0;
    while(i<a){
        for(row=0;row<m;row++){
            for(column=0;column<n;column++){
                if(row==0 || row==m-1){
                    vkarte[i].matrica[row][column]=196;
                }
                else if(column==0 || column==n-1){
                    vkarte[i].matrica[row][column]=179;
                }
            }
        }
        vkarte[i].matrica[0][0]=218;
        vkarte[i].matrica[0][n-1]=191;
        vkarte[i].matrica[m-1][0]=192;
        vkarte[i].matrica[m-1][n-1]=217;
        i++;
    }
    //matrice2
    i=0;
    while(i<a){

        b=(karte[i].n)%13;
        if(b>=2 && b<=9){
            vkarte[i].matrica[1][1]=b+48;
            vkarte[i].matrica[m-2][n-2]=b+48;
        }
        else if(b==10){
                vkarte[i].matrica[1][1]=49;
                vkarte[i].matrica[1][2]=48;
                vkarte[i].matrica[m-2][n-3]=49;
                vkarte[i].matrica[m-2][n-2]=48;
        }
        else if(b==11){
                vkarte[i].matrica[1][1]=74;
                vkarte[i].matrica[m-2][n-2]=74;
        }
        else if(b==12){
                vkarte[i].matrica[1][1]=81;
                vkarte[i].matrica[m-2][n-2]=81;
        }
        else if(b==0){
                vkarte[i].matrica[1][1]=75;
                vkarte[i].matrica[m-2][n-2]=75;
        }
        else if(b==1){
                vkarte[i].matrica[1][1]=65;
                vkarte[i].matrica[m-2][n-2]=65;
        }
        i++;
    }
    //matrice3
    i=0;
    while(i<a){
        if(strcmp(karte[i].naziv,string1)==0){
            vkarte[i].matrica[3][1]='D';
            vkarte[i].matrica[3][2]='i';
            vkarte[i].matrica[3][3]='a';
            vkarte[i].matrica[3][4]='m';
            vkarte[i].matrica[3][5]='o';
            vkarte[i].matrica[3][6]='n';
            vkarte[i].matrica[3][7]='d';
            vkarte[i].matrica[3][8]='s';

        }
        else if(strcmp(karte[i].naziv,string2)==0){
            vkarte[i].matrica[3][2]='C';
            vkarte[i].matrica[3][3]='l';
            vkarte[i].matrica[3][4]='u';
            vkarte[i].matrica[3][5]='b';
            vkarte[i].matrica[3][6]='s';
        }
        else if(strcmp(karte[i].naziv,string3)==0){
            vkarte[i].matrica[3][2]='H';
            vkarte[i].matrica[3][3]='e';
            vkarte[i].matrica[3][4]='a';
            vkarte[i].matrica[3][5]='r';
            vkarte[i].matrica[3][6]='t';
            vkarte[i].matrica[3][7]='s';
        }
        else if(strcmp(karte[i].naziv,string4)==0){
            vkarte[i].matrica[3][2]='S';
            vkarte[i].matrica[3][3]='p';
            vkarte[i].matrica[3][4]='a';
            vkarte[i].matrica[3][5]='d';
            vkarte[i].matrica[3][6]='e';
            vkarte[i].matrica[3][7]='s';
        }
        i++;
    }


 }


 void memorymatrix(int b,int a,MemoryKarte *karte,VisualMemoryKarte *vkarte,int m,int n){

    int row,column,i;
    char string1[10]="dijamant";
    char string2[10]="zir";
    char string3[10]="srce";
    char string4[10]="pik";

    //matrice0
    i=0;
    while(i<a){
        for(row=0;row<m;row++){
            for(column=0;column<n;column++){
                vkarte[i].matrica[row][column]=' ';
            }
        }
        i++;
    }
    //matrice1
    i=0;
    while(i<a){
        for(row=0;row<m;row++){
            for(column=0;column<n;column++){
                if(row==0 || row==m-1){
                    vkarte[i].matrica[row][column]=196;
                }
                else if(column==0 || column==n-1){
                    vkarte[i].matrica[row][column]=179;
                }
            }
        }
        vkarte[i].matrica[0][0]=218;
        vkarte[i].matrica[0][n-1]=191;
        vkarte[i].matrica[m-1][0]=192;
        vkarte[i].matrica[m-1][n-1]=217;
        i++;
    }
    //matrice2
    i=0;
    while(i<a){

        b=(karte[i].n)%13;
        if(b>=2 && b<=9){
            vkarte[i].matrica[1][1]=b+48;
            vkarte[i].matrica[m-2][n-2]=b+48;
        }
        else if(b==10){
                vkarte[i].matrica[1][1]=49;
                vkarte[i].matrica[1][2]=48;
                vkarte[i].matrica[m-2][n-3]=49;
                vkarte[i].matrica[m-2][n-2]=48;
        }
        else if(b==11){
                vkarte[i].matrica[1][1]=74;
                vkarte[i].matrica[m-2][n-2]=74;
        }
        else if(b==12){
                vkarte[i].matrica[1][1]=81;
                vkarte[i].matrica[m-2][n-2]=81;
        }
        else if(b==0){
                vkarte[i].matrica[1][1]=75;
                vkarte[i].matrica[m-2][n-2]=75;
        }
        else if(b==1){
                vkarte[i].matrica[1][1]=65;
                vkarte[i].matrica[m-2][n-2]=65;
        }
        i++;
    }
    //matrice3
    i=0;
    while(i<a){
        if(strcmp(karte[i].naziv,string1)==0){
            vkarte[i].matrica[3][1]='D';
            vkarte[i].matrica[3][2]='i';
            vkarte[i].matrica[3][3]='a';
            vkarte[i].matrica[3][4]='m';
            vkarte[i].matrica[3][5]='o';
            vkarte[i].matrica[3][6]='n';
            vkarte[i].matrica[3][7]='d';
            vkarte[i].matrica[3][8]='s';

        }
        else if(strcmp(karte[i].naziv,string2)==0){
            vkarte[i].matrica[3][2]='C';
            vkarte[i].matrica[3][3]='l';
            vkarte[i].matrica[3][4]='u';
            vkarte[i].matrica[3][5]='b';
            vkarte[i].matrica[3][6]='s';
        }
        else if(strcmp(karte[i].naziv,string3)==0){
            vkarte[i].matrica[3][2]='H';
            vkarte[i].matrica[3][3]='e';
            vkarte[i].matrica[3][4]='a';
            vkarte[i].matrica[3][5]='r';
            vkarte[i].matrica[3][6]='t';
            vkarte[i].matrica[3][7]='s';
        }
        else if(strcmp(karte[i].naziv,string4)==0){
            vkarte[i].matrica[3][2]='S';
            vkarte[i].matrica[3][3]='p';
            vkarte[i].matrica[3][4]='a';
            vkarte[i].matrica[3][5]='d';
            vkarte[i].matrica[3][6]='e';
            vkarte[i].matrica[3][7]='s';
        }
        i++;
    }
    //negmatrice
    i=0;
    while(i<a){
        for(row=0;row<m;row++){
            for(column=0;column<n;column++){
                vkarte[i].negmatrica[row][column]=' ';
            }
        }
        i++;
    }
    //dmatrice0
    i=0;
    while(i<a){
        for(row=0;row<m;row++){
            for(column=0;column<n;column++){
                vkarte[i].dmatrica[row][column]=' ';
            }
        }
        i++;
    }
    //dmatrice1
    i=0;
    while(i<a){
        for(row=0;row<m;row++){
            for(column=0;column<n;column++){
                vkarte[i].dmatrica[row][column]='?';
            }
        }
        i++;
    }
    //dmatrice2
    i=0;
    while(i<a){
        for(row=0;row<m;row++){
            for(column=0;column<n;column++){
                if(row==0 || row==m-1){
                    vkarte[i].dmatrica[row][column]=196;
                }
                else if(column==0 || column==n-1){
                    vkarte[i].dmatrica[row][column]=179;
                }
            }
        }
        vkarte[i].dmatrica[0][0]=218;
        vkarte[i].dmatrica[0][n-1]=191;
        vkarte[i].dmatrica[m-1][0]=192;
        vkarte[i].dmatrica[m-1][n-1]=217;
        i++;
    }
    //dmatrice3
    int d,o;
    i=0;
    while(i<a){
        if(i+1<10){
            vkarte[i].dmatrica[3][4]=(i+1)+48;
        }
        else if(i+1>=10){

            d=(i+1)/10;
            o=(i+1)%10;

            vkarte[i].dmatrica[3][4]=d+48;
            vkarte[i].dmatrica[3][5]=o+48;
        }
        i++;
    }
    //dmatrice4
    i=0;
    while(i<a){
        if(i+1<10){
            vkarte[i].dmatrica[3][5]=5;
            vkarte[i].dmatrica[3][3]=5;
            vkarte[i].dmatrica[2][4]=5;
            vkarte[i].dmatrica[4][4]=5;
        }
        else if(i+1>=10){
            vkarte[i].dmatrica[3][6]=5;
            vkarte[i].dmatrica[3][3]=5;
            vkarte[i].dmatrica[2][4]=5;
            vkarte[i].dmatrica[2][5]=5;
            vkarte[i].dmatrica[4][4]=5;
            vkarte[i].dmatrica[4][5]=5;
        }
        i++;
    }
    //open
    i=0;
    while(i<a){
        vkarte[i].open=i+1;
        i++;
    }
 }



 void pyramid(VisualKarte* pomvisl,int dp,int m,int n){

 	int i,j,d,p=1,row,column,s;

    for(i=0;i<4;i++){
        for(row=0;row<m;row++){
        	if(i==0){
        		printf("               ");
			}
			else if(i==1){
				printf("          ");
			}
			else if(i==2){
				printf("     ");
			}
			else if(i==3){
				printf("");
			}
            j=dp;
            d=0;
            while(d<p){
                for(column=0;column<n;column++){

                        if((pomvisl[j].matrica[row][column]!=179-256) && (pomvisl[j].matrica[row][column]!=191-256) && (pomvisl[j].matrica[row][column]!=192-256) &&
						(pomvisl[j].matrica[row][column]!=196-256) && (pomvisl[j].matrica[row][column]!=217-256) && (pomvisl[j].matrica[row][column]!=218-256)){

						pomvisl[j].dmatrica[row][column]='?';
						}
						else{
							pomvisl[j].dmatrica[row][column]=pomvisl[j].matrica[row][column];
						}
                        printf("%c",pomvisl[j].dmatrica[row][column]);
                }

                d++;
                j++;
            }
            printf("\n");
        }
        dp=dp+p;
        p++;
    }
 }



 int* testphase(int br_igr,Karte* karte,int t,int *niz,int *j){

    int a,b,i;

    a=br_igr*5;
    b=a+t;
    //niz za provjeru karata koje se ponavljaju
    for(i=0;i<a;i++){
        if(strcmp(karte[b].broj,karte[i].broj)==0){
            niz[*j]=i+1;
            *j=*j+1;
        }
    }

    return niz;
 }


 int status(Igraci* igraci,int br_igraca,int* novibrojig){

    int i,min=10,status=0;

    for(i=0;i<br_igraca;i++){
        if(igraci[i].cardN+1<min+1){
            if(igraci[i].cardN!=0){
                min=igraci[i].cardN;
            }
        }
    }

    for(i=0;i<br_igraca;i++){
        if(igraci[i].cardN==min || igraci[i].cardN==0){
            igraci[i].status='N';
        }
        else{
            igraci[i].status='P';
            status++;
            *novibrojig=*novibrojig+1;
        }
    }
    return status;

 }



 int game(Karte *karte,VisualKarte *vkarte,Igraci *igraci,int a,Igra igra,int igrac){

    int r,c,i=0,m=7,n=10,answer,global=0,niz[5],result,mak;
    //timer
    time_t seconds,secondsafter,dseconds;
    secondsafter=time(NULL)+30;
    seconds=time(NULL);
    dseconds=time(NULL);

    igra.c='>';

    while(1){
        seconds=time(NULL);
        if(seconds>=secondsafter){
            system("cls");
            printf("\n\n\n\n");
            SetColor(14);
            igraci[igrac].timer=0;
            printf("\t \t TIME'S OUT,YOU LOSE.(0 sec. remaining)\n\n");
            system("pause");
            SetColor(15);

            return 1;
        }
        system("cls");
        SetColor(15);
        printf("%s is playing..\n",igraci[igrac].username);
        if(global==6){
            global=1;
        }
        //pocetni slucaj
        if(global==0){
            for(r=0;r<m;r++){
                i=0;
                while(i<5){
                    for(c=0;c<n;c++){
                        if(vkarte[i].matrica[3][2]=='C' || vkarte[i].matrica[3][2]=='S'){
                            SetColor(1);
                        }
                        else{
                            SetColor(4);
                        }
                        printf("%c",vkarte[i].matrica[r][c]);
                        SetColor(15);
                    }
                    niz[i]=i;
                    i++;
                }
                printf("\n");
            }
            mak=maks(niz);
            SetColor(14);
            printf("%c\n",igra.c);
            SetColor(15);
            igra.p=1;
        }
        //svi ostali updatei
        else{

            niz[igra.p-1]=mak+1;
            for(r=0;r<m;r++){
                i=0;
                while(i<5){
                    for(c=0;c<n;c++){
                        if(vkarte[niz[i]].matrica[3][2]=='C' || vkarte[niz[i]].matrica[3][2]=='S'){
                            SetColor(1);
                        }
                        else{
                            SetColor(4);
                        }
                        printf("%c",vkarte[niz[i]].matrica[r][c]);
                        SetColor(15);
                    }
                    i++;
                }
                printf("\n");
            }
            mak=maks(niz);
            if(igra.n==1){
                igra.p++;
            }
            else if(igra.n==2){
                igra.p=1;
            }
            //drugo
            SetColor(14);
            if(igra.p==1){
                printf("%c\n",igra.c);
            }
            else if(igra.p==2){
                printf("          %c\n",igra.c);
            }
            else if(igra.p==3){
                printf("                    %c\n",igra.c);
            }
            else if(igra.p==4){
                printf("                              %c\n",igra.c);
            }
            else if(igra.p==5){
                printf("                                        %c\n",igra.c);
            }
            else if(igra.p==6){
                printf("                                                  %c\n",igra.c);
                system("cls");
                printf("\n\n\n\n");
                igraci[igrac].timer=seconds-dseconds;
                printf("\t \t CONGRATULATIONS YOU MADE IT!!!!!(%d sec. remaining)\n\n",30-igraci[igrac].timer);
                SetColor(15);
                system("pause");
                return 0;
            }
            SetColor(15);

        }
        //gametest1
        result=gametest(niz,igra,vkarte,karte);
        printf("lower(1) or higher(2)??\n");
        scanf("%d",&answer);
        //gametest2
        if(result==answer){
            igra.n=1;
        }
        else{
            igra.n=2;

        }
        global++;

    }

 }

 int gametest(int *niz,Igra igra,VisualKarte *vkarte,Karte *karte){

    int i,max=0,b1,b2;
    //max
    for(i=0;i<5;i++){
        if(niz[i]>max){
            max=niz[i];
        }
    }

    //vrijednost karata
    b1=(karte[max+1].n)%13;
    b2=(karte[niz[igra.p-1]].n)%13;

    //za kartu king
    if(b1==0){
        b1=13;
    }
    if(b2==0){
        b2=13;
    }
    //provjera vece manje
    if(b1>b2){

        return 2;
    }
    else if(b1<b2){

        return 1;
    }


 }
 int maks(int *niz){


    int i,mak=0;
    for(i=0;i<5;i++){
        if(niz[i]>mak){
            mak=niz[i];
        }
    }
    return mak;
 }

 int finalgame(Igraci *igraci,MemoryKarte *memkarte,VisualMemoryKarte *vmemkarte,int a,int igrac){

    int r,c,m=7,n=10,i,duz,sir,global=1,openone,opentwo,cardN=0,fcard=0,dcard=0,endGame=0;

    time_t pocetno,ciljno,trenutno;
    pocetno=time(NULL);
    trenutno=time(NULL);
    ciljno=time(NULL)+180;


    //check
    i=0;
    while(i<a){
        vmemkarte[i].check=0;
        i++;
    }

    while(1){
        //nepar:nakon unosa update
        //timer
        trenutno=time(NULL);
        if(trenutno>=ciljno){
            return 1;
        }
        system("cls");
        printf("%s is playing...\n",igraci[igrac].username);
        if(global%2!=0){
            cardN=0;
            fcard=0;
            dcard=0;
            duz=0;
            while(duz<4){
                cardN=dcard;
                fcard=dcard;
                for(r=0;r<m;r++){
                    sir=0;
                    while(sir<6){
                        for(c=0;c<n;c++){
                            if(vmemkarte[cardN].check==1){
                                printf("%c",vmemkarte[cardN].negmatrica[r][c]);
                            }
                            else{
                                printf("%c",vmemkarte[cardN].dmatrica[r][c]);
                            }
                        }
                        cardN++;
                        sir++;
                    }
                    dcard=cardN;
                    cardN=fcard;
                    printf("\n");
                }

                duz++;
            }
        }
        global++;
        //provjerit jel igra gotova
        endGame=memorytesttwo(vmemkarte);
        if(endGame==5){
            return 0;
        }
        printf("\n\n");
        printf("enter which two cards you want to open?\n");
        printf("example if you want to open second and seventh card: 2,7\n");
        scanf("%d,%d",&openone,&opentwo);
        system("cls");
        //par:za otvorit karte nakon unosa
        printf("%s is playing...\n",igraci[igrac].username);
        if(global%2==0){
            cardN=0;
            fcard=0;
            dcard=0;
            duz=0;
            while(duz<4){
                cardN=dcard;
                fcard=dcard;
                for(r=0;r<m;r++){
                    sir=0;
                    while(sir<6){
                        for(c=0;c<n;c++){
                            if(vmemkarte[cardN].open==openone || vmemkarte[cardN].open==opentwo){
                                printf("%c",vmemkarte[cardN].matrica[r][c]);
                            }
                            else if(vmemkarte[cardN].check==1){
                                printf("%c",vmemkarte[cardN].negmatrica[r][c]);
                            }
                            else{
                                printf("%c",vmemkarte[cardN].dmatrica[r][c]);
                            }
                        }
                        cardN++;
                        sir++;
                    }
                    dcard=cardN;
                    cardN=fcard;
                    printf("\n");
                }
                duz++;
            }
        }
        memorytestone(openone,opentwo,vmemkarte);
        global++;
        system("pause");
    }
 }


 void memorytestone(int openone,int opentwo,VisualMemoryKarte *vmemkarte){
    int i;
    if(vmemkarte[openone-1].matrica[3][2]==vmemkarte[opentwo-1].matrica[3][2]){
        if(vmemkarte[openone-1].matrica[1][1]==vmemkarte[opentwo-1].matrica[1][1] &&
           vmemkarte[openone-1].matrica[1][2]==vmemkarte[opentwo-1].matrica[1][2]){
               vmemkarte[openone-1].check=1;
               vmemkarte[opentwo-1].check=1;
        }
    }

 }


 int memorytesttwo(VisualMemoryKarte *vmemkarte){

    int i,a=24,t=5;
    i=0;
    while(i<a){
        if(vmemkarte[i].check==0){
            t=1;
        }
        i++;
    }
    return  t;

 }

int main()
{
    Igraci *igraci;
    Igra igra;
    Karte *karte;
    VisualKarte *vkarte;
    NewKarte *newkarte;
    VisualNewKarte *vnewkarte;
    MemoryKarte *memkarte;
    VisualMemoryKarte *vmemkarte;

    karte=(Karte*)calloc(105,sizeof(Karte));
    vkarte=(VisualKarte*)calloc(105,sizeof(VisualKarte));
    newkarte=(NewKarte*)calloc(52,sizeof(NewKarte));
    vnewkarte=(VisualNewKarte*)calloc(52,sizeof(VisualNewKarte));
    memkarte=(MemoryKarte*)calloc(24,sizeof(MemoryKarte));
    vmemkarte=(VisualMemoryKarte*)calloc(24,sizeof(VisualMemoryKarte));

    int br_igraca,b,m=7,n=10,deckposition;//konstante
    int i,j,a,row,column,d,f,t,h,u=0;//brojaci
    int *niz,br_N=0;
    int G=0,S=0;

    niz=(int*)calloc(50,sizeof(int));



    char string1[10]="dijamant";
    char string2[10]="zir";
    char string3[10]="srce";
    char string4[10]="pik";


    srand(time(NULL));

    //Datoteke
    FILE* cards=NULL;
    cards=fopen("karte.txt","r");
    FILE* newcards=NULL;
    newcards=fopen("karte2.txt","r");
    FILE* memorycards=NULL;
    memorycards=fopen("karte3.txt","w");


    //Unos broja igraca
    printf("Number of players: \n");
    while(1){
        scanf("%d",&br_igraca);
        if(br_igraca<2){
            system("cls");
            printf("Too few players!!!\n");
            printf("Enter again: \n");
        }
        else if(br_igraca>10){
            system("cls");
            printf("Too many players!!!\n");
            printf("Enter again: \n");
        }
        else{
            break;
        }
    }


    //Unos imena igraca
    igraci=(Igraci*)malloc(sizeof(Igraci)*br_igraca);
    printf("Usernames:\n");
    for(i=0;i<br_igraca;i++){
        scanf(" %[^\n]%*c",igraci[i].username);
    }

	printf ("Press any key to get cards...\n");
    system("pause");
    system("cls");

    //Prijenos datoteke u strukturu
    i=0;
    while(fscanf(cards,"%d/%[^/]/%[^\n]%*[\n]",&karte[i].n,karte[i].naziv,karte[i].broj)==3){
        i++;
    }
    a=i;
    //mijesanje karata
    shuffleDeck(karte,a);

    //matrice
    matrix(b,a,karte,vkarte,m,n);
    //prikaz igracevih karata u konzoli
    deckposition=display(igraci,vkarte,br_igraca,i,j,f,d,row,column,m,n,niz);

    SetColor(15);
    printf ("Press any key to continue playing...\n");
    system("pause");

    //piramida
    pyramid(vkarte,deckposition,m,n);
    SetColor(15);

    printf ("Press to open cards.\n");
    system("pause");


    //otvaranje piramide
    f=br_igraca*5;
    int br_otvorenih=0,brojac=0,v=f;
    t=0;
    while(t<11){

		system("pause");
    	system("cls");
    	display(igraci,vkarte,br_igraca,i,j,f,d,row,column,m,n,niz);
        f=v;
    	for(i=0;i<4;i++){
            for(row=0;row<m;row++){
                if(i==0){
                    printf("                  ");
                }
                else if(i==1){
                    printf("          ");
                }
                else if(i==2){
                    printf("     ");
                }
                else if(i==3){
                    printf("");
                }
                j=f;
                brojac=0;
                while(brojac<i+1){
                    for(column=0;column<n;column++){
                        if(j<=t+v){
                            if(vkarte[j].matrica[3][2]=='C' || vkarte[j].matrica[3][2]=='S'){
                                SetColor(1);
                            }
                            else{
                                SetColor(4);
                            }
                            printf("%c",vkarte[j].matrica[row][column]);
                            SetColor(15);
                        }
                        else{
                             printf("%c",vkarte[j].dmatrica[row][column]);
                        }
                    }
                    j++;
                    brojac++;
                }
                printf("\n");
            }
            f=f+(i+1);
    	}
    	niz=testphase(br_igraca,karte,t,niz,&u);
    	t++;
    }


    system("pause");
    system("cls");
    printf("\n");
    SetColor(14);
    printf("CARD STATUS:\n");
    printf("USERNAME   NUMB.OF CARDS\n");
     printf("--------------------------------\n");
    SetColor(15);
    for(i=0;i<br_igraca;i++){
        printf("\n");
        printf("%s   %d\n",igraci[i].username,igraci[i].cardN);
    }

    //RANG
    for(i=0;i<br_igraca;i++){
        for(j=0;j<br_igraca-1;j++){
            if(igraci[j].cardN<igraci[j+1].cardN){

                Igraci z=igraci[j];
                igraci[j]=igraci[j+1];
                igraci[j+1]=z;

            }
        }
    }

    //NEW PARAGRAPH
    S=status(igraci,br_igraca,&br_N);
    SetColor(14);
    printf("--------------------------------\n");
    printf("THE GAME CONTINUES FOR:\n\n");
    SetColor(15);
    for(i=0;i<br_igraca;i++){
        if(S==0){
            printf("%s\n\n",igraci[i].username);
        }
        else if(igraci[i].status=='P'){
            printf("%s\n\n",igraci[i].username);


        }
    }


    system("pause");
    //Main Game
    for(i=0;i<br_igraca;i++){
        if(S==0){
            shuffleDeck(karte,a);
            matrix(b,a,karte,vkarte,m,n);
            G=game(karte,vkarte,igraci,a,igra,i);
        }
        else if(igraci[i].status=='P'){
            shuffleDeck(karte,a);
            matrix(b,a,karte,vkarte,m,n);
            G=game(karte,vkarte,igraci,a,igra,i);

        }
    }


    system("pause");
    system("cls");
    printf("\n");
    SetColor(14);
    printf("THE GAME CONTINUES FOR:\n\n");
    SetColor(15);
    int provjera1=0;
    for(i=0;i<br_igraca;i++){
        if(S==0){
            if(igraci[i].timer!=0){
                provjera1=1;
                printf("%s\n\n",igraci[i].username);
            }

        }
        else if(igraci[i].status=='P'){
            if(igraci[i].timer!=0){
                provjera1=1;
                printf("%s\n\n",igraci[i].username);
            }

        }
    }

    printf("\n\n\n");
    SetColor(14);
    printf("TIME REMAINING  NUMB.OF CARDS    TOTAL SCORE\n");
    printf("-------------------------------------------\n");
    SetColor(15);
     for(i=0;i<br_igraca;i++){
        if(S==0){
            if(igraci[i].timer!=0){
                igraci[i].total=(30-igraci[i].timer)*igraci[i].cardN;
                printf("%d sec.         %d              %d\n",30-igraci[i].timer,igraci[i].cardN,igraci[i].total);
            }

        }
        else if(igraci[i].status=='P'){
            if(igraci[i].timer!=0){
                igraci[i].total=(30-igraci[i].timer)*igraci[i].cardN;
                printf("%d sec.         %d              %d\n",30-igraci[i].timer,igraci[i].cardN,igraci[i].total);
            }

        }
    }
    system("pause");
    if(provjera1==0){
        SetColor(14);
        system("cls");
        printf("you all lost.\n\n\n");
        for(i=0;i<10;i++){
            printf("\t \t ");
            for(j=0;j<10;j++){
                printf("GAME OVER ");
            }
            printf("\n\n\n");
        }
        SetColor(15);
        exit(0);
    }
    //RANG
    for(i=0;i<br_igraca;i++){
        for(j=0;j<br_igraca-1;j++){
            if(igraci[j].total<igraci[j+1].total){

                Igraci zp=igraci[j];
                igraci[j]=igraci[j+1];
                igraci[j+1]=zp;

            }
        }
    }
    //FINAL GAME
    i=0;
    while(fscanf(newcards,"%d/%[^/]/%[^\n]%*[\n]",&newkarte[i].n,newkarte[i].naziv,newkarte[i].broj)==3){
        i++;
    }
    a=i;
    int bc;
    shuffleNewDeck(newkarte,a);
    newmatrix(bc,a,newkarte,vnewkarte,m,n);

    fclose(cards);
    fclose(newcards);

    //pisanje u datoteku
    for(i=0;i<12;i++){
        fprintf(memorycards,"%d/%s/%s\n",newkarte[i].n,newkarte[i].naziv,newkarte[i].broj);
    }
    fclose(memorycards);
    memorycards=fopen("karte3.txt","r");
    i=0;
    while(fscanf(memorycards,"%d/%[^/]/%[^\n]%*[\n]",&memkarte[i].n,memkarte[i].naziv,memkarte[i].broj)==3){
        i++;
    }
    a=i;
    j=a;
    for(i=0;i<j;i++){
        memkarte[a].n=memkarte[i].n;
        strcpy(memkarte[a].naziv,memkarte[i].naziv);
        strcpy(memkarte[a].broj,memkarte[i].broj);
        a++;

    }

    int mc,EG;
    for(i=0;i<br_igraca;i++){
        if(S==0){
            if(igraci[i].timer!=0){
                 shuffleMemDeck(memkarte,a);
                 memorymatrix(mc,a,memkarte,vmemkarte,m,n);
                 EG=finalgame(igraci,memkarte,vmemkarte,a,i);
                 if(EG==0){
                    SetColor(14);
                    system("cls");
                    printf("you won.\n\n\n");
                    for(i=0;i<10;i++){
                        printf("\t \t ");
                        for(j=0;j<10;j++){
                            printf("WINNER WINNER ");
                        }
                        printf("\n\n\n");
                    }
                    SetColor(15);
                    exit(0);
                 }
                 else if(EG==1){
                    SetColor(14);
                    system("cls");
                    printf("\t \t TIME'S OUT,YOU LOSE.\n\n\n");
                    system("pause");
                    SetColor(15);
                 }
            }

        }
        else if(igraci[i].status=='P'){
            if(igraci[i].timer!=0){
                 shuffleMemDeck(memkarte,a);
                 memorymatrix(mc,a,memkarte,vmemkarte,m,n);
                 EG=finalgame(igraci,memkarte,vmemkarte,a,i);
                 if(EG==0){
                    SetColor(14);
                    system("cls");
                    printf("you won.\n\n\n");
                    for(i=0;i<10;i++){
                        printf("\t \t ");
                        for(j=0;j<10;j++){
                            printf("WINNER WINNER ");
                        }
                        printf("\n\n\n");
                    }
                    SetColor(15);
                    exit(0);
                 }
                 else if(EG==1){
                    SetColor(14);
                    system("cls");
                    printf("\t \t TIME'S OUT,YOU LOSE.\n\n\n");
                    system("pause");
                    SetColor(15);
                 }
            }

        }
    }

    fclose(memorycards);

    return 0;

}
