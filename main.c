/* 
 * File:   main.c
 * Author: Alexis Ramirez
 *
 * Created on January 18, 2022, 9:40 AM
 */

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

void __interrupt Interrupciones(){
    if (PIR1bits.RC1IF == 1 && PIE1bits.RC1IE == 1){
        PORTAbits.RA0 ^= 1;
        PORTB = UART_Read();
        mandar_mensaje = 1;
    }
}
int main(int argc, char** argv) {

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