#include <SFML/Graphics.hpp>
#include<time.h>
#include "game.h"
#include "AssertMenager.h"

void Game::UserBoardInit()
{
    for (int i = 1; i <=LENGHT; i++) {
        for (int j = 1; j <=WIDTH; j++) {
            user_board[i][j] = 10;
        }
}
}

void Game::BombsInit()
{

    for (int i = 1; i < BOMBS; i++) {
        int x = rand() % LENGHT + 1;
        int y = rand() % WIDTH + 1;
       
        game_board[x][y] = 9;
    }
}

void Game::NumsCreat()
{
    for (int i = 1; i <=LENGHT; i++) {
        for (int j = 1; j <= WIDTH; j++) {
            if (game_board[i][j] != 9) {
                int noBoms = 0;
                if (game_board[i-1][j-1] == 9) {
                    noBoms++;
                }
                if (game_board[i +1][j+ 1] == 9) {
                    noBoms++;
                }
                if (game_board[i - 1][j] == 9) {
                    noBoms++;
                }
                if (game_board[i][j - 1] == 9) {
                    noBoms++;
                }
                if (game_board[i +1][j] == 9) {
                    noBoms++;
                }
                if (game_board[i][j + 1] == 9) {
                    noBoms++;
                }
                if (game_board[i - 1][j + 1] == 9) {
                    noBoms++;
                }
                if (game_board[i + 1][j - 1] == 9) {
                    noBoms++;
                }
                game_board[i][j] = noBoms;
            }
        }
    }
}

void Game::Input() {
    Event event_play;

    firstMove = 0;
    Vector2i Pos = Mouse::getPosition(*window);
    int x = Pos.x/32;
        int y = Pos.y/32;
    while (window->pollEvent(event_play))
    {
        if (event_play.type == sf::Event::KeyPressed && event_play.key.code == sf::Keyboard::Escape) { window->close(); }
        if (event_play.type == Event::Closed) { window->close(); }
        if (event_play.type == Event::MouseButtonPressed) {
            if (event_play.key.code == Mouse::Left) {

                user_board[x][y] = game_board[x][y];
            }
            if (event_play.key.code == Mouse::Right) {

                user_board[x][y] = 11;
            }
            if (user_board[x][y] == 9){
                for (int i = 1; i <= LENGHT; i++) {
                    for (int j = 1; j <= WIDTH; j++)
                        user_board[i][j] = game_board[i][j];
                }
              
            }
        }

    }

}

void Game::gameMenu()
{
    RenderWindow Window(sf::VideoMode(1280, 720), L"mENU", sf::Style::Default);
    Window.requestFocus();
    Window.setActive(true);
    Window.setMouseCursorVisible(false);
    String name_menu[4]{ L"Start",L"Options",L"About",L"Выход" };
    GameMenu myMenu(Window, 950, 350, name_menu, 100, 120);
    myMenu.setCOolorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
    myMenu.AlignMenu(2);
  


    while (Window.isOpen())
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Up) { myMenu.MoveUp(); break; }
                if (event.key.code == sf::Keyboard::Down) { myMenu.MoveDown(); break; }
                if (event.key.code == sf::Keyboard::Return)
                {
                    switch (myMenu.getSelectedMenuNumber())
                    {
                    case 0:  Window.close(); return; break;

                    case 3:exit(0); break;
                    default:break;
                    }
                } break;
            default:break;
            }
        }
        Window.draw(background);
       
        myMenu.draw();
        Window.display();
    }
}

void Game::Inittext(Text& mtext, float xpos, float ypos, String str, int size_font, Color menu_text_color, int bord, Color border_color)
{

    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);

}


void Game::update(Time const& deltaTime) {
    MinesAnim.Update(deltaTime);
}
void Game::draw() {
    window->clear(Color::White);
    window->draw(background);
   
        for (int i = 1; i <=LENGHT; i++) {
            for (int j = 1; j <= WIDTH; j++) {
              
               Sprite Mines(mine);
                Mines.setTextureRect(IntRect(user_board[i][j] * 32, 0, 32, 32));
                Mines.setPosition(i * 32, j * 32);
                window->draw(Mines);
            }
        }
    
    window->display();
}

Game::Game()
{
    //найти более подходящуюю текстуру
    background.setTexture(&AssertMenager::GetTexture("Texture/Field.jpg"));
   
    auto MineSpriteSize=sf::Vector2i(17, 17);
     mine.loadFromFile("Texture/tiles.png");

   
     win = AssertMenager::GetTexture("Texture/win.png");
     WIN.setTexture(win);
 
    auto spriteSize = sf::Vector2i(100, 100);
    auto& idleForward = MinesAnim.CreatAnimation("MinesAnim", "Texture/SPRITESHEET.png", sf::seconds(1), true);
    idleForward.AddFrames(sf::Vector2i(0, 0), spriteSize, 6, 1);
    MinesSprite.setPosition(600, 350);
}

void Game::run()
{
   
    sf::Clock clock;
      UserBoardInit();
    
      BombsInit();
      NumsCreat();


    while (window->isOpen()) {

        Time dt = clock.restart();
        Input();
       
        update(dt);
        draw();
    }
}



