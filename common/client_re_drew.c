
#include "head.h"
#include "game.h"
#include <cjson/cJSON.h>

#define MAX 50

extern WINDOW *Football, *Football_t, *Score;
extern struct Bpoint ball;
extern struct Map court;
extern struct Score score;

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

void re_drew_rteam(cJSON *root) {
    int index = cJSON_GetArraySize(root);
    for (int i = 0; i < index; i++) {
        cJSON *rteam = cJSON_GetArrayItem(root, i);
        char name[20];
        strcpy(name, cJSON_GetObjectItem(rteam, "name")->valuestring);
        int locx = cJSON_GetObjectItem(rteam, "locx")->valueint;
        int locy = cJSON_GetObjectItem(rteam, "locy")->valueint;

        wattron(Football, COLOR_PAIR(2));
        w_gotoxy_putc(Football, locx, locy, 'K');
        w_gotoxy_puts(Football, locx + 1, locy - 1, name);
        wattroff(Football, COLOR_PAIR(2));
    }
}

void re_drew_bteam(cJSON *root) {
    int index = cJSON_GetArraySize(root);
    for (int i = 0; i < index; i++) {
        cJSON *rteam = cJSON_GetArrayItem(root, i);
        char name[20];
        strcpy(name, cJSON_GetObjectItem(rteam, "name")->valuestring);
        int locx = cJSON_GetObjectItem(rteam, "locx")->valueint;
        int locy = cJSON_GetObjectItem(rteam, "locy")->valueint;

        wattron(Football, COLOR_PAIR(6));
        w_gotoxy_putc(Football, locx, locy, 'K');
        w_gotoxy_puts(Football, locx + 1, locy - 1, name);
        wattroff(Football, COLOR_PAIR(6));
    }
}

void re_drew_ball(cJSON *root) {
    int x = cJSON_GetObjectItem(root, "x")->valueint;
    int y = cJSON_GetObjectItem(root, "y")->valueint;
    w_gotoxy_putc(Football, x, y, 'O');
}

void re_drew_score(cJSON *root) {
    werase(Score);
    box(Score, 0, 0);
    cJSON *xxxx = cJSON_GetObjectItem(root, "score");
    int rscore = cJSON_GetObjectItem(xxxx, "rscore")->valueint;
    int bscore = cJSON_GetObjectItem(xxxx, "bscore")->valueint;
    w_gotoxy_puts(Score, 1, 1, "red VS blue");
    wattron(Score, COLOR_PAIR(2));
    mvwprintw(Score, 2, 2, "%d", rscore);
    wattroff(Score, COLOR_PAIR(2));
    w_gotoxy_putc(Score, 5, 2, ':');
    wattron(Score, COLOR_PAIR(6));
    mvwprintw(Score, 2, 9, "%d", bscore);
    wattroff(Score, COLOR_PAIR(7));
    wrefresh(Score);
}


void client_re_drew(cJSON *root) {
    cJSON *rteams = cJSON_GetObjectItem(root, "rteam");
    cJSON *bteams = cJSON_GetObjectItem(root, "bteam");
    cJSON *balls = cJSON_GetObjectItem(root, "ball");
    werase(Football_t);
    box(Football_t, 0, 0);
    box(Football, 0, 0);
    re_drew_football();
    
    re_drew_rteam(rteams);
    re_drew_bteam(bteams);
    re_drew_ball(balls);
    
    wrefresh(Football_t);
}
