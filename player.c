/*
 * Bob Somers 2011 
 *   http://bobsomers.com
 * Modified by: Zachary Matthiesen for the MSP432p401R on Keil for Windows
 *
 * Made for the TI MSP430 LaunchPad
 *   http://ti.com/launchpadwiki
 */

#include <msp.h>

#include "player.h"
#include "music.h"

void song_measure_1() {
    play(E4, 1);
    play(E4, 1);
    rest(1);
    play(E4, 1);
    rest(1);
    play(C4, 1);
    play(E4, 1);
    rest(1);
    play(G4, 1);
    rest(3);
    play(G3, 1);
    rest(3);
}

void song_measure_2() {
    play(C4, 1);
    rest(2);
    play(G3, 1);
    rest(2);
    play(E3, 1);
    rest(2);
    play(A3, 1);
    rest(1);
    play(B3, 1);
    rest(1);
    play(As3, 1);
    play(A3, 1);
    rest(1);
}

void song_measure_3() {
    play(G3, 1);
    play(E4, 1);
    rest(1);
    play(G4, 1);
    play(A4, 1);
    rest(1);
    play(F4, 1);
    play(G4, 1);
    rest(1);
    play(E4, 1);
    rest(1);
    play(C4, 1);
    play(D4, 1);
    play(B3, 1);
    rest(2);
}

void song_measure_4() {
    rest(2);
    play(G4, 1);
    play(Fs4, 1);
    play(F4,1);
    play(Ds4, 1);
    rest(1);
    play(E4, 1);
    rest(1);
    play(Gs3, 1);
    play(A3, 1);
    play(C4, 1);
    rest(1);
    play(A3, 1);
    play(C4, 1);
    play(D4, 1);
}

void song_measure_5() {
    rest(2);
    play(G4, 1);
    play(Fs4, 1);
    play(F4,1);
    play(Ds4, 1);
    rest(1);
    play(E4, 1);
    rest(1);
    play(C5, 1);
    rest(1);
    play(C5, 1);
    play(C5, 1);
    rest(3);
}

void song_measure_6() {
    rest(2);
    play(Eb4, 1);
    rest(2);
    play(D4, 1);
    rest(2);
    play(C4, 1);
    rest(7);
}

void song_measure_7() {
    play(C4, 1);
    play(C4, 1);
    rest(1);
    play(C4, 1);
    rest(1);
    play(C4, 1);
    play(D4, 1);
    rest(1);
    play(E4, 1);
    play(C4, 1);
    rest(1);
    play(A3, 1);
    play(G3, 1);
    rest(3);
}

void song_measure_8() {
    play(C4, 1);
    play(C4, 1);
    rest(1);
    play(C4, 1);
    rest(1);
    play(C4, 1);
    play(D4, 1);
    play(E4,1);
    rest(7);
}

void song_play(void) {
    set_bpm(450);
    song_measure_1();
    song_measure_2();
    song_measure_3();
    song_measure_2();
    song_measure_3();
    song_measure_4();
    song_measure_5();
    song_measure_4();
    song_measure_6();
    song_measure_4();
    song_measure_5();
    song_measure_4();
    song_measure_6();
    song_measure_7();
    song_measure_8();
    song_measure_7();
}

void init(void) {
    /* Initialize the timer. */
   SysTick->LOAD = 8040 - 1;
   SysTick->CTRL = 7;

   
    
   NVIC_SetPriority(SysTick_IRQn, 2);
   NVIC_EnableIRQ(SysTick_IRQn);
    __enable_irq();
}

void SysTick_Handler(void) {
   
   if(sound_enabled == 1) {
      P1->OUT ^= SPEAKER;
   }
   
   SysTick->LOAD = current_note;
   ms_elapsed += 1;
}

int main(void) {
    /* Initialize the system. */
    init();

    while (1) {
       /* Red LED on. Green LED off. */
       LED_OUT |= LED_RED;
       LED_OUT &= ~LED_GREEN;
        
       /* Wait for button press. */
       while (BUTTON_IN & BUTTON);
        
       /* Red LED off. Green LED on. */
       LED_OUT &= ~LED_RED;
       LED_OUT |= LED_GREEN;

       song_setup();
       song_play();
    }
    
    return 0;
}
