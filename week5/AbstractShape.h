//
// Created by 李勃鋆 on 24-9-15.
//
#ifndef ABSTRACTSHAPE_H
#define ABSTRACTSHAPE_H
#include "../week5.h"

namespace day30_1 {
	class AbstractShape {
	public:
		virtual ~AbstractShape() = default;

		virtual double area() =0;

		virtual void draw() =0;
	};
}
#endif // ABSTRACTSHAPE_H
