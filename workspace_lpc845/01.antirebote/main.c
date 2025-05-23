#include "board.h"

#define BLUE_LED GPIO, 1, 1
#define RED_LED  GPIO, 1, 2
#define BOTON  GPIO, 0, 4

int main (void){

    //Inicaliza los puertos 
    GPIO_PortInit(GPIO, 1);
    GPIO_PortInit(GPIO, 0);

    //Crea las estrucuturas de inicializacion para los pines de entrada y salida
    gpio_pin_config_t out_config = { .pinDirection = kGPIO_DigitalOutput, .outputLogic = 1 };
    gpio_pin_config_t in_config = { .pinDirection = kGPIO_DigitalInput};

    //Inicializa los pines
    GPIO_PinInit(GPIO, 1, 1, &out_config);
    GPIO_PinInit(GPIO, 1, 2, &out_config);
    GPIO_PinInit(GPIO, 0, 4, &in_config);

    //este es un lopp que revisa constantemente el estao del boton 
    while (1){
        int FABRI = GPIO_PinRead(BOTON);
        //si el boton esta activado, prende el led azul
        if (FABRI == 1){
            GPIO_PinWrite(GPIO, 1, 1, 1);
            for(uint32_t i=0; i < 20; i++)
            FABRI = GPIO_PinRead(BOTON);
            //Si el boton sigue prendido despues de 20 ms, se prendera el led rojo
            if (FABRI == 1){
                GPIO_PinWrite(GPIO, 0, 4, 1);
            }
        }
        //Si el boton no esta activado, apaga los leds
        else{
            GPIO_PinWrite(GPIO, 1, 1, 0);
            GPIO_PinWrite(GPIO, 0, 4, 0);
        }   
    }

    return 0;
}