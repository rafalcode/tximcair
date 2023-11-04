#include <stdlib.h>
#include <math.h>
#include <pango/pangocairo.h>

#define CWID 640
#define CHEI 480
#define RADIUS 100
#define N_WORDS 5
#define FONT "FS Albert Bold 40"

static void drw_my_txt(cairo_t *cr, char *w)
{
    PangoLayout *layout;
    PangoFontDescription *desc;

    /* Center coordinates on the middle of the region we are drawing */
    cairo_translate (cr, CWID/2., CHEI/2.);
    /* Create a PangoLayout, set the font and text */
    layout = pango_cairo_create_layout (cr);

    desc = pango_font_description_from_string(FONT);
    pango_layout_set_font_description (layout, desc);
    pango_font_description_free (desc);

    int width=0, height=0;
    float red;

    pango_layout_set_text (layout, w, -1);
    cairo_save (cr);

    /* Gradient from red at angle == 60 to blue at angle == 240 */
    red   = 0.8;
    // cairo_set_source_rgb (cr, red, 0, 1.0 - red);
    cairo_set_source_rgb (cr, .9, .9, .9);

    pango_cairo_update_layout (cr, layout);

    pango_layout_get_size (layout, &width, &height);
    printf("W:%i H:%i\n", width, height); 

    /// cairo position point:
    // 0,0 is now centre of canvas.
    float crpospt[2]={0,0};
    crpospt[0] = -((float)width / PANGO_SCALE)/2.;
    crpospt[1] = -((float)height / PANGO_SCALE)/2.;
    cairo_move_to (cr, crpospt[0], crpospt[1]);
    printf("cp0:%.2f cp1:%.2f pngsca:%i\n", crpospt[0], crpospt[1], PANGO_SCALE);
    pango_cairo_show_layout (cr, layout);
    cairo_restore (cr);

    /* free the layout object: docs adamant about using g_object_unref */
    g_object_unref(layout);
}

int main (int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: ./pcaim OUTPUT_FILENAME\n");
        exit(EXIT_FAILURE);
    }

    cairo_surface_t *surface4 = cairo_image_surface_create_from_png("bb1.png");
    cairo_pattern_t *pattern4 = cairo_pattern_create_for_surface(surface4);

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, CWID, CHEI);
    cairo_t *cr = cairo_create (surface);
    cairo_set_source(cr, pattern4);
    cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
    cairo_rectangle(cr, 0, 0, CWID, CHEI);
    cairo_fill(cr);
    cairo_rectangle(cr, 0, 0, CWID, CHEI);
    cairo_set_source_rgba (cr, 0, 0.1, 0.05, 0.9);
    cairo_fill(cr);

    char *filename;
    filename = argv[1];

    /* His is our main function */
    /// char *w="2 Copies";
    char *w="nos sobran los motivos";
    // char *w="nos\nsobran\nlos\nmotivos";
    // actually at Albert Bold 40 without newlines, that text fits very well.
    drw_my_txt(cr, w);

    /*  destroying a cairo context causes all the info collected in it to be written onto the surface */
    cairo_destroy(cr);

    cairo_status_t status = cairo_surface_write_to_png (surface, filename);
    cairo_surface_destroy (surface);

    if (status != CAIRO_STATUS_SUCCESS) {
        printf("Cairo seems to have failed '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    return 0;
}
