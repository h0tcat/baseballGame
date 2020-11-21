#include <iostream>
#include <ncurses.h>
#include <string>
#include <thread>
#include <unistd.h>

void setup()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    nodelay(stdscr,true);
}

class BaseBall
{
public:
    std::string stick = "!";
    std::string ball = "O";

    int ball_y = 0;
    int ball_x = 15;

    int stick_x = 14;
    int stick_y = 15;

    void operator()()
    {
        int chr=0;
        while (this->ball_y<=16)
        {
            clear();
            this->ball_y++;

            mvprintw(this->ball_y,this->ball_x,this->ball.c_str());
            mvprintw(this->stick_y,this->stick_x,this->stick.c_str());

            std::this_thread::sleep_for(std::chrono::milliseconds(150));

            chr=getch();
            if(chr!=ERR)
                break;

            refresh();
        }
        if(this->ball_y==15){
            mvprintw(15,19,"HIT BALL!");
            nodelay(stdscr,false);
            getch();
        }
    }
};

int main(void)
{

    setup();
    BaseBall baseball;

    std::thread mainGameThread(baseball);

    mainGameThread.join();
    endwin();
    return 0;
}