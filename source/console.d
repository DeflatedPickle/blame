import std.stdio;
import core.sys.posix.sys.ioctl;

import widget;

class Console : Widget {
    auto running = false;

    char[][] raw_grid;
    char[][] screen_grid;

    char[] draw_buffer;

    this() {
        auto size = winsize();

        ioctl(1, TIOCGWINSZ, &size);
        this.view_area.width = size.ws_col;
        this.view_area.height = size.ws_row;

        foreach (y; 0..this.view_area.height) {
            char[] row;
            foreach (x; 0..this.view_area.width) {
                row ~= char.init;
            }
            // TODO: Could be a loop
            raw_grid ~= row;
            screen_grid ~= row;
        }
    }

    void mainLoop() {
        this.running = true;

        while (this.running) {
            if (this.redraw) {
                this.draw();
            }
        }
    }

    override void quit() {
        foreach (w; this.children) {
            w.quit();
        }
    }

    override void draw() {
        super.draw();

        foreach (w; this.children) {
            w.draw();
        }

        foreach (y; 0..this.raw_grid.length) {
            foreach (x; 0..this.raw_grid[y].length) {
                if (x == this.raw_grid[y].length) {
                    if (y != this.raw_grid.length) {
                        this.draw_buffer ~= "\n";
                    }
                }

                if (this.raw_grid[y][x] == char.init) {
                    this.draw_buffer ~= '░';
                }

                if (this.raw_grid[y][x] != this.screen_grid[y][x]) {
                    this.screen_grid[y][x] = this.raw_grid[y][x];
                }

                this.draw_buffer ~= this.screen_grid[y][x];
            }
        }

        writeln(this.draw_buffer);
    }
}

void main() {
    import label;

    auto console = new Console();
    auto labelw = new Label(console, console, "Label");
    labelw.place(4, 4, 8, 1);
    console.mainLoop();
}
