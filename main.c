#include <msp430.h> 

/*
 * main.c
 */
#include <msp430.h>
#include "msp430F135.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <INTRINSICS.H>

//DEFINO LOS NOMBRE PARA QUE SEA MAS FACIL RECORDAR

#define 	SENSOR_AR P6IN &= BIT0 //SENSOR ARBOL DE LEVA
#define 	SENSOR_CI P6IN &= BIT1 //SENSOR CIGUEÑAL

void CHISPA(short int contador);
void EXPLOSION(short int contador);
void ESCAPE(short int contador);
void ADMISION(short int contador);
void COMPRESION(short int contador);
void APAGAR();

void main(void) {

	//DEFINO VARIABLES
	short int contador = 0;

	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;

	// CONFIGURACION DEL CRISTAL PARA EL TIMER A
	BCSCTL1 = (DIVA_0); //CONFIGURA EL OSCILADOR DE BAJA FRECUENCIA DIVA0=DIVISOR POR 1, DCOCTL = DCO0 + DCO1 + DCO2; // Max DCO
	BCSCTL1 = RSEL0 + RSEL1 + RSEL2; // XT2on, max RSEL
	BCSCTL2 |= SELS; // SMCLK = XT2

//*********Configuracion de los pines**********

	//PINES DE ENTRADA DE DATOS
	P6DIR &= BIT0; //SENSOR ARBOL DE LEVA
	P6DIR &= BIT1; //SENSOR CIGUEÑAL
	P6DIR &= BIT2; //

//CONFIGURO LOS PINES DE SALIDA (PARA LUCES DE MOTOR) P1DIR |= BIT0;
	P1DIR |= BIT2;  //CILINDRO 1 AZUL
	P1DIR |= BIT3;  //CILINDRO 1 ROJO
	P1DIR |= BIT4;  //CILINDRO 1 VERDE
	P1DIR |= BIT5;  //CILINDRO 1 EXTRA

	P2DIR |= BIT0;  //CILINDRO 3 AZUL
	P2DIR |= BIT1;  //CILINDRO 3 ROJO
	P2DIR |= BIT2;  //CILINDRO 3 VERDE
	P2DIR |= BIT3;  //CILINDRO 3 EXTRA

	P3DIR |= BIT1;  //CILINDRO 5 AZUL
	P3DIR |= BIT2;  //CILINDRO 5 ROJO
	P3DIR |= BIT3;  //CILINDRO 5 VERDE
	P3DIR |= BIT5;  //CILINDRO 5 EXTRA

	P5DIR |= BIT4;  //CILINDRO 7 AZUL
	P1DIR |= BIT0;  //CILINDRO 7 ROJO
	P1DIR |= BIT1;  //CILINDRO 7 VERDE
	P1DIR |= BIT7;  //CILINDRO 7 EXTRA

	// Configuracion Inicial Timer A
	TACTL = (TASSEL_1 + ID_0 + MC_2); //TASSEL ELIGE LA FRECUENCIA DEL AUXCLOCK, ID ES DIVISOR, MC MODO CONTROL PUESTO ENCONTINUO. TAIE INTERRUP ENE A
	//TACCTL0 = (CM_2 + CAP + CCIE); //definimos la entrada del captura ccis_x elegimos la entrada cci0a

	//CONFIGURACION EXTRA DE PINES, HAY QUE ASIGNARLES UNA FUNCION
	//P1SEL |= BIT1; //Bit = 0: I/O Function is selected for the pin Bit = 1: Peripheral module function is selected for the pin

	//************************************ secuencia de encendido de luces motor CILINDRO 1**************************************************************************************
	/*El cilindro 1 le corresponen los tiempos junto al contador como sigue>
	 contador :  0-explosión
	 1-escape
	 2-admision
	 3-compresión

	 */

	if ((SENSOR_AR == 1) && (SENSOR_CI == 1)) { //LA CHISPA VA A ESTAR MIENTRAS ESTEN EN ESE ESTADO, NO HACE FALTA RETERLA.
		contador = 0;
		CHISPA(contador);
	}

	if ((SENSOR_AR == 0) && (SENSOR_CI == 1)) { //PROBLEMA QUE CUANDO PASE POR AHI EL TIMEPO DEL BOTON ES LARGUISIMO Y VA A CONTAR MUY RAPIDO. HAY QUE VER COMO LIMITAR ESO.LIMITAR CON FOR
		contador++;
	while (SENSOR_CI) { //ESTA HECHO PARA RETENER MIENTRAS EL PULSADOR SE QUEDE AHI.
		EXPLOSION(contador);
	}
}

if (contador == 0) { //explosion cilindro 1
	EXPLOSION(contador);

}
if (contador == 1) {  //escape
	ESCAPE(contador);
}
if (contador == 2) { //admision
	ADMISION(contador);

}
if (contador == 3) { //compresión
	COMPRESION(contador);

}
//************************************** fin secuencia cilindro 1 *************************************************************************************************************

//************************************ secuencia de encendido de luces motor CILINDRO 2**************************************************************************************

//************************************** fin secuencia cilindro 1 *************************************************************************************************************

}

void CHISPA(short int contador) {

if (contador == 0) {
	P1OUT |= BIT2;  //CILINDRO 1 AZUL
	P1OUT |= BIT3;  //CILINDRO 1 ROJO
	P1OUT |= BIT4; //CILINDRO 1 VERDE //CONFIGURO LA CHISPA ES RGB.
}
if (contador == 1) { //otro cilindro y asi.

}
}
//HAY QUE CONFIGURAR BIEN LOS LEDS
//
void EXPLOSION(short int contador) {
if (contador == 0) {
	P1OUT |= BIT2;
	P1OUT &= ~ BIT3;
	P1OUT &= ~ BIT4;
	P1OUT &= ~ BIT5;
}
}
void COMPRESION(short int contador) {
if (contador == 0) {
	P1OUT |= BIT2;
	P1OUT &= ~ BIT3;
	P1OUT &= ~ BIT4;
	P1OUT &= ~ BIT5;
}
}
void ESCAPE(short int contador) {
if (contador == 0) {
	P1OUT |= BIT2;
	P1OUT &= ~ BIT3;
	P1OUT &= ~ BIT4;
	P1OUT &= ~ BIT5;
}
}
void ADMISION(short int contador) {
if (contador == 0) {
	P1OUT |= BIT2;
	P1OUT &= ~ BIT3;
	P1OUT &= ~ BIT4;
	P1OUT &= ~ BIT5;
}
}
void APAGAR() { // Con esto apagaria todos los leds

}
