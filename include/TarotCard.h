#include <string>
#include "../json.hpp"

namespace gameapp {

    class TarotCard {

    public:
        std::string GetName();
        std::string name;
        std::string number;
        std::string img;
        //std::string fortune_telling;

        std::vector<std::string> questions_to_ask = {};
        std::vector<std::string> fortune_telling = {};
        std::vector<std::string> keywords = {};


    };

    void from_json(const nlohmann::json& j, gameapp::TarotCard& p);
}

