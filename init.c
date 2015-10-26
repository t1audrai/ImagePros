#include "init.h"
#include "myPrint.h"
#include <string.h>
#include <sys/ioctl.h>


void init_compute(){
    int t = 1;
    int T = 0;
    for(int R = 599; R>=0; R-- ){
        RADxPI_4[R] = R*CosPi_4;
        for(int angle=99; angle >=0; angle--){
                
                sinRADIUSxPI[R][angle] = R*(PI_1/angle);
                cosRADIUSxPI[R][angle] = R*(PI_1/angle);
        }
         
       /* if(t >= 6){
            t = 1;
            T++;
            loadBar(T,599,1, 30);
        }
        else t++;*/
        
        loadBar(t++,599,1,50);
       
    }
   
    
    
}