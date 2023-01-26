#include "GameTwo.h"
#include "game_simulation_app.h"

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"


#include "cinder/Rand.h"

#include "../json.hpp"

// for convenience
using json = nlohmann::json;
namespace gameapp {

    using glm::vec2;
    using std::vector;


    GameTwo::GameTwo() = default;


    void GameTwo::Display() {
        if (before_picking_cards_) {
            BeforePickingCards();
            BeginningInstructions();
        }

        if (picked_out_cards.size() == 1) {
            DisplayFirstCard();
        } else if (picked_out_cards.size() == 2) {
            DisplayFirstCard();
            DisplaySecondCard();
        } else if (picked_out_cards.size() == 3) {
            DisplayFirstCard();
            DisplaySecondCard();
            DisplayThirdCard();
        } else if (picked_out_cards.size() > 3) {
            done_choosing_ = true;
            ci::gl::clear();
            DisplayInfoForCard(displaying_card);
        }

    }

    void GameTwo::AdvanceOneFrame() {
        if (picked_out_cards.size() > 3) {
            done_choosing_ = true;
        }

    }

    std::string GameTwo::GetBoardImage() {
        return board_image_;
    }

    void GameTwo::BeforePickingCards() {


        float radius = (float) cinder::app::getWindowHeight() / 2 - 70;

        // preserve the default Model matrix
        ci::gl::pushModelMatrix();
        // move to the window center
        ci::gl::translate(cinder::app::getWindowCenter());

        // to display the cards in a semi-circle arrangement
        for (int c = 0; c < numCircles; ++c) {
            if (c == cards_displayed_count_ / 100 && c >= numCircles / 2) {
                float rel = c / (float) numCircles;
                float angle = rel * M_PI * 2;
                vec2 offset(cos(angle), sin(angle));

                // preserve the Model matrix
                cinder::gl::pushModelMatrix();
                // move to the correct position
                cinder::gl::translate(offset * radius);
                // set the color using HSV color
                ci::gl::draw(texture, ci::Rectf(
                        vec2(-cinder::app::getWindowSize().x / 16.66, -cinder::app::getWindowSize().y / 20),
                        vec2(cinder::app::getWindowSize().x / 16.66, cinder::app::getWindowSize().y / 7.14)));

                cinder::gl::color(ci::Color(0.1, 0.2, 0.3));
                cinder::gl::drawStrokedRect(
                        ci::Rectf(vec2(-cinder::app::getWindowSize().x / 16.66, -cinder::app::getWindowSize().y / 20),
                                  vec2(cinder::app::getWindowSize().x / 16.66, cinder::app::getWindowSize().y / 7.14)));
                // restore the Model matrix
                cinder::gl::popModelMatrix();
                cinder::gl::color(ci::Color("white"));

            } else if (cards_displayed_count_ > c * 100 && c > numCircles / 2) {
                should_cut_off = false;

                for (int card_number : picked_out_cards) {
                    if (c == card_number) {
                        should_cut_off = true;
                    }
                }
                if (should_cut_off) {
                    continue;
                }

                float rel = c / (float) numCircles;
                float angle = rel * M_PI * 2;
                vec2 offset(cos(angle), sin(angle));

                // preserve the Model matrix
                cinder::gl::pushModelMatrix();
                // move to the correct position
                cinder::gl::translate(offset * radius);
                // set the color using HSV color
                cinder::gl::color(ci::Color(ci::CM_HSV, rel, 0.3, 0.7));
                // draw a circle relative to Model matrix
                cinder::gl::drawSolidRect(
                        ci::Rectf(vec2(-cinder::app::getWindowSize().x / 16.66, -cinder::app::getWindowSize().y / 20),
                                  vec2(cinder::app::getWindowSize().x / 16.66, cinder::app::getWindowSize().y / 7.14)));


                ci::gl::draw(texture, ci::Rectf(
                        vec2(-cinder::app::getWindowSize().x / 16.66, -cinder::app::getWindowSize().y / 20),
                        vec2(cinder::app::getWindowSize().x / 16.66, cinder::app::getWindowSize().y / 7.14)));

                if (c == picked_card) {
                    cinder::gl::color(ci::Color(ci::Color("gold")));
                } else {
                    cinder::gl::color(ci::Color(ci::Color(0.1, 0.2, 0.3)));
                }


                cinder::gl::drawStrokedRect(
                        ci::Rectf(vec2(-cinder::app::getWindowSize().x / 16.66, -cinder::app::getWindowSize().y / 20),
                                  vec2(cinder::app::getWindowSize().x / 16.66, cinder::app::getWindowSize().y / 7.14)));
                // restore the Model matrix
                cinder::gl::popModelMatrix();
                cinder::gl::color(ci::Color("white"));
            }
            cards_displayed_count_++;
        }
        ci::gl::popModelMatrix();
    }

    void GameTwo::BeginningInstructions() {

        ci::gl::drawStringCentered(
                "Pick three cards.",
                glm::vec2(cinder::app::getWindowSize().x / 2, cinder::app::getWindowSize().y / 2),
                ci::Color(0.4, 0.3, 0.1), ci::Font("Courier", 35));

    }

    void GameTwo::keyDown(ci::app::KeyEvent event) {

        switch (event.getCode()) {

            case ci::app::KeyEvent::KEY_RIGHT:
                if (done_choosing_) {
                    displaying_card++;
                    if (displaying_card == number_of_required_cards_) {
                        displaying_card--;
                    }
                } else {
                    picked_card++;
                    for (int card_number : picked_out_cards) {
                        if (picked_card == card_number) {
                            picked_card++;
                        }
                    }
                    if (picked_card > 156) {
                        picked_card = 156;
                    }
                }

                break;

            case ci::app::KeyEvent::KEY_LEFT:
                if (done_choosing_) {
                    displaying_card--;
                    if (displaying_card == -1) {
                        displaying_card++;
                    }
                } else {
                    picked_card--;
                    for (int card_number : picked_out_cards) {

                        if (picked_card == card_number) {
                            picked_card--;
                        }
                    }

                    if (picked_card <= 78) {
                        picked_card = 79;
                    }
                }

                break;

            case ci::app::KeyEvent::KEY_RETURN:
                picked_out_cards.push_back(picked_card);
                picked_card--;

                for (int card_number : picked_out_cards) {
                    if (picked_card == card_number) {
                        picked_card--;
                    }
                }

                numCircles -= 2;
                break;
        }
    }

    void GameTwo::setup() {
        texture = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset("tarot_card_back.jpg")));
        std::ifstream file(
                "/Users/nandanadileep/Downloads/Cinder/my_projects/final-project-Nandana-dileep/Resources/tarot-images.json");
        json j = json::parse(file);
        TarotCards t = j.get<TarotCards>();


        cards_ = t.cards;

        srand((unsigned int) time(NULL));

        for (size_t i = 0; i < number_of_required_cards_; i++) {
            random.push_back(rand() % 77);
        }


    }

    void GameTwo::DisplayFirstCard() {

        ci::gl::Texture2dRef texture2 = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset(cards_[random[0]].img)));
        ci::gl::draw(texture2,
                     ci::Rectf(vec2(cinder::app::getWindowSize().x / 16.66, cinder::app::getWindowSize().y / 1.55),
                               vec2(cinder::app::getWindowSize().x / 3.3, cinder::app::getWindowSize().y)));
    }

    void GameTwo::DisplaySecondCard() {

        ci::gl::Texture2dRef texture2 = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset(cards_[random[1]].img)));
        ci::gl::draw(texture2,
                     ci::Rectf(vec2(cinder::app::getWindowSize().x / 2.8, cinder::app::getWindowSize().y / 1.55),
                               vec2(cinder::app::getWindowSize().x / 1.64, cinder::app::getWindowSize().y)));
    }

    void GameTwo::DisplayThirdCard() {

        ci::gl::Texture2dRef texture2 = ci::gl::Texture2d::create(loadImage(ci::app::loadAsset(cards_[random[2]].img)));
        ci::gl::draw(texture2,
                     ci::Rectf(vec2(cinder::app::getWindowSize().x / 1.5, cinder::app::getWindowSize().y / 1.55),
                               vec2(cinder::app::getWindowSize().x / 1.1, cinder::app::getWindowSize().y)));
    }

    void GameTwo::DisplayInfoForCard(int card_number) {

        texture3 = ci::gl::Texture2d::create(ci::loadImage(ci::app::loadAsset("t4.jpg")));

        ci::gl::draw(texture3, ci::Rectf(vec2(0, 0),
                                         ci::app::getWindowSize()));

        ci::gl::Texture2dRef texture2 = ci::gl::Texture2d::create(
                loadImage(ci::app::loadAsset(cards_[random[card_number]].img)));
        ci::gl::draw(texture2, ci::Rectf(vec2(cinder::app::getWindowSize().x / 30, cinder::app::getWindowSize().y / 4),
                                         vec2(cinder::app::getWindowSize().x / 2.5,
                                              cinder::app::getWindowSize().y / 1.18)));


        ci::gl::drawStringCentered(
                cards_[random[card_number]].GetName(),
                glm::vec2(cinder::app::getWindowSize().x / 2, cinder::app::getWindowSize().y / 11), ci::Color("white"),
                ci::Font("Courier", 35));
        int count = 1;
        for (std::string question : cards_[random[card_number]].questions_to_ask) {
            ci::gl::drawStringCentered(
                    question,
                    glm::vec2(cinder::app::getWindowSize().x / 2, cinder::app::getWindowSize().y / 1.17 + count * 23),
                    ci::Color("white"), ci::Font("Helvetica", 15));
            count++;
        }
        count = 1;
        for (std::string question : cards_[random[card_number]].fortune_telling) {
            ci::gl::drawStringCentered(
                    question,
                    glm::vec2(cinder::app::getWindowSize().x / 2, cinder::app::getWindowSize().y / 10 + 23 * count),
                    ci::Color("white"), ci::Font("Helvetica", 15));
            count++;
        }
        count = 1;
        for (std::string question : cards_[random[card_number]].keywords) {
            ci::gl::drawStringCentered(
                    question,
                    glm::vec2(cinder::app::getWindowSize().x / 1.33, cinder::app::getWindowSize().y / 18 + 23 * count),
                    ci::Color("white"), ci::Font("Helvetica", 15));
            count++;
        }


    }

}  // namespace gameapp

