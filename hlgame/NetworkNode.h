#pragma once
#ifndef NETWORKNODE_H
#define NETWORKNODE_H
#include "structs.h"
#include <string>
using std::string;
class NetworkNode {
private:
	hl_IpAddr m_ip;
	string id;
};

#endif