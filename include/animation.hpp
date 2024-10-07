#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>
#include <string>

#include "SDL_image.h"

class GIFAnimation 
{
    public:
        enum FrameOption { ALL_FRAMES = 0 };
    private:
        /**
         * @brief GIF 文件的路径所在。
        */
        std::string animationPath;

        /**
         * @brief SDL 支持 GIF 动画的加载与渲染，
         *        IMG_Animation 结构体保存了 GIF 动画每一帧的尺寸，平面信息，
         *        帧数，和延迟时间信息。
        */
        IMG_Animation * animation;

        /**
         * @brief IMG_Animation 内部的图片平面形象要被转化成纹理后存储在该链表中，
         *        使用链表可以快速的抽帧或插帧。
        */
        std::vector<SDL_Texture *> animationTextures;

    public:
        GIFAnimation(void) : animationPath(), animation(nullptr), animationTextures() {}

        /**
         * @brief 获取动画文件路径。
        */
        std::string getAnimationPath(void) const {
            return this->animationPath;
        }

        /**
         * @brief 获取加载好的 GIF 动画资源。
        */
        IMG_Animation * getAnimationInfo(void) const {
            return this->animation;
        }

        /**
         * @brief 获取加载好的所有 GIF 动画帧纹理的只读引用。
        */
        const std::vector<SDL_Texture *> & getAnimationTextures(void) const {
            return this->animationTextures;
        }

        /**
         * @brief 抽取 GIF 动画的第 __frameIndex 帧，
         *       帧计数从 1 开始。
        */
        void frameExtraction(int __frameIndex);

        /**
         * @brief 在 GIF 动画的第 __frameIndex 帧之前插入一帧。
         * 
         * @brief - 虽然接口内有检查，不过最好还是让 __frameTexure 有效。
        */
        void frameInsert(int __frameIndex, SDL_Texture * __frameTexure);

        /**
         * @brief 设置某一帧纹理的颜色值（RGB），帧计数从 1 开始。
         *        若 __frameIndex 为 ALL_FRAMES，则把所有帧颜色都设置成 __color。
        */
        void setFrameColor(int __frameIndex, SDL_Color __color);

        /**
         * @brief 设置某一帧纹理的透明度，帧计数从 1 开始。
         *        若 __frameIndex 为 ALL_FRAMES，则把所有帧透明度都设置成 __alpha。
        */
        void setFrameAlpha(int __frameIndex, Uint8 __alpha);

        /**
         * @brief 设置某一帧纹理的混合模式，帧计数从 1 开始。
         *        若 __frameIndex 为 ALL_FRAMES，则把所有帧混合模式都设置成 __blending。
        */
        void setBlendMode(int __frameIndex, SDL_BlendMode __blending);

        /**
         * @brief 加载指定的 GIF 文件。
        */
        void load(std::string __path, SDL_Renderer * __render);

/**
 * @brief GIF 动画的播放需要在外部程序主循环中实现，
 *        此处不声明与实现。
*/
#if false
        void play(void);
#endif

        /**
         * @brief 析构函数，销毁相关 GIF 动画资源。 
        */
        ~GIFAnimation();
};

#endif // __ANIMATION_H__