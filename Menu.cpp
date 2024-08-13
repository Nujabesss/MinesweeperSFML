#include "Menu.h"

void GameMenu::setInitText(sf::Text& text, sf::String str, float xpos, float ypos)
{
    text.setFont(font);
    text.setFillColor(menu_text_color);
    text.setString(str);
    text.setPosition(xpos, ypos);
    text.setCharacterSize(size_font);
    text.setOutlineThickness(3);
    text.setOutlineColor(border_color);
}

GameMenu::GameMenu(sf::RenderWindow& window, float menux, float menuy, sf::String name[], int sizeFont, int step):myWindow(window),menu_X(menux),menu_Y(menuy),size_font(sizeFont),menu_Step(step)
{
    //Загрузка шрифта
    if (!font.loadFromFile("font/menu.otf")) exit(32);
    
    max_menu = name->getSize() - 1;
    mainMenu = new sf::Text[name->getSize()]; //Массив пунктов меню
    for (int i = 0, ypos = menu_Y; i < max_menu; i++, ypos += menu_Step) setInitText(mainMenu[i], name[i], menu_X, ypos);
    mainMenuSelected = 0;
    mainMenu[mainMenuSelected].setFillColor(sf::Color::Yellow);
}

void GameMenu::draw()
{
    for (int i = 0; i < max_menu; i++)myWindow.draw(mainMenu[i]);
}

void GameMenu::MoveUp()
{
    mainMenuSelected-- ;
    if(mainMenuSelected >= 0)
    {
        mainMenu[mainMenuSelected].setFillColor(CHOSE_TEXT_COLOR);
        mainMenu[mainMenuSelected].setFillColor(menu_text_color);
    }
    else {
        mainMenu[0].setFillColor(menu_text_color);
        mainMenuSelected = max_menu - 1;
        mainMenu[mainMenuSelected].setFillColor(CHOSE_TEXT_COLOR);
    }
}

void GameMenu::MoveDown()
{
    mainMenuSelected++;
    if (mainMenuSelected <=max_menu)
    {
        mainMenu[mainMenuSelected-1].setFillColor(CHOSE_TEXT_COLOR);
        mainMenu[mainMenuSelected].setFillColor(menu_text_color);
    }
    else { //выход за границу
        mainMenu[max_menu-1].setFillColor(menu_text_color);
        mainMenuSelected = 0;
        mainMenu[mainMenuSelected].setFillColor(CHOSE_TEXT_COLOR);
    }
}

void GameMenu::setCOolorTextMenu(sf::Color mCOlor, sf::Color Cholor, sf::Color BordColor) //измененяет цвет текста меню
{
    menu_text_color = mCOlor;
    CHOSE_TEXT_COLOR = Cholor;
    border_color = BordColor;
    for (int i = 0; i < max_menu; i++) {
        mainMenu[i].setFillColor(menu_text_color);
        mainMenu[i].setOutlineColor(border_color);

    }
    mainMenu[mainMenuSelected].setFillColor(CHOSE_TEXT_COLOR);
}

void GameMenu::AlignMenu(int posx)
{
    float nullx = 0;
    for (int i = 0; i < max_menu; i++) {
        switch (posx)
        {
        case 0:
            nullx = 0;
            break;
        case 1:
            nullx = mainMenu[i].getLocalBounds().width;
            break;
        case 2:
            nullx= mainMenu[i].getLocalBounds().width/2;
            break;
        }
        mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
    }
}
