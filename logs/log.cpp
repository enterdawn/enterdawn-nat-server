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

#include "log.h"
#include "../tools/currenttime.h"
logs::logs(int level) {
    this->level = level;
}

void logs::debug(std::string s) {
    if (level == 1) {
        std::cout << getTime() << "[DEBUG] " << s << std::endl;
    }
}
void logs::error(std::string s) {
    std::cout << getTime() << "[ERROR] " << s << std::endl;
}
void logs::warning(std::string s) {
    std::cout << getTime() << "[WARNING] " << s << std::endl;
}
void logs::info(std::string s) {
    std::cout << getTime() << "[INFO] " << s << std::endl;
}

