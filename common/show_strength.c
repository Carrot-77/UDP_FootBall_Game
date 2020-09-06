
#include "head.h"

extern WINDOW *Write;
extern int sockfd;

void show_strength() {
    int carrotx = 2, offset = 1;
    int maxx, maxy;
    int arr[5] = {1, 2, 3, 2, 1};
    getmaxyx(Write, maxy, maxx);
    int stander = maxx / 5;
    for (int i = 2; i < maxx - 2; i++) {
        if (i < maxx / 5 || i > maxx * 4 / 5) {
            wattron(Write, COLOR_PAIR(7));
        } else if (i < maxx * 2 / 5 || i > maxx * 3 / 5) {
            wattron(Write, COLOR_PAIR(11));
        } else {
            wattron(Write, COLOR_PAIR(8));
        }
        mvwprintw(Write, 2, i, " ");
        //make_nonblock(0);
    }
    wrefresh(Write);
    wattron(Write, COLOR_PAIR(3));
    make_nonblock(0);
    while(1) {
        char c = getchar();
        if (c != -1) {
            if (c == ' ' || c == 'k') {
                make_block(0);
                break;
            }
        }
        usleep(20000);
        if (carrotx >= maxx - 2) offset = -1;
        else if (carrotx <= 2) offset = 1;
        mvwprintw(Write, 1, carrotx, " ");
        mvwprintw(Write, 3, carrotx, " ");
        carrotx += offset;
        mvwprintw(Write, 1, carrotx, "|");
        mvwprintw(Write, 3, carrotx, "|");
        mvwprintw(Write, 4, maxx, " ");
        wrefresh(Write);
    }
    struct FootBallMsg msg;
    bzero(&msg, sizeof(msg));
    msg.type = FT_CTL;
    msg.ctl.action = ACTION_KICK;
    msg.ctl.strength = arr[carrotx /stander];
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    return;
}
