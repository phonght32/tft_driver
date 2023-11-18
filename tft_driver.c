#include "stdbool.h"
#include "tft_driver.h"

#define USE_ILI9341

#ifdef USE_ILI9341
#include "ili9341/ili9341.h"
#endif

#define SPI_PARALLEL_LINES  	16
#define MAX_LINE_BUF  			2

/**
 * @struct  LCD lines.
 */
typedef struct {
	uint16_t *data;
} lines_t;

/**
 * @struct  TFT driver structure.
 */
typedef struct tft_driver {
	uint16_t 				height;
	uint16_t 				width;
	tft_driver_spi_trans	func_spi_trans;
	tft_driver_set_dc		func_set_dc;
	tft_driver_set_rst 		func_set_rst;
	tft_driver_delay		func_delay;
	uint8_t 				*data;
	lines_t 				lines[MAX_LINE_BUF];
	uint8_t 				line_idx;
	uint8_t 				pause;
	uint8_t 				is_started;
} tft_driver_t;

static void convert_pixel_to_lines(tft_driver_handle_t handle , int height_idx)
{
	/* Convert pixel data to RGB565 format */
	for (int idx = 0; idx < (handle->width * SPI_PARALLEL_LINES); idx++) {
		uint8_t *p_src = handle->data + handle->width * height_idx * 3 + idx * 3;
		uint16_t *p_desc = handle->lines[handle->line_idx].data + idx;

		uint16_t color_565 = (((uint16_t)p_src[0] & 0x00F8) << 8) |
		                     (((uint16_t)p_src[1] & 0x00FC) << 3) |
		                     ((uint16_t)p_src[2] >> 3);
		uint16_t swap565 = ((color_565 << 8) & 0xFF00) | ((color_565 >> 8) & 0x00FF);

		*p_desc = swap565;
	}
}

static void write_lines(tft_driver_handle_t handle,
                        uint16_t ypos,
                        uint16_t parallel_line,
                        uint16_t *lines_data)
{
	/* Display multi-line data to screen. Every TFT has specific write output operation */
#ifdef USE_ILI9341
	ili9341_write_lines(handle->func_spi_trans,
	                    handle->func_set_dc,
	                    handle->width,
	                    ypos,
	                    parallel_line,
	                    lines_data);
#endif
}

tft_driver_handle_t tft_driver_init(void)
{
	tft_driver_handle_t handle = calloc(1, sizeof(tft_driver_t));

	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return NULL;
	}

	return handle;
}

err_code_t tft_driver_set_func(tft_driver_handle_t handle,
                               tft_driver_spi_trans func_spi_trans,
                               tft_driver_set_dc func_set_dc,
                               tft_driver_set_rst func_set_rst,
                               tft_driver_delay func_delay)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->func_spi_trans = func_spi_trans;
	handle->func_set_dc = func_set_dc;
	handle->func_set_rst = func_set_rst;
	handle->func_delay = func_delay;

	return ERR_CODE_SUCCESS;
}

err_code_t tft_driver_config(tft_driver_handle_t handle, tft_driver_cfg_t config)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	/* Allocate memory for screen data buffer */
	handle->data = calloc(config.width * config.height * 3, sizeof(uint8_t));

	/* Allocate memory for lines buffer. These buffer will be used to store
	   temporarily data of screen buffer */
	for (uint8_t i = 0; i < MAX_LINE_BUF; i++)
	{
		handle->lines[i].data = calloc(config.width * SPI_PARALLEL_LINES, sizeof(uint16_t));
	}

	/* Call specific init function of TFT */
#ifdef USE_ILI9341
	ili9341_init(handle->func_spi_trans,
	             handle->func_set_dc,
	             handle->func_set_rst,
	             handle->func_delay);
#endif

	/* Update handle structure */
	handle->width = config.width;
	handle->height = config.height;
	handle->line_idx = 0;
	handle->pause = false;
	handle->is_started = true;

	return ERR_CODE_SUCCESS;
}

err_code_t tft_driver_screen_refresh(tft_driver_handle_t handle)
{
	int sending_line;

	/* Display all data from screen buffer to screen. Every cycle, SPI_PARALLEL_LINES
	   rows will be updated */
	for (int y = 0; y < handle->height; y += SPI_PARALLEL_LINES)
	{
		/* Convert buffer data from RGB888 to RGB565 and put to lines buffer */
		convert_pixel_to_lines(handle, y);

		/* Get current line buffer index */
		sending_line = handle->line_idx;

		/* Display data to screen */
		write_lines(handle, y, SPI_PARALLEL_LINES, handle->lines[sending_line].data);

		/* Toggle to refer other buffer */
		handle->line_idx ^= 1;
	}

	return ERR_CODE_SUCCESS;
}

uint8_t* tft_driver_get_buffer(tft_driver_handle_t handle)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return NULL;
	}

	return handle->data;
}