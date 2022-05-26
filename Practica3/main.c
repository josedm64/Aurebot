/*
          _____                    _____                    _____                    _____
         /\    \                  /\    \                  /\    \                  /\    \
        /::\    \                /::\____\                /::\    \                /::\    \
       /::::\    \              /:::/    /               /::::\    \              /::::\    \
      /::::::\    \            /:::/    /               /::::::\    \            /::::::\    \
     /:::/\:::\    \          /:::/    /               /:::/\:::\    \          /:::/\:::\    \
    /:::/__\:::\    \        /:::/    /               /:::/__\:::\    \        /:::/__\:::\    \
   /::::\   \:::\    \      /:::/    /               /::::\   \:::\    \      /::::\   \:::\    \
  /::::::\   \:::\    \    /:::/    /      _____    /::::::\   \:::\    \    /::::::\   \:::\    \
 /:::/\:::\   \:::\    \  /:::/____/      /\    \  /:::/\:::\   \:::\____\  /:::/\:::\   \:::\    \
/:::/  \:::\   \:::\____\|:::|    /      /::\____\/:::/  \:::\   \:::|    |/:::/__\:::\   \:::\____\
\::/    \:::\  /:::/    /|:::|____\     /:::/    /\::/   |::::\  /:::|____|\:::\   \:::\   \::/    /
 \/____/ \:::\/:::/    /  \:::\    \   /:::/    /  \/____|:::::\/:::/    /  \:::\   \:::\   \/____/
          \::::::/    /    \:::\    \ /:::/    /         |:::::::::/    /    \:::\   \:::\    \
           \::::/    /      \:::\    /:::/    /          |::|\::::/    /      \:::\   \:::\____\
           /:::/    /        \:::\__/:::/    /           |::| \::/____/        \:::\   \::/    /
          /:::/    /          \::::::::/    /            |::|  ~|               \:::\   \/____/
         /:::/    /            \::::::/    /             |::|   |                \:::\    \
        /:::/    /              \::::/    /              \::|   |                 \:::\____\
        \::/    /                \::/____/                \:|   |                  \::/    /
         \/____/                  ~~                       \|___|                   \/____/

   Programa de ejemplo para la AureBoard
   Requerido: Aureboard Versi�n>2.0

   - El programa configura el puerto Serie por USB.
   - Cada programa deber� ir en su carpeta al mismo nivel de la carpeta lib

    A.U.R.E. 2010
*/




/*
//NO ENCUENTRA LAS LIBRERIAS
#include <../lib/sonido.h>
#include <../lib/2leds.h>
*/

#include <../lib/aurebot.h>
#include <../lib/motores.h>
#include <../lib/flex_lcd.c>
#include <../lib/ldr.h>
#include <../lib/cny70.h>
#include <../lib/bumper.h>

// Rutina de gestion de pulsaciones serie
void aure_serie(){
    output_toggle(LED);

    switch(keypress){    //Control de movimiento
        case 'w':
            motores_palante();
            break;
        
        case 'W':
            motores_palante();
            break;
      
        case 's':
            motores_patras();
            break;
      
        case 'S':
            motores_patras();
            break;
            
        case 'd':
            motores_paderecha();
            break;
            
        case 'D':
            motores_paderecha();
            break;
      
        case 'a':
            motores_paizda();
            break;
      
        case 'A':
            motores_paizda();
            break;
      
        case 'q':
            motores_parar();
            break;
      
        case 'Q':
            motores_parar();
            break;
            
        default:
            printf (usb_cdc_putc, "NR:%c\r\n", keypress);
            break;
    }
   
    //Vaciamos el buffer
    keypress=0;
}

//Rutina principal
void main(){
    //Declaración de variables
    int LDR_1, LDR_2;
    int i, d, j, k;

    //Declaración de configuraciones
    aure_configurar();
    lcd_configurar();
    aure_configurar_usb_sinespera();

    for(i=0; i<50; i++){
        delay_ms(100);

        if(input(PULSADOR))
            i=100;
   }

    if (aure_configurar_usb_comprobar()==1){
        // Si esta conectado
        while (!input(PULSADOR)){
            aure_usb();  //Esperamos hasta que se pulse el pulsador
        }

        aure_usb();

        while (1){
            aure_usb();
        }


    } else{
        //Si no esta conectado
        while(!input(PULSADOR)){
            //Esperamos hasta que se presione el pulsador
        }

        /*
        //MOVIMIENTOS DEL ROBOT (DESHABILITADO TEMPORALMENTE PARA HACER PRUEBAS)
        motores_palante();
        delay_ms(10000);
        motores_parar();

        motores_paderecha();
        delay_ms(1000);
        motores_parar();
        */

        Output_high(PIN_A0); //LEDs del parachoque encendidos

        //Variables con los valores en tiempo real de los LDRs
        LDR_1 = Input(PIN_A1);
        LDR_2 = Input(PIN_A2);

        /*
        if(LDR_1 > 0 || LDR_2 > 0)
            Output_toggle(PIN_A0);
        */
        
        //Funcionamiento de la LCD
        lcd_init();
        printf(LDR_1);

        while(1){
            usb_task();
        }
    }
}
