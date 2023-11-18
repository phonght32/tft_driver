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

#ifndef __TFT_DRIVER_ILI9341__
#define __TFT_DRIVER_ILI9341__

#include "err_code.h"
#include "intf/intf.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief   Initialize ILI9341 with default parameters.
 *
 * @param   func_spi_trans Function SPI transfer.
 * @param   func_set_dc Function set pin DC.
 * @param   func_set_rst Function set pin RST.
 * @param   func_delay Function delay.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ili9341_init(tft_driver_spi_trans func_spi_trans,
                        tft_driver_set_dc func_set_dc,
                        tft_driver_set_rst func_set_rst,
                        tft_driver_delay func_delay);


/*
 * @brief   Display multi-lines.
 *
 * @param   func_spi_trans Function SPI transfer.
 * @param   func_set_dc Function set pin DC.
 * @param   width Screen width.
 * @param   ypos Y position.
 * @param   parallel_line Numb of line to display.
 * @param   lines_data Display buffer.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ili9341_write_lines(tft_driver_spi_trans func_spi_trans,
                               tft_driver_set_dc func_set_dc,
                               uint16_t width,
                               uint16_t ypos,
                               uint16_t parallel_line,
                               uint16_t *lines_data);

#ifdef __cplusplus
}
#endif

#endif /* __TFT_DRIVER_ILI9341__ */