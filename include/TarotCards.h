#include <string>
#include <array>
#include "TarotCard.h"

namespace gameapp {


    class TarotCards {

    public:
        std::array<TarotCard, 78> GetArray();
        std::string GetDescription();

        std::array<TarotCard, 78> cards = {};
        std::string description = "what";

    };

    void from_json(const nlohmann::json& j, gameapp::TarotCards& p);
}

