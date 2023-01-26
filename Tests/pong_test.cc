#include <catch2/catch.hpp>
#include <Ball.h>
#include <Racket.h>
#include <GameThree.h>

// basic testing for making sure the ball is bouncing around right


TEST_CASE("Testing check for collision)") {

    SECTION("Colliding horizontally") {

        gameapp::Racket particle1(vec2(790, 400), 0);
        gameapp::Ball particle2(vec2(760, 420), vec2(10, 10));

        REQUIRE(particle1.CheckIfColliding(particle2) == true);
    }SECTION("Colliding with the vertex") {
        gameapp::Racket particle1(vec2(790, 400), 3);
        gameapp::Ball particle2(vec2(780, 320), vec2(2, 3));

        REQUIRE(particle1.CheckIfColliding(particle2) == true);
    }

    SECTION("Colliding vertically") {
        gameapp::Racket particle1(vec2(790, 400), 1);
        gameapp::Ball particle2(vec2(790, 320), vec2(-1, -1));

        REQUIRE(particle1.CheckIfColliding(particle2) == true);
    }

}

TEST_CASE("Testing for when it's not supposed to collide") {
    SECTION("Not Colliding") {

        gameapp::Racket particle1(vec2(790, 400), 0);
        gameapp::Ball particle2(vec2(760, 500), vec2(10, 10));

        REQUIRE(particle1.CheckIfColliding(particle2) == false);

    }

    SECTION("Not colliding with the vertex") {

        gameapp::Racket particle1(vec2(790, 400), 3);
        gameapp::Ball particle2(vec2(759, 320), vec2(0, -1));

        REQUIRE(particle1.CheckIfColliding(particle2) == false);
    }

    SECTION("Not colliding due to direction of velocity") {

        gameapp::Racket particle1(vec2(0, 400), 0);
        gameapp::Ball particle2(vec2(30, 420), vec2(10, 10));

        REQUIRE(particle1.CheckIfColliding(particle2) == false);
    }
}


TEST_CASE("Testing the collision function") {

    SECTION("Colliding horizontally") {

        gameapp::Racket particle1(vec2(790, 400), 0);
        gameapp::Ball particle2(vec2(760, 420), vec2(10, 10));

        particle1.Collide(particle2);

        REQUIRE(particle2.GetVelocity() == vec2(-10, 10.5));
    }SECTION("Colliding with the vertex") {
        gameapp::Racket particle1(vec2(790, 400), 3);
        gameapp::Ball particle2(vec2(780, 320), vec2(2, 3));

        particle1.Collide(particle2);

        REQUIRE(particle2.GetVelocity() == vec2(2, -3));
    }

    SECTION("Colliding vertically") {
        gameapp::Racket particle1(vec2(790, 400), 1);
        gameapp::Ball particle2(vec2(790, 320), vec2(-1, -1));

        particle1.Collide(particle2);

        REQUIRE(particle2.GetVelocity() == vec2(-1, 1));
    }


}

TEST_CASE("Test for wall collision") {

    gameapp::GameThree pong;
    pong.SetPositionAndVelocity(vec2(780, 500), vec2(10, 0));


    SECTION("vertical wall collision") {
        pong.AdvanceOneFrame();
        pong.AdvanceOneFrame();
        REQUIRE(pong.GetBallVelocity() == vec2(-10, 0));

    }

    pong.SetPositionAndVelocity(vec2(500, 780), vec2(0, 8));

    SECTION("horizontal wall collision") {
        pong.AdvanceOneFrame();
        REQUIRE(pong.GetBallVelocity() == vec2(0, -8));

    }

    pong.SetPositionAndVelocity(vec2(780, 780), vec2(8, 8));

    SECTION("corner collision") {
        pong.AdvanceOneFrame();
        REQUIRE(pong.GetBallVelocity() == vec2(-8, -8));

    }
}

