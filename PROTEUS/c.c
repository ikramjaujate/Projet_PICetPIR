#include <c.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#int_TIMER1

int compteurAjout;
int limite = 5;
int x, i;
int time1;

char buffer[1];
boolean flag = 0; 

#INT_RDA
void  RDA_isr(void) 
{
   buffer[0] = getc();
   flag = 1;
}

int convertisseurSortie(int valeur){
   int sortie = 0;
   if (valeur < 10) {
      sortie = valeur;
   }else {
       x = valeur;
       x = x % 10;
       i = valeur;
       i = i/10;
   
       sortie = x + i*16;
   }
   return sortie;
}



void depasseNombrePermis(int valeur, int limite){
   if(valeur < limite){
            output_high(PIN_C0);
            output_low(PIN_C1);
   }else{
            output_low(PIN_C0);
            output_toggle(PIN_C1);
            delay_ms(10);

  }

}

void main()
{
   setup_low_volt_detect(FALSE);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_spi(FALSE);
   setup_wdt(WDT_OFF);
   setup_timer_1( T1_INTERNAL | T1_DIV_BY_1  );
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   setup_oscillator(False);

   enable_interrupts(INT_RDA); 
   enable_interrupts(GLOBAL);
   output_high(PIN_C0);
   output_low(PIN_C1);
  

   for(;;){
      
      if(flag) {
         flag = 0;
         limite = atoi(buffer);

      }

      // recuperation valeur temps de la sonde
      if(input(PIN_B1) == 0 && input(PIN_B0) == 1){

         compteurAjout += 1;
         delay_ms(1000);
         printf(" %d ", convertisseurSortie(compteurAjout));
         

   

      } else if(input(PIN_B0) == 0 && input(PIN_B1) == 1){

         compteurAjout -= 1;
         delay_ms(1000);
         printf(" %d ", convertisseurSortie(compteurAjout));

   
        
      }
      output_d(convertisseurSortie(compteurAjout));
      //output_d(convertisseurSortie(limite));
      depasseNombrePermis(compteurAjout, limite);
      // attente pour eviter spam
      delay_ms(100);
   } 
}
