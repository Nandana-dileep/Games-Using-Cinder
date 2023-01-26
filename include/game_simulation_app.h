#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "GameOne.h"
#include "GameTwo.h"
#include "../../../../../../../Library/Developer/CommandLineTools/usr/include/c++/v1/memory"
#include "ciAnimatedGif.h"


namespace gameapp {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
    class GameApp : public ci::app::App {
    public:
        GameApp();

        void draw() override;
        void update() override;
        void setup() override;

        int kWindowSize = 800;

        void keyDown(cinder::app::KeyEvent event) override;



    private:
        int roll_dice = 0;

        GameTwo game_two;

        GameOne game_one_;

        ci::gl::Texture2dRef texture = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("s.jpeg")));

        cinder::ciAnimatedGifRef  mGif = cinder::ciAnimatedGif::create( loadAsset("t8.gif") );

        ci::gl::Texture2dRef red_player = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("blue_player.png")));

        cinder::ciAnimatedGifRef  mGif2 = cinder::ciAnimatedGif::create( loadAsset("t2.gif") );

        cinder::ciAnimatedGifRef  dice_gif = cinder::ciAnimatedGif::create( loadAsset("dice.gif") );

        bool starting = true;

        int picked_game_temp_ = 0;

        int picked_game = -1;

        void DisplayGameOptions();

        ci::audio::VoiceRef mVoice;
    };

}
