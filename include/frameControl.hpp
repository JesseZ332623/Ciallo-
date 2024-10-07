#ifndef __FRAME_CONTROL_H__
#define __FRAME_CONTROL_H__

#include "SDL_stdinc.h"

/**
 * @brief 计算渲染一帧所需的标准时间。
*/
#define STANDING_RENDER_TIME(startTick, fps) (startTick / fps)

/**
 * @brief 维持帧数在一个固定值。
 * 
 * @param __startFrameTick       上一帧渲染的时间
 * @param __frameRenderTime      维持一定帧数渲染一帧所需要的标准时间
 * 
 * @return Uint64 当前渲染的是第几帧
*/
void frameControl(Uint64 & __startFrameTick, const Uint64 __frameRenderTime);

#endif // __FRAME_CONTROL_H__