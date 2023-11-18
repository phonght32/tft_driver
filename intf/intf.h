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

#ifndef __TFT_DRIVER_INTF_H__
#define __TFT_DRIVER_INTF_H__

#include "err_code.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef err_code_t (*tft_driver_spi_trans)(uint8_t *data, uint32_t len);
typedef err_code_t (*tft_driver_set_dc)(uint8_t level);
typedef err_code_t (*tft_driver_set_rst)(uint8_t level);
typedef err_code_t (*tft_driver_delay)(uint32_t delay_ms);


#ifdef __cplusplus
}
#endif

#endif /* __TFT_DRIVER_INTF_H__ */