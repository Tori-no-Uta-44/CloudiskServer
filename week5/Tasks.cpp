//
// Created by 李勃鋆 on 24-9-17.
//

#include "Tasks.h"

unique_ptr<day30_1::AbstractShape> day30_1::RectangleTask::getShape() {
	return make_unique<Rectangle>(1.2, 3.4);
}

unique_ptr<day30_1::AbstractColor> day30_1::RectangleTask::getColor() {
	return make_unique<RectangleColor>();
}

unique_ptr<day30_1::AbstractShape> day30_1::CircleTask::getShape() {
	return make_unique<Circle>(5.6);
}

unique_ptr<day30_1::AbstractColor> day30_1::CircleTask::getColor() {
	return make_unique<CircleColor>();
}
