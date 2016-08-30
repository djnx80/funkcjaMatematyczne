// wykorzystanie funkcji matematycznych
// rozdzielic na kilka czesci, kazda funkcje osobno

//#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include "allegroStart.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* sin */
#include <string>
#include <cmath>

#define PI 3.14159265

void point(unsigned char *pt, int xx, int yy, unsigned char r, unsigned char g, unsigned char b);
void rysujFunkcje();
void spirala(int ileP, double r, double dr);
void funkcja3D(int ileP);
//void plaszczyzna();
void plaszczyzna(double pA, double pB, double pC, double pD);
void plaszczyzna2(double pA, double pB, double pC, double pD);
void dwieFunkcje();
void spirala2(double A, double K, double B, double C, double D);



using namespace std;

allegroStart mA(800,600);
ALLEGRO_DISPLAY *okno = mA.openWindow();
ALLEGRO_BITMAP  *bitmapa = mA.openBitmap(800,600);
ALLEGRO_KEYBOARD_STATE klawisz;
ALLEGRO_LOCKED_REGION *lr;
unsigned char *ptr;

float udx = 0.1, udy = 0.1, udz=0.1;
float A=1.0, B=1.0;
float C=1.0, D=1.0;

//void *__gxx_personality_v0;


int main()  {

    double tdr=1000;
    double tpA=1, tpB=1, tpC=0, tpD=0.1;


    while( !al_key_down( & klawisz, ALLEGRO_KEY_ESCAPE ) )    {
        lr = al_lock_bitmap(bitmapa, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY);
        ptr = (unsigned char *)lr->data;

		al_clear_to_color(al_map_rgb(0,0,0));

        tdr+=1;
        tpB+=1;
        tpC+=2;
      //  plaszczyzna2(tdr/2,tpB/3,tpC/2,10);
   //    rysujFunkcje();
 //   spirala2(100,100,10,10,10);
//            spirala(50,1,tdr*tpC);
  //    funkcja3D(5000);
  //     plaszczyzna(tpA,tpB, tpC, tpD);

    dwieFunkcje();


        al_draw_bitmap(bitmapa,0,0,0);
        al_unlock_bitmap(bitmapa);
        al_flip_display();
        al_get_keyboard_state( & klawisz );
        al_rest(0.004);
        }

	return 0;
}
void plaszczyzna2(double pA, double pB, double pC, double pD)  {
    unsigned char grey=250;
    double z,u,v,q=5,alfa=pA;
    double wys[900];
    double r;

    for (int i=0; i<800; i++)   { wys[i]=-200;}

    for (double y=-400; y<400; y=y+10)   {
        for (double x=-400; x<400; x=x+1)   {
            r = sqrt(x*x+y*y);
            //    z = 200*exp(-(x*x+y*y)/pB/100);
       //     z = cos(r*PI/pC)*sin(r*PI/pC)*pC;
         //   z = pow( (sin((r+y)*PI/180)+cos((x-y)*PI/180)),3 )*pC/20;       // fajny efekt gór i dolin

            z = pC*(x*x*x-y*y)*sin((x+y)/20)/(x*x+y*y+0.3)/1000;
       // z = exp(-cos(r*PI/280)*pC/10)/100;
            if (z<0)    {   grey = 0; }
                else if (z>255) {   grey = 255; }
                else { grey = z;}
        //    u = x + q*y*cos(alfa*PI/180);
        //    v = z + q*y*sin(alfa*PI/180);
            u = x-0.5*y;
            v = z+0.5*y;
            if (400+u>=0 && 400+u<900)  {
                if (v>wys[(int)u+400])  {
                    point(ptr, 400+u,300-v, 250, grey, grey/10);
                    wys[(int)u+400] = v;
               }
            }
        }
    }
}

void spirala2(double A, double K, double B=0, double C=0, double D=0) {
    double omega=0,x,y,r,wsp;
    unsigned char grey=250;

    for (double fi=5; fi<5000; fi+=0.01)   {
        omega = fi*PI/180;
//        r = A*omega;
        r = 100*A/omega;
//        r = K*cos(A*omega);
//        r = K*cos(A*sin(B*omega));
//        r = K*(cos(A*omega)-abs(sin(B*omega)));
//        wsp = B+C*exp(-A*omega);
//        r = K*(1-exp(-A*omega) + wsp*sin(D*omega));
        x = 400+(r*cos(omega));
        y = 300-(r*sin(omega));

        point(ptr,x,y,grey,grey,grey);
    }
}

void dwieFunkcje()  {
    unsigned char grey=250;
    double x,y;
    double r1=150;
    double r2=150;
    double r=150;

    C+=0.05;
    D+=0.2;
    for (double alfa = 0; alfa<360; alfa+=0.01)  {
//        A = sin(alfa*PI/C)*1;
//        C = sin(alfa*PI/80)*alfa;
    r1 = cos(alfa*PI/280*C)*alfa;
//    r2=r1;
    r2 = sin(alfa*PI/180*D)*alfa;

        x = cos(alfa*PI/180*A)*r1;
        y = sin(alfa*PI/180*B)*r2;
        grey = alfa / 1.5;
        point(ptr, 400+x,300+y, grey, grey, grey);

    }
}

void plaszczyzna(double pA, double pB, double pC, double pD)  {
    // wzor 5x+2y-4z+3=0
    double d=100;
    unsigned char grey=250;
    double a,b,c;
  //  double pA=3, pB=4, pC=4, pD=-7;
    double x0,y0,z;
    pA = sin(pA*PI/180*A)*50;
    pB = sin(pB*PI/180*A)*50;

    a = -(pD/pA);
    b = -(pD/pB);
    c = -(pD/pC);
    A+=0.005;
    B+=0.002;

    for (double x=-250; x<250; x=x+5)   {
        for (double y=-250; y<250; y=y+5)   {

    pA = sin(x*PI/280)*50;
    pB = cos(y*PI/180)*60;
   // pC=sin(y*PI/x)*50;
                a = -(pD/pA);
    b = -(pD/pB);
    c = -(pD/pC);


      //      a = sin(x*PI/180*A)*50;
      //      b = cos(x*PI/180*B)*50;
            z = c*(1-(x/a)-(y/b));
            x0 = (d*x)/(z+d);
            y0 = (d*y)/(z+d);
            point(ptr, 400+x0,300+y0, grey, grey, grey);
        }
    }
}

void funkcja3D(int ileP)    {
    double d=300;
    double x,y,z;

    double ux=0.1, uy=500, uz=1;
    unsigned char grey;

    udx=udx+0.0;
    udy=udy+0.0;
    udz=udz+0.00005;
    A+=0.0002;      // im wyzsze wartosci tym szybciej sie porusza
    B+=0.0001;
    C+=0.0;
    D+=0.0001;
    double wsp = ileP / 250;

    for (int n=0; n<ileP; n++)  {
        x=sin(n*PI/180*A)*cos(n*PI/180*B);
        y=sin(n*PI/180*C)*cos(n*PI/180*D);
        z=cos(n*PI/180*C);

                x=x*ux;
        ux=ux+udx;
        y=y*uy;
        uy=uy-udy;
        z=z*uz;
        uz=uz-udz;
        x = (d*x)/(z+d);
        y = (d*y)/(z+d);
        grey = (unsigned char)z;
    //    if (grey>255)
    //        grey=255;
   //     if (grey<0)
   //         grey=0;
       grey=250;
        point(ptr, 400+x,300+y, grey, grey, grey);
    }
}

void spirala(int ileP, double r, double dr)  {
    double x,y;
    unsigned char grey=250;
    A+=0.0002;
    B+=0.0001;

    for (int n=0; n<ileP; n++)  {
            x = cos(n*PI/180*A)*r;
            x = cos((n/2)*PI/200*A)*r;;
            y = sin(n*PI/180*B)*r;
            y = (sin(n*PI/180*B)*sin(n*PI/250*A))*r;
            grey = n / 40;
            point(ptr, 400+x, 300+y, 250, grey, grey);
            r+=dr;
    }
}

void rysujFunkcje() {
    float x,y,ux=0.1, uy=500;
    unsigned char grey;

    udx=udx+0.0;
    udy=udy+0.0;
    A+=0.0002;
    B+=0.0001;
    C+=0.000;
    D+=0.0001;

    for (int n=0; n<7000; n++)   {
        x=sin(n*PI/180*A)*cos(n*PI/180*B);
        y=sin(n*PI/180*C)*cos(n*PI/180*D);
        x=x*ux;
        ux=ux+udx;
        y=y*uy;
        uy=uy-udy;
        grey = n/28;
        point(ptr, 400+x,300+y, grey, grey, grey);
    }
}

void point(unsigned char *pt, int xx, int yy,unsigned char r, unsigned char g, unsigned char b) {
    // rysuje pixel w (xx,yy) o kolorze (r,g,b) i alfa=250;
    if (xx<mA.screenW && yy<mA.screenH && xx>0 && yy>0) {
        int pixel;
        pixel = xx+yy*mA.screenW;
        pt[pixel*4] = r;
        pt[pixel*4+1] = g;
        pt[pixel*4+2] = b;
        pt[pixel*4+3] = 250;
    }
}


