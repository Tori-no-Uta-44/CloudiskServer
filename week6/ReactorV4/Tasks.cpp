//
// Created by 李勃鋆 on 24-9-17.
//

#include "Tasks.h"

ReactorV4::RectangleTask::RectangleTask(TcpConnectionPtr con):
	_con(con) {
}

ReactorV4::TcpConnectionPtr ReactorV4::RectangleTask::getSocketFd() const {
	return _con;
}

void ReactorV4::RectangleTask::execute() {
	auto shape = getShape();
	auto color = getColor();
	if (shape && color) {
		shape->draw();
		std::cout << "area is " << shape->area() << std::endl;
		color->fill();
	}
	_con->sendMessage("Rectangle");
}

shared_ptr<ReactorV4::AbstractShape> ReactorV4::RectangleTask::getShape() {
	return make_shared<Rectangle>(1.2, 3.4);
}

shared_ptr<ReactorV4::AbstractColor> ReactorV4::RectangleTask::getColor() {
	return make_shared<RectangleColor>();
}

ReactorV4::CircleTask::CircleTask(TcpConnectionPtr con):
	_con(con) {
}

ReactorV4::TcpConnectionPtr ReactorV4::CircleTask::getSocketFd() const {
	return _con;
}

void ReactorV4::CircleTask::execute() {
	auto shape = getShape();
	auto color = getColor();
	if (shape && color) {
		shape->draw();
		std::cout << "area is " << shape->area() << std::endl;
		color->fill();
	}
	_con->sendMessage("Circle");
}

shared_ptr<ReactorV4::AbstractShape> ReactorV4::CircleTask::getShape() {
	return make_shared<Circle>(5.6);
}

shared_ptr<ReactorV4::AbstractColor> ReactorV4::CircleTask::getColor() {
	return make_shared<CircleColor>();
}
