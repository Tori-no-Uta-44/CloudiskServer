//
// Created by 李勃鋆 on 24-9-17.
//

#ifndef SHAPE_H
#define SHAPE_H
#include "AbstractShape.h"

namespace ReactorV4 {
	class Rectangle : public AbstractShape {
		double _width = 0.0, _height = 0.0;

	public:
		Rectangle() = default;

		explicit Rectangle(double width, double height);

		void draw() override;

		double area() override;

		~Rectangle() override;
	};

	class Circle final : public AbstractShape {
		double _radius = 0.0;

	public:
		Circle() = default;

		explicit Circle(double radius);

		void draw() override;

		double area() override;

		~Circle() override;
	};
}
#endif //SHAPE_H
