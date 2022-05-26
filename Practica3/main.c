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
   Requerido: Aureboard Version>2.0

   - El programa configura el puerto Serie por USB.
   - Cada programa debera ir en su carpeta al mismo nivel de la carpeta lib

    A.U.R.E. 2010
*/


/*
//Librerias no encontradas
#include <../lib/sonido.h>
#include <../lib/2leds.h>
#include <../lib/18F4550.h>
*/

//Declaracion de includes
#include <../lib/aurebot.h>
#include <../lib/motores.h>
#include <../lib/flex_lcd.c>
#include <../lib/ldr.h>
#include <../lib/cny70.h>
#include <../lib/bumper.h>

//Declaracion de defines
#define FAROS PIN_A5
#define TRASERAS PIN_A3
#define LDR_I PIN_A0
#define LDR_D PIN_A1
#define MANDO PIN_A2
#define BUMPER_I PIN_E1
#define BUMPER_D PIN_E0
#define BUZZER PIN_E2

//Declaracion de variables globales
int a, b;

//Notas principales
void D0(){
    output_high(BUZZER);
    delay_ms(3.8);
    output_low(BUZZER);
    delay_ms(3.8);
}

void DO_S(){
    output_high(BUZZER);
    delay_ms(3.6);
    output_low(BUZZER);
    delay_ms(3.6);
}

void RE(){
    output_high(BUZZER);
    delay_ms(3.4);
    output_low(BUZZER);
    delay_ms(3.4);
}

void RE_S(){
    output_high(BUZZER);
    delay_ms(3.2);
    output_low(BUZZER);
    delay_ms(3.2);
}

void MI(){
    output_high(BUZZER);
    delay_ms(3);
    output_low(BUZZER);
    delay_ms(3);
}

void FA(){
    output_high(BUZZER);
    delay_ms(2.9);
    output_low(BUZZER);
    delay_ms(2.9);
}

void FA_S(){
    output_high(BUZZER);
    delay_ms(2.7);
    output_low(BUZZER);
    delay_ms(2.7);
}

void SOL(){
    output_high(BUZZER);
    delay_ms(2.6);
    output_low(BUZZER);
    delay_ms(2.6);
}

void SOL_S(){
    output_high(BUZZER);
    delay_ms(2.4);
    output_low(BUZZER);
    delay_ms(2.4);
}

void LA(){
    output_high(BUZZER);
    delay_ms(2.3);
    output_low(BUZZER);
    delay_ms(2.3);
}

void LA_S(){
    output_high(BUZZER);
    delay_ms(2.1);
    output_low(BUZZER);
    delay_ms(2.1);
}

void SI(){
    output_high(BUZZER);
    delay_ms(2);
    output_low(BUZZER);
    delay_ms(2);
}


//Sonidos
//Inicio
void inicio(){
    //BUZZER
}

void sonidoatras(){
    //BUZZER
}

//Movimientos
//Parpadeo de parachoques
void parpadeo(){
    int i;
    for (i = 0; i < 6; i++) {
        output_toggle(FAROS);
        delay_ms(200);
    }
}

//Avanzar
void alante(){
    motores_palante();
    a = leeradc(LDR_I);
    b = leeradc(LDR_D);
}

//Retroceder
void atras(){
    output_high(TRASERAS);
    sonidoatras();
    motores_patras();
    a = leeradc(LDR_I);
    b = leeradc(LDR_D);
    D0();
}

//Giro izquierda
void izda(){
    motores_paizda();
    a = leeradc(LDR_I);
    b = leeradc(LDR_D);
}

//Giro derecha
void drch(){
    motores_paderecha();
    a = leeradc(LDR_I);
    b = leeradc(LDR_D);
}

//Choque de bumper izquierdo
void choque_i(){
    atras();
    delay_ms(2000);
    output_low(TRASERAS);
    
    izda();
    delay_ms(5400);
}

//Choque de bumper derecho
void choque_d(){
    atras();
    delay_ms(2000);
    output_low(TRASERAS);
    
    drch();
    delay_ms(5400);
}



//Rutina principal (1)
void main() {

    //Declaracion de variables
    int i, d, j, k;

    //Declaración de puertos analogicos
    set_tris_A(0b00000111);
    set_tris_E(0b00000011);
    setup_adc_ports(AN0_TO_AN1_ANALOG);
    setup_ADC(ADC_CLOCK_INTERNAL);

    //Declaracion de configuraciones
    aure_configurar();
    lcd_configurar();
    aure_configurar_usb_sinespera();

   //Dejamos un tiempo de inicializacion
    output_low(FAROS); //Apaga los faros
    output_low(TRASERAS); //Apaga las luces traseras
    lcd_init();
    lcd_putc("Inicializando...");

    delay_ms(3000);

    //Una vez inicializado espera al mando
    lcd_init();
    lcd_gotoxy(3, 1);
    lcd_putc("Esperando...");
    
    //Espera al mando
    while (input(MANDO)){

    }

    //AQUI DETECTA EL MANDO
    lcd_init();
    lcd_putc("Todo funcionando correctamente :)");

    inicio();
    
    parpadeo();

    delay_ms(1000);

    lcd_init();

    //-------------------------------------------------------------------------------------------------------------------------------------------------------

    //Aqui empieza la rutina programable
    while (1) {
        //LDRs
        a = leeradc(LDR_I);
        b = leeradc(LDR_D);

        /*
        lcd_gotoxy(1, 2);
        printf(lcd_putc, "a=%u    b=%u", a, b);
        */

        if ((a > 80) || (b > 80))
            Output_high(FAROS);

        else
            Output_low(FAROS);


        //Movimiento
        lcd_putc("Sigo paseando :)");
        lcd_gotoxy(1, 2);
        lcd_putc("                ");

        if (input(BUMPER_I) && input(BUMPER_D)) {
            alante();
        } else if(!input(BUMPER_I)){
            lcd_init();
            lcd_gotoxy(3, 1);
            lcd_putc("Choque a la");

            lcd_gotoxy(3, 2);
            lcd_putc("izquierda :(");

            choque_d();
            lcd_init();
        } else if(!input(BUMPER_D)){
            lcd_init();
            lcd_gotoxy(3, 1);
            lcd_putc("Choque a la");

            lcd_gotoxy(4, 2);
            lcd_putc("derecha :(");

            choque_i();
            lcd_init();
        }
    }
}

