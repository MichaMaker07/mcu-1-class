

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "stm32f4xx_ll_usart.h"

#include "module.h"
#include "ttys.h"



/*
 *  Common macros
 *
 *  This module intergrates into the C language stdio system. The ttys device files can be viewed as always "open", with the following
 *  file descriptors. These are then mapped to FILE streams.
 *
 *  Note that one of the UARTs is mapped to stdout (file descriptor 1), which ist thus the one used for printf() and friends.
 *
 */

#define UART1_FD 	4
#define UART2_FD	1
#define UART6_FD	3


////////////////////////////////////////////////////////////////////////////////
// Type definitions
////////////////////////////////////////////////////////////////////////////////

// Pre-instance ttys state information.

struct ttys_state {
	struct ttys_cfg cfg;
	FILE* stream;
	int fd;
	USART_TypeDef* uart_reg_base;
	uint16_t rx_buf_get_idx;
	uint16_t rx_buf_put_idx;
	uint16_t tx_buf_get_idx;
	uint16_t rx_buf_put_idx;
	char tx_buf[TTYS_TX_BUF_SIZE];
	char rx_buf[TTYS_RX_BUF_SIZE];
};

// Performance measurement for ttys. Currently these are common to all instances.
// A future enhancement would be to make them per-instance


enum ttys_u16_pms {
	CNT_RX_UART_ORE,
	CNT_RX_UART_NE,
	CNT_RX_UART_FE,
	CNT_RX_UART_PE,
	CNT_TX_BUF_OVERRUN,
	CNT_RX_BUF_OVERRUN,

	NUM_U16_PMS
};


// Private (static) function declarations

static void ttys_interrupt(enum ttys_instance_id instance_id, IRQn_Type irq_type);
static int32_t cmd_ttys_status(int32_t argc, const char** argv);
static int32_t cmd_ttys_test(int32_t argc, const char** argv);




/*
 *  Private (static) variables
 */

static struct ttys_state ttys_states[TTYS_NUM_INSTANCES];

static int32_t log_level = LOG_DEFAULT;

// Storage for performance measurements.
static uint16_t cnts_u16[NUM_U16_PMS];

// Name of performance measurements.
static const char* cnts_u16_names[NUM_U16_PMS] = {
		"uart rx overrun err",
		"uart rx noise err",
		"uart rx frame err",
		"uart rx parity err",
		"tx buf overrun err",
		"rx buf overrun err",
};

// Data structure with console command info.
static struct cmd_cmd_info cmds[] = {
		{
				.name = "status",
				.func = cmd_ttys_status,
				.help = "Get module status, usage: ttys status",
		},
		{
				.name = "test",
				.func = cmd_ttys_test,
				.help = "Runt test, usage: ttys test [<op> [<arg>]] (enter no op/arg for help",
		}
};


// Data structure passed to cmd module for console interaction
static struct cmd_client_info cmd_info = {
		.name = "ttys",
		.num_cmds = ARRAY_SIZE(cmds),
		.cmd = cmds,
		.log_level_ptr = &log_level,
		.num_u16_pms = NUM_U16_PMS,
		.u16_pms = cnts_u16,
		.u16_pm_names = cnts_u16_names,
};


////////////////////////////////////////////////////////////////////////////////
// Public (global) variables and externs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Public (global) functions
////////////////////////////////////////////////////////////////////////////////

/*
 * @brief Get default ttys configuration.
 *
 * @param[out] cfg The ttys configuration with defaults filled in.
 *
 * @return 0 for success, else a "MOD_ERR" value. See code for details.
 *
 */

int32_t ttys_get_def_cfg(enum ttys_instance_id instance_id, struct ttys_cfg* cfg)
{
	if (cfg == NULL)
	{
		return MOD_ERR_ARG;
	}

	memset(cfg, 0, sizeof(*cfg));
	cfg->create_stream = true;
	cfg->send_cr_after_nl = true;
	return 0;
}



/*
 *  @brief Initialize ttys module instance
 *
 *  @param[in] instance_id Idenfies the ttys instance.
 *  @param[in] cfg The ttys moudle configuration (FUTURE)
 *
 *  @return 0 for successs, else a "MOD_ERR" value. Sie code for details.
 *
 *  This function initializes a ttys moudle instance. Generally, it should not accesss other moudles as they
 *  might other have been initialized yet
 */
int32_t ttys_init(enum ttys_instance_id instance_id, struct ttys_cfg* cfg)
{
	struct ttys_state* st;
	if (instance_id >= TTYS_NUM_INSTANCES)
	{
		return;
	}

	st = &ttys_state[instance_id];

	// If instance is not open, we should not get an interrupt, but for saftey
	// just disable it.

	if(st->uart_reg_base == NULL) {
		NVIC_DisableIRQ(irq_type);
		return;
	}

	sr = st->uart_reg_base->SR;




}








