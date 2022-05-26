// lib-i2c.h   i2c library routines

// routines for:
//   dallas ds1624 eeprom+thermometer
//

// (C) copyright 2003 j.d.sandoz / jds-pic !at! losdos.dyndns.org 

// released under the GNU GENERAL PUBLIC LICENSE (GPL)
// refer to http://www.gnu.org/licenses/gpl.txt

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

// ----------------------------------------------------------------------------

// routines for the dallas DS1624 i2c-based (temp + 256b eeprom) ic
//   essentials:
//   ds1624_init();   initializes device for continous temperature readings
//   ds1624_read_temperature_c();    reads temperature in deg C
//   ds1624_eeprom_read();           reads a byte from address       
//   ds1624_eeprom_write();          writes a byte into address     
//   ds1624_eeprom_clear();          clears the contents of the eeprom

#define DS1624_ID                      0b10010000
#define DS1624_CMD_ACCESSCONFIG        0xAC
#define DS1624_CMD_INITIATECONVERT     0xEE
#define DS1624_CMD_ACCESSTEMPERATURE   0xAA
#define DS1624_CMD_ACCESSMEMORY        0x17

void ds1624_init(int device_addr) {
   int addr_mask;
   addr_mask=i2c_addr_mask(device_addr);
   i2c_start();
   i2c_write(DS1624_ID | addr_mask | I2CWRITE); /* mode is write */
   i2c_write(DS1624_CMD_ACCESSCONFIG);          /* send access config command */
   i2c_write(0x00);       /* set up for continuous temp conversions */
   i2c_stop();
   delay_ms(20);          /* wait for the data to be written */
   i2c_start();
   i2c_write(DS1624_ID | addr_mask | I2CWRITE);   /* mode is write */
   i2c_write(DS1624_CMD_INITIATECONVERT);   /* initiate temperature conversions */
   i2c_stop();
}

int ds1624_read_temp_c(int device_addr) {
   int datah, datal;
   int addr_mask;
   addr_mask=i2c_addr_mask(device_addr);
   i2c_start();
   i2c_write(DS1624_ID | addr_mask | I2CWRITE); /* mode is write */
   i2c_write(DS1624_CMD_ACCESSTEMPERATURE); /* send access temperature command */
   i2c_start();
   i2c_write(DS1624_ID | addr_mask | I2CREAD);  /* mode is read */
   datah=i2c_read();                  /* msb */
   datal=i2c_read(0);                 /* lsb (=0.5 deg C) & No Ack */
   i2c_stop();
   if (BIT_TEST(datah,7)) /* defeat the two's complement data output; */
      return(0);          /* this means NO negative temps are returned */
   else                   /* if datal is > 0.5C, round up the value */
      return( ((datal & 0b10000000) ? datah+1 : datah) ); /* returns 0->125 deg C */
}

int ds1624_eeprom_read(int device_addr, int address) {
   int data;
   int addr_mask;
   addr_mask=i2c_addr_mask(device_addr);
   i2c_start();
   i2c_write(DS1624_ID | addr_mask | I2CWRITE); /* mode is write */
   i2c_write(DS1624_CMD_ACCESSMEMORY);  /* access memory command */
   i2c_write(address);                  /* address of memory to read from */
   i2c_start();                         /* repeated start */
   i2c_write(DS1624_ID | addr_mask | I2CREAD); /* mode is read */
   data=i2c_read(0);                    /* read the data, No Ack the read */
   i2c_stop();
   return(data);
}

int ds1624_eeprom_write(int device_addr, int address, int data) {
   int addr_mask;
   addr_mask=i2c_addr_mask(device_addr);
   i2c_start();
   i2c_write(DS1624_ID | addr_mask | I2CWRITE); /* mode is write */
   i2c_write(DS1624_CMD_ACCESSMEMORY);  /* access memory command */
   i2c_write(address);                  /* address of memory to write to */
   i2c_write(data);                     /* data to be written */
   i2c_stop();
   delay_ms(20); /* worst case write time for the eeprom */
   return (ds1624_eeprom_read(device_addr, address));
}

long ds1624_eeprom_clear(int device_addr, int fill_byte) {
   long i, memsum=0;
   for (i=0;i<=255;i++) {    /* mind the (int) rollover! */
      ds1624_eeprom_write(device_addr,(int)i,fill_byte);
      memsum+=ds1624_eeprom_read(device_addr,(int)i);
      restart_wdt();
      }
   return(memsum);
}
