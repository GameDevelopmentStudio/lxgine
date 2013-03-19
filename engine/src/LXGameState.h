#ifndef __LXGAMESTATE_H__
#define __LXGAMESTATE_H__

class LXGame;
class LXCamera;

class LXGameState {
 public:    
  // Not owned pointers
  LXGame *game;
  //
  // Owned pointers
  LXCamera *camera;
   
  int width;
  int height;

  LXGameState();
  virtual ~LXGameState();

  virtual void init();

  virtual void render();
  virtual void update();
};

#endif
