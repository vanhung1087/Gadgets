/*
 * Copyright © 2007 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Author: Behdad Esfahbod <behdad@behdad.org>
 */

#include <math.h>
#include "cairo-test.h"
#include <stdio.h>

#define SIZE 200

static cairo_test_draw_function_t draw;

static const cairo_test_t test = {
    "surface-pattern-scale-down",
    "Test scaled-down transformed not-repeated surface patterns"
    "\nFails xlib backend (with argb32) with inexplicable alpha in result",
    SIZE, SIZE,
    draw
};

static cairo_test_status_t
draw (cairo_t *cr, int width, int height)
{
    cairo_surface_t *surface;
    cairo_t * cr_surface;
    int surface_size = 300;

    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_paint (cr);

    /* Create an image surface with my favorite four colors in each
     * quadrant. */
    surface = cairo_image_surface_create (CAIRO_FORMAT_RGB24,
					  surface_size, surface_size);
    cr_surface = cairo_create (surface);
    cairo_set_source_rgb (cr_surface, 1, 1, 1);
    cairo_rectangle (cr_surface,
		     0, 0,
		     surface_size / 2, surface_size / 2);
    cairo_fill (cr_surface);
    cairo_set_source_rgb (cr_surface, 1, 0, 0);
    cairo_rectangle (cr_surface,
		     surface_size / 2, 0,
		     surface_size / 2, surface_size / 2);
    cairo_fill (cr_surface);
    cairo_set_source_rgb (cr_surface, 0, 1, 0);
    cairo_rectangle (cr_surface,
		     0, surface_size / 2,
		     surface_size / 2, surface_size / 2);
    cairo_fill (cr_surface);
    cairo_set_source_rgb (cr_surface, 0, 0, 1);
    cairo_rectangle (cr_surface,
		     surface_size / 2, surface_size / 2,
		     surface_size / 2, surface_size / 2);
    cairo_fill (cr_surface);
    cairo_destroy (cr_surface);

    cairo_scale (cr, 0.2, 0.2);
    cairo_rotate (cr, 1.);
    cairo_set_source_surface (cr, surface, 225, -225);
    cairo_surface_destroy (surface);

    cairo_pattern_set_extend (cairo_get_source (cr), CAIRO_EXTEND_NONE);
    cairo_paint (cr);

    return CAIRO_TEST_SUCCESS;
}

int
main (void)
{
    return cairo_test (&test);
}
