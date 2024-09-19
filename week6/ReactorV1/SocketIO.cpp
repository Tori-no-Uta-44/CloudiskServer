//
// Created by 李勃鋆 on 24-9-18.
//

#include "SocketIO.h"

namespace ReactorV1 {
	SocketIO::SocketIO(int socket):
		_socket(socket) {
	}

	int SocketIO::recvn(void *buf, int len) const {
		int left = len; //还剩多少个字节需要接收
		char *pbuf = static_cast<char *>(buf);
		while (left > 0) {
			int ret = recv(_socket, pbuf, left, 0);
			if (ret == 0) {
				break;
			}
			if (ret < 0) {
				if (errno == EINTR) {
					continue; // interrupted by signal, retry
				}
				throw std::runtime_error("recv failed: " + std::string(strerror(errno)));
			}
			pbuf += ret;
			left -= ret;
		}
		return len - left;
	}

	int SocketIO::sendn(const char *buf, int len) const {
		int left = len;
		const char *pbuf = buf;
		while (left > 0) {
			int ret = send(_socket, pbuf, left, 0);
			if (ret < 0) {
				if (errno == EINTR) {
					continue; // interrupted by signal, retry
				}
				throw std::runtime_error("send failed: " + std::string(strerror(errno)));
			}
			pbuf += ret;
			left -= ret;
		}
		return len - left;
	}

	int SocketIO::readLine(char *buf, int len) const {
		int left = len - 1;
		char *pbuf = buf;
		int ret = 0, total = 0;
		while (left > 0) {
			ret = recv(_socket, pbuf, left,MSG_PEEK);
			if (ret < 0) {
				if (errno == EINTR) {
					continue;
				}
				throw std::runtime_error("readLine error: " + std::string(strerror(errno)));
			}
			if (ret == 0) {
				break;
			}
			for (int i = 0; i < ret; i++) {
				if (pbuf[i] == '\n') {
					int size = i + 1;
					recvn(pbuf, size);
					pbuf += size;
					*pbuf = '\0';
					return total + size;
				}
			}
			recvn(pbuf, ret);
			total += ret;
			pbuf += ret;
			left -= ret;
		}
		*pbuf = '\0';
		return total;
	}

	SocketIO::~SocketIO() = default;
} // ReactorV1
