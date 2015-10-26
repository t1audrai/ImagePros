#include "init.h"

#include <string.h>
#include <sys/ioctl.h>

void init_compute(){
    
    for(int R = 599; R>=0; R-- ){
        RADxPI_4[R] = R*CosPi_4;
        for(int angle=99; angle >=0; angle--){
                
                sinRADIUSxPI[R][angle] = R*(PI_1/angle);
                cosRADIUSxPI[R][angle] = R*(PI_1/angle);
        }
        
    }
    
    
}