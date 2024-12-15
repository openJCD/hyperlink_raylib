#pragma once
#ifndef GAME_STRUCTS_H_
#define GAME_STRUCTS_H_
#include <string>
#define GAME_LOG(msg) std::cout << "[GAME: INFO]" << msg << std::endl;

using std::string;

// Data Types //

/// In-game IP address struct
struct hl_IpAddr {
	char one = 0;
	char two = 0;
	char three = 0;
	char four = 0;
};

// IP Address Helper Functions //
inline hl_IpAddr hl_RandomIp() {
	char one = (char)rand();
	char two = (char)rand();
	char three = (char)rand();
	char four = (char)rand();
	return hl_IpAddr {
		one,
		two,
		three,
		four
	};
}

inline string hl_IpToString(hl_IpAddr ip) {
	string ret;
	ret += std::to_string(ip.one) + "." +
		std::to_string(ip.two) + "." +
		std::to_string(ip.three) + "." +
		std::to_string(ip.four);
	return ret;
}

enum hl_NetworkNodeType {
	NET_NODE_HOMEPC,
	NET_NODE_REGION,
	NET_NODE_ROUTER,
	NET_NODE_DEVICE_PC,
	NET_NODE_DEVICE_SERVER,
	NET_NODE_DEVICE_PHONE
};
#endif