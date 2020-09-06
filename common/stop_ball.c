#include "head.h"
#include "game.h"
extern int sockfd;
extern WINDOW *Message;
void stop_ball() {
    struct FootBallMsg msg;
    bzero(&msg, sizeof(msg));
    msg.type = FT_CTL;
    msg.ctl.action=ACTION_STOP;
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    return;
}

void carry_ball() {
    //char temp[512] = {0};
    //sprintf(temp, "You want to carry the ball");
    //Show_Message(, NULL, temp, 1);
    struct FootBallMsg msg;
    bzero(&msg, sizeof(msg));
    msg.type = FT_CTL;
    msg.ctl.action = ACTION_CARRY;
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    return;
}
