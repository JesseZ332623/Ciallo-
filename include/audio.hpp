#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "SDL_mixer.h"

#include <string>

/**
 * @brief 常见的音频属性，如下：
 * 
 * @brief         - 采样频率:  44100 Hz
 * @brief         - 处理格式:  PCM 16 位深度
 * @brief         - 声道数:    立体声
 * @brief         - 比特率:    2048 kbps
*/
#define DEAULT_AUDIO_ATTRIBUTION {44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048}

struct AudioAttribution
{
    int     frequency;      // 采样频率（Hz）
    Uint16  format;         // 处理格式
    int     channels;       // 通道数
    int     chunkSize;      // 比特率
};

/**
 * @brief 封装一小部分 SDL_mixer 模块，
 *        用于处理 BGM（Background Music） 的播放。 
*/
class Audio
{
    private:
        Mix_Music *         music;
        AudioAttribution    attribution;
        std::string         audioName;
        double              duration;
        bool                ifPause;

        Audio(void) : 
        music(nullptr), attribution(), audioName(), 
        duration(0.0), ifPause(false) {}

        /**
         * @brief 初始化音频格式，确定音频的属性，
         *        需要传入 AudioAttribution 结构体。
         * 
         * @exception 如果传入格式有误，或其他原因出错，抛运行时异常。
        */
        void init(AudioAttribution & __attr);

// 直接调用 Mix_MusicDuration() 即可拿到音频的时长，就不用下面那么繁琐了。
#if false
        /**
         * @brief 调用 sndfile 库，
         *        读取音频元数据，从而计算音频时长。
         * 
         * @param __path 音频文件路径
        */
        double getAudioDuration(std::string & __path);
#endif

    public:

        /**
         * @brief 构造函数，传入要加载的音频属性，
         *        会在接下来的 init() 函数中进行初始化。
        */
        Audio(AudioAttribution __attr);
        
        /**
         * @brief 初始化音频格式，
         *        确定音频的 AudioAttribution 属性。 
        */
        void init(void);

        /**
         * @brief 加载路径 __path 指定的音频文件。
         * 
         * @param __path 音频路径
         * 
         * @exception 如果出现路径错误，或者音频格式不正确等，抛运行时异常。
        */
        void load(std::string __path);

        /**
         * @brief 播放加载好的音乐。
         * 
         * @param __playOption  播放选项（0 为正常播放，-1 为无限循环）
         * 
         * @exception 如果在尝试播放音乐的情况下出现错误，抛运行时异常。
        */
        void play(int __loops);

        /**
         * @brief 音乐快进指定秒数。
        */
        int fastForward(int __seconds);

        /**
         * @brief 音乐快退指定秒数。
        */
        int fastRewind(int __seconds);

        /**
         * @brief 暂停播放。 
        */
        void pause(void);

        /**
         * @brief 恢复播放。 
        */
        void resume(void);

        /**
         * @brief 立即停止播放所有音乐。
        */
        void stop(void);

        /**
         * @brief 设置音频音量（范围在 0 - 128，否则无效）
        */
        void setVolume(int __volume) {

            if (__volume >= 0 || __volume <= 128) {
                Mix_VolumeMusic(__volume);
            }
        }

        /**
         * @brief 获取加载好的音频资源。
        */
        Mix_Music * getMusicResource(void) const {
            return (!this->music) ? this->music : nullptr;
        }

        /**
         * @brief 获取音频名。
        */
        std::string getMusicName(void) const {
            return this->audioName;
        }

        /**
         * @brief 获取音频的时间长度（单位：秒）
        */
        double getDuration(void) const {
            return this->duration;
        }

        /**
         * @brief 音频是否被暂停
         * 
         * @return 暂停
         * @return 未暂停 
        */
        bool getPlayState(void) const {
            return this->ifPause;
        }

        /**
         * @brief 获取初始化音频时传入的属性（并非加载音频的属性）。
        */
        AudioAttribution getAttribution(void) const {
            return this->attribution;
        }

        /**
         * @brief 清理加载的音频资源。
        */
        ~Audio();
};

/**
 * @brief 封装 Mix_Chunk，用于处理音效。
*/
class SoundEffects
{
    private:
        Mix_Chunk *         soundEffect;
        AudioAttribution    attribution;
        std::string         effectName;

        int playChannel;

        SoundEffects(void) : soundEffect(nullptr), attribution(), effectName(), playChannel(0) {}

        void init(AudioAttribution & __attr);
    public:

        /**
         * @brief 构造函数，传入要加载的音频属性。
        */
        SoundEffects(AudioAttribution __attr);

        /**
         * @brief 初始化音频格式，
         *        确定音频的 AudioAttribution 属性。 
         * 
         * @param __ifInit      如果先前调用了 Audio::init() 这里就填 false
        */
        void init(bool __ifInit);

        /**
         * @brief 加载路径 __path 指定的音效文件。
         * 
         * @param __path 音效路径
         * 
         * @exception 如果出现路径错误，或者音频格式不正确等，抛运行时异常。
        */
        void load(std::string __path);

        /**
         * @brief 播放音效。
        */
        void play(int channel, int __loops);

        /**
         * @brief 停止播放指定频道内的音效。 
        */
        void stop(int __channal) {

            if (Mix_Playing(__channal))
                Mix_HaltChannel(__channal);
        }

        void setVolume(int __volume) {

            if (__volume >= 0 || __volume <= 128) {
                Mix_VolumeChunk(this->soundEffect, __volume);
            }
        }

        /**
         * @brief 清理音效资源。
        */
        ~SoundEffects();
};

#endif // __AUDIO_H__