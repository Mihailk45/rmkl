#include "TXLib.h"
//structuri_start
struct Hp
{
    int vid_nom;
    HDC blits;
    int clectka_x;
    int clectka_y;
    int x;
    int y;
    bool job;
    void vid()
    {
        clectka_x = vid_nom / 10;
        clectka_y = vid_nom % 10;
    }
    void draw()
    {
        txTransparentBlt(txDC(), x, y, 32, 32, blits, 32*clectka_x, 32*clectka_y,TX_WHITE);
    }
};
struct Button
{

    int x;
    int y;
    int w;
    int h;
    const char* text;
    bool visible;

    void draw()
    {
        txSetColor (TX_WHITE, 3);
        txSetFillColor (TX_YELLOW);
        Win32::RoundRect (txDC(), x, y, x+w, y+h, 30, 30);
        txSelectFont("Times New Roman", 30);
        txSetColor (TX_RED);
        txDrawText(x, y, x+w, y+h, text);
    }

    bool click()
    {
        return(txMouseX()>x && txMouseX()<x+w &&
                txMouseY()>y && txMouseY()<y+h &&
                txMouseButtons() == 1 && visible);
    }
};
struct Vizual
{
    int vid_nom;
    HDC blits;
    // = txLoadImage("pixelarts/New Piskel(3).bmp")
    int clectka_x;
    int clectka_y;
    int x;
    int y;
    void vid()
    {
        clectka_x = vid_nom / 10;
        clectka_y = vid_nom % 10;
    }
    void draw()
    {
        txTransparentBlt(txDC(), x, y, 96, 96, blits, 96*clectka_x, 96*clectka_y,TX_WHITE);
    }

};
//structuri_konec
//classi_start
class Character
{
private:
    int clectka_x = 0;
    int clectka_y = 0;
    int a = 0;
    int b = 0;
    int kon = 0;
    public:
    int x;
    int y;
    int index;
    HDC blits;
    int sech[12];
    bool vizible;
    bool r;
    bool l;
    bool u;
    bool d;
       void draw()
    {
        if (vizible == true)
        {
        if (index == 1)
        {
            a = 0;
        }
        if (index == 2)
        {
            a = 4;
        }
        if (index == 3)
        {
            a = 8;
        }
        if (r == true)
        {
            b = 1;
        }
        if (l == true)
        {
            b = 2;
        }
        if (u == true)
        {
            b = 3;
        }
        if (d == true)
        {
            b = 0;
        }
        kon = a + b;
        clectka_x = sech[kon] / 10;
        clectka_y = sech[kon] % 10;
        txTransparentBlt(txDC(), x*96, y*96, 96, 96, blits, 96*clectka_x, 96*clectka_y,TX_WHITE);
        }
    }
};
//classi_konec
//function_start
int functia_rotoraya_nujna_dlya_colisii(int u,int y);
int functia_rotoraya_nujna_dlya_colisii(int u,int y){
int otvet = y * 7 + u;
return (otvet);
}

//function_konec
int main()
{
txCreateWindow (672, 480);
string PAGE = "menu";
Vizual vizual = {0 , txLoadImage("pixelarts/New Piskel (3).bmp") ,0 ,0 ,0 ,0};
//knopki_sart
Button btn[4];

btn[0] = {100, 100, 200, 40, "Старт", true};
btn[1] = {100, 150, 200, 40, "Правила игры", true};
btn[2] = {100, 200, 200, 40, "Выход", true};
btn[3] = {0, 0, 200, 40, "Назад", true};
//knopki_konec
//peremennie_start
int timer = 0;
int x_otrisovki = 0;
int y_otrisovki = 0;
bool lampu = true;
bool lampd = true;
bool lampl = true;
bool lampr = true;
int hp0 = 40;
int hp1 = 40;
int xp = 0;
//peremennie_konec
//obiecti_start
Character character  = {};

character.sech[0] = 00;
character.sech[1] = 10;
character.sech[2] = 20;
character.sech[3] = 01;
character.sech[4] = 11;
character.sech[5] = 21;
character.sech[6] = 02;
character.sech[7] = 12;
character.sech[8] = 22;
character.sech[9] = 03;
character.sech[10] = 13;
character.sech[11] = 23;

character.blits = txLoadImage("pixelarts/New Piskel (2).bmp" );
character.vizible = true;
character.index = 1;
character.r = true;
character.d = false;
character.u = false;
character.l = false;

character.x = 3;
character.y = 2;
Hp hp [10];
hp[0] = {00 , txLoadImage("pixelarts/hp.bmp") ,0 ,0 ,640 ,0,true};
hp[1] = {00 , txLoadImage("pixelarts/hp.bmp") ,0 ,0 ,640 ,33,true};
hp[2] = {00 , txLoadImage("pixelarts/hp.bmp") ,0 ,0 ,640 ,66,true};
hp[3] = {00 , txLoadImage("pixelarts/hp.bmp") ,0 ,0 ,640 ,99,false};
hp[4] = {00 , txLoadImage("pixelarts/hp.bmp") ,0 ,0 ,640 ,132,false};
hp[5] = {01 , txLoadImage("pixelarts/hp.bmp") ,0 ,0 ,0 ,480,false};
hp[6] = {01 , txLoadImage("pixelarts/hp.bmp") ,0 ,0 ,0 ,447,false};
hp[7] = {01 , txLoadImage("pixelarts/hp.bmp") ,0 ,0 ,0 ,414,false};
hp[8] = {01 , txLoadImage("pixelarts/hp.bmp") ,0 ,0 ,0 ,381,false};
hp[9] = {01 , txLoadImage("pixelarts/hp.bmp") ,0 ,0 ,0 ,348,false};
//obiecti_konec
//podgruzca_kartinok_start
HDC fon = txLoadImage("pixelarts/fon.bmp");
//podgruzca_kartinok_start
//glavnicikl
while(!btn[2].click())
{
    //karta_i_otrisovka_start
int karta [35];

karta[0] = 20;
karta[1] = 20;
karta[2] = 20;
karta[3] = 20;
karta[4] = 20;
karta[5] = 20;
karta[6] = 20;

karta[7] = 20;
karta[8] = 00;
karta[9] = 00;
karta[10] = 00;
karta[11] = 00;
karta[12] = 00;
karta[13] = 20;

karta[14] = 20;
karta[15] = 00;
karta[16] = 00;
karta[17] = 03;
karta[18] = 00;
karta[19] = 00;
karta[20] = 20;

karta[21] = 20;
karta[22] = 00;
karta[23] = 00;
karta[24] = 00;
karta[25] = 00;
karta[26] = 00;
karta[27] = 20;

karta[28] = 20;
karta[29] = 20;
karta[30] = 20;
karta[31] = 20;
karta[32] = 20;
karta[33] = 20;
karta[34] = 20;
//karta_i_otrisovka_konec
    //chastoptimiz_start
    txBegin();
    txClear();
    //chastoptimiz_konec
    txSetFillColor (TX_YELLOW);
    //menu_start
    if(PAGE == "menu")
    {
        txBitBlt(txDC(), 0, 0, 672, 480, fon);
        btn[0].draw();
        btn[1].draw();
        btn[2].draw();
        btn[2].visible = true;
        if(btn[0].click())
        {
            PAGE = "game";
        }
        if(btn[1].click())
        {
            PAGE = "rules";
        }

        txSetFillColor (TX_BLACK);
    }
    //menu_konec
    //rules_start
    if(PAGE == "rules")
    {
        txBitBlt(txDC(), 0, 0, 800, 600, fon);
        btn[3].draw();
        txSelectFont ("Times", 20);
        txTextOut (50, 60, "вы слепы , но чувствуете магию");
        txTextOut (50, 90, "8num - вперед;");
        txTextOut (50, 120, "2num - назад;");
        txTextOut (50, 150, "6num - направо;");
        txTextOut (50, 180, "4num - налево;");
        txTextOut (50, 210, "задняя кнопка взаимодействия - ходьба;");
        txTextOut (50, 240, "правая часть экрана показывает направление;");
        txTextOut (50, 270, "сердце и xp добавляют сердца;");
        if(btn[3].click() || GetAsyncKeyState(VK_ESCAPE))
        {
            PAGE = "menu";
        }
        btn[2].visible = false;

        txSetFillColor (TX_YELLOW);
    }
    //rules_konec
    //game_start
    if(PAGE == "game")
    {
        while(timer != 35)
        {
            vizual.vid_nom = karta[timer];
            vizual.vid();
            if (x_otrisovki > 6)
            {
                x_otrisovki = 0;
                y_otrisovki += 1;
                if (y_otrisovki > 4)
                {
                    y_otrisovki = 0;
                }
            }
            vizual.x = 96 * x_otrisovki;
            vizual.y = 96 * y_otrisovki;
            vizual.draw();
            timer = timer + 1;
            x_otrisovki += 1;
        }
        timer = 0;
        character.draw();
//start_upravlenie

        if(lampu & lampd & lampr)
        {
        if(GetAsyncKeyState(VK_NUMPAD4))
        {
            if (!lampl)
            {
                lampl = true;
                //character.d = true;
                character.l = false;
            }
            else
            {
                character.l = true;
                character.r = false;
                character.d = false;
                character.u = false;
                lampl = false;
            }
        txSleep(10);
        }
        }
        if(lampu & lampd & lampl)
        {
        if(GetAsyncKeyState(VK_NUMPAD6))
        {
            if (!lampr)
            {
                lampr = true;
                //character.d = true;
                character.r = false;
            }
            else
            {
                character.r = true;
                character.l = false;
                character.d = false;
                character.u = false;
                lampr = false;
            }
        txSleep(10);
        }
        }
        if(lampl & lampd & lampr)
        {
        if(GetAsyncKeyState(VK_NUMPAD8))
        {
            if (!lampu)
            {
                lampu = true;
               // character.d = true;
                character.u = false;
            }
            else
            {
                character.u = true;
                character.r = false;
                character.d = false;
                character.l = false;
                lampu = false;
            }
        txSleep(10);
        }
        }
        if(lampu & lampl & lampr)
        {
        if(GetAsyncKeyState(VK_NUMPAD2))
        {
            if (!lampd)
            {
                lampd = true;
                //character.r = true;
                character.d = false;
            }
            else
            {
                character.d = true;
                character.r = false;
                character.l = false;
                character.u = false;
                lampd = false;
            }
        txSleep(10);
        }
        }

        if (!character.d)
        {
            txSetColor (RGB(255,30,30), 3);
            txSetFillColor (RGB(255,234,48));
            Win32::RoundRect (txDC(), 637, 445, 667, 475, 10, 10);
            txSelectFont("Times New Roman", 30);
            txSetColor (RGB(5,0,0));
            txDrawText(637, 445, 667, 475, "D");
        }
        else
        {
            txSetColor (RGB(255,234,48), 3);
            txSetFillColor (RGB(255,30,30));
            Win32::RoundRect (txDC(), 637, 445, 667, 475, 10, 10);
            txSelectFont("Times New Roman", 30);
            txSetColor (RGB(5,0,0));
            txDrawText(637, 445, 667, 475, "D");
        }
        if (!character.u)
        {
            txSetColor (RGB(255,30,30), 3);
            txSetFillColor (RGB(255,234,48));
            Win32::RoundRect (txDC(), 637, 410, 667, 440, 10, 10);
            txSelectFont("Times New Roman", 30);
            txSetColor (RGB(5,0,0));
            txDrawText(637, 410, 667, 440, "U");
        }
        else
        {
            txSetColor (RGB(255,234,48), 3);
            txSetFillColor (RGB(255,30,30));
            Win32::RoundRect (txDC(), 637, 410, 667, 440, 10, 10);
            txSelectFont("Times New Roman", 30);
            txSetColor (RGB(5,0,0));
            txDrawText(637, 410, 667, 440, "U");
        }
        if (!character.l)
        {
            txSetColor (RGB(255,30,30), 3);
            txSetFillColor (RGB(255,234,48));
            Win32::RoundRect (txDC(), 637, 375, 667, 405, 10, 10);
            txSelectFont("Times New Roman", 30);
            txSetColor (RGB(5,0,0));
            txDrawText(637, 375, 667, 405, "L");
        }
        else
        {
            txSetColor (RGB(255,234,48), 3);
            txSetFillColor (RGB(255,30,30));
            Win32::RoundRect (txDC(), 637, 375, 667, 405, 10, 10);
            txSelectFont("Times New Roman", 30);
            txSetColor (RGB(5,0,0));
            txDrawText(637, 375, 667, 405, "L");
        }
        if (!character.r)
        {
            txSetColor (RGB(255,30,30), 3);
            txSetFillColor (RGB(255,234,48));
            Win32::RoundRect (txDC(), 637, 340, 667, 370, 10, 10);
            txSelectFont("Times New Roman", 30);
            txSetColor (RGB(5,0,0));
            txDrawText(637, 340, 667, 370, "R");
        }
        else
        {
            txSetColor (RGB(255,234,48), 3);
            txSetFillColor (RGB(255,30,30));
            Win32::RoundRect (txDC(), 637, 340, 667, 370, 10, 10);
            txSelectFont("Times New Roman", 30);
            txSetColor (RGB(5,0,0));
            txDrawText(637, 340, 667, 370, "R");
        }



        if (
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 1] != 20 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 1] != 01 &&
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 1] != 21 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 1] != 02 &&
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 1] != 12
            )
        {
            if(character.l)
            {
                    if(GetAsyncKeyState(VK_NUMPAD6))
                {
                    character.x -= 1;
                    txSleep(20);
                }
            }
        }
        if (
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 1] != 20 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 1] != 01 &&
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 1] != 21 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 1] != 02 &&
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 1] != 12
            )
        {
            if(character.r)
            {
                    if(GetAsyncKeyState(VK_NUMPAD4))
                {
                    character.x += 1;
                    txSleep(20);
                }
            }
        }
         if (
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 7] != 20 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 7] != 01 &&
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 7] != 21 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 7] != 02 &&
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 7] != 12
            )
        {
            if(character.d)
            {
                    if(GetAsyncKeyState(VK_NUMPAD8))
                {
                    character.y += 1;
                    txSleep(20);
                }
            }
        }
         if (
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 7] != 20 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 7] != 01 &&
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 7] != 21 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 7] != 02 &&
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 7] != 12
            )
        {
            if(character.u)
            {
                    if(GetAsyncKeyState(VK_NUMPAD2))
                {
                    character.y -= 1;
                    txSleep(20);
                }
            }
        }
//konec_upravlenie
//start_sostaiania
    if
        (
        karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 20 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 01 &&
        karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 21 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 02 &&
        karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 12)
    {
        txDestroyWindow();
        txDeleteDC(fon);
    }
    if
        (
        karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 22 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 13
        )
    {
        xp += 1;
    }
    if
        (
        karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)+0] == 03 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 23
        )
    {
        hp0 = hp0 + 10;
    }
//konec_sostaianie
//start_hpandxp
 if (xp == 1)
    {
    hp[3].job = true;
 }
 if (xp <= 0)
    {
    hp[3].job = false;
    hp[4].job = false;
 }
     if (xp >= 2)
    {
    hp[3].job = true;
    hp[4].job = true;
 }
if (hp0 >= 20 & hp0 <=40)
    {
    hp[1].vid_nom = 10;
    hp[2].vid_nom = 10;
    hp[3].vid_nom = 10;
    hp[4].vid_nom = 10;
 }
 if (hp0 >= 41 & hp0 <=60)
    {
    hp[1].vid_nom = 00;
    hp[2].vid_nom = 10;
    hp[3].vid_nom = 10;
    hp[4].vid_nom = 10;
 }
if (hp0 >= 61 & hp0 <=80)
    {
    hp[1].vid_nom = 00;
    hp[2].vid_nom = 00;
    hp[3].vid_nom = 10;
    hp[4].vid_nom = 10;
 }
if (hp0 >= 81 & hp0 <=100)
    {
    hp[1].vid_nom = 00;
    hp[2].vid_nom = 00;
    hp[3].vid_nom = 00;
    hp[4].vid_nom = 10;
 }
if (hp0 >= 101 & hp0 <=120)
    {
    hp[1].vid_nom = 00;
    hp[2].vid_nom = 00;
    hp[3].vid_nom = 00;
    hp[4].vid_nom = 00;
 }
if (hp0 < 20)
{
      txDestroyWindow();
        txDeleteDC(fon);
}
hp[0].vid();
hp[1].vid();
hp[2].vid();
hp[3].vid();
hp[4].vid();
hp[0].draw();
hp[1].draw();
hp[2].draw();
if(hp[3].job)
{
    hp[3].draw();
}
if(hp[4].job)
{
    hp[4].draw();
}

//konec_hpandxp
    if(GetAsyncKeyState(VK_ESCAPE))
        {
            PAGE = "menu";
        }


    }
    //game_start
    //chastoptimiz_start
        txEnd();
    txSleep(1);
    //chastoptimiz_konec
}
txDestroyWindow();
txDeleteDC(fon);
}


