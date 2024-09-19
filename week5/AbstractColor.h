//
// Created by 李勃鋆 on 24-9-17.
//
#ifndef ABSTRACTCOLOR_H
#define ABSTRACTCOLOR_H
#include "../week5.h"

namespace day30_1 {
	class AbstractColor {
	public:
		virtual ~AbstractColor() = default;

		virtual void fill() =0;
	};
}
#endif // ABSTRACTCOLOR_H
