/* I amke a nice pattern here
 * I take 4 squares of those storage box canvas and set it as a pattern so I can extend it. Luckly there are greo black
 * and repeat them as a pattern, then I overlay a color rectangle with opacity over it, so I can colour it anyway I want
*/
#include <pango/pangocairo.h>

#define IMWIDTH 800
#define IMHEIGHT 600
#define DM 2

int main (int argc, char *argv[])
{
    // cairo_surface_t *surface4 = cairo_image_surface_create_from_png("ch2.png");
    cairo_surface_t *surface4 = cairo_image_surface_create_from_png("bb1.png");

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, IMWIDTH, IMHEIGHT);
    cairo_t *cr = cairo_create (surface);

    cairo_pattern_t *pattern4 = cairo_pattern_create_for_surface(surface4);

    cairo_set_source(cr, pattern4);
    cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
    // cairo_scale (cr, 1/4., 1/4.); //disna werk
    // // cairo_rectangle(cr, 150, 140, 200, 200);
    cairo_rectangle(cr, 0, 0, IMWIDTH, IMHEIGHT);
    cairo_fill(cr);
    cairo_rectangle(cr, 0, 0, IMWIDTH, IMHEIGHT);
    cairo_set_source_rgba (cr, 0, 0.1, 0.05, 0.9);
    cairo_fill(cr);

    cairo_pattern_destroy(pattern4);

    cairo_destroy(cr);

    cairo_surface_destroy(surface4);
    cairo_surface_write_to_png (surface, "pat.png");
    cairo_surface_destroy (surface);

    return 0;
}
