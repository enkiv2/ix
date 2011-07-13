#ifndef timer_h
#define timer_h
extern void timer_wait(int ticks);
extern void timer_install();
extern void displaytime();
extern int request_atomicity(int);
extern void yield();
extern int spawn(void(*fn)(int));
extern int fork();
extern void kill(int);
extern int renice(int, int);
#define MAX_PROCESSES 512
#endif

