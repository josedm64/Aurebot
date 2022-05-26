#define cny70 1
#define CNY_I 2
#define CNY_D 3


void cny70_configurar()
{
   //Configuramos el ADC
   //Todas las entradas analogicas activas y rango 0-Vdd
   setup_adc_ports( ALL_ANALOG|VSS_VDD );
   //Reloj interno
   setup_adc(ADC_CLOCK_INTERNAL );
   printf("-ADC\r\n");

   printf("-CNY70 configurado\r\n");
}