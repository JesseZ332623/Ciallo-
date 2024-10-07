#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "SDL.h"
#include "SDL_ttf.h"

#include <string>

/**
 * @brief 封装了 SDL 纹理的基类，声明对于纹理的一些通用操作。 
*/
class TextureBasic
{
    public:
        /**
         * @brief 纹理的旋转属性结构体 
        */
        struct FilpAttribution {
            double angle;               // 纹理旋转角度
            SDL_Point center;           // 旋转中心点坐标
            SDL_RendererFlip flipFlag;  // 旋转方向标志位（垂直/水平）

            bool empty(void) {
                return (angle == 0.0) && 
                       ((center.x) == 0 && (center.y == 0)) && (flipFlag == SDL_FLIP_NONE);
            }
        };

    private:
        SDL_Texture * texture;          // SDL 纹理
        SDL_Rect      renderPosition;   // 纹理的原始长宽，以及在屏幕中的渲染位置

    protected:
        /**
         * @brief 设置 SDL 纹理，可以将外部已经初始化好的纹理
        */
        void setTexture(SDL_Texture * __t) {
            this->texture = __t;
        }
    
    public:
        TextureBasic(void) : texture(nullptr), renderPosition({0}) {}

        /**
         * @brief 获取 SDL 纹理。
        */
        SDL_Texture * getTexture(void) const { return this->texture; }

        /**
         * @brief 获取该纹理的原始长宽的副本，以及该纹理渲染在屏幕的位置。
        */
        SDL_Rect getRenderPosition(void) const { return this->renderPosition; }

        /**
         * @brief 获取该纹理的原始长宽的引用，以及该纹理渲染在屏幕的位置。
        */
        SDL_Rect & getRenderPosition(void) { return this->renderPosition; }

        /**
         * @brief 设置纹理的颜色值（RGB）
        */
        void setColor(SDL_Color __color) {
            SDL_SetTextureColorMod(this->getTexture(), __color.r, __color.g, __color.b);
        }

        /**
         * @brief 设置纹理的混合模式。
        */
        void setBlendMode(SDL_BlendMode __blending) {
            SDL_SetTextureBlendMode(this->getTexture(), __blending);
        }

        /**
         * @brief 设置纹理的 Alpha 通道值（透明度 Tansparency）。
        */
        void setAlpha(Uint8 __alpha) { 
            SDL_SetTextureAlphaMod(this->getTexture(), __alpha);
        }

        /**
         * @brief 销毁该纹理，并重置所有数据成员。 
        */
        virtual ~TextureBasic();
};

/**
 * @brief 图片纹理类，用于加载渲染图片纹理。
*/
class TextureImage : public TextureBasic
{
    private:
        std::string textureName;            // 纹理编号
        SDL_Rect    clipPosition;           // 纹理的裁剪范围信息
        FilpAttribution flipAttribution;    // 纹理的旋转属性

        /**
         * @brief 设置纹理名
        */
        void setTextureName(std::string __path);

    public:
        TextureImage(void) : TextureBasic(), textureName(), clipPosition({0}) {}

        /**
         * @brief 获取纹理的裁剪位置和裁剪长宽的副本。
        */
        SDL_Rect getClipPosition(void) const { return this->clipPosition; }

        /**
         * @brief 获取纹理的裁剪位置和裁剪长宽的引用。
        */
        SDL_Rect & getClipPosition(void) { return this->clipPosition; }

        /**
         * @brief 加载一张图片的纹理信息。
         * 
         * @param __path                    图片路径
         * @param __transparentColor        纹理内需要透明化的颜色值
         * @param __ifEnble                 是否启用透明化操作
         * @param __render                  渲染器
         * 
         * @exception 如果在加载过程中出现任何错误，输出错误原因并抛运行时异常。
        */
        void load(std::string __path, SDL_Color __transparentColor, SDL_bool __ifEnble,
                  SDL_Renderer * __render);

        /**
         * @brief 默认的裁剪范围（即整个纹理），调用 render 时可以使用。
        */
        SDL_Rect defaultClip(void) const { 
            return {0, 0, this->getRenderPosition().w, this->getRenderPosition().h}; 
        };

        /**
         * @brief 指定纹理相对于屏幕的渲染平面坐标（x, y）和 裁剪范围，并交由渲染器渲染。
         * 
         * @param __render      渲染器
         * @param __clips       纹理裁剪的位置和长宽（如果不想裁剪，传入 defaultClip() 即可）
         * @param __flip        纹理的旋转信息
        */
        void render(
            int __x, int __y, SDL_Renderer * __render,
            SDL_Rect __clips, FilpAttribution __flip = {0.0, {0, 0}, SDL_FLIP_NONE}
        );

        ~TextureImage() override;
};

/**
 * @brief 矩形纹理类，用于加载和渲染一个矩形纹理 
*/
class RectangleTexture : public TextureBasic
{
    public:
        /**
         * @brief 渲染标志位，表明只渲染矩形边框还是填充整个矩形。 
        */
        enum RenderFlag { BORDER = 0, FILLED, WHOLE };
    private:
        std::string      rectName;      // 矩形纹理编号
        SDL_Color        rectColor;     // 矩形的颜色
        FilpAttribution  rectFlip;      // 矩形的旋转属性

    public:
        RectangleTexture(void) : 
        TextureBasic(), rectName(), rectColor(), rectFlip() {}

        /**
         * @brief 加载一个指定长宽和颜色（RGBA）的矩形 __name。
         * 
         * @param __name    矩形纹理编号
         * @param __w       矩形的宽
         * @param __h       矩形的高
         * @param __color   矩形的颜色值
         * @param __render  渲染器
         * 
         * @exception 如果在加载过程中出现任何错误，输出错误原因并抛运行时异常。
        */
        void load(
            std::string __name, int __w, int __h, SDL_Color __color, SDL_Renderer * __render);

        /**
         * @brief 把加载好的矩形纹理渲染在屏幕的 (__x, __y) 处。
         * 
         * @param __x           直角坐标 x
         * @param __y           直角坐标 y
         * @param __flip        旋转信息
         * @param __render      渲染器
         * @param __renderFlag  渲染标志位
        */
        void render(
            SDL_Renderer * __render, int __x, int __y, RenderFlag __renderFlag, 
            FilpAttribution __flip = {0.0, {0, 0}, SDL_FLIP_NONE}
        );

        ~RectangleTexture() override;
};

class FontsTexture : public TextureBasic
{
    private:
        TTF_Font *      font;                   // 字体资源（TTF_OpenFont() 返回）
        std::string     fontPath;               // 字体文件路径
        std::string     renderContent;          // 要渲染的文本内容
        FilpAttribution flipAttribution;        // 纹理的旋转属性

        /**
         * @brief 打开指定的字体文件，并指定字号。
         * 
         * @param __path        TTF 字库路径
         * @param __fontSize    字体大小
        */
        void openFontFile(std::string & __path, int __fontSize);
    
    public:
        FontsTexture(void) : 
        TextureBasic(), font(nullptr), fontPath(), renderContent(), flipAttribution() {}

        /**
         * @brief 打开指定的字体文件，并指定字号。
         * 
         * @param __path        TTF 字库路径
         * @param __fontSize    字体大小
        */
        void open(std::string __path, int __fontSize);

        /**
         * @brief 传入待渲染的字符串以及字体颜色，获取这个字符串的纹理信息。
         * 
         * @param __textContent     待渲染的字符串
         * @param __textColor       字符串纹理颜色
         * 
         * @exception 如果在加载过程中出现任何错误，输出错误原因并抛运行时异常。
        */
        void load(std::string __textContent, SDL_Color __textColor, SDL_Renderer * __render);

        /**
         * @brief 指定纹理相对于屏幕的渲染平面坐标（x, y）和 裁剪范围，并交由渲染器渲染。
         * 
         * @param __x           直角坐标 x
         * @param __y           直角坐标 y
         * @param __render      渲染器
         * @param __flip        纹理的旋转信息
        */
        void render(
            int __x, int __y, SDL_Renderer * __render, 
            FilpAttribution __flip = {0.0, {0, 0}, SDL_FLIP_NONE}
        );

        ~FontsTexture() override;
};

/**
 * @brief 圆形纹理类，这个类的实现会比较特殊，
 *        不需要依赖 SDL_Texture，而是通过渲染像素点的方式直接绘制出整个圆。
*/
class CircleTexture
{
    public:
        /**
         * @brief 渲染标志位，表明只渲染矩形边框还是整个矩形。 
        */
        enum RenderFlag { BORDER = 0, WHOLE };
        struct CircleInfo {
            int centerX, centerY;   // 圆心坐标
            int radius;             // 圆半径
        };

        /**
         * @brief 判断点 (__x, __y) 是否在这个圆（包括圆上）之内。
         *        方法很简单，求该点与圆形的欧几里得距离 d，
         *        如果大于圆半径就意味着不在圆上。
        */
        static bool isInCircle(int __x, int __y, CircleInfo & __circleInfo);

        /**
         * @brief 显示圆的相关数据（CircleInfo）。
        */
        void showCircleInfo(void);

    private:
        std::string circleName;     // 圆的编号
        CircleInfo  circleInfo;     // 圆的属性

        /**
         * @brief 将圆用 __color 颜色填充。
         * 
         * @param __color    圆的填充颜色。
         * @param __render   完成初始化的 SDL 渲染器。
        */
        void fill(SDL_Color & __color, SDL_Renderer * __render);

        /**
         * @brief 绘制圆的轮廓。
         * 
         * @param __segments 需要在圆上寻找点的数量。
         * @param __color    轮廓的颜色。
         * @param __render  完成初始化的 SDL 渲染器。
        */
        void drawOutline(int __segments, SDL_Color & __color, SDL_Renderer * __render);
    
    public:
        /**
         * @brief 设置该圆的编号和圆的属性。
         * 
         * @param __name        该圆纹理的编号
         * @param __circleInfo  该圆纹理的属性
        */
        void load(const std::string __name, CircleInfo __circleInfo);

        /**
         * @brief 圆形纹理的绘制
         * 
         * @param __segments 需要在圆上寻找点的数量（如果 RenderFlag 为 WHOLE，这个值可以为 0）。
         * @param __color    点的颜色（最后就是圆轮廓的颜色）。
         * @param __render   完成初始化的 SDL 渲染器。
         * @param __renderFlag  渲染标志位
        */
        void render(int __segments, SDL_Color __color, 
                    SDL_Renderer * __render, RenderFlag __renderFlag);

        ~CircleTexture();
};

#endif // __TEXTURE_H__