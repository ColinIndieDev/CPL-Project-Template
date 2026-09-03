#define CPL_IMPL
#include <cpl/cpl.h>

int main() {
    window_init(800, 600, "Hello from CPL", OPENGL_3_3);

    font_t font;
    font_load(&font, "assets/fonts/font.ttf", NULL, FILTER_LINEAR);

    while (!window_should_close()) {
        update();

        clear_background(BLACK);

        begin_draw(SHAPE_2D_UNLIT, false);
        draw_rect(VEC2F(0, 0), VEC2F(100, 100), RED, NO_ROTATION);

        begin_draw(TEXT, false);
        draw_text(&font, VEC2F(get_screen_width() / 2.0f,get_screen_height() / 2.0f), 1.0f, WHITE, "This is a text");

        end_frame();
    }
    window_close();
}
