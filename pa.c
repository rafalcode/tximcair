#include <stdlib.h>
#include <math.h>
#include <pango/pangocairo.h>

#define CWID 640
#define CHEI 480

int main (int argc, char **argv)
{
    cairo_surface_t *surf1 = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, CWID, CHEI);
    cairo_t *cr0 = cairo_create(surf1);

    int              w, h;
    cairo_surface_t *surf2 = cairo_image_surface_create_from_png ("bb1.png");
    cairo_pattern_t *pattern;

    w = cairo_image_surface_get_width(surf2);
    h = cairo_image_surface_get_height(surf2);

    pattern = cairo_pattern_create_for_surface(surf2);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_REPEAT);

    cairo_t *cr = cairo_create(surf2);
    cairo_translate (cr, 128.0, 128.0);
    cairo_rotate (cr, M_PI / 4);
    cairo_scale (cr, 1 / sqrt (2), 1 / sqrt (2));
    cairo_translate (cr, -128.0, -128.0);

    cairo_matrix_t   matrix;
    cairo_matrix_init_scale (&matrix, w/256.0 * 5.0, h/256.0 * 5.0);
    cairo_pattern_set_matrix (pattern, &matrix);

    cairo_set_source (cr, pattern);

    cairo_rectangle (cr, 0, 0, 256.0, 256.0);
    cairo_fill (cr);

    cairo_destroy(cr);
    cairo_pattern_destroy (pattern);
    cairo_surface_write_to_png (surf2, "pa.png");
    cairo_surface_destroy (surf2);
    cairo_surface_destroy (surf1);

    return 0;
}
