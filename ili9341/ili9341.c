#include "ili9341.h"

#define ILI3941_RST_ACTIVE_LEVEL 	0
#define ILI3941_RST_UNACTIVE_LEVEL 	1

/**
 * @struct  LCD configuration structure.
 */
typedef struct {
	uint8_t cmd;
	uint8_t data[16];
	uint8_t databytes; 		/*!< No of data in data; bit 7 = delay after set; 0xFF = end of cmds. */
} lcd_init_cmd_t;

/**
 * @struct 	LCD initialization commands.
 */
lcd_init_cmd_t ili_init_cmds[] = {
	/* Power contorl B, power control = 0, DC_ENA = 1 */
	{0xCF, {0x00, 0x83, 0X30}, 3},
	/* Power on sequence control,
	 * cp1 keeps 1 frame, 1st frame enable
	 * vcl = 0, ddvdh=3, vgh=1, vgl=2
	 * DDVDH_ENH=1
	 */
	{0xED, {0x64, 0x03, 0X12, 0X81}, 4},
	/* Driver timing control A,
	 * non-overlap=default +1
	 * EQ=default - 1, CR=default
	 * pre-charge=default - 1
	 */
	{0xE8, {0x85, 0x01, 0x79}, 3},
	/* Power control A, Vcore=1.6V, DDVDH=5.6V */
	{0xCB, {0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
	/* Pump ratio control, DDVDH=2xVCl */
	{0xF7, {0x20}, 1},
	/* Driver timing control, all=0 unit */
	{0xEA, {0x00, 0x00}, 2},
	/* Power control 1, GVDD=4.75V */
	{0xC0, {0x26}, 1},
	/* Power control 2, DDVDH=VCl*2, VGH=VCl*7, VGL=-VCl*3 */
	{0xC1, {0x11}, 1},
	/* VCOM control 1, VCOMH=4.025V, VCOML=-0.950V */
	{0xC5, {0x35, 0x3E}, 2},
	/* VCOM control 2, VCOMH=VMH-2, VCOML=VML-2 */
	{0xC7, {0xBE}, 1},
	/* Memory access contorl, MX=MY=0, MV=1, ML=0, BGR=1, MH=0 */
	{0x36, {0x28}, 1},
	/* Pixel format, 16bits/pixel for RGB/MCU interface */
	{0x3A, {0x55}, 1},
	/* Frame rate control, f=fosc, 70Hz fps */
	{0xB1, {0x00, 0x1B}, 2},
	/* Enable 3G, disabled */
	{0xF2, {0x08}, 1},
	/* Gamma set, curve 1 */
	{0x26, {0x01}, 1},
	/* Positive gamma correction */
	{0xE0, {0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0X87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00}, 15},
	/* Negative gamma correction */
	{0XE1, {0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F}, 15},
	/* Column address set, SC=0, EC=0xEF */
	{0x2A, {0x00, 0x00, 0x00, 0xEF}, 4},
	/* Page address set, SP=0, EP=0x013F */
	{0x2B, {0x00, 0x00, 0x01, 0x3f}, 4},
	/* Memory write */
	{0x2C, {0}, 0},
	/* Entry mode set, Low vol detect disabled, normal display */
	{0xB7, {0x07}, 1},
	/* Display function control */
	{0xB6, {0x0A, 0x82, 0x27, 0x00}, 4},
	/* Sleep out */
	{0x11, {0}, 0x80},
	/* Display on */
	{0x29, {0}, 0x80},
	{0, {0}, 0xff},
};

static err_code_t ili9341_write_cmd(tft_driver_spi_trans func_spi_trans,
                                    tft_driver_set_dc func_set_dc,
                                    uint8_t cmd)
{
	/* DC level equal to 0 when write SPI command */
	func_set_dc(0);

	/* Transfer command */
	func_spi_trans(&cmd, 1);

	return ERR_CODE_SUCCESS;
}

static err_code_t ili9341_write_data(tft_driver_spi_trans func_spi_trans,
                                     tft_driver_set_dc func_set_dc,
                                     uint8_t *data,
                                     uint32_t len)
{
	/* DC level equal to 1 when write SPI data */
	func_set_dc(1);

	/* Transfer data */
	func_spi_trans(data, len);

	return ERR_CODE_SUCCESS;
}

err_code_t ili9341_init(tft_driver_spi_trans func_spi_trans,
                        tft_driver_set_dc func_set_dc,
                        tft_driver_set_rst func_set_rst,
                        tft_driver_delay func_delay)
{
	err_code_t err;

	/* Reset screen */
	err = func_set_rst(ILI3941_RST_ACTIVE_LEVEL);
	if (err != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	func_delay(100);

	/* Activate screen again */
	err = func_set_rst(ILI3941_RST_UNACTIVE_LEVEL);
	if (err != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	func_delay(100);

	int cmd = 0;
	lcd_init_cmd_t* lcd_init_cmds = ili_init_cmds;

	/* Configure screen */
	while (lcd_init_cmds[cmd].databytes != 0xff) {
		/* Transfer command mode */
		ili9341_write_cmd(func_spi_trans, func_set_dc, lcd_init_cmds[cmd].cmd);

		if (lcd_init_cmds[cmd].databytes == 0x80) {
			func_delay(100);
		}
		else if (lcd_init_cmds[cmd].databytes != 0) {
			/* Transfer command data */
			ili9341_write_data(func_spi_trans,
			                   func_set_dc,
			                   lcd_init_cmds[cmd].data,
			                   lcd_init_cmds[cmd].databytes & 0x1F);
		}
		else {

		}

		cmd++;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t ili9341_write_lines(tft_driver_spi_trans func_spi_trans,
                               tft_driver_set_dc func_set_dc,
                               uint16_t width,
                               uint16_t ypos,
                               uint16_t parallel_line,
                               uint16_t *lines_data)
{
	uint8_t buf[4] = {0, 0, 0, 0};

	/* Command set column address */
	ili9341_write_cmd(func_spi_trans, func_set_dc, 0x2A);

	buf[0] = 0;					/* Start column high */
	buf[1] = 0;					/* Start column low */
	buf[2] = width >> 8;		/* End column high */
	buf[3] = width & 0xFF;		/* End column low */
	ili9341_write_data(func_spi_trans, func_set_dc, buf, 4);

	/* Command set page address */
	ili9341_write_cmd(func_spi_trans, func_set_dc, 0x2B);

	buf[0] = ypos >> 8;							/* Start page high */
	buf[1] = ypos & 0xFF;						/* Start page low */
	buf[2] = (ypos + parallel_line) >> 8;		/* End page high */
	buf[3] = (ypos + parallel_line) & 0xff;		/* End page low */
	ili9341_write_data(func_spi_trans, func_set_dc, buf, 4);

	/* Command set data */
	ili9341_write_cmd(func_spi_trans, func_set_dc, 0x2C);

	/* Transfer screen data */
	ili9341_write_data(func_spi_trans, func_set_dc, (uint8_t*)lines_data, width * sizeof(uint16_t) * parallel_line);

	return ERR_CODE_SUCCESS;
}