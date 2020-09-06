#ifndef _DATATYPE_H
#define _DATATYPE_H
#define MAXMSG 512
#include <pthread.h>

struct LogRequest {
    char name[80];
    int team; // 0 r 1 b
	char msg[512];
};

struct LogResponse{
	int type; //0 success 1 failed
	char msg[512];
};

struct Point {//位置
    int x, y;;
};

struct Bpoint{
    double x;
    double y;
};

struct User {
    int team;//默认蓝队
	int fd;
	int online;
    char name[80];//队名
    int flag; // 未响应的次数
    struct Point loc; //位置
};

#define ACTION_KICK 0x01
#define ACTION_CARRY 0x02
#define ACTION_STOP 0x04

struct Map {//场地
    int width; //宽
	int height;//长
    struct Point start;//开始的点
    int gate_width;
	int gate_height;//球门宽度和高度
};

struct Map court;

struct Ctrl { //控制
    int action;//带球
	int strength;
	int dirx;
	int diry;
};

#define FT_TEST 0x01  //服务端心跳信息
#define FT_WALL 0x02	//服务端以字符串方式广播游戏情况
#define FT_MSG 0x04		//客户端发送的信息，服务端转发的信息
#define FT_ACK 0x08		//客户端对心跳的ACK确认
#define FT_FIN 0x10		//客户端，服务端下线前，对彼此的告知
#define FT_CTL 0x20		//客户端发送的控制信息json发送
#define FT_GAME 0x40	//服务端向客户端广播的游戏实时图画 json发送
#define FT_SCORE 0x80		//服务端对客户端广播的游戏比分变化，json发送（包括进球人）
#define FT_GAMEOVER 0x100 //游戏结束

struct FootBallMsg {
	int type;
	int size;
	int team;
	char name[80];
	struct Ctrl ctl;
	char msg[MAXMSG];
};

struct Aspeed{
    double x;
    double y;
};

struct Speed{
    double x;
    double y;
};

struct BallStatus {
    struct Speed v;
    struct Aspeed a;
    int t;
    int who; //哪一对的人
    char name[80]; //踢球的人是谁
    int carry;
    struct User *user;
    pthread_mutex_t mutex;
};

struct Score {
    int red;
    int blue;
};
struct Score score;
#endif
