#define bumper 1
#define BUMPER_I PIN_C1
#define BUMPER_D PIN_C0

void bumpers_comprobar()
{
   int c;
   printf (usb_cdc_putc, "Comprobando bumpers...\r\n");
   while (1)
   {
      usb_task();
      if (usb_cdc_kbhit())
      {
         c=usb_cdc_getc();
         printf(usb_cdc_putc, "%c\r\n",c);
         if (c==27) return;
      }
      printf (usb_cdc_putc, "Bumper izquierdo: %d Bumper derecho: %d\r\n", input(BUMPER_I), input(BUMPER_D));
      delay_ms(100);
   }
}
