
#include "head.h"
#include "game.h"
#define MAX 50
#include "ball_status.h"
#include "cJSON_data.h"

extern struct Score score;
extern struct User *rteam,*bteam;
extern WINDOW *Football, *Help, *Score;
extern struct Bpoint ball;
extern struct BallStatus ball_status;
extern struct Map court;

void re_drew_player(int team, char *name, struct Point *loc) {
	char p = 'K';
    //Show_Message(, NULL, "in Windows", 1);
    char local[50] = {0};
    sprintf(local, "in (%d, %d)", loc->x, loc->y);
    //Show_Message(, NULL, local, 1);
	wattron(Football, COLOR_PAIR((team ? 6 : 2)));
	w_gotoxy_putc(Football, loc->x, loc->y, p);
	w_gotoxy_puts(Football, loc->x + 1, loc->y - 1, name);
	wattroff(Football, COLOR_PAIR((team ? 6 : 2)));
}

void re_drew_team(struct User *team) {
	for (int i = 0; i < MAX ; i++) {
		if (!team[i].online) continue;
		re_drew_player(team[i].team, team[i].name, &team[i].loc);
        //char local[50] = {0};
        //sprintf(local, "in (%d, %d)", team[i].loc.x, team[i].loc.y);
        //Show_Message(, NULL, local, 1);
	}
}

void re_drew_help() {
    wattron(Help, COLOR_PAIR(3));
    mvwprintw(Help, 1, 1, "W turn up");
    mvwprintw(Help, 2, 1, "S turn down");
    mvwprintw(Help, 3, 1, "A turn left");
    mvwprintw(Help, 4, 1, "D turn right");
    //mvwprintw(Help, 1, 5, "space 蓄力踢球");
    mvwprintw(Help, 6, 1, "Space kick");
    mvwprintw(Help, 7, 1, "Enter chat massage");
    mvwprintw(Help, 8, 1, "J stop");
    mvwprintw(Help, 9, 1, "K kick");
    mvwprintw(Help, 10, 1, "L carry kick");
    wattroff(Help, COLOR_PAIR(3));
}

void re_drew_ball() {
    if (ball_status.carry == 1) {
        ball.x = ball_status.user->loc.x;
        ball.y = ball_status.user->loc.y;
        if (ball_status.user->team) ball.x += 1;
        else ball.x -= 1;
    }
    if (ball_status.v.x * (ball_status.v.x + ball_status.a.x) > 0) {
        ball.x = ball.x + ball_status.v.x * 0.1 + ball_status.a.x * 0.5 * 0.01;
        ball.y = ball.y + ball_status.v.y * 0.1 + ball_status.a.y * 0.5 * 0.01;
        ball_status.v.x += ball_status.a.x  * 0.1;
        ball_status.v.y += ball_status.a.y  * 0.1;
        char local[512] = {0};
        if ((int)ball_status.v.x & 1) {
            sprintf(local, "v(%lf, %lf), a(%lf, %lf)", ball_status.v.x, ball_status.v.y, ball_status.a.x, ball_status.a.y);
            Show_Message( , NULL, local, 1);
        }
    }
    if (ball.x <= 0 || ball.x >= 114 || ball.y <= 0 || ball.y >= 24) {
        if ((ball.y >= 10 && ball.y <= 14)) {
            char temp[512] = {0};
            if (ball.x <= 0) {
                score.red++;
            } else if (ball.x >= 113) {
                score.blue++;
            }
        }
        ball.x = court.width / 2;
        ball.y = court.height / 2;
        ball_status.v.x = ball_status.v.y = 0;
        ball_status.a.x = ball_status.a.y = 0;        
    }
    w_gotoxy_putc(Football, (int)ball.x, (int)ball.y, 'O');
}

void re_drew_score() {
    w_gotoxy_puts(Score, 1, 1, "red VS blue");
    wattron(Score, COLOR_PAIR(2));
    mvwprintw(Score, 2, 2, "%d", score.red);
    wattroff(Score, COLOR_PAIR(2));
    w_gotoxy_putc(Score, 5, 2, ':');
    wattron(Score, COLOR_PAIR(6));
    mvwprintw(Score, 2, 9, "%d", score.blue);
    wattroff(Score, COLOR_PAIR(6));
}

void re_drew_football() {
    w_gotoxy_putc(Football_t, 1, 11, 'X');
    w_gotoxy_putc(Football_t, 1, 12, 'X');
    w_gotoxy_putc(Football_t, 1, 13, 'X');
    w_gotoxy_putc(Football_t, 1, 14, 'X');
    w_gotoxy_putc(Football_t, 1, 15, 'X');
    w_gotoxy_putc(Football_t, 117, 11, 'X');
    w_gotoxy_putc(Football_t, 117, 12, 'X');
    w_gotoxy_putc(Football_t, 117, 13, 'X');
    w_gotoxy_putc(Football_t, 117, 14, 'X');
    w_gotoxy_putc(Football_t, 117, 15, 'X');
}

void re_drew() {
   // wclear(Football);
	werase(Football_t);
    box(Football_t, 0, 0);
	box(Football, 0, 0);
    re_drew_ball();
    re_drew_help();
    re_drew_score();
	re_drew_team(rteam);
	re_drew_team(bteam);
    re_drew_football();
    wrefresh(Football_t);
    wrefresh(Football);
    wrefresh(Help);
    wrefresh(Score);
    send_data();
    send_score();
}
