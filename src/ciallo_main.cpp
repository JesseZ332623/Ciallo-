#include "./ciallo~.h"

#ifdef main
#undef main
#endif

int main(int argc, char const *argv[])
{
    CialloAnimation cialloAnimation;

    cialloAnimation.init();
    cialloAnimation.load();

    cialloAnimation.run();

    return EXIT_SUCCESS;
}
