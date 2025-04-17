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
};//хп_будет_отвечать_за_отрисовку_сердечек_врагов(но_у_меня_не_получилось)_и_персонажа
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
};//кнопки_для_интерфейса
struct Vizual
{
    int vid_nom;
    HDC blits;
    int clectka_x;
    int clectka_y;
    int x;
    int y;
    void vid()
    {
        clectka_x = vid_nom / 10;//переработка_шифра_в_идекс_спрайта
        clectka_y = vid_nom % 10;
    }
    void draw()
    {
        txTransparentBlt(txDC(), x, y, 96, 96, blits, 96*clectka_x, 96*clectka_y,TX_WHITE);
    }

};//клетка-то_на_чем_строится_визуал
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
        if (vizible == true)//видны_ли(могло_пригодится,но_не_пригодилось)_
        {
        if (index == 1)//система_выбора_спрайта
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
        clectka_x = sech[kon] / 10;//переработка_шифра_в_идекс_спрайта
        clectka_y = sech[kon] % 10;
        txTransparentBlt(txDC(), x*96, y*96, 96, 96, blits, 96*clectka_x, 96*clectka_y,TX_WHITE);
        }
    }
};//враги_и_игрок
//classi_konec
//function_start
int functia_rotoraya_nujna_dlya_colisii(int u,int y);
int functia_rotoraya_nujna_dlya_colisii(int u,int y){
int otvet = y * 7 + u;
return (otvet);
}//в_коде_используется_для_выяснения_шифра_клетки_и_выдачи_инструкций
//function_konec
int main()
{
txCreateWindow (672, 480);//окно
string PAGE = "menu";//меню
Vizual vizual = {0 , txLoadImage("pixelarts/New Piskel (3).bmp") ,0 ,0 ,0 ,0};//иницилизация_клеток
//knopki_sart
Button btn[4];//иницилизация_кнопок

btn[0] = {100, 100, 200, 40, "продолжить", true};//нкопки
btn[1] = {100, 150, 200, 40, "правила", true};
btn[2] = {100, 200, 200, 40, "выйти", true};
btn[3] = {0, 0, 200, 40, "выйти", true};
//knopki_konec
//peremennie_start
int timer = 0;//таймер_для_перезапуска_клеток
int x_otrisovki = 0;//координаты_клеток
int y_otrisovki = 0;
bool lampu = true;//лампы_поворота_игрока
bool lampd = true;
bool lampl = true;
bool lampr = true;
int hp0 = 40;//хп_игрока
int hp1 = 5;//хп_врагов
int xp = 0;//уровень_игрока
int tb = 0;//таймер_раундов_боя
int rb0 = 3;//удар
int rb1 = 2;//удачность_удара
int maxx = 0;//номер_сцены
int maxy = 0;
int points = 0;//кол-во_убитых_боссов
bool gamee = true;
//peremennie_konec

//obiecti_start
Character character  = {};//игрок

character.sech[0] = 00;//комбинации_шифра
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

Character character1  = {};//враг_1

character1.x = 1;
character1.y = 2;

character1.sech[0] = 00;//комбинации_шифра
character1.sech[1] = 10;
character1.sech[2] = 20;
character1.sech[3] = 01;
character1.sech[4] = 11;
character1.sech[5] = 21;
character1.sech[6] = 02;
character1.sech[7] = 12;
character1.sech[8] = 22;
character1.sech[9] = 03;
character1.sech[10] = 13;
character1.sech[11] = 23;

character1.blits = txLoadImage("pixelarts/New Piskel (2).bmp" );
character1.vizible = true;

Character character2  = {};//враг_2

character2.sech[0] = 00;//комбинации_шифра
character2.sech[1] = 10;
character2.sech[2] = 20;
character2.sech[3] = 01;
character2.sech[4] = 11;
character2.sech[5] = 21;
character2.sech[6] = 02;
character2.sech[7] = 12;
character2.sech[8] = 22;
character2.sech[9] = 03;
character2.sech[10] = 13;
character2.sech[11] = 23;

character2.x = 5;
character2.y = 2;

character2.blits = txLoadImage("pixelarts/New Piskel (2).bmp" );
character2.vizible = true;

Hp hp [10];//иницилизация_хп
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
HDC fon = txLoadImage("pixelarts/fon.bmp");//иницилизация_фонов
HDC boi = txLoadImage("pixelarts/boi.bmp");
HDC smert = txLoadImage("pixelarts/vimertvi.bmp");
HDC pobeda = txLoadImage("pixelarts/pobda.bmp");
//podgruzca_kartinok_konec
//glavnicikl
while(gamee)
{

//start_vragi
if (maxx == 0 && maxy == 0)//персонализация_врагов_в_зависимости_от_сцены
{
    character2.index = 3;
    character2.r = false;
    character2.d = false;
    character2.u = false;
    character2.l = true;

    character1.index = 2;
    character1.r = true;
    character1.d = false;
    character1.u = false;
    character1.l = false;
}
if (maxx == 0 && maxy == 1)
{
    character2.index = 2;
    character2.r = false;
    character2.d = false;
    character2.u = false;
    character2.l = true;

    character1.index = 2;
    character1.r = true;
    character1.d = false;
    character1.u = false;
    character1.l = false;
}
if (maxx == 1 && maxy == 1)
{
    character2.index = 3;
    character2.r = false;
    character2.d = false;
    character2.u = false;
    character2.l = true;

    character1.index = 2;
    character1.r = true;
    character1.d = false;
    character1.u = false;
    character1.l = false;
}
if (maxx == -1 && maxy == 1)
{
    character2.index = 2;
    character2.r = false;
    character2.d = false;
    character2.u = false;
    character2.l = true;

    character1.index = 3;
    character1.r = true;
    character1.d = false;
    character1.u = false;
    character1.l = false;
}
//konec_vragi
    //karta_i_otrisovka_start
int karta [35];//шифры_клеток_в_зависимости_от_сцены
if (maxx == 0 && maxy == 0)
{
    karta[0] = 20;
    karta[1] = 20;
    karta[2] = 20;
    karta[3] = 00;
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
}
if (maxx == 0 && maxy == 1)
{
    karta[0] = 12;
    karta[1] = 12;
    karta[2] = 12;
    karta[3] = 12;
    karta[4] = 12;
    karta[5] = 12;
    karta[6] = 12;

    karta[7] = 12;
    karta[8] = 11;
    karta[9] = 11;
    karta[10] = 11;
    karta[11] = 11;
    karta[12] = 11;
    karta[13] = 12;

    karta[14] = 21;
    karta[15] = 11;
    karta[16] = 11;
    karta[17] = 13;
    karta[18] = 11;
    karta[19] = 11;
    karta[20] = 21;

    karta[21] = 12;
    karta[22] = 11;
    karta[23] = 11;
    karta[24] = 11;
    karta[25] = 11;
    karta[26] = 11;
    karta[27] = 12;

    karta[28] = 12;
    karta[29] = 12;
    karta[30] = 12;
    karta[31] = 11;
    karta[32] = 12;
    karta[33] = 12;
    karta[34] = 12;
}
if (maxx == 1 && maxy == 1)
{
    karta[0] = 12;
    karta[1] = 12;
    karta[2] = 12;
    karta[3] = 12;
    karta[4] = 12;
    karta[5] = 12;
    karta[6] = 12;

    karta[7] = 12;
    karta[8] = 11;
    karta[9] = 11;
    karta[10] = 11;
    karta[11] = 11;
    karta[12] = 11;
    karta[13] = 12;

    karta[14] = 21;
    karta[15] = 11;
    karta[16] = 11;
    karta[17] = 11;
    karta[18] = 11;
    karta[19] = 11;
    karta[20] = 12;

    karta[21] = 12;
    karta[22] = 11;
    karta[23] = 11;
    karta[24] = 11;
    karta[25] = 11;
    karta[26] = 11;
    karta[27] = 12;

    karta[28] = 12;
    karta[29] = 12;
    karta[30] = 12;
    karta[31] = 12;
    karta[32] = 12;
    karta[33] = 12;
    karta[34] = 12;
}
if (maxx == -1 && maxy == 1)
{
    karta[0] = 12;
    karta[1] = 12;
    karta[2] = 12;
    karta[3] = 12;
    karta[4] = 12;
    karta[5] = 12;
    karta[6] = 12;

    karta[7] = 12;
    karta[8] = 11;
    karta[9] = 11;
    karta[10] = 11;
    karta[11] = 11;
    karta[12] = 11;
    karta[13] = 12;

    karta[14] = 12;
    karta[15] = 11;
    karta[16] = 11;
    karta[17] = 11;
    karta[18] = 11;
    karta[19] = 11;
    karta[20] = 21;

    karta[21] = 12;
    karta[22] = 11;
    karta[23] = 11;
    karta[24] = 11;
    karta[25] = 11;
    karta[26] = 11;
    karta[27] = 12;

    karta[28] = 12;
    karta[29] = 12;
    karta[30] = 12;
    karta[31] = 12;
    karta[32] = 12;
    karta[33] = 12;
    karta[34] = 12;
}
//karta_i_otrisovka_konec
    //chastoptimiz_start
    txBegin();
    txClear();
    //chastoptimiz_konec
    txSetFillColor (TX_YELLOW);
    //menu_start
    if(PAGE == "menu")//меню
    {
        txBitBlt(txDC(), 0, 0, 672, 480, fon);//отрисовка_фона
        btn[0].draw();//отрисовка_кнопок
        btn[1].draw();
        btn[2].draw();
        btn[2].visible = true;
        if(btn[0].click())//взаимодействие_кнопок
        {
            PAGE = "game";
        }
        if(btn[1].click())
        {
            PAGE = "rules";
        }
        if(btn[2].click())
        {
        exit(0);
        }
        txSetFillColor (TX_BLACK);
    }
    //menu_konec
    //rules_start
    if(PAGE == "rules")//правила
    {

        txBitBlt(txDC(), 0, 0, 800, 600, fon);
        btn[3].draw();
        txSelectFont ("Times", 20);
        txSetColor (RGB(255,255,255), 3);
        txSetFillColor (RGB(255,255,255));
        txTextOut (50, 60, "вы слепы , но чувствуете магию;ваша задача победить боссов;");
        txTextOut (50, 90, "8num - повернуться вперед;2num - повернуться назад;");
        txTextOut (50, 120, "6num - повернуться вправо;4num - повернуться влево;");
        txTextOut (50, 150, "противоположная кнопка взаимодействия - ходьба;");
        txTextOut (50, 180, "правая часть экрана показывает направление;");
        txTextOut (50, 210, "сердце и xp добавляют сердца;помни любое лекарство в больших дозах - вред;");
        txTextOut (50, 240, "пример игры: игрок нажал 4 на нумпаде (но не аккуратно)");
        txTextOut (50, 270, "и захотел пойт, нажал 6(противоположная кнопка взаимодействия),");
        txTextOut (50, 300, "но так как на панели справа не обозначено направленине 'L'");
        txTextOut (50, 330, "он запутался и начал метаться из стороны в сторону ;");
        txTextOut (50, 360, "чтобы начать бой встань на соперника;");
        txTextOut (50, 390, "боссы желтые,враги серые;");
        txTextOut (50, 420, "во время боя нажимай на числа нумпада, которые показываются в виде примеров;");
        txTextOut (50, 450, "победи трех боссов для завершения игры;");
        if(btn[3].click() || GetAsyncKeyState(VK_ESCAPE))//выход_через_кнопку_или_esc
        {
            PAGE = "menu";
        }
        btn[2].visible = false;

        txSetFillColor (TX_YELLOW);
    }
    //rules_konec
    //game_start
    if(PAGE == "game")//игра
    {
        while(timer != 35)//отрисовка_клеток
        {
            vizual.vid_nom = karta[timer];//выбор_шифра_клеток
            vizual.vid();//переработка_шифра_в_индекс
            if (x_otrisovki > 6)//перевод_клеток_со_строки_на_строку
            {
                x_otrisovki = 0;
                y_otrisovki += 1;
                if (y_otrisovki > 4)
                {
                    y_otrisovki = 0;
                }
            }
            vizual.x = 96 * x_otrisovki;//выбор_координат_клетки
            vizual.y = 96 * y_otrisovki;
            vizual.draw();//отрисовка_клетки
            timer = timer + 1;//1_шаг
            x_otrisovki += 1;//1_шаг
        }
        timer = 0;//таймер_сброшен
        character.draw();//отрисовка_персонажей
        character1.draw();
        character2.draw();
//start_upravlenie

        if(lampu & lampd & lampr)//проверка_влючен_ли_другой_поворот
        {
        if(GetAsyncKeyState(VK_NUMPAD4))//нажатие_клавиши
        {
            if (!lampl)//работает_по_принципу_рычага(поворот_налево)
            {
                lampl = true;
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
        txSleep(10);//замедление_программы
        }
        }
        if(lampu & lampd & lampl)//проверка_влючен_ли_другой_поворот
        {
        if(GetAsyncKeyState(VK_NUMPAD6))//нажатие_клавиши
        {
            if (!lampr)//работает_по_принципу_рычага(поворот_направо)
            {
                lampr = true;
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
        txSleep(10);//замедление_программы
        }
        }
        if(lampl & lampd & lampr)//проверка_влючен_ли_другой_поворот
        {
        if(GetAsyncKeyState(VK_NUMPAD8))//нажатие_клавиши
        {
            if (!lampu)//работает_по_принципу_рычага(поворот_вверх)
            {
                lampu = true;
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
        txSleep(10);//замедление_программы
        }
        }
        if(lampu & lampl & lampr)//проверка_влючен_ли_другой_поворот
        {
        if(GetAsyncKeyState(VK_NUMPAD2))//нажатие_клавиши
        {
            if (!lampd)//работает_по_принципу_рычага(поворот_вниз)
            {
                lampd = true;
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
        txSleep(10);//замедление_программы
        }
        }

        if (!character.d)//индикатор_поворота_вниз
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
        if (!character.u)//индикатор_поворота_вверх
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
        if (!character.l)//индикатор_поворота_налево
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
        if (!character.r)//индикатор_поворота_направо
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
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 1] != 02 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 1] != 12
            )//проверка_нет_ли_слева_припядствий
        {
            if(character.l)
            {
                    if(GetAsyncKeyState(VK_NUMPAD6))
                {
                    character.x -= 1;//движение_влево
                    txSleep(20);
                }
            }
        }
        if (
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 1] != 20 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 1] != 01 &&
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 1] != 02 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 1] != 12
            )//проверка_нет_ли_спрва_припядствий
        {
            if(character.r)
            {
                    if(GetAsyncKeyState(VK_NUMPAD4))
                {
                    character.x += 1;//движение_вправо
                    txSleep(20);
                }
            }
        }
         if (
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 7] != 20 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 7] != 01 &&
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 7] != 02 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) + 7] != 12
            )//проверка_нет_ли_внизу_припядствий
        {
            if(character.d)
            {
                    if(GetAsyncKeyState(VK_NUMPAD8))
                {
                    character.y += 1;//движение_вниз
                    txSleep(20);
                }
            }
        }
         if (
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 7] != 20 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 7] != 01 &&
            karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 7] != 02 && karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y) - 7] != 12
            )//проверка_нет_ли_вверху_припядствий
        {
            if(character.u)
            {
                    if(GetAsyncKeyState(VK_NUMPAD2))
                {
                    character.y -= 1;//движение_вверх
                    txSleep(20);
                }
            }
        }
//konec_upravlenie
//start_sostaiania
    if
        (
        karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 20 or karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 01 or
        karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 02 or karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 12
        )//проверка_нет_ли_под_игроком_стены
    {
        txBitBlt(txDC(), 0, 0, 800, 600, smert);
        exit(0);//выход
    }
    if
        (
       karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 13
        )//проверка_нет_ли_под_игроком_повышения_уровня
    {
        xp += 1;//повышение_уровня
    }
        if
        (
        karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 22
        )//проверка_нет_ли_под_игроком_повышения_уровня
    {
        xp += 1;//повышение_уровня
    }
    if
        (
        karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)+0] == 03
        )//проверка_нет_ли_под_игроком_увеличения_хп
    {
        hp0 = hp0 + 1;//увеличение_хп
    }
    if
        (
        karta[functia_rotoraya_nujna_dlya_colisii(character.x,character.y)] == 23
        )//проверка_нет_ли_под_игроком_увеличения_хп
    {
        hp0 = hp0 + 1;//увеличение_хп
    }
//konec_sostaianie
//start_bitvi
if (character.x == character1.x && character.y == character1.y or character.x == character2.x && character.y == character2.y)//находится_ли_игрок_на_враге
{
    txSelectFont("Times New Roman", 30);
    txSetColor (RGB(255,255,255));
    txBitBlt(txDC(), 0, 0, 672, 480, boi);//отрисовка_фон_боя
    tb += 1;//таймер_боя_пошел

    if (tb >= 130)//ограничитель_времени_раунда
    {
        tb = 0;//обнуоение_времни_боя
        rb1 = 1 + rand() % 5;//рандомизация
        rb0 = 1 + rand() % 5;//рандомизация
        hp0 -= 12;//урон_игрока
    }
    if (rb0 == 1)//вариант_удара_противника
    {
        if (rb1 == 1)//сила_удара
        {
            txTextOut (50, 400, "7");
        }
        if (rb1 == 2)//сила_удара
        {
            txTextOut (178, 200, "x-7=0");
        }
        if (rb1 == 3)//сила_удара
        {
            txTextOut (458, 100, "49^0,5");
        }
        if (rb1 == 4)//сила_удара
        {
            txTextOut (12, 10, "10!/518400");

        }
        if (rb1 == 5)//сила_удара
        {
            txTextOut (278, 153, "x-x^2=-42");

        }
        if(GetAsyncKeyState(VK_NUMPAD7))//нажатие_на_нужную_кнопку
        {
            hp1 -= 1;
            tb = 0;
            rb1 = 1 + rand() % 5;
            rb0 = 1 + rand() % 5;
        }
        if(GetAsyncKeyState(VK_NUMPAD9) or GetAsyncKeyState(VK_NUMPAD1) or GetAsyncKeyState(VK_NUMPAD3))//неправильное_нажатие
        {
            tb = 0;
            rb1 = 1 + rand() % 5;
            rb0 = 1 + rand() % 5;
            hp0 -= 12;
        }
    }
    //и_так_далее
    if (rb0 == 2)
    {
        if (rb1 == 1)
        {
            txTextOut (50, 400, "9");
        }
        if (rb1 == 2)
        {
            txTextOut (12, 10, "x-9=0");
        }
        if (rb1 == 3)
        {
            txTextOut (178, 200, "81^0,5");
        }
        if (rb1 == 4)
        {
            txTextOut (278, 153, "27!/1209874383379816906752000000");

        }
        if (rb1 == 5)
        {
            txTextOut (458, 100, "x-x^2=-72");

        }
        if(GetAsyncKeyState(VK_NUMPAD9))
        {
            hp1 -= 1;
            tb = 0;
            rb1 = 1 + rand() % 5;
            rb0 = 1 + rand() % 5;
        }
        if(GetAsyncKeyState(VK_NUMPAD7) or GetAsyncKeyState(VK_NUMPAD1) or GetAsyncKeyState(VK_NUMPAD3))
        {
            tb = 0;
            rb1 = 1 + rand() % 5;
            rb0 = 1 + rand() % 5;
            hp0 -= 12;
        }
    }
    if (rb0 == 3)
    {
        if (rb1 == 1)
        {
            txTextOut (150, 300, "1");
        }
        if (rb1 == 2)
        {
            txTextOut (112, 110, "x-1=0");
        }
        if (rb1 == 3)
        {
            txTextOut (78, 200, "1^0,5");
        }
        if (rb1 == 4)
        {
            txTextOut (178, 53, "7!/5040");

        }
        if (rb1 == 5)
        {
            txTextOut (358, 100, "x-x^2=0");

        }
        if(GetAsyncKeyState(VK_NUMPAD1))
        {
            hp1 -= 1;
            tb = 0;
            rb1 = 1 + rand() % 5;
            rb0 = 1 + rand() % 5;
        }
        if(GetAsyncKeyState(VK_NUMPAD9) or GetAsyncKeyState(VK_NUMPAD7) or GetAsyncKeyState(VK_NUMPAD3))
        {
            tb = 0;
            rb1 = 1 + rand() % 5;
            rb0 = 1 + rand() % 5;
            hp0 -= 12;
        }
    }
    if (rb0 == 4)
    {
        if (rb1 == 1)
        {
            txTextOut (150, 300, "3");
        }
        if (rb1 == 2)
        {
            txTextOut (112, 110, "x-3=0");
        }
        if (rb1 == 3)
        {
            txTextOut (78, 200, "9^0,5");
        }
        if (rb1 == 4)
        {
            txTextOut (178, 53, "12!/159667200");

        }
        if (rb1 == 5)
        {
            txTextOut (358, 100, "x-x^2=-6");

        }
        if(GetAsyncKeyState(VK_NUMPAD3))
        {
            hp1 -= 1;
            tb = 0;
            rb1 = 1 + rand() % 5;
            rb0 = 1 + rand() % 5;
        }
        if(GetAsyncKeyState(VK_NUMPAD9) or GetAsyncKeyState(VK_NUMPAD1) or GetAsyncKeyState(VK_NUMPAD7))
        {
            tb = 0;
            rb1 = 1 + rand() % 5;
            rb0 = 1 + rand() % 5;
            hp0 -= 12;
        }
    }
    if (hp1 <= 0)//если_враг_мертв
    {
        if(character.x == character1.x && character.y == character1.y)//какой_именно
        {
            character1.x = -1;//убрать_врага_со_сцены
            character1.y = -1;
            hp1 += 5;
            if(character1.index == 3)//если_это_босс_добавить_счет
            {
                points += 1;
            }
        }
        if(character.x == character2.x && character.y == character2.y)//какой_именно
        {
            character2.x = -1;//убрать_врага_со_сцены
            character2.y = -1;
            hp1 += 5;
            if(character2.index == 3)//если_это_босс_добавить_счет
            {
                points += 1;
            }
        }
    }
    if (rb0 == 5)//крит_удар_врага
    {
        hp0 -= 5;
        tb = 0;
        rb1 = 1 + rand() % 5;
        rb0 = 1 + rand() % 5;
    }
}


//konec_bitvi
//start_hpandxp
 if (xp == 1)//отбражение_хп_через_проверку_xp
    {
    hp[3].job = true;
 }
 if (xp <= 0)//отбражение_хп_через_проверку_xp
    {
    hp[3].job = false;
    hp[4].job = false;
 }
 if (xp >= 2)//отбражение_хп_через_проверку_xp
    {
    hp[3].job = true;
    hp[4].job = true;
 }
if (hp0 >= 20 & hp0 <=40)//отбражение_хп
    {
    hp[1].vid_nom = 10;
    hp[2].vid_nom = 10;
    hp[3].vid_nom = 10;
    hp[4].vid_nom = 10;
 }
 if (hp0 >= 41 & hp0 <=60)//отбражение_хп
    {
    hp[1].vid_nom = 00;
    hp[2].vid_nom = 10;
    hp[3].vid_nom = 10;
    hp[4].vid_nom = 10;
 }
if (hp0 >= 61 & hp0 <=80)//отбражение_хп
    {
    hp[1].vid_nom = 00;
    hp[2].vid_nom = 00;
    hp[3].vid_nom = 10;
    hp[4].vid_nom = 10;
 }
if (hp0 >= 81 & hp0 <=100)//отбражение_хп
    {
    hp[1].vid_nom = 00;
    hp[2].vid_nom = 00;
    hp[3].vid_nom = 00;
    hp[4].vid_nom = 10;
 }
if (hp0 >= 101 & hp0 <=120)//отбражение_хп
    {
    hp[1].vid_nom = 00;
    hp[2].vid_nom = 00;
    hp[3].vid_nom = 00;
    hp[4].vid_nom = 00;
 }
if (hp0 < 20)//выход
{
    txBitBlt(txDC(), 0, 0, 800, 600, smert);
    exit(0);
}
if (hp1 == 1)//отбражение_хп_врага
{
    hp[5].job == true;
    hp[6].job == false;
    hp[7].job == false;
    hp[8].job == false;
    hp[9].job == false;
}
if (hp1 == 2)//отбражение_хп_врага
{
    hp[5].job == true;
    hp[6].job == true;
    hp[7].job == false;
    hp[8].job == false;
    hp[9].job == false;
}
if (hp1 == 3)//отбражение_хп_врага
{
    hp[5].job == true;
    hp[6].job == true;
    hp[7].job == true;
    hp[8].job == false;
    hp[9].job == false;
}
if (hp1 == 4)//отбражение_хп_врага
{
    hp[5].job == true;
    hp[6].job == true;
    hp[7].job == true;
    hp[8].job == true;
    hp[9].job == false;
}
if (hp1 == 5)//отбражение_хп_врага
{
    hp[5].job == true;
    hp[6].job == true;
    hp[7].job == true;
    hp[8].job == true;
    hp[9].job == true;
}
hp[0].vid();//отбражение_хп
hp[1].vid();
hp[2].vid();
hp[3].vid();
hp[4].vid();
hp[5].vid();
hp[6].vid();
hp[7].vid();
hp[8].vid();
hp[9].vid();
hp[0].draw();
hp[1].draw();
hp[2].draw();
if(hp[3].job)//отбражение_хп
{
    hp[3].draw();
}
if(hp[4].job)//отбражение_хп
{
    hp[4].draw();
}
if(hp[5].job)//отбражение_хп
{
    hp[5].draw();
}
if(hp[6].job)//отбражение_хп
{
    hp[6].draw();
}
if(hp[7].job)//отбражение_хп
{
    hp[7].draw();
}
if(hp[8].job)//отбражение_хп
{
    hp[8].draw();
}
if(hp[9].job)//отбражение_хп
{
    hp[9].draw();
}
//konec_hpandxp
//start_world
if (character.x >= 6)//перход_сцены
{
    character.x = 1;
    maxx += 1;
    character1.x = 1;
    character1.y = 2;
    character2.x = 5;
    character2.y = 2;
}
if (character.x <= 0)//перход_сцены
{
    character.x = 5;
    maxx -= 1;
    character1.x = 1;
    character1.y = 2;
    character2.x = 5;
    character2.y = 2;
}
if (character.y >= 4)//перход_сцены
{
    character.y = 1;
    maxy -= 1;
    character1.x = 1;
    character1.y = 2;
    character2.x = 5;
    character2.y = 2;
}
if (character.y <= 0)//перход_сцены
{
    character.y = 3;
    maxy += 1;
    character1.x = 1;
    character1.y = 2;
    character2.x = 5;
    character2.y = 2;
}
//konec_world
//start_pobeda
if (points >= 3)
{
    txBitBlt(txDC(), 0, 0, 800, 600, pobeda);
    exit(0);
}
//konec_pobeda
    if(GetAsyncKeyState(VK_ESCAPE))//выход_в_меню
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
txDeleteDC(boi);
}


