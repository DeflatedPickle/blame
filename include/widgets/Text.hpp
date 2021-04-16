#pragma once

#include <widgets/Widget.hpp>
#include <widgets/Scrollable.hpp>

namespace Blame::Widgets {
    class Text : public Blame::Widgets::Scrollable {
        public:
            Text(Blame::Console *console, Blame::Widgets::Widget *parent);
    
            void redraw() override;
    
            void move(Blame::Util::Direction direction) override;
            void activate() override {}
            void text(std::string text) override;
    
            int caret_x;
            int caret_y;
    
        protected:
    
            std::string symbol_caret;
            std::string colour_caret;
    
    };
}

