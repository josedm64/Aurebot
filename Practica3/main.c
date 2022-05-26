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


#define FAROS PIN_A0
#define LDR_I PIN_A1
#define LDR_D PIN_A2
#define MANDO PIN_A3
#define BUMPER_I PIN_A5
#define BUMPER_D PIN_E0


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
    int i, d, j, k;
    setup_adc_ports(PIN);

    //Declaración de configuraciones
    aure_configurar();
    lcd_configurar();
    aure_configurar_usb_sinespera();
    
    //Funcionamiento de la LCD
        lcd_init();
        lcd_putc("Esperando...");

    for(i=0; i<50; i++){
        delay_ms(100);
    }

    if (aure_configurar_usb_comprobar()==1){
        // Si esta conectado
        while (!input(PULSADOR)){
      //  while (!input(MANDO)){
            aure_usb();  //Esperamos hasta que se pulse el pulsador
        }

        aure_usb();

        while (1){
            aure_usb();
        }


    } else{
        //Si no esta conectado
        //while(!input(PULSADOR)){
        while(input(MANDO)){
            //Esperamos hasta que se presione el pulsador
        }
        
        //Output_high(PIN_A0); //LEDs del faro encendidos
        
        lcd_init();
        lcd_putc("Inicializando...");
        
        delay_ms(4000);
        
        lcd_init();
        lcd_putc("Todo funcionando bien :)");
        
        //Funcionamiento del LDR
        if(LDR_I < 5 || LDR_D < 5 ){
            Output_high(FAROS);
        }
        else{
            Output_low(FAROS);
        }

        //MOVIMIENTOS DEL ROBOT (DESHABILITADO TEMPORALMENTE PARA HACER PRUEBAS)
        
        motores_parar();
        delay_ms(500);
        
        if(BUMPER_I == 5 && BUMPER_D == 5 ){
            motores_parar();
            delay_ms(1000);
            
            motores_patras();
            delay_ms(10000);
            
            motores_paderecha();
            delay_ms(6000);
            
        } else if(BUMPER_I == 5 ){
            motores_parar();
            delay_ms(1000);
            
            motores_patras();
            delay_ms(5000);
            
            motores_paderecha();
            delay_ms(6000);
            
        }else if(BUMPER_D == 5 ){
            motores_parar();
            delay_ms(1000);
            
            motores_patras();
            delay_ms(5000);
            
            motores_paizda();
            delay_ms(6000);
            
        }else{
            motores_palante();
        }
        
        
        
        
    

        /*
        if(LDR_1 > 0 || LDR_2 > 0)
            Output_toggle(PIN_A0);
        */
        
        

        while(1){
            usb_task();
        }
    }
}
