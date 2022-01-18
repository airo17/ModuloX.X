/* 
 * File:   main.c
 * Author: Alexis Ramirez
 *
 * Created on January 18, 2022, 9:40 AM
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * 
 */

void EUSART_WriteByte(const uint8_t txData);
void Enviar_Cadena(const uint8_t *prtDatos_TX, uint8_t tamanio);
uint8_t UART_Read();
char UART_Read_Text(uint8_t *Output, uint8_t length);

char serial_cadena[] = {0x03,0x04,0x05};
uint8_t mandar_mensaje = 0;
uint8_t Output;
uint8_t length;

void __interrupt() Interrupciones(void){
    /*if (PIR1bits.RC1IF == 1 && PIE1bits.RC1IE == 1){
        PORTAbits.RA0 ^= 1;
        PORTB = UART_Read();
        mandar_mensaje = 1;
    }*/
}

int main(int argc, char** argv) {
    
    // <editor-fold defaultstate="collapsed" desc="Configuracion hardware interno PIC">
     //Configuracion inicial de los pines
    ANSELA = 0x00;                                  //Configuracion de pines como digitales
    ANSELB = 0x00;                                  //Configuracion de pines como digitales
    ANSELC = 0x00;                                  //Configuracion de pines como digitales
    
    //Configuracion de entradas y salidas
    TRISA = 0x00;                                   //Todos como salida
    TRISB = 0x00;                                   //Todos como entrada
    TRISC = 0x00;
    //TRISC = 0b01000000;                              //C6 como entrada Todos como salida
    
    //Estado inicial del pin
    PORTA= 0x00;                                    //Todos en cero
    PORTB= 0x00;                                    //Todos en cero
    PORTC= 0x00;                                    //Todos en cero
    
    //Configuracion del oscilador
    
    //Habilitar interrupciones globales
    
    //******Configuracion EUSART*****
    //Configuracon de registros de envio
    TX1STAbits.TX9 = 0;                             //Selecciona la transmición de 8 bits
    TX1STAbits.TXEN = 1;                            //Activada la transmision
    TX1STAbits.SYNC = 0;                            //Asincrono
    TX1STAbits.BRGH = 1;                            //High Baudrate
    
    //Configuracion de registros de recepcion
    RC1STAbits.SPEN = 1;                            //Habilita el puerto serial
    RC1STAbits.RX9 = 0;                             //Recepcion de 8 bits, 1 PAra recepcion de 9 bits
    RC1STAbits.SREN = 0;                            //No importa en asincrona
    RC1STAbits.CREN = 1;                            //Habilita la recepcion
    
     //Configuracion de registros del baudrate
    
    // </editor-fold>
    
    while (1){
        
        EUSART_WriteByte(0x8F);
        EUSART_WriteByte(0x81);
        
    }
    
    return (EXIT_SUCCESS);
}

void EUSART_WriteByte(const uint8_t txData)
{   
    while(!TXSTA1bits.TRMT);            //****Cuando esta en 0 se mete al bucle del while
    TXREG1 = txData;                    // Write the data byte to the USART.
}

void Enviar_Cadena(const uint8_t *prtDatos_TX, uint8_t tamanio)
{
    uint8_t i = 0;
    
    for (i = 0; i <= tamanio-1; i++)
    {
        EUSART_WriteByte(prtDatos_TX[i]);
    }
}

uint8_t UART_Read(){
    //while(!PIR1bits.RC1IF);
    if(RCSTA1bits.OERR == 1){
        // EUSART1 error - restart
        RCSTA1bits.CREN = 0; 
        RCSTA1bits.CREN = 1; 
    }
    return RCREG1;
}

char UART_Read_Text(uint8_t *Output, uint8_t length){
	uint8_t i = 9;
	for(uint8_t i=0;i<length;i++)
		Output[i] = RCREG1;
}