#include "mbed.h"
#include "rtos.h"
#include "hcsr04.h"
#include "DCMotor.h"


typedef unsigned int ui;
HCSR04  sensorFront(p25,p6);
DigitalOut enable(p7);  //Habilitación del puente H
DCMotor Motor1(p21,p22,p23);
ui dist;

void switch_sensor(void const *args){ 
    while(1){
        sensorFront.start();
        dist = sensorFront.get_dist_cm();
        //Thread::wait(500);
    }
}

int main() {
    Thread hilo(switch_sensor);
    bool state = true;
    while(true){
        printf("%d\n",dist);
        wait_ms(500);
        if(dist <= 20 && state){
            enable = 1;
            Motor1.driveIt(100);
            state = false;
        }else if(dist > 20 && !state){
            state = true;
            Motor1.driveIt(0);
        }
    }
}
