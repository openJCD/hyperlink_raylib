#pragma once
#ifndef NETWORKNODE_H  
#define NETWORKNODE_H
#include "game_structs.h"
#include <string>
#include <list>
#include <random>
using std::string;
using std::list;

// A node on the global network map. Has a list of one-way links to child nodes; each node has a reference to its parent
// to facilitate network scans, et cetera.
class NetworkNode {
protected:
	hl_IpAddr m_ip = hl_RandomIp();
	short m_id = rand();
	string m_name;
	string m_regionName;
	hl_NetworkNodeType m_type;
	list<NetworkNode*> m_linkedNodes;
	NetworkNode* m_parent = nullptr;
public:
	NetworkNode(NetworkNode* parent, string name, string region, hl_NetworkNodeType type)
		: m_name(std::move(name)), m_regionName(std::move(region)), m_type(type), m_parent(parent) { }

	void LinkTo(NetworkNode* node) {
		node->m_parent = this;
		m_linkedNodes.emplace_back(node);
	}
};
#endif