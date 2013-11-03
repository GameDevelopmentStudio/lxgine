#ifndef __DERAI_H__
#define __DERAI_H__

#include "Game.h"

class Derai : public Game {
public:
    Derai();
    ~Derai();

    void initSettings();

    void init(int argc, char **argv);
};

#endif
