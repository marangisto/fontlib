////
//
//      Font library for embedded systems
//
////

#pragma once

#include <stdint.h>

namespace fontlib
{

struct glyph_t
{
    uint8_t         width;
    uint8_t         height;
    int8_t          offset_h;
    int8_t          offset_v;
    const uint8_t   *bitmap;
};

struct font_t
{
    uint16_t start_row() const { return -min_y; }
    uint16_t line_spacing() const { return 1 + max_y - min_y; }

    uint8_t         height;
    int8_t          min_y;
    int8_t          max_y;
    char            first;
    char            last;
    const glyph_t   *glyphs;
};

const glyph_t *get_glyph(const font_t& font, char c);

} // fontlib

#include "fontlist.h"

