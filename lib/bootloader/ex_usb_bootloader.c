#include <18F4550.h>
//Configuramos el pic para que trabaje a 48Mhz con un cristal de 4 Mhz.
#fuses XTPLL,MCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG, VREGEN 
#fuses IESO,BROWNOUT,STVREN,NOWRT,FCMEN,USBDIV,PLL1,CPUDIV1
#use delay(clock=48000000)
  
//Cargamos los archivos necesarios para el bootloader
#define _bootloader
#include "usb_bootloader.h"
#define LOADER_ISR 0x28
#build(interrupt=LOADER_ISR)

// Incluimos las rutinas de gestión del usb y del "Comunications Device Class"
#include ".\usb_cdc.h"

// Salto al gestor de interrupciones dell bootloader o de la aplicación
#org 0x08,0x17
void high_isr(void) 
{
   if (bit_test(g_InBootloader,0))
   {
    #ASM
     goto LOADER_ISR
    #ENDASM
   }
   else
   {
    #ASM
     goto APPLICATION_ISR
    #ENDASM
   }
}

#org 0x18,0x27
void low_isr(void) 
{
   if (bit_test(g_InBootloader,0))
   {
    #ASM
     goto LOADER_ISR+0x10
    #ENDASM
   }
   else
   {
    #ASM
     goto APPLICATION_ISR+0x10
    #ENDASM
   }
}

//Write to Flash ROM.
//
// location - flash program memory address
// src - pointer to data to write
// size - number of bytes to write to flash
//
// Here is the sequence of events:
//   1.) Goes to the beginning of the first erase block for this address
//   2.) Reads n records to ram, where n is the PIC's flash erase size
//   3.) Erases block in flash
//   4.) Modifies block in RAM
//   5.) Writes changed block back to FLASH.  Writes in chunks defined by PIC's flash write size
//   6.) Goes back to step1 if there is still more data to be written
void rom_w(int32 location, char *src, int16 size)
{
   #define EEPROM_ERASE_SIZE  getenv("FLASH_ERASE_SIZE")
   #define EEPROM_WRITE_SIZE  getenv("FLASH_WRITE_SIZE")
   int8 block[EEPROM_ERASE_SIZE];
   int32 block_start;
   int8 i;
   int8 num;

   block_start = location & (~((int32)EEPROM_ERASE_SIZE-1));
   i=location-block_start;

   while (size) 
   {
      read_program_memory(block_start, block, sizeof(block));  //read entire block to ram buffer

      if (size>(EEPROM_ERASE_SIZE-i)) {num=EEPROM_ERASE_SIZE-i;} else {num=size;}

      memcpy(&block[i],src,num);    //modify ram buffer

      erase_program_eeprom(block_start);     //erase entire block

      write_program_memory(block_start, block, sizeof(block));    //write modified block

      src+=num;
      block_start+=EEPROM_ERASE_SIZE;
      i=0;
      size-=num;
   }
}

#define BUFFER_LEN_LOD 64

#define ACKLOD 0x06
#define XON    0x11
#define XOFF   0x13

// Convert two hex characters to a int8
unsigned int8 atoi_b16(char *s) 
{  
   char c;
   unsigned int8 result = 0;
   int i;

   for (i=0; i<2; i++,s++)  
   {
      c = *s;
      if (c >= 'A')
         result = 16*result + c - 'A' + 10;
      else
         result = 16*result + c - '0';         
   }

   return(result);
}

void load_program(void)
{
   int1  do_ACKLOD, done=FALSE;
   int8  checksum, line_type;
   int16 l_addr,h_addr=0;
   int8 to;
   int32 addr;
   int8  dataidx, i, count;
   int8  data[32];
   int  buffidx;
   char buffer[BUFFER_LEN_LOD];
   
   while (!done)  // Loop until the entire program is downloaded
   {
      usb_task();
      
      if (!usb_cdc_kbhit())
         continue;
         
      buffidx = 0;  // Read into the buffer until 0x0D ('\r') is received or the buffer is full
      to = 250;   //250 milliseconds
      do 
      {
         if (!usb_cdc_kbhit())
         {
            delay_ms(1);
            to--;
            if (!to)
               break;
         }
         else
            to = 250;
         i = usb_cdc_getc();
         buffer[buffidx++] = i;
      } while ( (i != 0x0D) && (i != 0x0A) && (buffidx <= BUFFER_LEN_LOD) );
            
      if (!to)
         continue;

      usb_cdc_putc(XOFF);  // Suspend sender

      do_ACKLOD = TRUE;

      // Only process data blocks that start with ':'
      if (buffer[0] == ':') {
         count = atoi_b16 (&buffer[1]);  // Get the number of bytes from the buffer

         // Get the lower 16 bits of address
         l_addr = make16(atoi_b16(&buffer[3]),atoi_b16(&buffer[5]));

         line_type = atoi_b16 (&buffer[7]);

         addr = make32(h_addr,l_addr);

         // If the line type is 1, then data is done being sent
         if (line_type == 1) 
         {
            done = TRUE;
         }
         else if ((addr >= (int32)APPLICATION_START) && (addr < ((int32)0x300000)))
         {
            checksum = 0;  // Sum the bytes to find the check sum value
            for (i=1; i<(buffidx-3); i+=2)
               checksum += atoi_b16 (&buffer[i]);
            checksum = 0xFF - checksum + 1;

            if (checksum != atoi_b16 (&buffer[buffidx-3]))
               do_ACKLOD = FALSE;
            else   
            {
               if (line_type == 0) {
                  // Loops through all of the data and stores it in data
                  // The last 2 bytes are the check sum, hence buffidx-3
                  for (i = 9,dataidx=0; i < buffidx-3; i += 2)
                     data[dataidx++]=atoi_b16(&buffer[i]);
                    
                  rom_w(addr, data, count);
               }
               else if (line_type == 4)
                  h_addr = make16(atoi_b16(&buffer[9]), atoi_b16(&buffer[11]));
            }
         }
      }

      if (do_ACKLOD)
         usb_cdc_putc (ACKLOD);

      usb_cdc_putc(XON);
   }

   usb_cdc_putc (ACKLOD);
   usb_cdc_putc(XON);
   delay_ms(2000);   //give time for packet to flush
   reset_cpu();
}

void main(void) 
{
   /*
   Si A4 esta alto (Estamos pulsándolo, pasamos al bootloader, en otro caso
   a la aplicación)
      */
   if(input(PIN_A4) || read_EEPROM (0)=='B')
   {
      g_InBootloader = TRUE;
      output_high(PIN_C2); // Encendemos el led
      write_eeprom(0,' '); //Borramos la bandera de entrar a bootloader
      usb_cdc_init();
      usb_init();
      while(!usb_enumerated());
      load_program();
   }

   g_InBootloader = FALSE;
  #ASM
   goto APPLICATION_START
  #ENDASM
}

