//
// Created by 李勃鋆 on 24-9-18.
//

#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include "InetAddress.h"
#include "Socket.h"
#include "../../func.h"
#include "../../week01.h"

namespace ReactorV4 {

	class Acceptor {
	public:
		Acceptor(const string &ip, uint16_t port);

		void setSocketOptions();

		void binding();

		void listening() const;

		int accepting() const;

		int getFd() const;

		~Acceptor();

	private:
		Socket _socket;
		InetAddress _address;
	};

}

#endif //ACCEPTOR_H
