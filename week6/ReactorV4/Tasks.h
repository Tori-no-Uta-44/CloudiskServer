//
// Created by 李勃鋆 on 24-9-17.
//

#ifndef TASKS_H
#define TASKS_H
#include "Color.h"
#include "Shape.h"
#include "Task.h"
#include "TcpConnection.h"

namespace ReactorV4 {
	class RectangleTask : public Task {
	public:
		explicit RectangleTask(TcpConnectionPtr con);
		shared_ptr<AbstractShape> getShape() override;

		shared_ptr<AbstractColor> getColor() override;
		[[nodiscard]] TcpConnectionPtr getSocketFd() const override;
		void execute() override;
	private:
		TcpConnectionPtr _con;
	};

	class CircleTask : public Task {
	public:
		explicit CircleTask(TcpConnectionPtr con);
		shared_ptr<AbstractShape> getShape() override;
		shared_ptr<AbstractColor> getColor() override;
		[[nodiscard]] TcpConnectionPtr getSocketFd() const override;
		void execute() override;
	private:
		TcpConnectionPtr _con;
	};
}
#endif //TASKS_H
