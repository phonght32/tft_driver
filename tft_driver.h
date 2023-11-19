// MIT License

// Copyright (c) 2023 phonght32

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __TFT_DRIVER_H__
#define __TFT_DRIVER_H__

#include "err_code.h"
#include "intf/tft_driver_intf.h"
#include "fonts.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct  TFT driver handle structure.
 */
typedef struct tft_driver* tft_driver_handle_t;

/**
 * @struct  TFT driver configuration structure.
 */
typedef struct {
    uint16_t height;
    uint16_t width;
} tft_driver_cfg_t;

/*
 * @brief   Initialize TFT driver with default parameters.
 *
 * @note    This function must be called first before any APIs.
 *
 * @param   None.
 *
 * @return
 *      - TFT driver handle structure.
 *      - NULL: Fail.
 */
tft_driver_handle_t tft_driver_init(void);

/*
 * @brief   Set communication function.
 *
 * @note    Pass NULL as argument if this function not be used.
 *
 * @param   handle Handle structure.
 * @param   func_spi_trans Function SPI transfer.
 * @param   func_set_dc Function set pin DC.
 * @param   func_set_rst Function set pin RST.
 * @param   func_delay Function delay.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_set_func(tft_driver_handle_t handle,
                               tft_driver_spi_trans func_spi_trans,
                               tft_driver_set_dc func_set_dc,
                               tft_driver_set_rst func_set_rst,
                               tft_driver_delay func_delay);

/*
 * @brief   Configure TFT ready for display.
 *
 * @param   handle Handle structure.
 * @param   config Config structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_config(tft_driver_handle_t handle, tft_driver_cfg_t config);

/*
 * @brief   Refresh screen.
 *
 * @param   handle Handle structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_screen_refresh(tft_driver_handle_t handle);

/**
 * @brief   Fill screen with color.
 *
 * @param   handle Handle structure.
 * @param   color Color.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_fill(tft_driver_handle_t handle, uint32_t color);

/**
 * @brief   Write character.
 *
 * @param   handle Handle structure.
 * @param   font_size Font size.
 * @param   chr Character.
 * @param   color Color.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_write_char(tft_driver_handle_t handle,
                                 font_size_t font_size,
                                 uint8_t chr,
                                 uint32_t color);

/**
 * @brief   Write string.
 *
 * @param   handle Handle structure.
 * @param   font_size Font size.
 * @param   str Pointer references to the data.
 * @param   color Color.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_write_string(tft_driver_handle_t handle,
                                   font_size_t font_size,
                                   uint8_t *str,
                                   uint32_t color);

/**
 * @brief   Write pixel.
 *
 * @param   handle Handle structure.
 * @param   x Horizontal position.
 * @param   y Vertical position.
 * @param   color Color.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_write_pixel(tft_driver_handle_t handle,
                                  uint16_t x,
                                  uint16_t y,
                                  uint32_t color);

/**
 * @brief   Write line.
 *
 * @param   handle Handle structure.
 * @param   x1 The first horizontal position.
 * @param   y1 The first vertical postion.
 * @param   x2 The second horizontal position.
 * @param   y2 The second vertical position.
 * @param   color Color.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_write_line(tft_driver_handle_t handle,
                                 uint16_t x1,
                                 uint16_t y1,
                                 uint16_t x2,
                                 uint16_t y2,
                                 uint32_t color);

/**
 * @brief   Write rectangle.
 *
 * @param   handle Handle structure.
 * @param   x_origin Origin horizontal position.
 * @param   y_origin Origin vertical position.
 * @param   width Width in pixel.
 * @param   height Height in pixel.
 * @param   color Color.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_write_rectangle(tft_driver_handle_t handle,
                                      uint16_t x_origin,
                                      uint16_t y_origin,
                                      uint16_t width,
                                      uint16_t height,
                                      uint32_t color);

/**
 * @brief   Write Circle.
 *
 * @param   handle Handle structure.
 * @param   x_origin Origin horizontal position.
 * @param   y_origin Origin vertical position.
 * @param   radius Radius in pixel.
 * @param   color Color.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_write_circle(tft_driver_handle_t handle,
                                   uint16_t x_origin,
                                   uint16_t y_origin,
                                   uint16_t radius,
                                   uint32_t color);

/**
 * @brief   Set current position.
 *
 * @param   handle Handle structure.
 * @param   x Horizontal position.
 * @param   y Vertical position.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_set_position(tft_driver_handle_t handle, uint16_t x, uint16_t y);

/**
 * @brief   Get current position.
 *
 * @param   handle Handle structure.
 * @param   x Pointer references to the horizontal position.
 * @param   y Pointer references to the vertical position.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t tft_driver_get_position(tft_driver_handle_t handle, uint16_t *x, uint16_t *y);

/*
 * @brief   Get screen buffer.
 *
 * @param   handle Handle structure.
 *
 * @return
 *      - Screen buffer address.
 *      - NULL: Fail.
 */
uint8_t* tft_driver_get_buffer(tft_driver_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __TFT_DRIVER_H__ */