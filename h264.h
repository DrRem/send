//
// Created by Administrator on 2022/3/7.
//

#ifndef SEND_H264_H
#define SEND_H264_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <netdb.h>
#include <linux/string.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "pthread.h"

#define PACKET_BUFFER_END      (unsigned int)0x00000000
#define MAX_RTP_PKT_LENGTH     1400
#define DEST_IP                "127.0.0.1" //客户端IP
#define IP_SELF                "127.0.0.1" //本机IP
#define DEST_PORT              12346    //流媒体播放器端口
#define DEST_PORT1             12348    //测量程序端口
#define BACK_PORT              12350    //数据包发回端口
#define H264                   96
#define PRTP                   101
#define MAXDATASIZE            1500

#define DELTA                  10000          //us
#define Measure_message_length 600         //bytes
#define File_location          "/root/jetbrains/tmp/tmp.rGyBnC6xMm/test.h264"
#define Timestamp_parameter    1640966400000000

typedef int SOCKET;

/******************************************************************
RTP_FIXED_HEADER
0               1               2               3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|V=2|P|X|  CC   |M|     PT      |       sequence number         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                           timestamp                           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|           synchronization source (SSRC) identifier            |
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
|            contributing source (CSRC) identifiers             |
|                             ....                              |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

******************************************************************/
typedef struct
{
    /* byte 0 */
    unsigned char csrc_len:4;       /* expect 0 */
    unsigned char extension:1;      /* expect 1, see RTP_OP below */
    unsigned char padding:1;        /* expect 0 */
    unsigned char version:2;        /* expect 2 */
    /* byte 1 */
    unsigned char payload:7;        /* RTP_PAYLOAD_RTSP */
    unsigned char marker:1;         /* expect 1 */
    /* bytes 2, 3 */
    unsigned short seq_no;
    /* bytes 4-7 */
    unsigned  int timestamp;      /* !!Can not use long type,long = 8 Byte int 64 bit  system!!*/
    /* bytes 8-11 */
    unsigned int ssrc;            /* stream number is used here. */
} RTP_FIXED_HEADER;




/******************************************************************
NALU_HEADER
+---------------+
|0|1|2|3|4|5|6|7|
+-+-+-+-+-+-+-+-+
|F|NRI|  Type   |
+---------------+
******************************************************************/
typedef struct {
    //byte 0
    unsigned char TYPE:5;
    unsigned char NRI:2;
    unsigned char F:1;

} NALU_HEADER;/* 1 BYTES */



/******************************************************************
FU_INDICATOR
+---------------+
|0|1|2|3|4|5|6|7|
+-+-+-+-+-+-+-+-+
|F|NRI|  Type   |
+---------------+
******************************************************************/
typedef struct {
    //byte 0
    unsigned char TYPE:5;
    unsigned char NRI:2;
    unsigned char F:1;
} FU_INDICATOR; /* 1 BYTES */



/******************************************************************
FU_HEADER
+---------------+
|0|1|2|3|4|5|6|7|
+-+-+-+-+-+-+-+-+
|S|E|R|  Type   |
+---------------+
******************************************************************/
typedef struct {
    //byte 0
    unsigned char TYPE:5;
    unsigned char R:1;
    unsigned char E:1;
    unsigned char S:1;
} FU_HEADER;	/* 1 BYTES */



typedef struct
{
    /* bytes 0-3 */
    unsigned int send_Index;
    /* bytes 4-7 */
    unsigned int send_count;
    /* bytes 8-11 */
    unsigned int send_time;

}PRTPDATA;

typedef struct
{
    /**//* byte 0-3 */
    unsigned int send_Index;
    /**//* bytes 4-7 */
    unsigned int send_Count;
    /**//* bytes 8-11 */
    unsigned int send_Time;   /* stream number is used here. */
    /**//* bytes 12-15 */
    unsigned int receive_Time;
    /**//* bytes 16-20 */
    unsigned int receive_resend_Time;
    /**//* bytes 21-24 */
} PRTPDATA_RETURN;

#endif //SEND_H264_H
