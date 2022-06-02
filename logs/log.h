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

#ifndef ENTERDAWN_NAT_SERVER_LOG_H
#define ENTERDAWN_NAT_SERVER_LOG_H
#include <iostream>
#include <string>
#include <ctime>


class logs {
private:
    int level;
public:
    logs(int level=1);
    void debug(std::string text);
    void info(std::string text);
    void warning(std::string text);
    void error(std::string text);
};

#endif //ENTERDAWN_NAT_SERVER_LOG_H
