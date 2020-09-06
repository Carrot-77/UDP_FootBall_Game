
#include "head.h"
#include "game.h"
#include "cjson/cJSON.h"
#include "client_re_drew.h"

extern int sockfd;
cJSON *root, *score_t;

void *client_recv(void *arg) {
	while (1) {
		struct FootBallMsg msg;
		struct User user;
		bzero(&msg, sizeof(msg));

		recv(sockfd, (void *)&msg, sizeof(msg), 0);
		strcpy(user.name, msg.name);
		user.team = msg.team;
		if (msg.type & FT_TEST) {
			DBG(RED"HeartBeat from Server 心跳\n"NONE);
			msg.type = FT_ACK;
			send(sockfd, (void *)&msg, sizeof(msg), 0);
		} else if (msg.type & FT_MSG) {
			DBG(GREEN"%s : "NONE"%s\n", user.name, msg.msg);
			Show_Message( , &user, msg.msg, 0);
		} else if (msg.type & FT_WALL) {
			DBG(GREEN"Server Msg: "NONE"%s\n", msg.msg);
			Show_Message( , NULL, msg.msg, 1);
		} else if (msg.type & FT_FIN) {
			DBG(GREEN"Server is going to stop!\n"NONE);
			endwin();	
			exit(0);
        } else if(msg.type & FT_SCORE) {
            score_t = cJSON_Parse(msg.msg);
            char temp[512] = {0};
            re_drew_score(score_t);
            //sprintf(temp, "%s get 1 score", cJSON_GetObjectItem(root, "score")->valuestring);
            //Show_Message(, NULL, temp, 1);
        } else if (msg.type & FT_GAME) {
            root = cJSON_Parse(msg.msg);
            client_re_drew(root);
        } else {
			DBG(GREEN"Server Msg :"NONE"Unsupport Message Type.\n");
		}
	}
}
