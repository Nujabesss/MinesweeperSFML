#pragma once
#include <SFML/Graphics.hpp>
#include<time.h>
#include<memory>
#include "AssertMenager.h"
#include"Animator.h"
#include"Menu.h"
#define LENGHT 12
#define WIDTH 12
#define BOMBS 40

using namespace sf;
using namespace std;

class Game {
private:
    AssertMenager manager;

    int user_board[LENGHT+1][WIDTH+1];
    int game_board[LENGHT+1][WIDTH+1];
    int firstMove, Bomsfound;


    sf::Time MinesTime;
    sf::Sprite MinesSprite;
    Animator MinesAnim = Animator(MinesSprite);
    Texture win;
    Sprite WIN;
    Texture mine;

    std::vector<sf::IntRect>m_Frames;
    std::unique_ptr < sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(VideoMode(1280, 720), L"MiniSweeper", Style::Default);

    RectangleShape background = RectangleShape(Vector2f(1280, 720));
    void UserBoardInit();
    void BombsInit();
    void NumsCreat();
    void Inittext(Text& mtext, float xpoos, float ypos, String str, int size_font = 60, Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);
    void Input();
    void gameMenu();
    void update(Time const& deltaTime);
    void draw();
   
public:


    Game();
  

    void run();
};

