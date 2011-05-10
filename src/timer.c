/* bkerndev - Bran's Kernel Development Tutorial
*  By:   Brandon F. (friesenb@gmail.com)
*  Desc: Timer driver
*
*  Notes: No warranty expressed or implied. Use at own risk. */
#include <system.h>

/* This will keep track of how many ticks that the system
*  has been running for */
int timer_ticks = 0;
int uptime_secs;
/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler(struct regs *r) //@
{
    /* Increment our 'tick count' */
    timer_ticks++;
    uptime_secs=(int)(timer_ticks/18.222);
}

/* This will continuously loop until the given time has
*  been reached */
void timer_wait(int ticks) //@
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install() //@
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}
