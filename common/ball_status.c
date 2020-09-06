#include <math.h>
#include "head.h"
#define PI 3.1415926
#include "game.h"
extern WINDOW *Message;
extern struct Bpoint ball;
extern struct BallStatus ball_status;

int can_kick(struct Point *loc, int strength) {
    int px = loc->x, py = loc->y;
    char local[512] = {0};
    sprintf(local, "persion(%d, %d), ball(%lf, %lf)", px, py, ball.x, ball.y);
    Show_Message(Message, NULL, local, 1);
    if ((abs(px - (int)ball.x) <= 2) && (abs(py - (int)ball.y) <= 2)) {
        if (px == (int)ball.x && py == (int)ball.x) {
            return 0;
        }
        double x = ball.x - px, y = ball.y - py;
        double dx = x / pow((pow(x, 2) + pow(y, 2)), 0.5);
        double dy = y / pow((pow(x, 2) + pow(y, 2)), 0.5);
        ball_status.a.x = -3.0 * dx;
        ball_status.a.y = -3.0 * dy;
        ball_status.v.x = strength * 6.0 * dx;
        ball_status.v.y = strength * 6.0 * dy;
        char local[512] = {0};
        sprintf(local, "persion(%d, %d), ball(%lf, %lf)", px, py, ball.x, ball.y);
        Show_Message(Message, NULL, local, 1);
        return 1;       
    }
    return 0;
}

int can_access(struct Point *loc) {
    int px = loc->x, py = loc->y;
    if ((abs(px - (int)ball.x) <= 2) && (abs(py - (int)ball.y) <= 2)) {
        char temp[512] = {0};
        sprintf(temp, "The ball has stopped in (%lf, %lf)", ball.x, ball.y);
        Show_Message(, NULL, temp, 1);
        return 1;
    }
    return 0;
}

int grap_ball() {
    srand(time(0));
    int seed = (rand() % 4), grap;
    switch(seed) {
        case 0:
        case 1:
        case 2: grap = 1; break;
        case 3: grap = 0; break;
    }
    return grap;
}
