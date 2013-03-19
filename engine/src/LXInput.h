#ifndef __LXINPUT_H__
#define __LXINPUT_H__

class LXInput {
 public:
  // Keyboard
  bool *keyStates;
  bool *specialKeyStates;

  LXInput();
  ~LXInput();

  void update();

  // Keyboards
  bool keyPressed(unsigned char key);
  bool specialKeyPressed(int key);
};

#endif
