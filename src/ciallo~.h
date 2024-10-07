#ifndef __TIMING_H__
#define __TIMING_H__

#include "../include/SDLTemplate.hpp"

#include <random>

#define SCREEN_WIDTH   1600     // 初始窗口宽  
#define SCREEN_HEIGHT  1000     // 初始窗口高

#define FPS            165      // Frame Per Second

/**
 * @brief 弹幕类 
*/
class Danmaku
{
    private:
        TextureImage            cialloImage;

        SDL_Color               color;
        Uint32                  moveSpeed;
        SDL_Point               renderPos;
    
    public:
        Danmaku(void) : 
        color(), moveSpeed(0), renderPos() {}

        /**
         * @brief 判断当前弹幕是否完全超过了窗口的左边界。
        */
        bool isOffsetScreem(void) const {
            return (this->renderPos.x < -this->cialloImage.getRenderPosition().w);
        }

        /**
         * @brief 更新弹幕位置（当前是从窗口右边向左移动）。 
        */
        void update(void) {
            this->renderPos.x -= this->moveSpeed;
        }

        /**
         * @brief 弹幕纹理以及相关属性的加载，由 DanmakuManager 类内部调用。
         * 
         * @param __path                图片路径
         * @param __speed               纹理移动速度
         * @param __renderPos           纹理的初始渲染位置（后续调用 update() 方法不断变动）
         * @param __color               纹理颜色
         * @param __currentWindowSize   当前窗口尺寸（来自 CialloAnimation::windowSize 的引用）
         * @param __render              渲染器            
        */
        void load(
            std::string __path, 
            int __speed, SDL_Point __renderPos, SDL_Color __color,
            SystemInit::WindowSize & __currentWindowSize, SDL_Renderer * __render
        );

        /**
         * @brief 渲染该弹幕。
         * 
         * @param __render 渲染器
        */
        void render(SDL_Renderer * __render);
};

/**
 * @brief 弹幕管理类，管理弹幕的创建于销毁。
*/
class DanmakuManager
{
    private:
        std::vector<Danmaku *>      danmakus;               // 使用动态数组存储弹幕类
        SystemInit::WindowSize &    currentWindowSize;      // 当前的窗口尺寸（来自 CialloAnimation::windowSize 的引用）

        std::random_device          randomDevice;           // 真随机数源
        std::mt19937                randomEngine;           // 随机数生成引擎（这里使用 Mersenne Twister 法）

        std::uniform_int_distribution<int>     speedDistrbution;    // 速度值随机数分配器
        std::uniform_int_distribution<Uint8>   colorDistribution;   // 颜色值随机数分配器

        /**
         * @brief 弹幕 Y 轴生成位置的边界随窗口的高变化而变化，
         *        所以这里要用指针，配合 setposYDistributionBound() 方法随时替换。
        */
        std::uniform_int_distribution<int> *   posYDistribution;

    public:
        DanmakuManager(SystemInit::WindowSize & __w) : currentWindowSize(__w), randomEngine(randomDevice()),
        speedDistrbution(3, 6), colorDistribution(1, 0xFF), 
        posYDistribution(new std::uniform_int_distribution<int>(0, currentWindowSize.h)) {}

        /**
         * @brief 获取当前的弹幕数量。
        */
        std::size_t getDanmakusAmount(void) const {
            return this->danmakus.size();
        }

        /**
         * @brief 获取随机数生成引擎（可以传给别的类用）
        */
        std::mt19937 & getRandomEngine(void) {
            return this->randomEngine;
        }

        /**
         * @brief 窗口尺寸发生变化时要重设 posYDistribution 的分配范围。
        */
        void setposYDistributionBound(void) {
            delete this->posYDistribution;
            this->posYDistribution = new std::uniform_int_distribution<int>(0, currentWindowSize.h);
        }

        /**
         * @brief 创建一个新弹幕。
         * 
         * @param __render 渲染器
        */
        void add(SDL_Renderer * __render);

        /**
         * @brief 更新当前所有弹幕的位置信息。
        */
        void update(void);

        /**
         * @brief 渲染所有弹幕。
         * 
         * @param __render 渲染器
        */
        void render(SDL_Renderer * __render);

        /**
         * @brief 程序结束时销毁还在 danmakus 内的弹幕资源。
        */
        ~DanmakuManager();
};

class CialloAnimation
{   
    public:
        struct TimePiece { Uint64 lastTime; Uint64 currentTime; };
    
    private:
        SystemInit::WindowSize  windowSize;
        SystemInit              sysInit;
        EventsControl           events;

        GIFAnimation            cialloAnimation;        // Ciallo~ GIF 动画
        SDL_Rect                animationRenderRect;    // 动画渲染信息
        Uint8                   currentFrame;           // 当前渲染应该渲染的帧计数

        /**
         * @brief 该纹理的渲染由鼠标事件触发，渲染位置随鼠标移动。
         */
        TextureImage            cialloImage;
        SDL_Point               cialloImageRenderPos;
        bool                    ifCialloImageRender;
        int                     cialloImageAlpha;

        /**
         * @brief 弹幕的资源管理与生成。
        */
        DanmakuManager                      danmakuManager;
        std::uniform_int_distribution<int>  danmakuGenerate;
        
        FontsTexture            clickCountShown;
        Uint32                  clickCount;

        /**
         * @brief 音效的播放由鼠标左键触发，
         *        可以设置一个计时器 playTimePiece 进行延迟避免频繁触发。
        */
        SoundEffects            soundEffects;
        TimePiece               playTimePiece;

        Uint64                  startTime;
        Uint64                  renderTime;
        int                     mainLoopCount;

        /**
         * @brief GIF 动画的播放。 
        */
        void playGIFAnimation(void);

        /**
         * @brief GIF 动画的播放控制。
        */
        void GIFAnimationFrameControl(void);

        /**
         * @brief Ciallo~ 图片纹理经鼠标事件触发后的播放逻辑。
        */
        void playCialloImage(void);

        /**
         * @brief 对于鼠标按键按下时要做的操作。 
        */
        void mouseEventBehavior(void);

        /**
         * @brief 对于键盘按键按下时要做的操作。 
        */
        void keyboradEventsBehavior(void);

        /**
         * @brief 窗口尺寸变化后，计算新的 GIF 动画渲染中心点。
        */
        void getCurrentCenterPos(void);

        /**
         * @brief 弹幕的生成逻辑。 
        */
        void danmakuGenerater(void);

        /**
         * @brief 当窗口尺寸变动时要做的操作。
        */
        void windowResizeBehavior(void);

        /**
         * @brief 低帧率的 GIF 动画在高帧率的播放逻辑。
        */
        void playGIFInHighFrame(void);

        /**
         * @brief 点击分数的更新与渲染。 
        */
        void scoreLoadAndRender(void);

        public:
            CialloAnimation(void) : windowSize({SCREEN_WIDTH, SCREEN_HEIGHT}), sysInit(windowSize, "Ciallo~"), 
            currentFrame(0), ifCialloImageRender(false), cialloImageAlpha(0xFF), 
            danmakuManager(windowSize), danmakuGenerate(0, 10),
            clickCount(0), soundEffects(DEAULT_AUDIO_ATTRIBUTION), mainLoopCount(0) {}

            void init(void);    

            void load(void);

            void run(void);
};

#endif // __TIMING_H__