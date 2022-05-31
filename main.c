/*
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "h_bridge.h"
//#include "servo.h"
/*
#define LED1                 PG1 // knipperled pin 40
#define LED2                 PG2 // knipperled pin 39

#define KNOP_OMHOOG          PL1 //knop1 pin 48
#define KNOP_OMLAAG          PL0 //knop2 pin 49
#define KNOP_beveileging     PB3 //knop3 pin 50
#define KNOP_KLEMMEN         PB2 //knop4 pin 51
#define END_SWITCH_ONDER     PL5 // end switch 1 pin 44
#define END_SWITCH_MIDDEL    PL4 // end switch 2 pin 45
#define END_SWITCH_BOVEN     PL3 // end switch 3 pin 46
#define ZOEMMER              PC0 // zoemmer pin 37
#define NOODSTOP             PC7 // noodstop pin 30
//#define MOTOR_REM            PC1 //h-brugrem pin 36
/*
#define schildknop_S1        PF1
#define schildknop_S2        PF2
#define schildknop_S3        PF3

#define schildled_D1         PB7
#define schildled_D2         PB6
#define schildled_D3         PB5
#define schildled_D4         PB4
*/
#define _BV(bit) (1 << (bit))
/*
void init_timer(void)
{
    TCCR2A = 0;
	TCCR2B = (0<<CS22) | (1<<CS21) | (1<<CS20);
	// Interrupts on OCA, and OVF
	TIMSK2 = (1<<TOIE2);
}

void init(void)
{
    init_h_bridge();
    init_servo();
    init_timer();

    DDRG |= _BV(LED1);
    DDRG |= _BV(LED2);
    DDRC |= _BV(ZOEMMER);
    //DDRC |= _BV(MOTOR_REM);


    PORTG   |= _BV(LED1);
    PORTG   |= _BV(LED2);
    PORTC   |= _BV(ZOEMMER);
    //PORTC   |= _BV(MOTOR_REM);

    /*DDRB |= _BV(schildled_D1);
    DDRB |= _BV(schildled_D2);
    DDRB |= _BV(schildled_D3);
    DDRB |= _BV(schildled_D4);
    PORTB   |= _BV(schildled_D1);
    PORTB   |= _BV(schildled_D2);
    PORTB   |= _BV(schildled_D3);
    PORTB   |= _BV(schildled_D4);

    DDRL &= ~_BV(KNOP_OMHOOG);
    DDRL &= ~_BV(KNOP_OMLAAG);
    DDRB &= ~_BV(KNOP_beveileging);
    DDRB &= ~_BV(KNOP_KLEMMEN);
    DDRL &= ~_BV(END_SWITCH_BOVEN);
    DDRL &= ~_BV(END_SWITCH_MIDDEL);
    DDRL &= ~_BV(END_SWITCH_ONDER);
    DDRC &= ~_BV(NOODSTOP);

    /*DDRF &= ~_BV(schildknop_S1);
    DDRF &= ~_BV(schildknop_S2);
    DDRF &= ~_BV(schildknop_S3);

}

static int counter;
static int knipperled_aan;
ISR(TIMER2_OVF_vect)
{
    if (knipperled_aan==1)
    {
        if (counter < 1600)
        {
        counter++;
        }
        else
        {
        PORTG ^= (1<<LED1);
        PORTG ^= (1<<LED2);
        counter = 0;
        }
    }
    if (PINC & _BV(NOODSTOP)== 0)
    {
        h_bridge_set_percentage(0);
       // PORTC |= (1<<MOTOR_REM);
    }
}

void motor_omhoog (void)
{
    if ((PINL & _BV(KNOP_OMHOOG))== 0) //&& (PINF & _BV(NOODSTOP)== 1)) //motor omhoog/ gevarengeluid bij knop omhoog ingedrukthouden
        {
        h_bridge_set_percentage(100);
        //PORTC &= ~(1<<MOTOR_REM);
        PORTC &= ~(1<<ZOEMMER);         // zoemer
        }
}

void motor_omlaag (void)
{
    if ((PINL & _BV(KNOP_OMLAAG))== 0) //motor omhoog/ gevarengeluid bij knop omhoog ingedrukthouden
        {
        h_bridge_set_percentage(-100);
        PORTC &= ~(1<<ZOEMMER);         // zoemer
        //PORTC &= ~(1<<MOTOR_REM);
        }
}

void motor_uit (void)
{
    h_bridge_set_percentage(0);
    PORTC |= (1<<ZOEMMER);
    //PORTC |= (1<<MOTOR_REM);
}
*/
int main(void)
{

    /*
    init();
    sei();
    int stand = 0;      //omhoog
    int stand2 = 0;     //omlaag
    while(1)
    {
    switch(stand)
    {
    case 0:
       if  ((PINL & _BV(END_SWITCH_ONDER)) == 0)//steiger vast pakken bij knop omhoog daarna kleine delay
        {
        //gevaren led knipperen
        motor_omlaag();
        }
        else
        {
        motor_uit();
        }
        if ((PINL & _BV(END_SWITCH_ONDER) == 1))
        {
        stand++;
        }
    break;
    case 1:
        if (((PINL & _BV(KNOP_KLEMMEN))== 0) && ((PINL & _BV(END_SWITCH_ONDER) == 1)))
        {
        knipperled_aan = 1;
        servo_grijper_set_percentage(100);
        servo_grijper2_set_percentage (-100);

        stand++;
        stand2 = 100;
        }
    break;
    case 2:
        motor_omhoog();
        if ((PINL & _BV(END_SWITCH_BOVEN))==1)  // bovenste switch
        {
        motor_uit();
        stand++;
        }
    break;
    case 3:
        motor_omlaag();
            if ((PINB & _BV(KNOP_beveileging))==0) // midde swicht
            {
            motor_uit();
            stand++;
            }
    break;
    case 4:
        if ((PINB & _BV(KNOP_KLEMMEN))==0) // knop servo
        {
            servo_grijper_set_percentage(-100);
            servo_grijper2_set_percentage(100);
            stand++;
        }
    break;
    case 5:
        if ((PINL & _BV(KNOP_OMLAAG))==0) // motor omlaag
        {
            motor_omlaag();
        }
        if ((PINL & _BV(END_SWITCH_ONDER))==1) // onderste switcht
        {
            motor_uit();
            stand = 0;
            stand2 =0;
        }
    break;
    }
    switch(stand2)
    {
    case 0:
        if ((PINL & _BV(KNOP_OMHOOG))== 0)//steiger vast pakken bij knop omhoog daarna kleine delay
        {
        motor_omhoog();
        knipperled_aan = 1;

        }
        else
        {
            motor_uit();
        }
        if ((PINB & _BV(KNOP_beveileging))==0)
        {
            stand = 100;
            stand2++;
        }
    break;
    case 1:
        if ((PINB & _BV(KNOP_KLEMMEN))== 0)
        {
        servo_grijper_set_percentage(50);
        servo_grijper2_set_percentage (-50);
        stand2++;
        }
    break;
    case 2:
        motor_omhoog();
        if ((PINL & _BV(END_SWITCH_BOVEN))==1)  // bovenste switch
        {
        motor_uit();
        stand2++;
        }
    break;
    case 3:
        if ((PINL & _BV(KNOP_OMLAAG))==0) // motor omlaag
        {
            motor_omlaag();
        }
        if ((PINL & _BV(END_SWITCH_ONDER))==1) // onderste switcht
        {
            motor_uit();
            stand2++;
        }
    case 4:
         if ((PINL & _BV(KNOP_KLEMMEN))== 0)
        {
        servo_grijper_set_percentage(0);
        servo_grijper2_set_percentage (0);
        stand2 = 0;
        stand = 0;
        }
    break;
    }*/
    init_h_bridge();
    while(1)
    {

    h_bridge_set_percentage(50);
    }
    return 0;
}
