/*
 *      // light.h
 *
 *      Rus:
 *          Описание структуры для моделирования освещения на сцене
 *
 *      Eng:
 *          Description of the structure for modeling lighting on the stage
*/

#ifndef LIGHT
#define LIGHT

#include "geometry.h"

struct Light
{
/*
 *  Rus:
 *      Область описания методов структуры
 *  Eng:
 *      Description area of structure methods
*/
    Light(const Vec3f &s, const float &d) : stand(s), depth(d) {}

// **********************************************************

/*
 *  Rus:
 *      Область объявления переменных
 *  Eng:
 *      Variable declaration scope
*/
    Vec3f stand;
    float depth;
};

#endif // LIGHT

