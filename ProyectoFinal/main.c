#define F_CPU 16000000L // FRECUENCIA DEL SISTEMA
#include <avr/io.h>
#include <util/delay.h>

void main(void)
{
DDRA=0xFE; /**DEFINIR PUERTOS DE ENTRADA Y SALIDA**/
DDRC=0xFF;
DDRB=0XFF;
uint16_t i=0;
uint16_t c=0;
uint16_t a[32];
uint16_t d[32];
uint8_t j=1;
ADMUX=_BV(REFS0); /**PONE COMO VOLTAJE DE REFERENCIA AVCC **/
ADCSRA=_BV(ADEN)| _BV(ADPS0)| _BV(ADPS1)| _BV(ADPS2); /** HABILITAR EL ADC Y DEFINE FRECUENCIA DEL ADC,PREESCALADO DE 128 **/
/** 10M/128 /13 CICLOS NECESARIOS PARA LA CONVERSIÓN, LA CONVERSION DE CADA DATO TARDA 104uS**/
PORTA=0x00;


    while(1)
    {

    while (i<32)
{
    _delay_ms(300);
    ADCSRA=_BV(ADSC); /** ADC START CONVERSION**/
    while(ADCSRA & _BV(ADSC));/** ESPERA LOS CICLOS DE RELOJ NECESARIOS PARA LA CONVERSION DE UN SOLO DATO**/
    if(ADC>800)
    {
        a[i]=1; /** SE QUIERE LLENAR UN VECTOR CON 32 CONVERSIONES, ESTAS SERÁN CODIFICADAS MODULADAS Y ENVIADAS**/
    }else
    a[i]=0;
    i++;
    _delay_ms(499);/** LOS 999,8 mS DE DELAY Y OS 0,185 mS NECESARIOS PARA A CONVERSIÓN DAN AÑ USUARIO UN APROXIMADO DE 1 SEGUNDO PARA INGRESAR CADA DATP¿O**/

   PORTC=j;
   j=j<<1;
   if(j>15) j=1;
   _delay_ms(200);
}
   for(i=1;1<32;i++)
   {

   d[32]=a[0];
   d[32-i]=(a[i-1])^(a[i]); /** cunado el vector a se tiene lleno con los valores ingresados, se  usa la codificacion gray**/
   i++;
   }

   DDRB = _BV(PB3); /** pin B3 salida PWM**/

    TCCR0 = _BV(WGM00) | _BV(WGM01) | _BV(COM01) | _BV(CS01); /** FAst PWM no invertido, preescalado de 8**/
 for(i=0;i++;i<32){
 if(d[i]==1){
    OCR0=240; /**Ciclo útil, el pwm se maneja a 8 bits, valor maximo 255**/
 }else
 OCR0=69;
 }
}

 return 0;
}
