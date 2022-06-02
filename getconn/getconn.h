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

#ifndef ENTERDAWN_NAT_SERVER_GETCONN_H
#define ENTERDAWN_NAT_SERVER_GETCONN_H
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <thread>
#include <pthread.h>
class getConn{
public:
    getConn(int port,std::string token);
    int sendData(std::string data);
    std::thread *get;
    ~getConn();
private:
    sockaddr_in serverAddr;
    int fd_client;
};

#endif //ENTERDAWN_NAT_SERVER_GETCONN_H
