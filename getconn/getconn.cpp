//
// Created by enterdawn on 2022/6/1. admin@mail.enterdawn.top
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

#include "getconn.h"
#include "../logs/log.h"
#include "../conn/conn.h"

extern logs *logger;
extern int fd_client_conn;
getConn::getConn(int port,std::string token) {

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_port = htons(port);
    serverAddr.sin_family = AF_INET;//TCPIP协议
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);//接收来自任意IP的通信
    int fd_skt = socket(AF_INET, SOCK_STREAM, 0);//新建套接字
    int err_code=-1;
    if (fd_skt < 0) {
        logger->error("server socket err");
        exit(1);
    }
    err_code=bind(fd_skt, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
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
        fd_client = accept(fd_skt, (struct sockaddr*)&clientAddr, &length);
        if (fd_client < 0) {
            logger->error("server accept err");
            exit(1);
        }
        logger->info("Get connection from "+ std::to_string(clientAddr.sin_addr.s_addr)+
                     ",port "+ std::to_string(port)+", socket"+ std::to_string(fd_client));
        int cLen = recv(fd_client, cmsg, sizeof(cmsg), 0);
        if (cLen <= 0) {
            logger->error("server recv err");
            exit(1);
        }
        cmsg[cLen] = '\0';
        if(strcmp(cmsg,smsg)!=0){
            logger->info("token error");
            logger->info(cmsg);
            strcpy(smsg,"token error");
        }
        else{
            strcpy(smsg,"success");
        }
        if(send(fd_client, smsg, strlen(smsg), 0) <= 0) { //将服务器的消息发给客户端
            logger->error("server send err");
            continue;
        }
        while(cLen = recv(fd_client, cmsg, sizeof(cmsg), 0)){
            if(cLen==1&&cmsg[0]==0){
                continue;
            }
            cmsg[cLen]='\0';
            logger->info(cmsg);
            std::string s1=cmsg;
            int i=s1.find(":");
            s1=s1.substr(i+1);
            i=s1.find(":");
            s1=s1.substr(i+1);
            logger->info(s1);
            get=new std::thread(listenAndSend,std::stoi(s1),this);

        }
        while(cLen = recv(fd_client, cmsg, sizeof(cmsg), 0)){
            logger->info(std::to_string(cLen));
            cmsg[cLen]='\0';
            logger->info("main:");
            logger->info(cmsg);
            send(fd_client_conn, cmsg, strlen(cmsg), 0);

        }
        logger->error("server closed by client");
    }

}
int getConn::sendData(std::string data) {
    int result = send(fd_client, data.c_str(), data.length(), 0);
    return result;
}
getConn::~getConn() {
    close(fd_client);
}