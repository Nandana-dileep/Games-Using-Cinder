#include "TarotCards.h"
namespace gameapp {

    std::array<TarotCard, 78> TarotCards::GetArray() {
        return cards;
    }

    std::string TarotCards::GetDescription() {
        return description;
    }
}
using nlohmann::json;

namespace gameapp {
    void to_json(json& j, const gameapp::TarotCards& card) {
        j = json{{"description", card.description}};
    }

    void from_json(const json& j, gameapp::TarotCards& p) {
        j.at("cards").get_to(p.cards);

    }
}
