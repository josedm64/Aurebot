#define servos 1
#define servos_A PIN_D2
#define servos_B PIN_D3

/*
179-15
*/

#define servos_numero   2

int servos_p[servos_numero]={90,90};
int16 servos_contador=0;
int int_servo=0;

void servos_off()
{
   // Reloj a 48 Mhz.
   //    -> Objetivo: Interrupcion cada 10 uS (10e-6)
   //    -> ciclo cada 48000000/4 -> 83 nS (83.333e-9)
   //    -> 120=0x78 ciclos.
   //Configuramos el TIMER2

   disable_interrupts(int_timer2);
   printf ("-TIMER2 desconfigurado\r\n");
   printf ("-Servos desconectados\r\n");
}

void servos_configurar()
{
   // Reloj a 48 Mhz.
   //    -> Objetivo: Interrupcion cada 10 uS (10e-6)
   //    -> ciclo cada 48000000/4 -> 83 nS (83.333e-9)
   //    -> 120=0x78 ciclos.
   //Configuramos el TIMER2

   servos_contador=0;
   setup_timer_2(T2_DIV_BY_1,0x78,1);
   enable_interrupts(int_timer2);
   printf ("-TIMER2 Configurado\r\n");
   printf ("-Servos configurados\r\n");
}


#int_timer2
void servos_inttimer()
{

   servos_contador++;
   //Servos Futaba 3003
   // Pulso minimo 0.3 mS
   // Pulso maximo 2.1 mS
   if (servos_contador>servos_p[0]+45) output_low(servos_A);
   if (servos_contador>servos_p[1]+45) output_low(servos_B);
   if (servos_contador>1998)
   {
      output_high(servos_A);
      output_high(servos_B);
      servos_contador=0;
      int_servo++;
   }
}

void servos_mover_a(int grados, int servo)
{
   int posicion;
   //if (grados>180) grados=180;
   posicion=grados;
   printf ("%i\r\n",posicion);
   //servos_configurar();
   switch (servo)
   {
      case 1:
         servos_p[0]=posicion;
         break;
      case 2:
         servos_p[1]=posicion;
         break;
   }
   //int_servo=0;
   //while (int_servo<50)
   //{
   //}
   //servos_off();
}

void servos_modificar(int grados, int servo, int direccion)
{
   int posicion;


   switch (servo)
   {
      case 1:
         posicion=grados*direccion+servos_p[0];
         servos_mover_a(posicion,servo);
         break;
      case 2:
         posicion=grados*direccion+servos_p[1];
         servos_mover_a(posicion,servo);
         break;
   }
}



void servos_control_auto()
{
   int espera=0;
   int grados;
   int direccion=10;
   while(1)
   {
      if (espera>10)
      {
         espera=0;
         grados=grados+direccion;
         if (grados>180) {grados=180; direccion=-direccion;}
         if (grados<=1) {grados=1; direccion=-direccion;}
         servos_mover_a(grados,1);
         servos_mover_a(180-grados,2);
         printf("Servo: %u    \r",grados);
      } else {
         delay_ms(10);
         espera++;
         //printf ("E:%u\r\n",espera);
      }
   }
}

void servos_comprobar()
{
   int j=0;
   printf (usb_cdc_putc, "Comprobando servos...\r\n");
   servos_configurar();
   servos_mover_a(0, 1);
   servos_mover_a(0, 0);
   delay_ms(100);

   while (!usb_cdc_kbhit())
   {
      for (  j=0; j<180; j+=10)
      {
         servos_mover_a(j, 1);
         servos_mover_a(180-j, 2);
         printf ("Servos a %u y %u respectivamente.\r\n", j, 180-j);
         delay_ms(100);
         if (usb_cdc_kbhit()) break;
      }

   }
}

