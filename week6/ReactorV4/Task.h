//
// Created by 李勃鋆 on 24-9-14.
//
#ifndef TASK_H
#define TASK_H
#include "TcpConnection.h"
#include "../../week01.h"

namespace ReactorV4 {
	class AbstractColor;
	class AbstractShape;

	class Task {
	public:
		virtual ~Task() = default;

		virtual shared_ptr<AbstractShape> getShape() =0;

		virtual shared_ptr<AbstractColor> getColor() =0;

		[[nodiscard]] virtual TcpConnectionPtr getSocketFd() const =0;

		virtual void execute() =0;
	};
}
#endif // TASK_H
