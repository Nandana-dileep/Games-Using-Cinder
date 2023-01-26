
#pragma once

#include <cinder/app/KeyEvent.h>
#include "cinder/gl/gl.h"

#include "cinder/gl/Texture.h"

#include "ciAnimatedGif.h"

#include "TarotCards.h"

#include "cinder/Rand.h"



using glm::vec2;
using std::vector;

namespace gameapp {

    class GameTwo {
    public:

        GameTwo();

        void Display();

        void AdvanceOneFrame();

        std::string GetBoardImage();

        void BeforePickingCards();

        void BeginningInstructions();

        void keyDown(cinder::app::KeyEvent event);

        void setup();


    private:

        std::string board_image_ = "t4.jpg";

        bool before_picking_cards_ = true;

        int picked_card = 79;

        int cards_displayed_count_ = 0;

        std::vector<int> picked_out_cards = {};

        cinder::ciAnimatedGifRef  mGif = cinder::ciAnimatedGif::create( ci::app::loadAsset("t.gif") );

        ci::gl::Texture2dRef texture;
        ci::gl::Texture2dRef texture3;

        bool should_cut_off = false;

        int numCircles = 156;

        TarotCards cards;

        std::vector<int> random;

        int number_of_required_cards_ = 3;

        bool done_choosing_ = false;

        int displaying_card = 0;




        std::array<TarotCard, 78> cards_;

        void DisplayFirstCard();

        void DisplaySecondCard();

        void DisplayCard(int card_number);

        void DisplayThirdCard();

        void DisplayInfoForCard(int card_number);
    };

}  // namespace gameapp
