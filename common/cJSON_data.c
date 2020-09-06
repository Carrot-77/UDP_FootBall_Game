#include <stdio.h>
#include <cjson/cJSON.h>
#include "head.h"
#include "datatype.h"

#define MAX 50
extern struct Bpoint ball;
extern struct BallStatus ball_status;
extern struct Score score;
extern struct User *rteam, *bteam;

cJSON *cJSON_data() {
    cJSON *root = cJSON_CreateObject();
    cJSON *json_red = cJSON_CreateArray();
    cJSON *json_blue = cJSON_CreateArray();
    cJSON *json_ball = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "ball", json_ball);
    cJSON_AddItemToObject(root, "rteam", json_red);
    cJSON_AddItemToObject(root, "bteam", json_blue);

    cJSON_AddNumberToObject(json_ball, "x", ball.x);
    cJSON_AddNumberToObject(json_ball, "y", ball.y);


    for (int i = 0; i < MAX; i++) {
        if (rteam[i].online) {
            cJSON *rteams = cJSON_CreateObject();
            cJSON_AddStringToObject(rteams, "name", rteam[i].name);
            cJSON_AddNumberToObject(rteams, "locx", rteam[i].loc.x);
            cJSON_AddNumberToObject(rteams, "locy", rteam[i].loc.y);
            cJSON_AddItemToArray(json_red, rteams);
        }
        if (bteam[i].online) {
            cJSON *bteams = cJSON_CreateObject();
            cJSON_AddStringToObject(bteams, "name", bteam[i].name);
            cJSON_AddNumberToObject(bteams, "locx", bteam[i].loc.x);
            cJSON_AddNumberToObject(bteams, "locy", bteam[i].loc.y);
            cJSON_AddItemToArray(json_blue, bteams);
        }

    }
    return root;
}

cJSON *cJSON_score() {
    cJSON *json_score = cJSON_CreateObject();
    cJSON *score_tt = cJSON_AddObjectToObject(json_score, "score");
    //cJSON_AddItemToObject(json_score, "score", json_score);
    cJSON_AddNumberToObject(score_tt, "rscore", score.red);
    cJSON_AddNumberToObject(score_tt, "bscore", score.blue);
    DBG("%s\n", cJSON_Print(json_score));
    return json_score;
}

void send_score() {
    struct FootBallMsg msg;
    msg.type = FT_SCORE;
    strcpy(msg.msg, cJSON_Print(cJSON_score()));
    for (int i = 0; i < MAX; i++) {
        if (rteam[i].online) {
            send(rteam[i].fd, (void *)&msg, sizeof(msg), 0);
        }
        if (bteam[i].online) {
            send(bteam[i].fd, (void *)&msg, sizeof(msg), 0);
        }
    }
}

void send_data() {
    struct FootBallMsg msg;
    msg.type = FT_GAME;
    strcpy(msg.msg, cJSON_Print(cJSON_data()));
    DBG("%s\n", msg.msg);
    for (int i = 0; i < MAX; i++) {
        if (rteam[i].online) {
            send(rteam[i].fd, (void *)&msg, sizeof(msg), 0);
        }
        if (bteam[i].online) {
            send(bteam[i].fd, (void *)&msg, sizeof(msg), 0);
        }
    }
}

