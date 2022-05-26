void ds1307_init(void)
{
   BYTE seconds = 0;

   i2c_start();
   i2c_write(0xD0);      // WR to RTC
   i2c_write(0x00);      // REG 0
   i2c_start();
   i2c_write(0xD1);      // RD from RTC
   seconds = bcd2bin(i2c_read(0)); // Read current "seconds" in DS1307
   i2c_stop();
   seconds &= 0x7F;

   delay_us(3);

   //i2c_start();
   //i2c_write(0xD0);      // WR to RTC
   //i2c_write(0x00);      // REG 0
   //i2c_write(bin2bcd(seconds));     // Start oscillator with current "seconds value
   i2c_start();
   i2c_write(0xD0);      // WR to RTC
   i2c_write(0x07);      // Control Register
   i2c_write(0x80);     // Disable squarewave output pin
   i2c_stop();

}

void ds1307_set_date_time(BYTE day, BYTE mth, BYTE year, BYTE dow, BYTE hr, BYTE min, BYTE sec)
{
  sec &= 0x7F;
  hr &= 0x3F;

  i2c_start();
  i2c_write(0xD0);            // I2C write address
  i2c_write(0x00);            // Start at REG 0 - Seconds
  i2c_write(bin2bcd(sec));      // REG 0
  i2c_write(bin2bcd(min));      // REG 1
  i2c_write(bin2bcd(hr));      // REG 2
  i2c_write(bin2bcd(dow));      // REG 3
  i2c_write(bin2bcd(day));      // REG 4
  i2c_write(bin2bcd(mth));      // REG 5
  i2c_write(bin2bcd(year));      // REG 6
  i2c_write(0x80);            // REG 7 - Disable squarewave output pin
  i2c_stop();
}

void ds1307_get_date(BYTE &day, BYTE &mth, BYTE &year, BYTE &dow)
{
  i2c_start();
  i2c_write(0xD0);
  i2c_write(0x03);            // Start at REG 3 - Day of week
  i2c_start();
  i2c_write(0xD1);
  dow  = bcd2bin(i2c_read() & 0x7f);   // REG 3
  day  = bcd2bin(i2c_read() & 0x3f);   // REG 4
  mth  = bcd2bin(i2c_read() & 0x1f);   // REG 5
  year = bcd2bin(i2c_read(0));            // REG 6
  i2c_stop();
}

void ds1307_get_time(BYTE &hr, BYTE &min, BYTE &sec)
{
  i2c_start();
  i2c_write(0xD0);
  i2c_write(0x00);            // Start at REG 0 - Seconds
  i2c_start();
  i2c_write(0xD1);
  sec = bcd2bin(i2c_read() & 0x7f);
  min = bcd2bin(i2c_read() & 0x7f);
  hr  = bcd2bin(i2c_read(0) & 0x3f);
  i2c_stop();

}
