//
//  color.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/29.
//

#include "color.h"

const Color Color::BLACK(EPS, EPS, EPS),
			Color::WHITE(1, 1, 1),
			Color::RED(1, EPS, EPS),
			Color::BLUE(EPS, EPS, 1),
			Color::GREEN(EPS, 1, EPS),
			Color::YELLOW(1, 1, EPS),
			Color::CYAN(EPS, 1, 1),
			Color::MAGNETA(1, EPS, 1);
