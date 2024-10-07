#ifndef __POINT_COMPARE_H__
#define __POINT_COMPARE_H__

#include "SDL_rect.h"

/**
 * @brief 比较两个坐标是否完全相等。
*/
bool operator==(const SDL_Point & __a, const SDL_Point & __b) {
    return (__a.x == __b.x) && (__a.y == __b.y);
}

/**
 * @brief 比较两个坐标是否完全不相等。
*/
bool operator!=(const SDL_Point & __a, const SDL_Point & __b) {
    return (__a.x != __b.x) && (__a.y != __b.y);
}

/**
 * @brief 判断点 A 是否在点 B 的左侧区域（包括点 B）。
*/
bool operator<=(const SDL_Point & __a, const SDL_Point & __b) {
    return (__a.x <= __b.x) && (__a.y <= __b.y);
}

/**
 * @brief 判断点 A 是否在点 B 的左侧区域（包括点 B）。
*/
bool operator>=(const SDL_Point & __a, const SDL_Point & __b) {
    return (__a.x >= __b.x) && (__a.y >= __b.y);
}

/**
 * @brief 判断点 A 是否在点 B 的左侧区域（不包括点 B）。
*/
bool operator<(const SDL_Point & __a, const SDL_Point & __b) {
    return (__a.x < __b.x) && (__a.y < __b.y);
}

/**
 * @brief 判断点 A 是否在点 B 的左侧区域（不包括点 B）。
*/
bool operator>(const SDL_Point & __a, const SDL_Point & __b) {
    return (__a.x > __b.x) && (__a.y > __b.y);
}

/**
 * @brief 比较两个坐标是否完全相等。
*/
bool operator==(const SDL_FPoint & __a, const SDL_FPoint & __b) {
    return (__a.x == __b.x) && (__a.y == __b.y);
}

/**
 * @brief 比较两个坐标是否完全不相等。
*/
bool operator!=(const SDL_FPoint & __a, const SDL_FPoint & __b) {
    return (__a.x != __b.x) && (__a.y != __b.y);
}

/**
 * @brief 判断点 A 是否在点 B 的左侧区域（包括点 B）。
*/
bool operator<=(const SDL_FPoint & __a, const SDL_FPoint & __b) {
    return (__a.x <= __b.x) && (__a.y <= __b.y);
}

/**
 * @brief 判断点 A 是否在点 B 的左侧区域（包括点 B）。
*/
bool operator>=(const SDL_FPoint & __a, const SDL_FPoint & __b) {
    return (__a.x >= __b.x) && (__a.y >= __b.y);
}

/**
 * @brief 判断点 A 是否在点 B 的左侧区域（不包括点 B）。
*/
bool operator<(const SDL_FPoint & __a, const SDL_FPoint & __b) {
    return (__a.x < __b.x) && (__a.y < __b.y);
}

/**
 * @brief 判断点 A 是否在点 B 的左侧区域（不包括点 B）。
*/
bool operator>(const SDL_FPoint & __a, const SDL_FPoint & __b) {
    return (__a.x > __b.x) && (__a.y > __b.y);
}

#endif // __POINT_COMPARE_H__