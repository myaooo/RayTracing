//
//  color.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/29.
//

#include "color.h"
namespace RayTracing{
    const Color Color::BLACK(Epsilon, Epsilon, Epsilon),
                Color::WHITE(1, 1, 1),
                Color::RED(1, Epsilon, Epsilon),
                Color::BLUE(Epsilon, Epsilon, 1),
                Color::GREEN(Epsilon, 1, Epsilon),
                Color::YELLOW(1, 1, Epsilon),
                Color::CYAN(Epsilon, 1, 1),
                Color::MAGNETA(1, Epsilon, 1);
}
