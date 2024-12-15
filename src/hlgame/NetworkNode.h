#pragma once
#ifndef NETWORKNODE_H  
#define NETWORKNODE_H
#include "game_structs.h"
#include <string>
#include <list>
#include <utility>
using std::string;
using std::list;
using std::rand;
class NetworkNode {
protected:
	hl_IpAddr m_ip = hl_RandomIp();
	short m_id = (short)rand();
	string m_name;
	string m_regionName;
	hl_NetworkNodeType m_type;
	list<NetworkNode*> m_linkedNodes;
	NetworkNode* m_parent = nullptr;
public:
	inline NetworkNode(NetworkNode* parent, string name, string region, hl_NetworkNodeType type)
		: m_name(std::move(name)), m_regionName(std::move(region)), m_type(type), m_parent(parent) { }
};
#endif