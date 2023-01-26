#include "GameOne.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"


#include "cinder/Rand.h"

namespace gameapp {

    using glm::vec2;
    using std::vector;


    GameOne::GameOne() = default;


    void GameOne::Display() {
        ci::gl::color(ci::Color("white"));



    }

    void GameOne::AdvanceOneFrame() {
        count_for_move++;

        if (count_for_move == 100) {
            int dice_roll = RollDice();
            player_pos_top.x += 80 * dice_roll;
            player_pos_bottom.x += 80 * dice_roll;
            to_roll_dice = true;
        }

        if (count_for_move > 50 && count_for_move < 100) {
            to_roll_dice = true;
        }

        if (count_for_move == 100) {
            to_roll_dice = false;
            count_for_move = 0;
        }


    }

    int GameOne::RollDice() {
        int dice_roll;
        int min = 1;
        int max = 6;

        dice_roll = (int) random() % (max) + min;
        return dice_roll;
    }

    std::string GameOne::GetBoardImage() {
        return board_image_;
    }

    vec2 GameOne::GetPlayerPosTop() {
        return player_pos_top;
    }

    vec2 GameOne::GetPlayerPosBottom() {
        return player_pos_bottom;
    }

    bool GameOne::CheckToRollDice() {
        return to_roll_dice;
    }
}  // namespace gameapp


