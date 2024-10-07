#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "SDL_events.h"

#include <unordered_map>
#include <vector>

/**
 * @brief SDL 事件的封装类，
 *        事件操作都可以在这里扩展。
 */
class EventsControl
{
    public:
        /**
         * @brief 该结构体可以记录某个
         *        游戏控制器左右摇杆的实时位置。
        */
        struct RokerPosition 
        {
            int             deviceNo;         // 设备号
            SDL_FPoint      leftRokerPos;
            SDL_FPoint      rightRokerPos;

            std::string show(void) const 
            {   
                using std::to_string;
                return {
                    "Device No. [" + to_string(deviceNo) + "]"
                    " L Roker: (" + to_string(leftRokerPos.x) + ", " + to_string(leftRokerPos.y) + ") "
                    " R Roker: (" + to_string(rightRokerPos.x) + ", " + to_string(rightRokerPos.y) + ") "
                };
            }
        };

        struct TriggerValue
        {
            int  deviceNo;         // 设备号
            int  leftTriggerVal;
            int  rightTriggerVal;

            std::string show(void) const 
            {
                using std::to_string;
                return {
                    "Device No. [" + to_string(deviceNo) + "]"
                    " L Trigger: " + to_string(leftTriggerVal) + 
                    " R Trigger: " + to_string(rightTriggerVal)
                };
            }
        };

        /**
         * @brief 详细记录键盘中某一个键的详细状态，
         *        相比起一个单纯的 bool 类型，能做到更精细的控制。
        */
        struct KeyState 
        {
            bool pressed;       // 是否被按下
            bool released;      // 是否松开
            bool processed;     // 是否接受过相关处理（一般是延时处理）

            Uint64 lastKeyPressTime;    // 该键按下时的时间刻
        };

        struct CurrentWindowSize {
            int width; int height;
            bool ifResize;
        };

        static const int    KeyCount;           // SDL 能记录到的键盘键位总数

        static const float  RokerMotionMax;     // SDL 能记录到的摇杆移动最大值
        static const float  RokerMotionMin;     // SDL 能记录到的摇杆移动最小值

        static const float  TriggerMotionMax;   // SDL 能记录到的板机最大力度值

        /**
         * @brief 一张记录键盘事件的哈希表，
         *        其中 Key 代表某个键对应 SDL 内部的键码，
         *        Value 为布尔类型，表示该键是否被按下。
        */
        typedef std::unordered_map<SDL_Scancode, KeyState> KeyCodeMap;

        /**
         * @brief 一张记录鼠标事件的哈希表，
         *        其中 Key 代表鼠标上某个键对应 SDL 内部的键码，
         *        Value 为布尔类型，表示该键是否被按下。
        */
        typedef std::unordered_map<decltype(SDL_MouseButtonEvent::button), bool> MouseButtonMap;

        /**
         * @brief 哈希表 gameControllers 用于管理多个手柄的连接与断开，
         *        其中 Key 表示的是连接本机的游戏控制器的设备号，
         *        Value 则是指向了一个游戏控制器对象的指针。
        */
        typedef std::unordered_map<int, SDL_GameController *> GameControllerMap;

        /**
         * @brief 动态数组 GameControllersPosition 用于保存
         *        多个游戏控制器左右摇杆的实时位置。
        */
        typedef std::vector<RokerPosition> GameControllerRokersPosition;

        /**
         * @brief 动态数组 GameControllerTriggerValue 用于保存
         *        多个游戏控制器左右板机的实时力度值。
        */
        typedef std::vector<TriggerValue>  GameControllerTriggerValue;

    private:
        SDL_Event           events;             // SDL 事件类

        bool                runState;           // 程序是否运行标志位

        KeyCodeMap          keyboardState;      // 键盘按键事件管理

        MouseButtonMap      mouseButtonState;   // 鼠标按键事件管理

        bool                mouseMotionState;   // 鼠标的运动状态

        SDL_Point           mousePosition;      // 记录在某一帧下鼠标位于窗口的坐标。

        GameControllerMap            gameControllers;      // 游戏控制器资源管理

        GameControllerRokersPosition rokersPosition;       // 游戏控制器左右摇杆记录

        GameControllerTriggerValue   triggerValue;         // 游戏控制器左右板机记录

        CurrentWindowSize            windowResize;       // 检查窗口尺寸是否变化

        /**
         * @brief 当键盘的某一个键按下时要做的操作。 
        */
        void keyPress(void);

        /**
         * @brief 当键盘的某一个键回弹时要做的操作。 
        */
        void keyRelease(void);

        /**
         * @brief 当鼠标的某一个键按下时要做的操作。 
        */
        void mouseButtonPress(void);

        /**
         * @brief 当鼠标的某一个键松开时要做的操作。 
        */
        void mouseButtonRelease(void);

        /**
         * @brief 当鼠标在移动时要做的操作。
        */
        void mouseMotion(void);

        /**
         * @brief 每隔一小段时间检查鼠标的位置，由此判断鼠标是否停止。
         * 
         * @param __interval 每隔多少毫秒检测一次（默认 100 毫秒）
         * @param __times    检测次数（默认 3 次）
         * 
         * @return true  鼠标已静止
         * @return false 鼠标在移动
        */
        bool isMouseMotionless(const Uint32 __interval = 100, int __times = 3);

        /**
         * @brief 有些时候断开手柄并不能触发 SDL_CONTROLLERDEVICEREMOVED 信号，
         *        所以需要一个函数来手动检测控制器连接状态，以正确处理相关资源。
        */
        //void checkControllerStatus(void);

        /**
         * @brief 当某一个游戏控制器连接要做的操作。
        */
        void gameControllerAdded(void);

        /**
         * @brief 当某一个游戏控制器断开要做的操作。
        */
        void gameControllerMoved(void);

        /**
         * @brief 处理游戏控制器左右摇杆的运动。
        */
        void processGameControllerRokerMotion(void);

        /**
         * @brief 处理游戏控制器左右板机的运动。
        */
        void processGameControllerTriggerMotion(void);
    
    public:
        EventsControl(void) : 
        events(), runState(false), keyboardState(), 
        mouseButtonState(), mouseMotionState(false), mousePosition(),
        gameControllers(), rokersPosition(), windowResize({0, 0, false}) {}

        /**
         * @brief 获取程序的运行状态，确定合适的时机来退出程序。
         * 
         * @return true     收到退出信号
         * @return false    未收到退出信号
        */
        bool getRunstate(void) const { 
            return this->runState; 
        }

        /**
         * @brief 获取当前键盘键位的状态。
        */
        KeyCodeMap & getKeyboardState(void) { 
            return this->keyboardState; 
        };

        /**
         * @brief 获取当前鼠标键位的状态。
        */
        const MouseButtonMap & getMouseState(void) const { 
            return this->mouseButtonState; 
        }

        /**
         * @brief 获取鼠标的运动状态
         * 
         * @return true  鼠标已静止
         * @return false 鼠标在移动
        */
        bool getMouseMotionState(void) const {
            return this->mouseMotionState;
        }

        /**
         * @brief 获取当前的鼠标位置。
        */
        const SDL_Point getMousePosition(void) const { 
            return this->mousePosition; 
        }

        /**
         * @brief 获取事件控制类所管理的所有游戏控制器资源。
        */
        GameControllerMap & getGameContorller(void) {
            return this->gameControllers;
        }

        /**
         * @brief 获取所有连接系统的游戏控制器的左右摇杆位置。
        */
        const GameControllerRokersPosition & getRockersPosition(void) const {
            return this->rokersPosition;
        }

        /**
         * @brief 获取所有连接系统的游戏控制器的左右板机力度。
        */
        const GameControllerTriggerValue & getTriggerValue(void) const {
            return this->triggerValue;
        }

        /**
         * @brief 获取变化后的窗口尺寸。
        */
        CurrentWindowSize & getWindowSizeState(void) {
            return this->windowResize;
        }

        /**
         * @brief 事件记录，
         *        调用 SDL_PollEvent() 探测事件并改变相应的标志位。
        */
        void recordEvents(void);

        /**
         * @brief 类析构的时候需要检查 GameControllerMap 内是否还有成员，
         *        如果有，需要处理掉避免泄漏。
        */
        ~EventsControl();
};

#endif // __EVENTS_H__