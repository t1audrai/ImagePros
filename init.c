#include "init.h"
#include "myPrint.h"
#include <string.h>
#include <sys/ioctl.h>
#include <math.h> 


void init_compute(){
    int t = 1;
    //int T = 0;
    for(int R = 599; R>=0; R-- ){
     
        
        float angle = _2PI/99;
        int pas =0;
        while(pas < 100){
                
                sinRADIUSxPI[R][pas] = (int) (R*sin(angle)+0.5);
                cosRADIUSxPI[R][pas] = (int) (R*cos(angle)+0.5);
                angle += angle;
                pas++;
        }
         
        /*if(t >= 6){
            t = 1;
            T++;
            loadBar(T,599,1, 30);
        }
        else t++;*/
        
        loadBar(t++,599,1,50);
       
    }
    
   
    
    
}
