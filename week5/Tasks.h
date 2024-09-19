//
// Created by 李勃鋆 on 24-9-17.
//

#ifndef TASKS_H
#define TASKS_H
#include "Color.h"
#include "Shape.h"
#include "Task.h"

namespace day30_1 {
	class RectangleTask : public Task {
		unique_ptr<AbstractShape> getShape() override;

		unique_ptr<AbstractColor> getColor() override;
	};

	class CircleTask : public Task {
		unique_ptr<AbstractShape> getShape() override;
		unique_ptr<AbstractColor> getColor() override;
	};
}
#endif //TASKS_H
