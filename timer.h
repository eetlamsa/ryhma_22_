#ifndef TIMER_H
#define TIMER_H



// Ajastimen alustus
void timer1_init(uint16_t compareMatch, uint16_t prescaler);

// Ajastimen pysäytys
void timer1_stop();

#endif

