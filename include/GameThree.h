
#pragma once

#include "cinder/gl/gl.h"



using glm::vec2;
using std::vector;

namespace gameapp {


    class GameThree {
    public:
        GameThree();


        void Display();


        void AdvanceOneFrame();

        std::string GetBoardImage();

    private:
        std::string board_image_ = "ludo.jpg";


    };

}  // namespace gameapp

