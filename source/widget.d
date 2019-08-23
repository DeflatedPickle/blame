import console;
import area;

abstract class Widget {
    Console console;
    Widget parent;
    Widget[] children;

    auto redraw = true;

    auto client_area = Area(0, 0, 0, 0);
    auto view_area = Area(0, 0, 0, 0);

    void quit() {
    }

    void draw() {
        this.redraw = false;
    }

    void place(int x, int y, int width, int height) {
        this.client_area.x = x;
        this.client_area.y = y;
        this.client_area.width = width;
        this.client_area.height = height;
    }
}
