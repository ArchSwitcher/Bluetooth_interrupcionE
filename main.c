/*
 * File:   main.c
 * Author: dell
 *
 * Created on March 12, 2020, 11:00 PM
 */


#include <xc.h>
#include "config.h"
#include "USART_Header_File.h"



void Funcion_configuracion_INTB(void);

void main(void) {
    char dato_de_entrada;
    OSCCON = 0x72;                  //RELOJ A 8MHZ =  0b1110010
    TRISDbits.RD0 = 0;              //PUERTO D bit 0 Salida =0 ENTRADA=1
    
    Funcion_configuracion_INTB();      //INTB= Interrupcion externa por puerto b
    
    USART_Init(9600);               //inicio de transmision TRISC6=tx TRISC7=RX
    __delay_ms(50);
    
    USART_SendString("Hola Mundo"); //envia hola mundo a terminal bt
    __delay_ms(50);
        
//    ADCON1bits.PCFG = 0xF;
    
    while(1){
       char dato_de_entrada = USART_ReceiveChar();   //recibe los datos del bt
            
        if(dato_de_entrada == '1'){              //Si recibe el char 1 del BT
            USART_SendString("Entro al IF");   //se Mostrar en terminal BT(ENVIA)
            PORTDbits.RD0 = ~PORTDbits.RD0 ;     //autonegacion para cambio de estado
         }
        else{
            USART_SendString("Envie 1 para cambio de estado");     // Envia dos veces esto 
                                                     //por la funcion USART_ReceveiveChar()
        }
        __delay_ms(100);
        
    }
}

void Funcion_configuracion_INTB(void){
    TRISBbits.RB0 = 1;          //RB0 Salida
    INTCONbits.INT0IE = 1;      //Habilitar INT0 
    INTCONbits.INT0IF = 0;      //FLag 0
    INTCON2bits.INTEDG0 = 0;    //Flanco descendete
    INTCONbits.GIE = 1;         //Interrupcion Globales
}



void __interrupt(low_priority) Aqui_van_las_interrupciones(void){ //MODIFICAR ESTE NOMBRE
    
    if (INTCONbits.INT0F){
        PORTDbits.RD0 = ~PORTDbits.RD0;
        USART_SendString("INTERRUPCION");             //Enviara cuando entre a la 
                                                        //INTERRUPCION
        INTCONbits.INT0F = 0;                       //Reinicio de la bandera de RB0
    }

}













/*tiene una interrupcion externa pull up a PUERTOB = 0 y envia y recibe para controlar 
  1 led y su cambio de estado          */