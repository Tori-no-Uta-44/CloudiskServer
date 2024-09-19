//
// Created by 李勃鋆 on 24-9-18.
//

#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include "InetAddress.h"
#include "Socket.h"
#include "../../func.h"
#include "../../week01.h"

namespace ReactorV1 {

	class Acceptor {
	public:
		Acceptor(const string &ip, uint16_t port);

		void reSet();

		void binding();

		void listening() const;

		void accepting() const;

		~Acceptor();

	private:
		Socket _socket;
		InetAddress _address;
	};

} // ReactorV1

#endif //ACCEPTOR_H
