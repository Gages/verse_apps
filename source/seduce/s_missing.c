#include "seduce.h"

float sui_text_line_length(float size, float spacing, const char* text, int param)
{
     return sui_compute_text_length(size, spacing, text);
}

void sui_text_screen_mode_update()
{
}

void sui_draw_gl_rgb(uint draw_type, const float *array, uint length, uint dimensions, float red, float green, float blue)
{
     sui_draw_gl(draw_type, array, length, dimensions, red, green, blue, 1.0f);
}

boolean sui_type_number_uint_rgba(BInputState *input, float pos_x, float pos_y, float center, float length, float size, uint32 *number, void *id, float red, float green, float blue, float ignored) {
    sui_type_number_uint(input, pos_x, pos_y, center, length, size, number, id, red, green, blue);
}
