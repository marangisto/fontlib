#include <fontlib.h>

namespace fontlib
{

const glyph_t *get_glyph(const font_t& font, char c)
{
    if (c >= font.first && c <= font.last)
        return &font.glyphs[c - font.first];
    else
        return 0;   // FIXME: add box glyph
}

} // fontlib
