#include "elements.h"
#include <assets_icons.h>
#include <gui/icon_i.h>
#include <m-string.h>
#include <furi.h>
#include "canvas_i.h"
#include <string.h>

void elements_scrollbar(Canvas* canvas, uint8_t pos, uint8_t total) {
    furi_assert(canvas);

    uint8_t width = canvas_width(canvas);
    uint8_t height = canvas_height(canvas);
    // prevent overflows
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_box(canvas, width - 3, 0, 3, height);
    // dot line
    canvas_set_color(canvas, ColorBlack);
    for(uint8_t i = 0; i < height; i += 2) {
        canvas_draw_dot(canvas, width - 2, i);
    }
    // Position block
    if(total) {
        uint8_t block_h = ((float)height) / total;
        canvas_draw_box(canvas, width - 3, block_h * pos, 3, block_h);
    }
}

void elements_frame(Canvas* canvas, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    furi_assert(canvas);

    canvas_draw_line(canvas, x + 2, y, x + width - 2, y);
    canvas_draw_line(canvas, x + 1, y + height - 1, x + width, y + height - 1);
    canvas_draw_line(canvas, x + 2, y + height, x + width - 1, y + height);

    canvas_draw_line(canvas, x, y + 2, x, y + height - 2);
    canvas_draw_line(canvas, x + width - 1, y + 1, x + width - 1, y + height - 2);
    canvas_draw_line(canvas, x + width, y + 2, x + width, y + height - 2);

    canvas_draw_dot(canvas, x + 1, y + 1);
}

void elements_button_left(Canvas* canvas, const char* str) {
    const uint8_t button_height = 13;
    const uint8_t vertical_offset = 3;
    const uint8_t horizontal_offset = 3;
    const uint8_t string_width = canvas_string_width(canvas, str);
    const IconData* icon = assets_icons_get_data(I_ButtonLeft_4x7);
    const uint8_t icon_offset = 6;
    const uint8_t icon_width_with_offset = icon->width + icon_offset;
    const uint8_t button_width = string_width + horizontal_offset * 2 + icon_width_with_offset;

    const uint8_t x = 0;
    const uint8_t y = canvas_height(canvas);

    canvas_draw_box(canvas, x, y - button_height, button_width, button_height);
    canvas_draw_line(canvas, x + button_width + 0, y, x + button_width + 0, y - button_height + 0);
    canvas_draw_line(canvas, x + button_width + 1, y, x + button_width + 1, y - button_height + 1);
    canvas_draw_line(canvas, x + button_width + 2, y, x + button_width + 2, y - button_height + 2);

    canvas_invert_color(canvas);
    canvas_draw_icon_name(
        canvas, x + horizontal_offset, y - button_height + vertical_offset, I_ButtonLeft_4x7);
    canvas_draw_str(
        canvas, x + horizontal_offset + icon_width_with_offset, y - vertical_offset, str);
    canvas_invert_color(canvas);
}

void elements_button_right(Canvas* canvas, const char* str) {
    const uint8_t button_height = 13;
    const uint8_t vertical_offset = 3;
    const uint8_t horizontal_offset = 3;
    const uint8_t string_width = canvas_string_width(canvas, str);
    const IconData* icon = assets_icons_get_data(I_ButtonRight_4x7);
    const uint8_t icon_offset = 6;
    const uint8_t icon_width_with_offset = icon->width + icon_offset;
    const uint8_t button_width = string_width + horizontal_offset * 2 + icon_width_with_offset;

    const uint8_t x = canvas_width(canvas);
    const uint8_t y = canvas_height(canvas);

    canvas_draw_box(canvas, x - button_width, y - button_height, button_width, button_height);
    canvas_draw_line(canvas, x - button_width - 1, y, x - button_width - 1, y - button_height + 0);
    canvas_draw_line(canvas, x - button_width - 2, y, x - button_width - 2, y - button_height + 1);
    canvas_draw_line(canvas, x - button_width - 3, y, x - button_width - 3, y - button_height + 2);

    canvas_invert_color(canvas);
    canvas_draw_str(canvas, x - button_width + horizontal_offset, y - vertical_offset, str);
    canvas_draw_icon_name(
        canvas,
        x - horizontal_offset - icon->width,
        y - button_height + vertical_offset,
        I_ButtonRight_4x7);
    canvas_invert_color(canvas);
}

void elements_button_center(Canvas* canvas, const char* str) {
    const uint8_t button_height = 13;
    const uint8_t vertical_offset = 3;
    const uint8_t horizontal_offset = 3;
    const uint8_t string_width = canvas_string_width(canvas, str);
    const IconData* icon = assets_icons_get_data(I_ButtonCenter_7x7);
    const uint8_t icon_offset = 6;
    const uint8_t icon_width_with_offset = icon->width + icon_offset;
    const uint8_t button_width = string_width + horizontal_offset * 2 + icon_width_with_offset;

    const uint8_t x = (canvas_width(canvas) - button_width) / 2;
    const uint8_t y = canvas_height(canvas);

    canvas_draw_box(canvas, x, y - button_height, button_width, button_height);

    canvas_draw_line(canvas, x - 1, y, x - 1, y - button_height + 0);
    canvas_draw_line(canvas, x - 2, y, x - 2, y - button_height + 1);
    canvas_draw_line(canvas, x - 3, y, x - 3, y - button_height + 2);

    canvas_draw_line(canvas, x + button_width + 0, y, x + button_width + 0, y - button_height + 0);
    canvas_draw_line(canvas, x + button_width + 1, y, x + button_width + 1, y - button_height + 1);
    canvas_draw_line(canvas, x + button_width + 2, y, x + button_width + 2, y - button_height + 2);

    canvas_invert_color(canvas);
    canvas_draw_icon_name(
        canvas, x + horizontal_offset, y - button_height + vertical_offset, I_ButtonCenter_7x7);
    canvas_draw_str(
        canvas, x + horizontal_offset + icon_width_with_offset, y - vertical_offset, str);
    canvas_invert_color(canvas);
}

void elements_multiline_text_aligned(
    Canvas* canvas,
    uint8_t x,
    uint8_t y,
    Align horizontal,
    Align vertical,
    const char* text) {
    furi_assert(canvas);
    furi_assert(text);

    uint8_t font_height = canvas_current_font_height(canvas);
    string_t str;
    string_init(str);
    const char* start = text;
    char* end;

    // get lines count
    uint8_t i, lines_count;
    for(i = 0, lines_count = 0; text[i]; i++) lines_count += (text[i] == '\n');

    switch(vertical) {
    case AlignBottom:
        y -= font_height * lines_count;
        break;
    case AlignCenter:
        y -= (font_height * lines_count) / 2;
        break;
    case AlignTop:
    default:
        break;
    }

    do {
        end = strchr(start, '\n');
        if(end) {
            string_set_strn(str, start, end - start);
        } else {
            string_set_str(str, start);
        }
        canvas_draw_str_aligned(canvas, x, y, horizontal, vertical, string_get_cstr(str));
        start = end + 1;
        y += font_height;
    } while(end);
    string_clear(str);
}

void elements_multiline_text(Canvas* canvas, uint8_t x, uint8_t y, char* text) {
    furi_assert(canvas);
    furi_assert(text);

    uint8_t font_height = canvas_current_font_height(canvas);
    string_t str;
    string_init(str);
    char* start = text;
    char* end;
    do {
        end = strchr(start, '\n');
        if(end) {
            string_set_strn(str, start, end - start);
        } else {
            string_set_str(str, start);
        }
        canvas_draw_str(canvas, x, y, string_get_cstr(str));
        start = end + 1;
        y += font_height;
    } while(end);
    string_clear(str);
}