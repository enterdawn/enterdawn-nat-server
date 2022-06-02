//
// Created by enterdawn on 2022/6/2. admin@mail.enterdawn.top
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef ENTERDAWN_NAT_SERVER_CONN_H
#define ENTERDAWN_NAT_SERVER_CONN_H

#include "../getconn/getconn.h"
#include "../logs/log.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
extern logs *logger;
extern int fd_client_conn;
static void listenAndSend(int port,getConn *conn){
    sockaddr_in serverAddr_conn;
    memset(&serverAddr_conn, 0, sizeof(serverAddr_conn));
    serverAddr_conn.sin_port = htons(port);
    serverAddr_conn.sin_family = AF_INET;//TCPIP协议
    serverAddr_conn.sin_addr.s_addr = htonl(INADDR_ANY);//接收来自任意IP的通信
    int fd_skt = socket(AF_INET, SOCK_STREAM, 0);//新建套接字
    int err_code=-1;
    if (fd_skt < 0) {
        logger->error("server socket err");
        exit(1);
    }
    err_code=bind(fd_skt, (struct sockaddr*)&serverAddr_conn, sizeof(serverAddr_conn));
    if ( err_code< 0 ) { //bind绑定套接字与serverAddr
        logger->error("server bind err");
        exit(1);
    }
    err_code=listen(fd_skt, 20);
    if (err_code < 0) { // 监听套接字
        logger->error("server listen err");
        exit(1);
    }
    logger->info("Listening port "+std::to_string(port)+" ...");
    while(1){
        char cmsg[1024];
        char smsg[1024]="a";
        struct sockaddr_in clientAddr;
        socklen_t length = sizeof(clientAddr);
        fd_client_conn = accept(fd_skt, (struct sockaddr*)&clientAddr, &length);
        if (fd_client_conn < 0) {
            logger->error("server accept err");
            exit(1);
        }
        logger->info("Get connection from "+ std::to_string(clientAddr.sin_addr.s_addr)+
                     ",port "+ std::to_string(port)+", socket"+ std::to_string(fd_client_conn));

        int cLen;
        while(cLen = recv(fd_client_conn, cmsg, sizeof(cmsg), 0)){
            cmsg[cLen]='\0';
            logger->info(cmsg);
            logger->info("thread:");
            conn->sendData(cmsg);
        }
        logger->error("server closed by client");
    }
}


#endif //ENTERDAWN_NAT_SERVER_CONN_H
