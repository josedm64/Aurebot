#define barra_leds 1
#define beds_time 70 //Tiempo que esta encendido cada led

void barraleds_comprobar_b()
{
      output_high(PIN_B0);
      output_low(PIN_B1);
      delay_ms(beds_time);
      output_high(PIN_B1);
      output_low(PIN_B0);
      delay_ms(beds_time);
      output_high(PIN_B2);
      output_low(PIN_B1);
      delay_ms(beds_time);
      output_high(PIN_B3);
      output_low(PIN_B2);
      delay_ms(beds_time);
      output_high(PIN_B4);
      output_low(PIN_B3);
      delay_ms(beds_time);
      output_high(PIN_B5);
      output_low(PIN_B4);
      delay_ms(beds_time);
      output_high(PIN_B6);
      output_low(PIN_B5);
      delay_ms(beds_time);
      output_high(PIN_B7);
      output_low(PIN_B6);
      delay_ms(beds_time);


      output_high(PIN_B6);
      output_low(PIN_B7);
      delay_ms(beds_time);
      output_high(PIN_B5);
      output_low(PIN_B6);
      delay_ms(beds_time);
      output_high(PIN_B4);
      output_low(PIN_B5);
      delay_ms(beds_time);
      output_high(PIN_B3);
      output_low(PIN_B4);
      delay_ms(beds_time);
      output_high(PIN_B2);
      output_low(PIN_B3);
      delay_ms(beds_time);
      output_high(PIN_B1);
      output_low(PIN_B2);
      delay_ms(beds_time);
 }


void barraleds_comprobar_a()
{
      output_high(PIN_E2);
      delay_ms(beds_time);
      output_low(PIN_E2);

      output_high(PIN_E1);
      delay_ms(beds_time);
      output_low(PIN_E1);

      output_high(PIN_E0);
      delay_ms(beds_time);
      output_low(PIN_E0);

      output_high(PIN_A5);
      delay_ms(beds_time);
      output_low(PIN_A5);

      output_high(PIN_A3);
      delay_ms(beds_time);
      output_low(PIN_A3);

      output_high(PIN_A2);
      delay_ms(beds_time);
      output_low(PIN_A2);

      output_high(PIN_A1);
      delay_ms(beds_time);
      output_low(PIN_A1);

      output_high(PIN_A0);
      delay_ms(beds_time);
      output_low(PIN_A0);

}
