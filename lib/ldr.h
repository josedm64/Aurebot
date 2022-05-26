#define ldr 1
#define LDR_I 1
#define LDR_D 0

void ldr_configurar()
{
   //Configuramos el ADC
   //Todas las entradas analogicas activas y rango 0-Vdd
   setup_adc_ports( ALL_ANALOG|VSS_VDD );
   //Reloj interno
   setup_adc(ADC_CLOCK_INTERNAL );
   printf("-ADC\r\n");
   printf("-LDRs configuradas\r\n");
}

void ldr_comprobar()
{
   printf (usb_cdc_putc, "Comprobando sensores LDR...\r\n");
   printf (usb_cdc_putc, "Configurando...\r\n");
   ldr_configurar();
   printf (usb_cdc_putc, "\tSensor derecho:\r\n");
   while (!usb_cdc_kbhit())
   {

      barra(leeradc(LDR_D));
      delay_ms(250);
   }
   usb_cdc_getc();
   printf (usb_cdc_putc, "\r\n");
   printf (usb_cdc_putc, "\tSensor izquierdo:\r\n");
   while (!usb_cdc_kbhit())
   {

      barra(leeradc(LDR_I));
      delay_ms(250);
   }
   usb_cdc_getc();
   printf (usb_cdc_putc, "\r\n");
}
