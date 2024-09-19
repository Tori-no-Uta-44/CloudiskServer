//
// Created by 李勃鋆 on 24-9-18.
//

#ifndef INETADDRESS_H
#define INETADDRESS_H
#include "../../func.h"
#include "../../week01.h"

namespace ReactorV2 {
	class InetAddress {
	public:
		explicit InetAddress(const sockaddr_in &address);

		InetAddress(const string &ip, uint16_t port);

		[[nodiscard]] string getIp() const;

		[[nodiscard]] uint16_t getPort() const;

		sockaddr_in *getAddress();

		~InetAddress();

	private:
		sockaddr_in _address = {};
	};

} // ReactorV1

#endif //INETADDRESS_H
