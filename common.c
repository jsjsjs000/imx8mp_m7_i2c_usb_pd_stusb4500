#include <stdlib.h>
#include <string.h>

/* Freescale includes. */
#include <fsl_device_registers.h>
#include <fsl_debug_console.h>
#include <fsl_uart_freertos.h>
#include <fsl_uart.h>

// print debug info about string
void debug_string(char *s, int max_string)
{
	int i;
	for (i = 0; i < max_string; i++)
	{
		if (s[i] == 0)
		{
			PRINTF("[NULL](%d)\r\n", i);
			return;
		}
		PRINTF("%c", s[i]);
	}
	PRINTF("[-](%d)\r\n", i);
}
