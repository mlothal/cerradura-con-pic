#include <16F877.h>
#DEVICE ADC = 10
#use delay (clock=4M)
#FUSES XT,NOWDT,NOPROTECT,NOLVP,NODEBUG
 
//==============================================================================
//********************* DEFINIR PINES DE CONTROL LCD ***************************
//==============================================================================
#define LCD_DATA_PORT getenv("SFR:PORTC")
 
#include <lcd.c>
//=============================================================================
 
// A TRAVES DE LA RAM
 
#BYTE PORTA=0xf80
#BYTE PORTB=0xf81
#BYTE PORTC=0xf82
#BYTE PORTD=0xf83
#BYTE PORTE=0xf84
 
#use fast_io(A)
#use fast_io(B)
#use fast_io(C)     //   con esta instruccion evitamos que
#use fast_io(D)     //   se este configurando cada vez que usamos
#use fast_io(E)     //   alguna instruccion de entrada o salida
 
 
 
//!#bit puerta1 = porta.3
//!#bit puerta2 = porta.4
//==============================================================================
//*********************** VECTOR DE INTERUCCION ********************************
//==============================================================================
       
//#int_rb           // Cambio de estado RB4 -RB7
 
int16 k=0, Key, mun=0,j=0,i=0;
 
#int_RB              
 
void RB_isr(void)       //función de interrupción  RB4 -RB7
{ 
 
   disable_interrupts(INT_RB);
 
   IF (INPUT(PIN_B4)==0)      // Colummna 4
   {
      PORTB = 0B0111;         // Fila 1
      if (INPUT(PIN_B4)==0)  j--;      //'A';
       
      PORTB = 0B1011;         // Fila 2
      if (INPUT(PIN_B4)==0)  j++;       //'B';
       
      PORTB = 0B1101;         // Fila 3
      if (INPUT(PIN_B4)==0) {k=0;i++;};     //'C';
       
                
     PORTB = 0B1110;         // Fila 4
      if (INPUT(PIN_B4)==0)  Key = 14;       // 'D';
       
   }
    IF (INPUT(PIN_B5)==0)      // Colummna 3
   {
      PORTB = 0B0111;         // Fila 1
      if (INPUT(PIN_B5)==0)  Key = 3;
       
      PORTB = 0B1011;         // Fila 2
      if (INPUT(PIN_B5)==0)  Key = 6;
       
      PORTB = 0B1101;         // Fila 3
      if (INPUT(PIN_B5)==0)  Key = 9;
       
      PORTB = 0B1110;         // Fila 4
      if (INPUT(PIN_B5)==0)  Key = 24;          // '#';
       
   }
    IF (INPUT(PIN_B6)==0)      // Colummna 2
   {
      PORTB = 0B0111;         // Fila 1
      if (INPUT(PIN_B6)==0)  Key = 8;
       
      PORTB = 0B1011;         // Fila 2
      if (INPUT(PIN_B6)==0)  Key = 5;
       
      PORTB = 0B1101;         // Fila 3
      if (INPUT(PIN_B6)==0)  Key = 2;
       
      PORTB = 0B1110;         // Fila 4
      if (INPUT(PIN_B6)==0)  Key = 0;
       
   }
    IF (INPUT(PIN_B7)==0)      // Colummna 1
   {
      PORTB = 0B0111;         // Fila 1
      if (INPUT(PIN_B7)==0)  Key = 1;
       
      PORTB = 0B1011;         // Fila 2
      if (INPUT(PIN_B7)==0)  Key = 4;
       
      PORTB = 0B1101;         // Fila 3
      if (INPUT(PIN_B7)==0)  Key = 7;
       
      PORTB = 0B1110;         // Fila 4
      if (INPUT(PIN_B7)==0)  Key = 15;          //'X';
       
   }
    
  
 
   if(k==1)
   mun=key;
    
   if(k==2)
   mun=(mun*10)+key;
    
   if(k==3)
   mun=(mun*10)+key;
   
   if(k==4)
   mun=(mun*10)+key;
     
    
   delay_ms(500);
   k++;
  if (k>4)k=0;
     
    
   
   
   PORTB = 0b11110000;
   enable_interrupts(INT_RB);  
    
    
 
}
//==========================================================================
//********** Programa Principal ********************************************
//==========================================================================
void main ()
{
 
   int16 medicion,h;
   float p,l;
    
    
   SET_TRIS_a (0b11111111);
   SET_TRIS_b(0b11110000);
   SET_TRIS_d(0);   
   SET_TRIS_c(0);
   SET_TRIS_e(0);
    
   portd=0;
   portb = 0b11110000;
   
   port_b_pullups(true); 
   enable_interrupts(INT_RB);       //habilita interrupción RB4-RB7 
   enable_interrupts(global);
 
    
    
   //===== Configuracion del ADC ======
   set_adc_channel (0);
   setup_adc (adc_clock_internal);
    
    
       lcd_init();
       
       
     
     
  
while (true)
  
{
if(i==1)
{
  
        
   printf(lcd_putc, "\f CONFIGURE TEMP ");
   printf(lcd_putc, "\n TEMP MAX %Lu",mun);
      
   delay_ms(1000);
    
  if (i>1)i=0;
  }   
 
 
if(i==0)
{
 
if(j==1)
{ set_adc_channel(0);
   delay_us(20);
   medicion = read_adc();
   p = 0.14662756598 * medicion;
   delay_ms(10);
printf(lcd_putc, "\f TEMPERATURA");
printf(lcd_putc, "\n %.2f C", p);
delay_ms(200);
if (p>mun&&mun!=0)portc=255;
else portc=0;
}
 

 

 
}
if(j==4)


   


 
if(j<1) j=1;
if(j>4) j=4;
}}
 

