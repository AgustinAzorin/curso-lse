
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

#include "app_tasks.h"

int main(void)
{
	
	// Configurar clock del sistema a 30 MHz
	BOARD_BootClockFRO30M();

	// Inicializar consola de debug para printf
	BOARD_InitDebugConsole();


	// Tarea de inicialización del sistema
	xTaskCreate(task_system_init,
				"System Init",
				tskSYSTEM_INIT_STACK,
				NULL,
				tskSYSTEM_INIT_PRIORITY,
				NULL);

	// Tarea para trigger del ADC
	xTaskCreate(task_adc_trigger,
				"ADC Trigger",
				tskADC_TRIGGER_STACK,
				NULL,
				tskADC_TRIGGER_PRIORITY,
				NULL);

	// Tarea para sensor de luz BH1750
	xTaskCreate(task_light_sensor,
				"Light Sensor",
				tskLIGHT_SENSOR_STACK,
				NULL,
				tskLIGHT_SENSOR_PRIORITY,
				NULL);

	

	// Tarea de control PWM
	xTaskCreate(task_pwm_control,
				"PWM Control",
				tskPWM_CONTROL_STACK,
				NULL,
				tskPWM_CONTROL_PRIORITY,
				NULL);

	// Tarea de control LED RGB
	xTaskCreate(task_rgb_controller,
				"RGB Controller",
				tskRGB_CONTROLLER_STACK,
				NULL,
				tskRGB_CONTROLLER_PRIORITY,
				NULL);


	// Tarea de manejo del display
	xTaskCreate(task_display_manager,
				"Display Manager",
				tskDISPLAY_MANAGER_STACK,
				NULL,
				tskDISPLAY_MANAGER_PRIORITY,
				&handle_display);

	// Tarea para alternar modo del display
	xTaskCreate(task_display_toggle,
				"Display Toggle",
				tskDISPLAY_TOGGLE_STACK,
				NULL,
				tskDISPLAY_TOGGLE_PRIORITY,
				NULL);


	// Tarea del botón de usuario
	xTaskCreate(task_user_button,
				"User Button",
				tskUSER_BUTTON_STACK,
				NULL,
				tskUSER_BUTTON_PRIORITY,
				NULL);

	// Tarea de control del buzzer
	xTaskCreate(task_buzzer_control,
				"Buzzer Control",
				tskBUZZER_CONTROL_STACK,
				NULL,
				tskBUZZER_CONTROL_PRIORITY,
				NULL);

	// Tarea de botones para setpoint
	xTaskCreate(task_setpoint_buttons,
				"Setpoint Buttons",
				tskSETPOINT_BUTTONS_STACK,
				NULL,
				tskSETPOINT_BUTTONS_PRIORITY,
				NULL);

	// Tarea de monitoreo del sistema
	xTaskCreate(task_system_monitor,
				"System Monitor",
				tskSYSTEM_MONITOR_STACK,
				NULL,
				tskSYSTEM_MONITOR_PRIORITY,
				NULL);

	vTaskStartScheduler();

	return 0;
}
