//
// Created by 李勃鋆 on 24-9-17.
//

#ifndef COLOR_H
#define COLOR_H
#include "AbstractColor.h"

namespace ReactorV4 {
	class RectangleColor : public AbstractColor {
	public:
		void fill() override;
	};

	class CircleColor : public AbstractColor {
	public:
		void fill() override;
	};
}
#endif //COLOR_H
