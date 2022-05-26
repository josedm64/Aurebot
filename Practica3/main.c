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
#define FAROS PIN_A3
#define TRASERAS PIN_A5
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
    delay_us(3800);
    output_low(BUZZER);
    delay_us(3800);
}

void DO_S(){
    output_high(BUZZER);
    delay_us(3600);
    output_low(BUZZER);
    delay_us(3600);
}

void RE(){
    output_high(BUZZER);
    delay_us(3400);
    output_low(BUZZER);
    delay_us(3400);
}

void RE_S(){
    output_high(BUZZER);
    delay_us(3200);
    output_low(BUZZER);
    delay_us(3200);
}

void MI(){
    output_high(BUZZER);
    delay_us(3000);
    output_low(BUZZER);
    delay_us(3000);
}

void FA(){
    output_high(BUZZER);
    delay_us(2900);
    output_low(BUZZER);
    delay_us(2900);
}

void FA_S(){
    output_high(BUZZER);
    delay_us(2700);
    output_low(BUZZER);
    delay_us(2700);
}

void SOL(){
    output_high(BUZZER);
    delay_us(2600);
    output_low(BUZZER);
    delay_us(2600);
}

void SOL_S(){
    output_high(BUZZER);
    delay_us(2400);
    output_low(BUZZER);
    delay_us(2400);
}

void LA(){
    output_high(BUZZER);
    delay_us(2300);
    output_low(BUZZER);
    delay_us(2300);
}

void LA_S(){
    output_high(BUZZER);
    delay_us(2100);
    output_low(BUZZER);
    delay_us(2100);
}

void SI(){
    output_high(BUZZER);
    delay_us(2000);
    output_low(BUZZER);
    delay_us(2000);
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
    long i;

    output_high(TRASERAS);
    motores_patras();

    for(i = 0; i < 722; i++){
        D0();
    }
    
    a = leeradc(LDR_I);
    b = leeradc(LDR_D);
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
    delay_ms(200);
    output_low(TRASERAS);
    
    izda();
    delay_ms(5400);
}

//Choque de bumper derecho
void choque_d(){
    atras();
    delay_ms(200);
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
    
    //inicio();
    
    parpadeo();

    lcd_init();

    //-------------------------------------------------------------------------------------------------------------------------------------------------------

    //Aqui empieza la rutina programable
    while (1) {
        //LDRs
        a = leeradc(LDR_I);
        b = leeradc(LDR_D);

        
        // lcd_gotoxy(1, 2);
        // printf(lcd_putc, "a=%u    b=%u", a, b);


        if ((a > 21) | (b > 21))
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
        
        
        if(!input(MANDO)){
           lcd_init();
           
           lcd_gotoxy(4, 1);
           lcd_putc("Eso es todo");
           
           lcd_gotoxy(5, 2);
           lcd_putc("amigos :)");
           
           while(1){
              motores_parar();
           }
        }
    }
}
