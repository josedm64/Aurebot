#include <../lib/18F4550.h>
//Configuramos el pic para que trabaje a 48Mhz con un cristal de 4 Mhz.
#fuses XTPLL,MCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG, VREGEN 
#fuses IESO,BROWNOUT,STVREN,NOWRT,FCMEN,USBDIV,PLL1,CPUDIV1
#device adc=8
#use delay(clock=48000000)


// Incluimos el descriptor del cargador
#include "..\lib\bootloader\usb_bootloader.h"
// Incluimos las rutinas de gestión del usb y del "Comunications Device Class"
#include "..\lib\bootloader\usb_cdc.h"

//Creamos el puerto serie (96008N1)
#use rs232 (baud=9600,XMIT=PIN_C6,RCV=PIN_C7,BITS=8)


// Configuramos los dispositivos incluidos en la placa.
#define LED PIN_C2
#define PULSADOR PIN_A4

#define LED_I PIN_D1
#define LED_D PIN_D0

// Alias de funciones
#define ENCENDER  output_high
#define APAGAR    output_low
#define CONMUTAR  output_toggle


// Para configurar el usb si esperar al host
void aure_configurar_usb_sinespera()
{
   usb_cdc_init();
   usb_init();
}


// Devuelve 1 si el dispositivo cdc está conectado
int aure_configurar_usb_comprobar()
{
   if (usb_cdc_connected() && usb_enumerated()) return 1;
   return 0;
}

// Configura el usb y espera al host
void aure_configurar_usb()
{
   usb_cdc_init();
   usb_init();
   while(!usb_cdc_connected()) {}
   if (usb_enumerated()) printf(usb_cdc_putc, "\r\n\n-AureBoard ¡Lista!\r\n");
}


// Inicializa el PIC
void aure_configurar()
{
   int t=0;
   printf ("\r\nAUREBOT\r\n_______\r\n\r\nIniciando...\r\n");
   printf("[Delay 300 ms]\r\n");
   delay_ms(300);
   printf("[Ok]\r\n");
   for (t=0; t<10; t++)
   {
      output_toggle(LED);
      delay_ms(50);
   }
   printf("-Led Verde\r\n");

   /*
      Configuramos el usb-serie
      -aure_configurar_usb()
         Espera a que el host configure el dispositivo, la ejecución del
         programa no comienza hasta ese momento.
      -aure_configurar_usb_sinespera()
         No espera a que el host configure el dispositivo. Se puede usar la 
         función aure_configurar_usb_comprobar() para saber si el dispositivo
         esta conectado (f()==1 conectado, f()==0 desconectado)
   */
   //aure_configurar_usb();
   printf("-USB CDC\r\n");

   //Configuramos los registros TRIS
   //set_tris_a(0b00000111);
   //set_tris_b(0x00);
   //set_tris_c(0x00);
   //set_tris_d(0x00);
   //set_tris_e(0x00);
   //printf("-Registros TRIS\r\n");

   //Configuramos las resistencias de pullup del puerto B
   port_b_pullups(FALSE);
   printf("-Pull up's OFF\r\n");

   //Todos los puertos a nivel bajo
   //output_a (0x00);
   //output_b (0x00);
   //output_c (0xff);
   //output_d (0x00);
   //output_e (0x00);
   //printf("-Puertos a 0\r\n");

   //Configuramos el TIMER0

   //setup_timer_2( T2_DIV_BY_4, 0x4B, 1);
   //enable_interrupts(INT_timer2);


   //Configuramos el TIMER1
   //setup_timer_1(RTCC_INTERNAL|RTCC_DIV_8);
   //set_timer1(0x0000);

   //Configuramos el ADC
   //Todas las entradas analogicas activas y rango 0-Vdd
   //setup_adc_ports( ALL_ANALOG|VSS_VDD );
   setup_adc_ports(NO_ANALOGS);
   //setup_adc(ADC_CLOCK_INTERNAL);

   //Reloj interno
   //setup_adc(ADC_CLOCK_INTERNAL );
   //set_adc_channel(0);
   //printf("-ADC\r\n");

   // Habilitamos el TIMER1
   //enable_interrupts(INT_TIMER1);

   //Habilitamos la interrupcion serie
   enable_interrupts(int_rda);   printf ("-Interrupcion SERIE\r\n");

   // Habilitamos las interrupcione globales
   enable_interrupts(GLOBAL);   printf ("-Interrupciones globales\r\n");


   printf ("¡Lista!\r\n\r\n");
}

//Interrupción y gestión serie
int keypress=0;

#int_rda
void aure_serie_int()
{
   int key;
   key=getc();
    if (key!=0x00 && key!=0xFF)
    {
      output_toggle(LED);
      keypress=key;
      //printf ("\rRX:%u->%c\r\n", key,key);
      if (key==27) reset_cpu();
    }
}


void aure_usb_serie_int()
{
   int key;
   key=usb_cdc_getc();
    if (key!=0x00 && key!=0xFF)
    {
      output_toggle(LED);
      keypress=key;
      //printf ("\rUSB RX:%u->%c\r\n", key,key);
      if (key==27) reset_cpu();
    }
}

void barra(int valor)
{
   float lectura;
   int j, lec[25];
         lectura=valor;
         lectura=lectura/10;
         for (j=0; j<25; j++) if (j<=lectura) { lec[j]='O'; } else {lec[j]=' ';}
         lec[24]='\0';
         printf (usb_cdc_putc, "%s | (%u)\r\n", lec, valor);
}

void aure_serie();

void aure_usb()
{
     // Si usamos el USB
     usb_task();
     // Comprobamos si tenemos algún caracter en el buffer serie/usb, si lo
     // tenemos llamamos a aure_usb_serie_int() que nos lo guardará en keypress
     if (usb_cdc_kbhit())
     {
         aure_usb_serie_int();
         if (keypress!=0x00) aure_serie();
     }
}

#inline
int leeradc(int canal)
{
   set_adc_channel(canal);
   canal=read_adc();
   return canal;
}

