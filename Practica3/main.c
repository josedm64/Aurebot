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
#include <../lib/18F4550.h>
*/

#include <../lib/aurebot.h>
#include <../lib/motores.h>
#include <../lib/flex_lcd.c>
#include <../lib/ldr.h>
#include <../lib/cny70.h>
#include <../lib/bumper.h>


#define FAROS PIN_A3
#define LDR_I PIN_A0
#define LDR_D PIN_A1
#define MANDO PIN_A2
#define BUMPER_I PIN_E1
#define BUMPER_D PIN_E0
#define TRASERAS PIN_A5


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
    int i, d, j, k, a, b;
    
    set_tris_A(0b00000111);
    set_tris_E(0b00000011);
    setup_adc_ports(AN0_TO_AN1_ANALOG);
    setup_ADC(ADC_CLOCK_INTERNAL);
   

    //Declaracion de configuraciones
    aure_configurar();
    lcd_configurar();
    aure_configurar_usb_sinespera();
    
    //Funcionamiento de la LCD
        lcd_init();
        lcd_putc("Esperando...");
        
        Output_low(FAROS);

    for(i=0; i<50; i++){
        delay_ms(100);
    }

        //Si no esta conectado
        //while(!input(PULSADOR)){
        while(input(MANDO)){
            lcd_putc("Esperando...");//Esperamos hasta que se presione el pulsador
        }
        
        
        lcd_init();
        lcd_putc("Inicializando...");
       
        
        delay_ms(4000);
        
        
        while(1){
           lcd_init();
           lcd_putc("Todo funcionando bien :)");
           
           a=leeradc(LDR_I);
           b=leeradc(LDR_D);
           
           lcd_init();
           printf(lcd_putc,"a=%u    b=%u",a b);
        
        
        //Funcionamiento del LDR 
        if( (a> 1.0) ||  (b > 1) ){
            Output_high(FAROS);
        }
        else{
            Output_low(FAROS);
        }
        
        if(input(BUMPER_I) && input(BUMPER_D)){
            motores_palante();
            delay_ms(10000);
            
            motores_paizda();
            delay_ms(5000);
            
            lcd_init();
            lcd_putc(":)");
        }
        
        if(!input(BUMPER_I) && !input(BUMPER_D)){
            motores_parar();
            delay_ms(1000);
            
            motores_patras();
            delay_ms(10000);
            
            motores_paderecha();
            delay_ms(6000);
            
        } else if(!input(BUMPER_I)){
            motores_parar();
            delay_ms(1000);
            
            motores_patras();
            delay_ms(5000);
            
            motores_paderecha();
            delay_ms(6000);
            
        }else if (!input(BUMPER_D)){
            motores_parar();
            delay_ms(1000);
            
            motores_patras();
            delay_ms(5000);
            
            motores_paizda();
            delay_ms(6000);
         }
        }
}

