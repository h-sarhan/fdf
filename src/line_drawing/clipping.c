/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:09:26 by hsarhan           #+#    #+#             */
/*   Updated: 2023/06/20 20:22:39 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
// typedef int outCode;

typedef enum
{
    INSIDE = 0,   // 0000
    LEFT = 1,     // 0001
    RIGHT = 2,    // 0010
    BOTTOM = 4,   // 0100
    TOP = 8,      // 1000
} outCode;

// Compute the bit code for a point (x, y) using the clip rectangle
// bounded diagonally by (0, 0), and (SCREEN_W - 1, SCREEN_H - 1)

// ASSUME THAT SCREEN_W - 1, 0, SCREEN_H - 1 and 0 are global constants.

static outCode compute_out_code(float *x, float *y)
{
    outCode code = INSIDE;   // initialised as being inside of clip window

    if (*x < 0)   // to the left of clip window
        code |= LEFT;
    else if (*x > SCREEN_W - 1)   // to the right of clip window
        code |= RIGHT;
    if (*y > SCREEN_H - 1)   // below the clip window
        code |= BOTTOM;
    else if (*y < 0)   // above the clip window
        code |= TOP;

    return code;
}

// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with
// diagonal from (0, 0) to (SCREEN_W - 1, SCREEN_H - 1).
bool clip_line(float *x0, float *y0, float *x1, float *y1)
{
    // compute outcodes for P0, P1, and whatever point lies outside the clip
    // rectangle
    outCode outcode0 = compute_out_code(x0, y0);
    outCode outcode1 = compute_out_code(x1, y1);
    bool accept = false;

    while (true)
    {
        if (!(outcode0 | outcode1))
        {
            // bitwise OR is 0: both points inside window; trivially accept and
            // exit loop
            accept = true;
            break;
        }
        else if (outcode0 & outcode1)
        {
            // bitwise AND is not 0: both points share an outside zone (LEFT,
            // RIGHT, TOP, or BOTTOM), so both must be outside window; exit loop
            // (accept is false)
            break;
        }
        else
        {
            // failed both tests, so calculate the line segment to clip
            // from an outside point to an intersection with clip edge
            float x, y;

            // At least one endpoint is outside the clip rectangle; pick it.
            outCode outcodeOut = outcode1 > outcode0 ? outcode1 : outcode0;

            // Now find the intersection point;
            // use formulas:
            //   slope = (y1 - y0) / (x1 - x0)
            //   x = x0 + (1 / slope) * (ym - y0), where ym is 0 or SCREEN_H - 1
            //   y = y0 + slope * (xm - x0), where xm is 0 or SCREEN_W - 1
            // No need to worry about divide-by-zero because, in each case, the
            // outcode bit being tested guarantees the denominator is non-zero
            if (outcodeOut & TOP)
            {   // point is above the clip window
                x = *x0 + (*x1 - *x0) * (0 - *y0) / (*y1 - *y0);
                y = 0;
            }
            else if (outcodeOut & BOTTOM)
            {   // point is below the clip window
                x = *x0 + (*x1 - *x0) * (SCREEN_H - 1 - *y0) / (*y1 - *y0);
                y = SCREEN_H - 1;
            }
            else if (outcodeOut & RIGHT)
            {   // point is to the right of clip window
                y = *y0 + (*y1 - *y0) * (SCREEN_W - 1 - *x0) / (*x1 - *x0);
                x = SCREEN_W - 1;
            }
            else if (outcodeOut & LEFT)
            {   // point is to the left of clip window
                y = *y0 + (*y1 - *y0) * (0 - *x0) / (*x1 - *x0);
                x = 0;
            }

            // Now we move outside point to intersection point to clip
            // and get ready for next pass.
            if (outcodeOut == outcode0)
            {
                *x0 = x;
                *y0 = y;
                outcode0 = compute_out_code(x0, y0);
            }
            else
            {
                *x1 = x;
                *y1 = y;
                outcode1 = compute_out_code(x1, y1);
            }
        }
    }
    return accept;
}