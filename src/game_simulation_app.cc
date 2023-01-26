#include "game_simulation_app.h"
#include "ciAnimatedGif.h"
#include "GameOne.h"
#include "cinder/audio/SamplePlayerNode.h"
#include "cinder/audio/Node.h"
#include "cinder/audio/Voice.h"


namespace gameapp {

GameApp::GameApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void GameApp::draw() {

    if (picked_game != -1) {
        starting = false;
    }
    if (starting) {
        mGif2->draw(ci::Rectf (vec2(0,0),
                              ci::app::getWindowSize()));
        DisplayGameOptions();
    } else if (picked_game == 2){
        texture = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset(game_two.GetBoardImage())));
        ci::gl::draw(texture, ci::Rectf (vec2(0,0),
                                         ci::app::getWindowSize()));
        mGif->draw(ci::Rectf (vec2(0,0),
                              ci::app::getWindowSize()));

        game_two.Display();
    } else if (picked_game == 0) {
        texture = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset(game_one_.GetBoardImage())));
        ci::gl::draw(texture, ci::Rectf (vec2(0,0),
                                         ci::app::getWindowSize()));

        ci::gl::draw(red_player, ci::Rectf (game_one_.GetPlayerPosTop(),
                                            game_one_.GetPlayerPosBottom()));

        if (game_one_.CheckToRollDice()) {
            dice_gif->draw(vec2(ci::app::getWindowCenter().x/4, ci::app::getWindowCenter().y/4));
            roll_dice++;
        }

        game_one_.Display();
    }


}

void GameApp::update() {
    if (picked_game == 0) {
        game_one_.AdvanceOneFrame();
    } else if (picked_game == 1) {
        game_two.AdvanceOneFrame();
    }

}

void GameApp::keyDown(cinder::app::KeyEvent event) {
   if (starting) {
       switch (event.getCode()) {

           case ci::app::KeyEvent::KEY_DOWN:
               picked_game_temp_++;
               if (picked_game_temp_ > 2) {
                   picked_game_temp_--;
               }
               break;
           case ci::app::KeyEvent::KEY_UP:
               picked_game_temp_--;
               if (picked_game_temp_ < 0) {
                   picked_game_temp_++;
               }
               break;

           case ci::app::KeyEvent::KEY_RETURN:
               picked_game = picked_game_temp_;
               break;
       }
   } else {
       game_two.keyDown(event);
   }


}

void GameApp::setup() {

    game_two.setup();

    ci::audio::SourceFileRef sourceFile = ci::audio::load( ci::app::loadAsset( "summer.wav" ) );
    mVoice = ci::audio::Voice::create( sourceFile );


    // Start playing audio from the voice:
    mVoice->start();
}

void GameApp::DisplayGameOptions() {


    cinder::gl::color( ci::Color( ci::Color( "white")));

    ci::gl::drawStringCentered(
            "Pick one",
            glm::vec2(cinder::app::getWindowSize().x / 2, cinder::app::getWindowSize().y / 20),
            ci::Color("white"),ci::Font("Zapfino", 50));

    if (picked_game_temp_ == 0) {
        cinder::gl::drawStrokedRect( ci::Rectf(vec2(cinder::app::getWindowSize().x / 10, cinder::app::getWindowSize().y / 5),
                                             vec2(cinder::app::getWindowSize().x / 1.2, cinder::app::getWindowSize().y / 2.5)), 6);

    }


    cinder::gl::color( ci::Color( ci::Color( "pink")));
    cinder::gl::drawSolidRect( ci::Rectf(vec2(cinder::app::getWindowSize().x / 10, cinder::app::getWindowSize().y / 5),
                                         vec2(cinder::app::getWindowSize().x / 1.2, cinder::app::getWindowSize().y / 2.5)));

    ci::gl::drawStringCentered(
            "Snakes and Ladders",
            glm::vec2(cinder::app::getWindowSize().x / 2, cinder::app::getWindowSize().y / 3.33),
            ci::Color("black"),ci::Font("Courier", 35));

    if (picked_game_temp_ == 1) {
        cinder::gl::color( ci::Color( ci::Color( "white")));
        cinder::gl::drawStrokedRect( ci::Rectf(vec2(cinder::app::getWindowSize().x / 10, cinder::app::getWindowSize().y / 2),
                                               vec2(cinder::app::getWindowSize().x / 1.2, cinder::app::getWindowSize().y / 1.5)), 6);
    }


    cinder::gl::color( ci::Color( ci::Color( 0.9, 0.5, 0.34)));


    cinder::gl::drawSolidRect( ci::Rectf(vec2(cinder::app::getWindowSize().x / 10, cinder::app::getWindowSize().y / 2),
                                         vec2(cinder::app::getWindowSize().x / 1.2, cinder::app::getWindowSize().y / 1.5)));

    ci::gl::drawStringCentered(
            "Ludo",
            glm::vec2(cinder::app::getWindowSize().x / 2.2, cinder::app::getWindowSize().y / 1.7),
            ci::Color("black"),ci::Font("Courier", 35));


    if (picked_game_temp_ == 2) {
        cinder::gl::color( ci::Color( ci::Color( "white")));
        cinder::gl::drawStrokedRect( ci::Rectf(vec2(cinder::app::getWindowSize().x / 10, cinder::app::getWindowSize().y / 1.32),
                                               vec2(cinder::app::getWindowSize().x / 1.2, cinder::app::getWindowSize().y / 1.07)), 6);
    }

    cinder::gl::color( ci::Color( ci::Color( 0.7, 0.8, 0.98)));


    cinder::gl::drawSolidRect( ci::Rectf(vec2(cinder::app::getWindowSize().x / 10, cinder::app::getWindowSize().y / 1.32),
                                         vec2(cinder::app::getWindowSize().x / 1.2, cinder::app::getWindowSize().y / 1.07)));

    ci::gl::drawStringCentered(
            "Tarot reading",
            glm::vec2(cinder::app::getWindowSize().x / 2.2, cinder::app::getWindowSize().y / 1.2),
            ci::Color("black"),ci::Font("Courier", 35));

}


}  // namespace gameapp
