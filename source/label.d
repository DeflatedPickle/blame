import std.stdio;

import widget;
import console;

class Label : Widget {
    string text;

    this(Console console, Widget parent, string text) {
        super(console, parent);

        this.text = text;
    }

    override void draw() {
        super.draw();

        while (this.text.length < this.client_area.width) {
            this.text ~= ' ';
        }

        foreach (y; 0..this.client_area.height) {
            foreach (x; 0..this.client_area.width) {
                this.console.raw_grid[this.client_area.y][this.client_area.x + x] = this.text[x];
            }
        }
    }
}
