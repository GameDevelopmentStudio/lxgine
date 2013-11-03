#ifndef __INPUT_H__
#define __INPUT_H__

class Input {
public:
    // Keyboard
    bool *keyStates;
    bool *specialKeyStates;

    Input();
    ~Input();

    void update();

    // Keyboards
    bool keyPressed(unsigned char key);
    bool specialKeyPressed(int key);
};

#endif
