#define CPL_IMPL
#include <cpl/cpl.h>

int main() {
    window_init(800, 800, "Hello world", OPENGL_3_3);
    while (!window_should_close()) {
        update();
        clear_background(RED);
        end_frame();
    }
    window_close();
}
