@echo off

REM 源文件路径所在
SET SourceCode="./*.cpp"

REM SDL2 接口路径所在 
SET SDLHeadFile="F:\SDL\SDL2\include"

REM SDL_Image 接口路径所在
SET SDLImageHeadFile="F:\SDL\SDL2_image\include"

REM SDL_TTF 接口路径所在
SET SDLTTFHeadFile="F:\SDL\SDL2_ttf\include"

REM SDL_Mixer 接口路径所在
SET SDL_MixerHeadFile="F:\SDL\SDL2_mixer\include"

REM FMT 日志库的接口路径所在
SET FMTHeadFile="F:\fmt\include\fmt"

REM SDL 的库文件，库名
SET SDL_LibPath="F:\SDL\SDL2\lib\x64"
SET SDL_LibName="SDL2"

REM SDL_Image 的库文件，库名
SET SDLImage_LibPath="F:\SDL\SDL2_image\lib\x64"
SET SDLImage_LibName="SDL2_image"

REM SDL_TTF 的库文件，库名
SET SDLTTF_LibPath="F:\SDL\SDL2_ttf\lib\x64"
SET SDLTTF_LibName="SDL2_ttf"

REM SDL_Mixer 的库文件，库名
SET SDLMixer_LibPath="F:\SDL\SDL2_mixer\lib\x64"
SET SDLMixer_LibName="SDL2_mixer"

REM SDL 开发模板库的路径所在
SET SDLTemplate_LibPath="..\lib"
SET SDLTemplate_LibName="SDLTemplateCode"

REM FMT 日志库的库文件路径所在
SET FMT_LibPath="F:\fmt\lib\libfmtd.a"

REM 可执行文件路径
SET ExecutionFilePath="../bin/Ciallo~.exe"

SET ALL_INCLUDE=-I%SDLHeadFile% -I%SDLImageHeadFile% -I%SDLTTFHeadFile% -I%SDL_MixerHeadFile%
SET ALL_LIB=-L%SDLTemplate_LibPath% -L%SDL_LibPath% -L%SDLImage_LibPath% -L%SDLTTF_LibPath% -L%SDLMixer_LibPath%
SET ALL_LIBNAME=-l%SDLTemplate_LibName% -l%SDL_LibName% -l%SDLImage_LibName% -l%SDLTTF_LibName% -l%SDLMixer_LibName%

g++ %SourceCode% %FMT_LibPath% %ALL_INCLUDE% %ALL_LIB% -o %ExecutionFilePath% -O3 -Wall %ALL_LIBNAME% -std=c++23