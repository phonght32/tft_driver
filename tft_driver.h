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
#include "intf/intf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct 	TFT driver handle structure.
 */
typedef struct tft_driver* tft_driver_handle_t;

/**
 * @struct 	TFT driver configuration structure.
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
 * @param 	config Config structure.
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