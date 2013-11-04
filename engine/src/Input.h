#ifndef __INPUT_H__
#define __INPUT_H__

#define NUM_KEYS 256
#define NUM_SPECIAL_KEYS 246

class Input {
public:
    
    // Keyboard
    unsigned char dirtyKeys[NUM_KEYS];
    int nDirtyKeys;
    int dirtySpecialKeys[NUM_SPECIAL_KEYS];
    int nDirtySpecialKeys;
    
    bool *keyStates;
    bool *specialKeyStates;
    
    bool *prevKeyStates;
    bool *prevSpecialKeyStates;
    bool *currKeyStates;
    bool *currSpecialKeyStates;

    Input();
    ~Input();

    void update();
    void onKeyPressed(unsigned char key);
    void onKeyReleased(unsigned char key);
    void onSpecialKeyPressed(int key);
    void onSpecialKeyReleased(int key);
    
    // Keyboards
    bool keyCheck(unsigned char key);
    bool specialKeyCheck(int key);
    bool keyPressed(unsigned char key);
    bool specialKeyPressed(int key);
    bool keyReleased(unsigned char key);
    bool specialKeyReleased(int key);
};

#endif
