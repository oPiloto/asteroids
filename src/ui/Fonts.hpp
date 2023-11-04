#pragma once

#include "fonts/Fonts.hpp"
#include "includes.hpp"

namespace aste {
    class Fonts {
    public:
        static const sf::Font &MartianMono() {
            static sf::Font font;
            if (!font.loadFromMemory(font_MartianMono, font_MartianMono_len))
                throw std::runtime_error("Error loading MartianMono font.");
            return font;
        }

        static const sf::Font &Exo2() {
            static sf::Font font;
            if (!font.loadFromMemory(font_Exo2_ExtraBoldItalic, font_Exo2_ExtraBoldItalic_len))
                throw std::runtime_error("Error loading Exo2 font.");
            return font;
        }
    };
} // namespace aste
