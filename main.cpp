#include <iostream>
#include <fstream>
#include <graphics.h>
#include <cstring>
#include "adder.h"

using namespace std;

int curent=0;
bool ok = false;


class screen{
public:
    const char* img;                            //the image that opens
    int sheight = getmaxheight();               //height of the screen
    int swidth = getmaxwidth();                 //width of the screen
    void open_image()                           //opens the background image
    {
        initwindow(swidth, sheight, "Nassi-Schneidermann", 0, 0);
        readimagefile(img, 0, 0, swidth, sheight);
    }
    void close_screen()
    {
        getch();
        closegraph();
    }
};

class start_screen : public screen{
public:
    start_screen(){
        img = "start_image.img";
    }
};

class button{
public:
    int top, bottom, left, right;                    //coordonates
    int width, height;                               //dimensions
    int button_color, frame_color, text_color;       //color of the button and of the frame surrounding the button
    char text[20];                                   //text inside the button
    int text_length, text_height;                    //length and height of text
    void create_button()
    {
        setfillstyle(1, button_color);
        bar(top, left, bottom, right);
        setcolor(frame_color);
        setlinestyle(0, 0, 3);
        rectangle(top, left, bottom, right);
    }
    void put_text()
    {
        int x, y;                                   //coordinates of the text where it starts
        setcolor(text_color);                       //we set the text color
        setbkcolor(button_color);                   //we set the background text color
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);   //we set the font, dimension, direction
        text_height = textheight(text);             //we save the height and length only after aplying fonts
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;          //x starts from the x of the button, we add half the width of the button and substract the half the length of the text
        y = left + height/2 - text_height/2;        //y starts from the y of the button, we add half of the height of the button and substract half od the height of the text
        outtextxy(x, y, text);
    }
    void open_window(int a, int b)
    {
        initgraph(&a, &b, "");
    }
    bool is_inside_button()
    {
        clearmouseclick(WM_LBUTTONDOWN);
        int mx = mousex();
        int my = mousey();
        return (mx >= top && mx <= top + width && my >= left && my <= left + height);
    }
    void draw_menu();
    void search_for_mouse_activity();
};


class rectangle_button : public button{
public:
    rectangle_button(){
        width = 200, height = 100;
        button_color = LIGHTGRAY, frame_color = DARKGRAY, text_color = WHITE;
    }
};

class square_button : public button{
public:
    square_button(){
        width = 50, height = 50;
        button_color = LIGHTGRAY, frame_color = DARKGRAY, text_color = WHITE;
    }
};

class exit_button : public square_button{
public:
    //const char* img = "x.jpg";
    exit_button(){
        button_color = LIGHTRED, frame_color = DARKGRAY, text_color = WHITE;
    }
    void close_program(){
        ok = true;
        closegraph();
        exit(0);
    }
    void open_image()
    {
        readimagefile("x.jpg", top, left, width, height);
    }
    void put_text()
    {
        int x, y;
        setcolor(text_color);
        setbkcolor(button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
        text_height = textheight(text);
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;
        y = left + height/2 - text_height/2;
        outtextxy(x, y, text);
    }
};

class diagram_button : public button{
public:
    diagram_button (){
        top = 150, left = 300, bottom = 350, right = 400;
        width = 200, height = 100;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
};

class presets_button : public button{
public:
    presets_button (){
        top = 150, left = 475, bottom = 350, right = 575;
        width = 200, height = 100;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
};

class back_button : public button{
public:
    back_button (){
        top = 150, left = 650, bottom = 350, right = 750;
        width = 200, height = 100;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
};

class text_input_button : public button{
public:
    text_input_button (){
        top = 500, left = 150, bottom = 1800, right = 900;
        width = 575, height = 700;
        button_color = COLOR(33,64,95), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void open_text_input(){

    }
};

class start_button : public rectangle_button{
public:
    void open_program_start()
    {
        setbkcolor(COLOR(100, 155, 187));
        cleardevice();

        diagram_button dgr;
        presets_button pre;
        back_button bck;
        text_input_button ti;


        dgr.create_button();
        strcpy(dgr.text, "Diagram");
        dgr.put_text();

        pre.create_button();
        strcpy(pre.text, "Presets");
        pre.put_text();

        bck.create_button();
        strcpy(bck.text, "Back");
        bck.put_text();

        ti.create_button();
    }
};


class atribuire_button : public button{
public:
    atribuire_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 100, bottom = getmaxwidth()/2 + width/2, right = 200;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void put_text()
    {
        int x, y;
        setcolor(text_color);
        setbkcolor(button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        text_height = textheight(text);
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;
        y = left + height/2 - text_height/2;
        outtextxy(x, y, text);
    }
};

class daca_button : public button{
public:
    daca_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 250, bottom = getmaxwidth()/2 + width/2, right = 350;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
};
class pentru_button : public button{
public:
    pentru_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 400, bottom = getmaxwidth()/2 + width/2, right = 500;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
};
class cat_timp_button : public button{
public:
    cat_timp_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 550, bottom = getmaxwidth()/2 + width/2, right = 650;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void put_text()
    {
        int x, y;
        setcolor(text_color);
        setbkcolor(button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        text_height = textheight(text);
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;
        y = left + height/2 - text_height/2;
        outtextxy(x, y, text);
    }
};

class pana_cand_button : public button{
public:
    pana_cand_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 700, bottom = getmaxwidth()/2 + width/2, right = 800;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void put_text()
    {
        int x, y;
        setcolor(text_color);
        setbkcolor(button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        text_height = textheight(text);
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;
        y = left + height/2 - text_height/2;
        outtextxy(x, y, text);
    }
};
class cazuri_button : public button{
public:
    cazuri_button (){
        width = 200, height = 100;
        top = getmaxwidth()/2 - width/2, left = 850, bottom = getmaxwidth()/2 + width/2, right = 950;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
};

class back_info_button: public button{
public:
    back_info_button(){
        width = 200, height = 100;
        top = 50, left = 50, bottom = 250, right = 150;
        button_color = COLOR(160,82,45), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
};





class info_button : public rectangle_button {
public:
    void open_program_info()
    {
        setbkcolor(COLOR(255,228,196));
        cleardevice();

        atribuire_button atb;
        daca_button dc;
        pentru_button pt;
        cat_timp_button ct;
        pana_cand_button pc;
        cazuri_button cz;
        back_info_button bck;

        atb.create_button();
        strcpy(atb.text, "Atribuire");
        atb.put_text();

        dc.create_button();
        strcpy(dc.text, "Daca");
        dc.put_text();

        pt.create_button();
        strcpy(pt.text, "Pentru");
        pt.put_text();

        ct.create_button();
        strcpy(ct.text, "Cat timp");
        ct.put_text();

        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
        pc.create_button();
        strcpy(pc.text, "Pana cand");
        pc.put_text();

        cz.create_button();
        strcpy(cz.text, "Cazuri");
        cz.put_text();

        bck.create_button();
        strcpy(bck.text, "Back");
        bck.put_text();



    }
};

class language_button : public button{
public:
    language_button(){
        width = 200, height = 100;
        top = 500, left = 500, bottom = 700, right = 600;
        button_color = COLOR(85, 107, 47), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
    void put_text()
    {
        int x, y;
        setcolor(text_color);
        setbkcolor(button_color);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        text_height = textheight(text);
        text_length = textwidth(text);
        x = top + width/2 - text_length/2;
        y = left + height/2 - text_height/2;
        outtextxy(x, y, text);
    }
};

class back_settings_button : public button {
public:
     back_settings_button(){
        width = 200, height = 100;
        top = 50, left = 50, bottom = 250, right = 150;
        button_color = COLOR(85, 107, 47), frame_color = COLOR(255,250,226), text_color = WHITE;
    }
};

class settings_button : public rectangle_button{
public:
    void open_program_settings()
    {
        setbkcolor(COLOR(143, 188, 143));
        cleardevice();

        language_button language;
        back_settings_button bck;

        language.create_button();
        strcpy(language.text, "Language");
        language.put_text();

        bck.create_button();
        strcpy(bck.text, "Back");
        bck.put_text();

    }
};

class chat_button : public square_button{
public:
    int GdChat = DETECT, GmChat;
    char input[100];
    void open_chat()
    {
        clearmouseclick(WM_LBUTTONDOWN);
        open_window(GdChat, GmChat);

        int x = 10, y = 10;
        outtextxy(x, y, "Hello. How can I help you?");

        do
        {
            cin.getline(input, 100);
            if (strcmp(input, "How to use an if?")== 0 || strcmp(input, "How to use a while?") == 0 || strcmp(input, "How to use a for?") ==0)
            {
                    outtextxy(x, y+=30, "Please go back and click on the info button to know more about this.");
            }
            else if (strcmp(input, "How to use this app?") == 0)
            {
                    outtextxy(x, y+=30, "Press the START button and introduce your code in the correct order");
                    outtextxy(x, y+=30, "and the result will be the representative diagram");
            }
            else if (strcmp(input, "exit") == 0)
            {
                outtextxy(x, y+=30, "Nice talking to you. Press any key to exit.");
            }
            else
            {
                    outtextxy(x, y+=30, "I'm sorry. I'm not smart enough to understand that.");
            }
        }while(strcmp(input, "exit") != 0);
        getch();
    }
    closegraph();
};


    screen s;

    info_button info;
    settings_button settings;
    start_button start;
    chat_button chat;
    exit_button exitt;

    diagram_button diagram;
    presets_button presets;
    back_button bck;

    atribuire_button atribuire;
    daca_button daca;
    pentru_button pentru;
    cat_timp_button cat_timp;
    pana_cand_button pana_cand;
    cazuri_button cazuri;
    back_info_button back_info;

    language_button language;
    back_settings_button back_settings;



void button::draw_menu()
{
    setbkcolor(BLACK);
    cleardevice();

    //we create the buttons and we put the text inside
    {
        start.create_button();
        info.create_button();
        settings.create_button();
        exitt.create_button();
        chat.create_button();

        start.put_text();
        info.put_text();
        settings.put_text();
        exitt.put_text();

        //exitt.open_image();
    }
}

void button::search_for_mouse_activity()
{
    bool clicked = false;
    int chosen=0, command = 0;
    while(!clicked)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(curent == 0 && !clicked)
            {
                if(start.is_inside_button())
                {
                    chosen = 1;
                    clicked = true;
                    curent = 1;
                }
                else if(info.is_inside_button())
                {
                    chosen = 2;
                    clicked = true;
                    curent = 2;
                }
                else if(settings.is_inside_button())
                {
                    chosen = 3;
                    clicked = true;
                    curent = 3;
                }
                else if(chat.is_inside_button())
                {
                    chosen = 4;
                    clicked = true;
                    curent = 4;
                }
                else if(exitt.is_inside_button())
                {
                    chosen = 5;
                    clicked = true;
                    curent = 0;
                }
            }
            else if(curent == 1 && !clicked)
            {
                if(diagram.is_inside_button())
                {
                    chosen = 6;
                    clicked = true;
                }
                else if(presets.is_inside_button())
                {
                    chosen = 7;
                    clicked = true;
                }
                else if(bck.is_inside_button())
                {
                    chosen = 8;
                    clicked = true;
                    curent = 0;
                }
            }
            else if(curent == 2 && !clicked)
            {
                if(atribuire.is_inside_button())
                {
                    chosen = 9;
                    clicked = true;
                }
                else if(daca.is_inside_button())
                {
                    chosen = 10;
                    clicked = true;
                }
                else if(pentru.is_inside_button())
                {
                    chosen = 11;
                    clicked = true;
                }
                else if(cat_timp.is_inside_button())
                {
                    chosen = 12;
                    clicked = true;
                }
                else if(pana_cand.is_inside_button())
                {
                    chosen = 13;
                    clicked = true;
                }
                else if(cazuri.is_inside_button())
                {
                    chosen = 14;
                    clicked = true;
                }
                else if(back_info.is_inside_button())
                {
                    chosen = 15;
                    clicked = true;
                    curent = 0;
                }
            }
            else if(curent == 3)
            {
                if(language.is_inside_button())
                {
                    chosen = 16;
                    clicked = true;
                }
                else if(back_settings.is_inside_button())
                {
                    chosen = 17;
                    clicked = true;
                    curent = 0;
                }
            }
        }
    }
    if(chosen!=0)
    {
        command = chosen;
        if(command == 1)
            start.open_program_start();
        else if(command == 2)
            info.open_program_info();
        else if(command == 3)
            settings.open_program_settings();
        else if(command == 4)
            chat.open_chat();
        else if(command == 5)
            exitt.close_program();
        //}
        //else if(command == 5)
            //chat.open_chat();
        //else if(command == 6)
            //chat.open_chat();
        else if(command == 8)
            bck.draw_menu();
        else if(command == 15)
            back_info.draw_menu();
        else if(command == 17)
            back_settings.draw_menu();
    }

}




int main()
{
    screen s;
    //initialize the main screen
    {
        s.img="miaumiau.jpg";
        s.open_image();
    }

    //info for buttons
    {
        strcpy(start.text, "Start");
        strcpy(info.text, "Info");
        strcpy(settings.text, "Settings");
        strcpy(exitt.text, "X");

        start.top = s.swidth/2 - start.width/2, start.left = s.sheight/4, start.bottom = s.swidth/2 + start.width/2, start.right = s.sheight/4 + start.height;
        info.top = s.swidth/2 - info.width/2, info.left = s.sheight/4 + info.height+70, info.bottom = s.swidth/2 + info.width/2, info.right = s.sheight/4 + 2*info.height + 70;
        settings.top = s.swidth/2 - settings.width/2, settings.left = s.sheight/4 +140 + 2*settings.height, settings.bottom = s.swidth/2 + settings.width/2, settings.right = s.sheight/4 + 3*settings.height +140;

        exitt.top = 50, exitt.left = 50, exitt.bottom = 100, exitt.right = 100;
        chat.top = s.swidth-100, chat.left = s.sheight-100, chat.bottom = s.swidth-50, chat.right = s.sheight-50;
    }


    start.draw_menu();
    while(!ok)
    {
        start.search_for_mouse_activity();
    }
    closegraph();
    return 0;
}
