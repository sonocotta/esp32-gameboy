extern "C"
{
#include <nes/nes.h>
}

#include "hw_config.h"

#include <Arduino_GFX_Library.h>

DISPLAY_INIT;

static int16_t w, h, frame_x, frame_y, frame_x_offset, frame_width, frame_height, frame_line_pixels;
extern int16_t bg_color;
extern uint16_t myPalette[];

extern void display_begin()
{
    gfx->begin();
    bg_color = gfx->color565(24, 28, 24); // DARK DARK GREY
    gfx->fillScreen(bg_color);

#ifdef TFT_BL
    // turn display backlight on
    #ifdef TFT_BRIGHTNESS
	log_d("setup LEDC: pin=%d, ch=%d, f=%d, bit=%d", TFT_BL, 1, 12000, 8);
    ledcSetup(1, 12000, 8);       // 12 kHz PWM, 8-bit resolution
    ledcAttachPin(TFT_BL, 1);     // assign TFT_BL pin to channel 1
    ledcWrite(1, TFT_BRIGHTNESS); // brightness 0 - 255
    #else
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    #endif
#endif
}

extern "C" void display_init()
{
    w = gfx->width();
    h = gfx->height();
    if (w < 480) // assume only 240x240 or 320x240
    {
        if (w > NES_SCREEN_WIDTH)
        {
            frame_x = (w - NES_SCREEN_WIDTH) / 2;
            frame_x_offset = 0;
            frame_width = NES_SCREEN_WIDTH;
            frame_height = NES_SCREEN_HEIGHT;
            frame_line_pixels = frame_width;
        }
        else
        {
            frame_x = 0;
            frame_x_offset = (NES_SCREEN_WIDTH - w) / 2;
            frame_width = w;
            frame_height = NES_SCREEN_HEIGHT;
            frame_line_pixels = frame_width;
        }
        frame_y = (gfx->height() - NES_SCREEN_HEIGHT) / 2;
        #ifdef TFT_Y_OFFSET
        frame_y += TFT_Y_OFFSET;
        #endif
    }
    else // assume 480x320
    {
        frame_x = 0;
        frame_y = 0;
        frame_x_offset = 8;
        frame_width = w;
        frame_height = h;
        frame_line_pixels = frame_width / 2;
    }
    log_d("display_init: w=%d, h=%d, x=%d, y=%d, xoff=%d, lpx=%d", frame_width, frame_height, frame_x, frame_y, frame_x_offset, frame_line_pixels);
}

extern "C" void display_write_frame(const uint8_t *data[])
{
    gfx->startWrite();
    if (w < 480)
    {
        log_v("writeAddrWindow: x=%d, y=%d, w=%d, h=%d", frame_x, frame_y, frame_width, frame_height);
        gfx->writeAddrWindow(frame_x, frame_y, frame_width, frame_height);
        for (int32_t i = 0; i < NES_SCREEN_HEIGHT; i++)
        {
            gfx->writeIndexedPixels((uint8_t *)(data[i] + frame_x_offset), myPalette, frame_line_pixels);
        }
    }
    else
    {
        /* ST7796 480 x 320 resolution */

        /* Option 1:
         * crop 256 x 240 to 240 x 214
         * then scale up width x 2 and scale up height x 1.5
         * repeat a line for every 2 lines
         */
        // gfx->writeAddrWindow(frame_x, frame_y, frame_width, frame_height);
        // for (int16_t i = 10; i < (10 + 214); i++)
        // {
        //     gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
        //     if ((i % 2) == 1)
        //     {
        //         gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
        //     }
        // }

        /* Option 2:
         * crop 256 x 240 to 240 x 214
         * then scale up width x 2 and scale up height x 1.5
         * simply blank a line for every 2 lines
         */
        int16_t y = 0;
        for (int16_t i = 10; i < (10 + 214); i++)
        {
            gfx->writeAddrWindow(frame_x, y++, frame_width, 1);
            gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
            if ((i % 2) == 1)
            {
                y++; // blank line
            }
        }

        /* Option 3:
         * crop 256 x 240 to 240 x 240
         * then scale up width x 2 and scale up height x 1.33
         * repeat a line for every 3 lines
         */
        // gfx->writeAddrWindow(frame_x, frame_y, frame_width, frame_height);
        // for (int16_t i = 0; i < 240; i++)
        // {
        //     gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
        //     if ((i % 3) == 1)
        //     {
        //         gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
        //     }
        // }

        /* Option 4:
         * crop 256 x 240 to 240 x 240
         * then scale up width x 2 and scale up height x 1.33
         * simply blank a line for every 3 lines
         */
        // int16_t y = 0;
        // for (int16_t i = 0; i < 240; i++)
        // {
        //     gfx->writeAddrWindow(frame_x, y++, frame_width, 1);
        //     gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
        //     if ((i % 3) == 1)
        //     {
        //         y++; // blank line
        //     }
        // }
    }
    gfx->endWrite();
}

extern "C" void display_clear()
{
    gfx->fillScreen(bg_color);
}
