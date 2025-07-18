#ifndef _APP_TASKS_H_
#define _APP_TASKS_H_

#include <stdio.h>
#include "board.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "wrappers.h"
#include "isr.h"


// Prioridades de inicialización
#define tskSYSTEM_INIT_PRIORITY (tskIDLE_PRIORITY + 3UL)

// Prioridades de control crítico
#define tskSETPOINT_BUTTONS_PRIORITY (tskIDLE_PRIORITY + 2UL)
#define tskBUZZER_CONTROL_PRIORITY (tskIDLE_PRIORITY + 2UL)

// Prioridades de tareas principales
#define tskADC_TRIGGER_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define tskDISPLAY_MANAGER_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define tskDISPLAY_TOGGLE_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define tskPWM_CONTROL_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define tskLIGHT_SENSOR_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define tskUSER_BUTTON_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define tskRGB_CONTROLLER_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define tskSYSTEM_MONITOR_PRIORITY (tskIDLE_PRIORITY + 1UL)


// Stack para inicialización
#define tskSYSTEM_INIT_STACK (3 * configMINIMAL_STACK_SIZE)

// Stack para tareas de adquisición de datos
#define tskADC_TRIGGER_STACK (configMINIMAL_STACK_SIZE)
#define tskLIGHT_SENSOR_STACK (2 * configMINIMAL_STACK_SIZE)

// Stack para tareas de control
#define tskPWM_CONTROL_STACK (3 * configMINIMAL_STACK_SIZE / 2)
#define tskRGB_CONTROLLER_STACK (3 * configMINIMAL_STACK_SIZE)

// Stack para tareas de interfaz de usuario
#define tskDISPLAY_MANAGER_STACK (3 * configMINIMAL_STACK_SIZE / 2)
#define tskDISPLAY_TOGGLE_STACK (3 * configMINIMAL_STACK_SIZE / 2)

// Stack para tareas de entrada
#define tskUSER_BUTTON_STACK (configMINIMAL_STACK_SIZE)
#define tskSETPOINT_BUTTONS_STACK (configMINIMAL_STACK_SIZE)
#define tskBUZZER_CONTROL_STACK (configMINIMAL_STACK_SIZE)

// Stack para tareas de monitoreo
#define tskSYSTEM_MONITOR_STACK (3 * configMINIMAL_STACK_SIZE)


// Handler para la tarea de display manager
extern TaskHandle_t handle_display;



void task_system_init(void *params);


void task_adc_trigger(void *params);


void task_light_sensor(void *params);


void task_pwm_control(void *params);

void task_rgb_controller(void *params);


void task_display_manager(void *params);


void task_display_toggle(void *params);


void task_user_button(void *params);

void task_buzzer_control(void *params);

void task_setpoint_buttons(void *params);


void task_system_monitor(void *params);


static inline bool wrapper_btn_get_with_debouncing_with_pull_up(gpio_t btn)
{
	// Verificar si se presionó el pulsador (lógica negativa por pull-up)
	if (!wrapper_btn_get(btn))
	{
		// Aplicar antirebote de 20ms
		vTaskDelay(pdMS_TO_TICKS(20));
		// Confirmar que el pulsador sigue presionado
		if (!wrapper_btn_get(btn))
		{
			return true;
		}
	}
	return false;
}

#endif /* _APP_TASKS_H_ */
