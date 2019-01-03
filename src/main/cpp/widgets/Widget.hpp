#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <sstream>
#include "../Console.hpp"
#include "Listener.hpp"
#include "../util/EscapeCodes.hpp"
#include "../util/State.hpp"
#include "../styles/Style.hpp"
#include "managers/Manager.hpp"
#include "managers/Pack.hpp"

// TODO: Add checks for if the widget is focused or disabled
namespace Blame::Widgets {
    class Widget : public Blame::Widgets::Listener {
    public:
        Widget(Blame::Console *console, Blame::Widgets::Widget *parent);

        virtual void redraw();

        void quit() override {}

        void focus() override {
            this->console->focused_widget = this;
            this->state = Blame::Util::State::FOCUSED;

            this->console->redraw();
        }

        void unfocus() override {
            this->state = Blame::Util::State::NORMAL;
            this->console->redraw();

        }

        void move(Blame::Util::Direction direction) override {
            this->console->redraw();
        }
        void activate() override {
            this->state = Blame::Util::State::ACTIVE;
            this->console->redraw();
        }

        void text(std::string text) override {
            this->console->redraw();
        }

        std::string getCurrentColour(Blame::Styles::StateColours stateColours) {
            switch (this->state) {
                case Blame::Util::State::NORMAL:
                    return stateColours.normal;

                case Blame::Util::State::FOCUSED:
                    return stateColours.focused;

                case Blame::Util::State::ACTIVE:
                    return stateColours.active;

                case Blame::Util::State::DISABLED:
                    return stateColours.disabled;
            }
        }

        void place(int x, int y, int width, int height) {
            this->column = x;
            this->row = y;
            this->width = width;
            this->height = height;

            this->updateClientArea();
        }
        // void placeRemove();

        void pack(Blame::Util::Direction direction) {
            if (this->parent->manager == nullptr) {
                this->updateClientArea();

                this->parent->manager = new Blame::Widgets::Managers::Pack();
                auto manager = static_cast<Blame::Widgets::Managers::Pack *>(this->parent->manager);
                manager->direction = direction;
                manager->next_x = this->parent->client_area.left;
                manager->next_y = this->parent->client_area.top;

                this->parent->manager = manager;
            }

            auto manager = static_cast<Blame::Widgets::Managers::Pack *>(this->parent->manager);
            manager->widgets.push_back(this);

            this->column = manager->next_x;
            this->row = manager->next_y;

            switch (direction) {
                case Blame::Util::Direction::LEFT:
                    manager->next_x += this->width + 2;
                    break;

                case Blame::Util::Direction::DOWN:
                    manager->next_y += this->height;
                    break;
            }

            manager->direction = direction;

            this->parent->manager = manager;
        }
        // void packRemove();

        // void grid(int row, int column);
        // void gridRemove();

        virtual void updateClientArea() {
            this->client_area.left = this->column + 1;
            this->client_area.right = this->column - 1 + this->width;
            this->client_area.top = this->row + 1;
            this->client_area.bottom = this->row - 1 + this->height;
        }

        int column;
        int row;
        int width;
        int height;

        Blame::Util::ClientArea client_area;

        bool resizable;

        std::ostringstream widget_stream;

        std::atomic_bool is_redrawn;

        Blame::Widgets::Managers::Manager *manager;
        std::vector<Blame::Widgets::Widget *> children;

    protected:
        Blame::Console *console;
        Blame::Widgets::Widget *parent;

        // int padding_top;
        // int padding_left;
        // int padding_right;
        // int padding_bottom;

        // int internal_padding_top;
        // int internal_padding_left;
        // int internal_padding_right;
        // int internal_padding_bottom;

        Blame::Styles::Style *style;
    };
}