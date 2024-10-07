#ifndef __SYSTEM_INIT_H__
#define __SYSTEM_INIT_H__

#include "SDL.h"

#include <string>

/**
 * @brief 初始化类，该类封装了程序所有的初始化操作。 
*/
class SystemInit
{
    public:
        struct WindowSize {int w; int h;};

    private:

        SDL_Window   * mainWindow;  // 窗口
        WindowSize     windowSize;  // 窗口尺寸
        std::string    windowName;  // 窗口名

        SDL_Renderer * render;  // 渲染器

        /**
         * 所有游戏控制器对象存于此处（不要这样做）
         * 处理多个控制器的连接和断开会稍显复杂（毕竟在游戏中断开手柄连接是常有的事情），
         * 所以，把 SDL_GameController 资源以及行为的管理全权交给事件管理类（EventsControl）去做才是正确的策略。
        */
        //std::vector<SDL_GameController *> gameControllers;

        /**
         * @brief SDL 主模块初始化。
        */
        void SDLMainInit(void);

        /**
         * @brief SDL 音频模块初始化。
        */
        void SDLMixerInit(void);

        /**
         * @brief 游戏控制器子系统的初始化。
        */
        void gameControllerInit(void);

        /**
         * @brief 创建窗口。
        */
        void createWindow(void);

        /**
         * @brief 创建渲染器。
        */
        void createRenderer(void);

        /**
         * @brief SDL Image 模块初始化。 
        */
        void SDLImageInit(void);

        /**
         * @brief SDL TTF 字体渲染模块初始化。 
        */
        void SDLTTFInit(void);

    public:
        /**
         * @brief 构造函数，初始化窗口和渲染器指针，
         *        但需要在 init() 方法中指定窗口名和窗口的长宽参数。
        */
        SystemInit(void) : mainWindow(nullptr), render(nullptr) {}

        /**
         * @brief 构造函数，初始化窗口和渲染器指针，并设置窗口大小和窗口名。
         *        后续调用无参的 init() 方法即可。
         * 
         * @param __windowSize      窗口长宽
         * @param __windowName      窗口名
        */
        SystemInit(WindowSize __windowSize, std::string __windowName = "Unknow Name");

        /**
         * @brief 系统所有组件的初始化，按顺序分别是：
         * @brief - SDL 主模块
         * @brief - SDL 游戏控制器子系统
         * @brief - 主窗口
         * @brief - 基于窗口的渲染器
         * @brief - SDL image 模块
         * @brief - SDL TTF 模块
         * 
         * @param __windowSize      窗口尺寸
         * @param __windowName      窗口名
        */
        void init(WindowSize __windowSize, std::string __windowName);

        /**
         * @brief 系统所有组件的初始化，按顺序分别是：
         * @brief - SDL 主模块
         * @brief - SDL 游戏控制器子系统
         * @brief - 主窗口
         * @brief - 基于窗口的渲染器
         * @brief - SDL image 模块
         * @brief - SDL TTF 模块
        */
        void init(void) { 
            this->init(this->windowSize, this->windowName); 
        }

        /**
         * @brief 获取窗口类。
        */
        SDL_Window * getWindow(void) const { 
            return this->mainWindow; 
        }

        /**
         * @brief 获取窗口名。
        */
        std::string getWindowName(void) const { 
            return this->windowName; 
        };

        /**
         * @brief 获取窗口大小。
        */
        WindowSize getWindowSize(void) const { 
            return this->windowSize; 
        }

        /**
         * @brief 获取渲染器类。
        */
        SDL_Renderer * getRenderer(void) const { 
            return this->render; 
        }

        /**
         * @brief 析构函数，销毁窗口与渲染器，
         *        以及所有的 SDL 资源。
        */
        ~SystemInit();
};

#endif // __SYSTEM_INIT_H__