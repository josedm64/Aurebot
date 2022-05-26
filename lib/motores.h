#define motores 1
#define MIR PIN_D5
#define MIF PIN_D4
#define MDR PIN_D7
#define MDF PIN_D6

void motores_patras()
{
      output_bit(MDF,1);
      output_bit(MDR,0);
      output_bit(MIF,1);
      output_bit(MIR,0);

}

void motores_palante()
{
      output_bit(MDF,0);
      output_bit(MDR,1);
      output_bit(MIF,0);
      output_bit(MIR,1);
}

void motores_paderecha()
{
      output_bit(MDF,1);
      output_bit(MDR,0);
      output_bit(MIF,0);
      output_bit(MIR,1);
}

void motores_paizda()
{
      output_bit(MDF,0);
      output_bit(MDR,1);
      output_bit(MIF,1);
      output_bit(MIR,0);
}

void motores_parar()
{
      output_bit(MDF,0);
      output_bit(MDR,0);
      output_bit(MIF,0);
      output_bit(MIR,0);
}



void motores_comprobar()
{
   printf (usb_cdc_putc, "Comprobando motores...\r\n");
   printf (usb_cdc_putc, "\tAdelante\r\n");
   motores_palante();
   delay_ms(2000);
   printf (usb_cdc_putc, "\tAtras\r\n");
   motores_patras();
   delay_ms(2000);
   printf (usb_cdc_putc, "\tDerecha\r\n");
   motores_paderecha();
   delay_ms(2000);
   printf (usb_cdc_putc, "\tIzquierda\r\n");
   motores_paizda();
   delay_ms(2000);
   printf (usb_cdc_putc, "Motores comprobados\r\n\r\n");
}
