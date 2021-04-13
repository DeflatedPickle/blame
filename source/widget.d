import console;
import area;

abstract class Widget {
    Console console;
    Widget parent;
    Widget[] children;

    auto redraw = true;

    auto client_area = Area(0, 0, 0, 0);
    auto view_area = Area(0, 0, 0, 0);

    this() {
    }

    this(Console console, Widget parent) {
        this.console = console;
        this.parent = parent;

        this.parent.children ~= this;
    }

    void quit() {
    }

    void activate() {
    }

    void draw() {
        this.redraw = false;

        foreach (y; 0..this.client_area.height) {
            foreach (x; 0..this.client_area.width) {
                this.console.raw_grid[this.client_area.y + y][this.client_area.x + x] = ' ';
            }
        }
    }

    void place(int x, int y, int width, int height) {
        this.client_area.x = x;
        this.client_area.y = y;
        this.client_area.width = width;
        this.client_area.height = height;
    }
}
