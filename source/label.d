import std.stdio;

import widget;
import console;

class Label : Widget {
    string text;

    this(Console console, Widget parent, string text) {
        this.console = console;
        this.parent = parent;

        this.parent.children ~= this;

        this.text = text;
    }

    override void draw() {
        super.draw();

        foreach (x; 0..this.text.length) {
            this.console.raw_grid[this.client_area.y][this.client_area.x + x] = this.text[x];
        }
    }
}
