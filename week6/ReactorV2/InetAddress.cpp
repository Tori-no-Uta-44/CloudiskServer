//
// Created by 李勃鋆 on 24-9-18.
//

#include "InetAddress.h"

namespace ReactorV2 {
	InetAddress::InetAddress(const sockaddr_in &address):
		_address(address) {
	}

	InetAddress::InetAddress(const string &ip, uint16_t port) {
		_address.sin_family = AF_INET;
		_address.sin_addr.s_addr = inet_addr(ip.c_str());
		_address.sin_port = htons(port);
	}

	string InetAddress::getIp() const {
		return {inet_ntoa(_address.sin_addr)};
	}

	uint16_t InetAddress::getPort() const {
		return ntohs(_address.sin_port);
	}

	sockaddr_in *InetAddress::getAddress() {
		return &_address;
	}

	InetAddress::~InetAddress() = default;
} // ReactorV1
