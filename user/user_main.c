#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"

#include "softuart.h"

#define user_procTaskPrio        0
#define user_procTaskQueueLen    1
os_event_t    user_procTaskQueue[user_procTaskQueueLen];


//create global softuart instances
Softuart softuart;
Softuart softuart2;
//-------------------------------------------------------------------------------------------------
// loop function will be execute by "os" periodically
static void ICACHE_FLASH_ATTR  loop(os_event_t *events)
{
	char buffer_char;

	//print something on uart_0 to see progress
	os_printf(".");

	if(Softuart_Available(&softuart)) {
		os_printf("Softuart 1: %c\r\n", Softuart_Read(&softuart));
	}

	//write example output to softuart 1
	Softuart_Puts(&softuart,"eins");

	//check if character is available at second uart
	if(Softuart_Available(&softuart2)) {
		buffer_char = Softuart_Read(&softuart2);

		//character is available and will be sent to first software uart
		os_printf("Sent to Softuart 1: %c\r\n", buffer_char); 
		Softuart_Putchar(&softuart,buffer_char);
	}

	//write example output to softuart 2
	Softuart_Puts(&softuart2,"2");

	//some delay until we run this task again
    os_delay_us(100000);

	// run (schedule) this loop task again 
    system_os_post(user_procTaskPrio, 0, 0 );
}

//-------------------------------------------------------------------------------------------------
//Init function
void ICACHE_FLASH_ATTR  user_init()
{
	// Initialize UART0 to use as debug
    uart_div_modify(0, UART_CLK_FREQ / 9600);

	//init software uart
	Softuart_SetPinRx(&softuart,14);	
	Softuart_SetPinTx(&softuart,12);

	//startup
	Softuart_Init(&softuart,9600);

	//second uart
	//init software uart
	Softuart_SetPinRx(&softuart2,4);	
	Softuart_SetPinTx(&softuart2,5);

	//startup
	Softuart_Init(&softuart2,9600);

    //Start our loop task
    system_os_task(loop, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
    system_os_post(user_procTaskPrio, 0, 0 );
}
