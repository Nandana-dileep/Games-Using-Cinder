#pragma once

#include "cinder/gl/gl.h"
#include "cinder/audio/SamplePlayerNode.h"
#include "cinder/audio/Node.h"
#include "cinder/audio/Voice.h"



using glm::vec2;
using std::vector;

namespace gameapp {


class GameOne {
 public:
  GameOne();

  void Display();

  void AdvanceOneFrame();

  std::string GetBoardImage();

  vec2 GetPlayerPosTop();

  vec2 GetPlayerPosBottom();

  bool CheckToRollDice();

private:

    std::string board_image_ = "snake.jpg";

    vec2 player_pos_top = vec2(0, 720);

    vec2 player_pos_bottom = vec2(80, 800);

    int count_for_move = 0;

    bool to_roll_dice = false;

    int RollDice();
};

}  // namespace gameapp
