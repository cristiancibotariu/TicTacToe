#include <bits/stdc++.h>
#include <graphics.h>
#include <cstdlib>
#include <time.h>
using namespace std;
int x, y, cadran, viz[10], m, pozitii_libere, game_over, tb, a[3][3], egal;

/*
    x si y sunt folosite ca coordonate pentru click-uri
    cadran retine zona curenta de pe tabla de joc
    viz retine cadranele vizitate si ajuta la testarea conditiilor de castig
    m tine cont de jucatorul al carui este randul
    pozitii_libere tine cont de numarul de pozitii libere ramase
    game_over este 1 cand jocul este terminat si 0 cand nu este gata inca
    egal este 1 daca rezultatul este egalitate, 0 in caz contrar

    variabila m1 folosita local mai jos tine cont daca o tura a luat sfarsit sau nu
*/

void meniu()//meniu bot/player
{
    line(100,250,100,350);
    line(100,250,700,250);
    line(700,250,700,350);
    line(100,350,700,350);
    line(400,250,400,350);
    outtextxy(200,290,"vs Bot");
    outtextxy(485,290,"2 Jucatori");
}
void dificultate_bot()
{
    line(100,100,100,175);
    line(100,175,700,175);
    line(700,175,700,100);
    line(700,100,100,100);

    line(100,200,100,275);
    line(100,275,700,275);
    line(700,275,700,200);
    line(700,200,100,200);

    line(100,300,100,375);
    line(100,375,700,375);
    line(700,375,700,300);
    line(700,300,100,300);

    outtextxy(350,120,"Usor");
    outtextxy(330,220,"Normal");
    outtextxy(300,320,"Imposibil");
}
void init_joc() //initializam tabla
{
    line(300,0,300,600);
    line(500,0,500,600);
    line(100,200,700,200);
    line(100,400,700,400);
}
void egalitate()
{
    delay(1000);
    cleardevice();
    line(100,290,100,350);
    line(100,290,700,290);
    line(700,290,700,350);
    line(100,350,700,350);
    outtextxy(300,300,"Egalitate!");
}
int pozitie(int x, int y) //Afla in ce pozitie ne aflam
{
    if(x>=100 && x<300 && y>=0 && y<200)
        return 1;
    if(x>=300 && x<500 && y>=100 && y<200)
        return 2;
    if(x>=500 && x<=700 && y>=100 && y<200)
        return 3;
    if(x>=100 && x<300 && y>=200 && y<400)
        return 4;
    if(x>=300 && x<500 && y>=200 && y<400)
        return 5;
    if(x>=500 && x<=700 && y>=200 && y<400)
        return 6;
    if(x>=100 && x<300 && y>=400 && y<=600)
        return 7;
    if(x>=300 && x<500 && y>=400 && y<=600)
        return 8;
    if(x>=500 && x<=700 && y>=400 && y<=600)
        return 9;
}
void desen_X(int s) // desenam x-uri in functie de cadran
{
    if(cadran==1)
    {
        line(110, 10, 290, 190);
        line(110, 190, 290, 10);
        return;
    }
    if(cadran==2)
    {
        line(310, 10, 490, 190);
        line(310, 190, 490, 10);
        return;
    }
    if(cadran==3)
    {
        line(510, 10, 690, 190);
        line(510, 190, 690, 10);
        return;
    }
    if(cadran==4)
    {
        line(110, 210, 290, 390);
        line(110, 390, 290, 210);
        return;
    }
    if(cadran==5)
    {
        line(310, 210, 490, 390);
        line(310, 390, 490, 210);
        return;
    }
    if(cadran==6)
    {
        line(510, 210, 690, 390);
        line(510, 390, 690, 210);
        return;
    }
    if(cadran==7)
    {
        line(110, 410, 290, 590);
        line(110, 590, 290, 410);
        return;
    }
    if(cadran==8)
    {
        line(310, 410, 490, 590);
        line(310, 590, 490, 410);
        return;
    }
    if(cadran==9)
    {
        line(510, 410, 690, 590);
        line(510, 590, 690, 410);
        return;
    }
}
void desen_0(int s) // se deseneaza in casuta corespunzatoare un cerc, reprezentand zeroul
{


    if(cadran==1)
    {
        circle(200, 100, 80);
        return;
    }
    if(cadran==2)
    {
        circle(400, 100, 80);
        return;
    }
    if(cadran==3)
    {
        circle(600, 100, 80);
        return;
    }
    if(cadran==4)
    {
        circle(200, 300, 80);
        return;
    }
    if(cadran==5)
    {
        circle(400, 300, 80);
        return;
    }
    if(cadran==6)
    {
        circle(600, 300, 80);
        return;
    }
    if(cadran==7)
    {
        circle(200, 500, 80);
        return;
    }
    if(cadran==8)
    {
        circle(400, 500, 80);
        return;
    }
    if(cadran==9)
    {
        circle(600, 500, 80);
        return;
    }
}
bool x_castiga() // la aceste 2 functii se testeaza toate combinatiile de castig la x si zero
{
    if(viz[1]+viz[2]+viz[3]==3 || viz[4]+viz[5]+viz[6]==3 || viz[7]+viz[8]+viz[9]==3 ||
            viz[1]+viz[4]+viz[7]==3 || viz[2]+viz[5]+viz[8]==3 || viz[3]+viz[6]+viz[9]==3
            || viz[1]+viz[5]+viz[9]==3 || viz[3]+viz[5]+viz[7]==3)
        return 1;
    else return 0;

}
bool zero_castiga()
{
    if(viz[1]+viz[2]+viz[3]==-3 || viz[4]+viz[5]+viz[6]==-3 || viz[7]+viz[8]+viz[9]==-3 ||
            viz[1]+viz[4]+viz[7]==-3 || viz[2]+viz[5]+viz[8]==-3 || viz[3]+viz[6]+viz[9]==-3
            || viz[1]+viz[5]+viz[9]==-3 || viz[3]+viz[5]+viz[7]==-3)
        return 1;
    else return 0;
}
void reprez_matrice()
{
    int k=1;
    for(int i=1; i<=3; i++)
        for(int j=1; j<=3; j++)
        {
            a[i][j]=viz[k];
            k++;
        }
}
void zero_bot_easy()
{
    int m1=1;
    while(m1!=0)
    {
        srand(time(NULL));
        cadran=rand()%9+1; // se ia o valoare random intre 0 si 8, la care se adauga 1 pentru a fi in intervalul necesar
        if(viz[cadran]==0)
        {
            desen_0(cadran); // desenam
            m1=0; // se incheie tura
            viz[cadran]=-1;
            pozitii_libere-=1;
            if(zero_castiga()==1) // daca botul castiga: se termina jocul, se goleste ecranul si apare mesajul corespunzator
            {
                game_over=1;
                delay(1000);
                cleardevice();
                line(100,290,100,350);
                line(100,290,700,290);
                line(700,290,700,350);
                line(100,350,700,350);
                outtextxy(270,300,"Ai pierdut!");
                egal=0;
            }
        }
    }
    m=1;

}
void zero_bot_medium()
{
    int m1=1;
    while(m1!=0)
    {   cadran=0;
        while(cadran==0)
        {
            if(tb==1)
            {
                srand(time(NULL));    // se ia o valoare random intre 0 si 8, la care se adauga 1 pentru a fi in intervalul necesar
                cadran=rand()%9+1;
            }
            else
            {
                if(tb==2)
                {
                    int i,j;
                    for(i=1; i<=3; i++)
                        for(j=1; j<=3; j++)
                            if(a[i][j]==-1)
                                break;
                    for(int k1=-1; k1<=1 && cadran==0; k1++)
                    {
                        for(int k2=1; k2>=-1 && cadran==0; k2--)
                            if(a[i+k1][j+k2]==0)
                            {
                                if(i+k1==1 && j+k2==1)
                                {
                                    cadran=1;
                                    break;
                                }
                                if(i+k1==2 && j+k2==1)
                                {
                                    cadran=4;
                                    break;
                                }
                                if(i+k1==3 && j+k2==1)
                                {
                                    cadran=7;
                                    break;
                                }
                                if(i+k1==1 && j+k2==2)
                                {
                                    cadran=2;
                                    break;
                                }
                                if(i+k1==2 && j+k2==2)
                                {
                                    cadran=5;
                                    break;
                                }
                                if(i+k1==3 && j+k2==2)
                                {
                                    cadran=8;
                                    break;
                                }
                                if(i+k1==1 && j+k2==3)
                                {
                                    cadran=3;
                                    break;
                                }
                                if(i+k1==2 && j+k2==3)
                                {
                                    cadran=6;
                                    break;
                                }
                                if(i+k1==3 && j+k2==3)
                                {
                                    cadran=9;
                                    break;
                                }
                            }
                    }
                    if(cadran==0)
                        tb=1;

                }
                if(tb==3)
                {
                    if(a[1][1]+a[1][2]==-2 && a[1][3]==0)
                        cadran=3;
                    if(a[1][1]+a[1][3]==-2 && a[1][2]==0)
                        cadran=2;
                    if(a[1][2]+a[1][3]==-2 && a[1][1]==0)
                        cadran=1;
                    if(a[2][1]+a[2][2]==-2 && a[2][3]==0)
                        cadran=6;
                    if(a[2][2]+a[2][3]==-2 && a[2][1]==0)
                        cadran=4;
                    if(a[2][1]+a[2][3]==-2 && a[2][2]==0)
                        cadran=5;
                    if(a[3][1]+a[3][2]==-2 && a[3][3]==0)
                        cadran=9;
                    if(a[3][2]+a[3][3]==-2 && a[3][1]==0)
                        cadran=7;
                    if(a[3][1]+a[3][3]==-2 && a[3][2]==0)
                        cadran=8;
                    if(a[1][1]+a[2][1]==-2 && a[3][1]==0)
                        cadran=7;
                    if(a[2][1]+a[3][1]==-2 && a[1][1]==0)
                        cadran=1;
                    if(a[1][1]+a[3][1]==-2 && a[2][1]==0)
                        cadran=4;
                    if(a[1][2]+a[2][2]==-2 && a[3][2]==0)
                        cadran=8;
                    if(a[1][2]+a[3][2]==-2 && a[2][2]==0)
                        cadran=5;
                    if(a[2][2]+a[3][2]==-2 && a[1][2]==0)
                        cadran=2;
                    if(a[1][3]+a[2][3]==-2 && a[3][3]==0)
                        cadran=9;
                    if(a[1][3]+a[3][3]==-2 && a[2][3]==0)
                        cadran=6;
                    if(a[2][3]+a[3][3]==-2 && a[1][3]==0)
                        cadran=3;
                    if(a[1][1]+a[2][2]==-2 && a[3][3]==0)
                        cadran=9;
                    if(a[1][1]+a[3][3]==-2 && a[2][2]==0)
                        cadran=5;
                    if(a[2][2]+a[3][3]==-2 && a[1][1]==0)
                        cadran=1;
                    if(a[1][3]+a[2][2]==-2 && a[3][1]==0)
                        cadran=7;
                    if(a[1][3]+a[3][1]==-2 && a[2][2]==0)
                        cadran=5;
                    if(a[3][1]+a[2][2]==-2 && a[1][3]==0)
                        cadran=3;
                    if(cadran==0)
                        tb=2;
                }
            }
        }
        if(viz[cadran]==0)
        {
            desen_0(cadran); // desenam
            m1=0; // se incheie tura
            viz[cadran]=-1;
            pozitii_libere-=1;
            if(zero_castiga()==1) // daca botul castiga: se termina jocul, se goleste ecranul si apare mesajul corespunzator
            {
                game_over=1;
                delay(1000);
                cleardevice();
                line(100,290,100,350);
                line(100,290,700,290);
                line(700,290,700,350);
                line(100,350,700,350);
                outtextxy(270,300,"Ai pierdut!");
                egal=0;
            }
        }
    }
    m=1;
}
void zero_bot_impossible()
{
    int m1=1;
    while(m1!=0)
    {
        cadran=0;
        while(cadran==0)
        {
            if(tb==1)
            {
                srand(time(NULL));
                cadran=rand()%9+1;
            }
            else
            {
                if(a[1][1]+a[1][2]==2 && a[1][3]==0)
                    cadran=3;
                if(a[1][1]+a[1][3]==2 && a[1][2]==0)
                    cadran=2;
                if(a[1][2]+a[1][3]==2 && a[1][1]==0)
                    cadran=1;
                if(a[2][1]+a[2][2]==2 && a[2][3]==0)
                    cadran=6;
                if(a[2][2]+a[2][3]==2 && a[2][1]==0)
                    cadran=4;
                if(a[2][1]+a[2][3]==2 && a[2][2]==0)
                    cadran=5;
                if(a[3][1]+a[3][2]==2 && a[3][3]==0)
                    cadran=9;
                if(a[3][2]+a[3][3]==2 && a[3][1]==0)
                    cadran=7;
                if(a[3][1]+a[3][3]==2 && a[3][2]==0)
                    cadran=8;
                if(a[1][1]+a[2][1]==2 && a[3][1]==0)
                    cadran=7;
                if(a[2][1]+a[3][1]==2 && a[1][1]==0)
                    cadran=1;
                if(a[1][1]+a[3][1]==2 && a[2][1]==0)
                    cadran=4;
                if(a[1][2]+a[2][2]==2 && a[3][2]==0)
                    cadran=8;
                if(a[1][2]+a[3][2]==2 && a[2][2]==0)
                    cadran=5;
                if(a[2][2]+a[3][2]==2 && a[1][2]==0)
                    cadran=2;
                if(a[1][3]+a[2][3]==2 && a[3][3]==0)
                    cadran=9;
                if(a[1][3]+a[3][3]==2 && a[2][3]==0)
                    cadran=6;
                if(a[2][3]+a[3][3]==2 && a[1][3]==0)
                    cadran=3;
                if(a[1][1]+a[2][2]==2 && a[3][3]==0)
                    cadran=9;
                if(a[1][1]+a[3][3]==2 && a[2][2]==0)
                    cadran=5;
                if(a[2][2]+a[3][3]==2 && a[1][1]==0)
                    cadran=1;
                if(a[1][3]+a[2][2]==2 && a[3][1]==0)
                    cadran=7;
                if(a[1][3]+a[3][1]==2 && a[2][2]==0)
                    cadran=5;
                if(a[3][1]+a[2][2]==2 && a[1][3]==0)
                    cadran=3;
                if(cadran==0)
                    tb=1;
            }
        }
        if(viz[cadran]==0)
        {
            desen_0(cadran); // desenam
            m1=0; // se incheie tura
            viz[cadran]=-1;
            pozitii_libere-=1;
            if(zero_castiga()==1) // daca botul castiga: se termina jocul, se goleste ecranul si apare mesajul corespunzator
            {
                game_over=1;
                delay(1000);
                cleardevice();
                line(100,290,100,350);
                line(100,290,700,290);
                line(700,290,700,350);
                line(100,350,700,350);
                outtextxy(270,300,"Ai pierdut!");
                egal=0;
            }
        }
    }
    m=1;
}
void zero_player()
{
    int m1=1; // incepe tura
    while(m1!=0)
    {
        while(!ismouseclick(WM_LBUTTONDOWN)) // se asteapta click
            delay(1000);
        getmouseclick(WM_LBUTTONDOWN, x, y); // se iau coordonatele click ului
        cadran=pozitie(x, y); // se retine in cadran pozitia propriu-zisa
        if(viz[cadran]==0)
        {
            desen_0(cadran); // se deseneaza
            m1=0; // se termina tura
            viz[cadran]=-1;
            pozitii_libere-=1; // se scade numarul pozitiilor libere
            if(zero_castiga()==1) // daca sunt implinite conditiile de castig: se termina jocul, se goleste ecranul si apare mesajul corespunzator
            {
                game_over=1;
                delay(1000);
                cleardevice();
                line(100,290,100,350);
                line(100,290,700,290);
                line(700,290,700,350);
                line(100,350,700,350);
                outtextxy(130,300,"Zero este invingator!");
                egal=0;
            }
        }
    }
    m=1; // se schimba tura pe x
}

void X()
{
    int m1=1; // incepe randul jucatorului cu x
    while(m1!=0)
    {
        while(!ismouseclick(WM_LBUTTONDOWN))
        {
            delay(1000);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        cadran=pozitie(x, y);
        if(viz[cadran]==0)
        {
            desen_X(cadran);
            m1=0; // randul jucatorului cu x s-a terminat
            viz[cadran]=1;
            pozitii_libere-=1;
            if(x_castiga()==1)
            {
                game_over=1; // jocul s-a terminat
                delay(1000);
                cleardevice();
                line(100,290,100,350);
                line(100,290,700,290);
                line(700,290,700,350);
                line(100,350,700,350);
                outtextxy(180,300,"X este invingator!");
                egal=0;
            }
        }
    }
    m=0;
}
int main()
{
    tb=0;
    int dificultate=0;
    initwindow(800, 600);
    settextstyle(8,0,3); // modificam formatul textului
    meniu();
    settextstyle(8,0,5);
    pozitii_libere=9;
    game_over=0;
    m=1; //tine cont de a cui este tura
    egal=1; // ramane 1 daca la final este egalitate
    while(!ismouseclick(WM_LBUTTONDOWN)) // meniul vs player/bot
    {
        delay(1000);
    }
    int bot=0;
    getmouseclick(WM_LBUTTONDOWN, x, y); // ismouseclick asteapta click stanga si getmouseclick ia "coordonatele" clickului
    if(x>=100 && x<400)
    {
        bot=1;
        cleardevice(); // goleste window-ul
        dificultate_bot();
        while(!ismouseclick(WM_LBUTTONDOWN)) // meniul dificultate bot
        {
            delay(1000);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(y>=100 && y<=175)
            dificultate=1;
        if(y>=200 && y<=275)
            dificultate=2;
        if(y>=300 && y<=375)
            dificultate=3;
    }
    cleardevice();
    init_joc();
    while(game_over==0)
    {
        if(m==1) // se verifica al cui rand este
        {
            X();
        }
        else
        {
            if(bot==0)
                zero_player();
            else
            {
                if(dificultate==1)
                    zero_bot_easy();
                if(dificultate==2)
                {
                    tb++;
                    reprez_matrice();
                    zero_bot_medium();
                }
                if(dificultate==3)
                {
                    tb++;
                    reprez_matrice();
                    zero_bot_impossible();
                }
            }
        }
        if(pozitii_libere==0)
            game_over=1;
    }
    if(egal==1)
        egalitate();
    getch();
    closegraph();
    return 0;
}
