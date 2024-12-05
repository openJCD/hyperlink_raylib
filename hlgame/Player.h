//
// Created by openjcd on 01/12/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include<memory>
#include "NetworkNode.h"
using std::shared_ptr;
class Player {
    shared_ptr<NetworkNode> m_CurrentConnection;
    shared_ptr<NetworkNode> m_HomeNode;

};

#endif //PLAYER_H
