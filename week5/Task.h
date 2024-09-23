//
// Created by 李勃鋆 on 24-9-14.
//
#ifndef TASK_H
#define TASK_H
#include "../week5.h"

namespace day30_1 {
	class AbstractColor;
	class AbstractShape;

	class Task {
	public:
		virtual ~Task() = default;

		virtual unique_ptr<AbstractShape> getShape() =0;

		virtual unique_ptr<AbstractColor> getColor() =0;
	};

}
#endif // TASK_H
