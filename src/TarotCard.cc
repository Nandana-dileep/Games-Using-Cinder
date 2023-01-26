#include "TarotCard.h"
#include "../json.hpp"

namespace gameapp {


    std::string TarotCard::GetName() {
        return name;
    }
}

using nlohmann::json;

namespace gameapp {
    void to_json(json& j, const gameapp::TarotCard& card) {
        j = json{{"name", card.name}};
    }

    void from_json(const json& j, gameapp::TarotCard& p) {
        j.at("name").get_to(p.name);
        j.at("img").get_to(p.img);
        j.at("fortune_telling").get_to(p.fortune_telling);
        j.at("Questions to Ask").get_to(p.questions_to_ask);
        j.at("keywords").get_to(p.keywords);
    }
} // namespace ns


