#pragma once

/* A superclass representing a widget that can be assigned a scroll bar;
 * so far, the List and Text widgets support this, but the general
 * conditions are to contain a vector (`items`) that the user scrolls 
 * through and a way to respond to arrow key presses in a given
 * Direction (`move`).
 *
 * This class was added in an effort to fix scroll functionality.
 */

#include <widgets/Widget.hpp>

namespace Blame::Widgets {
    
    class Scrollable : public Blame::Widgets::Widget {
        
        public:
            Scrollable(Blame::Console *console, Blame::Widgets::Widget *parent);
            virtual ~Scrollable();
            
            /* TODO consider changing this... a MOVE on a Scrollable
             * widget is not quite the same as a MOVE on a Scroll button itself. */
            virtual void move(Blame::Util::Direction direction) = 0;
            virtual void redraw() = 0;
            virtual void activate() = 0;

            const std::vector<std::string> &getContent() {
                return content;
            }
            
            void addItem(std::string nextItem) {
                content.push_back(nextItem);
            }

            void setContent(const std::vector<std::string> &nextVector) {
                content = nextVector;
            }
        
        protected:
            /* A list of strings:
             * One string corresponds to one element of the Scrollable 
             * structure. This could be a filename, or a line in a file.
             * ...or perhaps in a future edition, an entire widget? */
            std::vector<std::string> content;
        
    };
}

