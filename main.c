struct  RCC_REGISTER {
    //unsigned int = 32 bits in stm
    volatile unsigned int CR;
    volatile unsigned int CFGR;
    volatile unsigned int CIR;   
    volatile unsigned int APB2RSTR;
    volatile unsigned int APB1RSTR;
    volatile unsigned int AHBENR;
    volatile unsigned int APB2ENR;
    volatile unsigned int APB1ENR;
    volatile unsigned int BDCR; 
    volatile unsigned int CSR;
}

struct GPIO{
    volatile unsigned int CRL; //first 8 pins
    volatile unsigned int CRH; //last 8 pins
    volatile unsigned int IDR;
    volatile unsigned int ODR;
    volatile unsigned int BSRR;
    volatile unsigned int BRR;
    volatile unsigned int LCKR;
}

#define RCC (struct RCC_REGISTER*) 0x40021000
#define GPIOA (struct GPIO*) 0x40010800
#define GPIOB (struct GPIO*) 0x40010C00
//#define GPIOC (struct GPIO*) 0x40011000



#define VGA

#ifdef VGA
    uint_16 width=640;
    uint_16 height=480;
#endif

#ifdef QVGA
    uint_16 width=320;
    uint_16 height=240;
#endif
#ifdef CIF
    uint_16 width=352;
    uint_16 height=240;
#endif
#ifdef QCIF
    uint_16 width=176;
    uint_16 height=144;
#endif



#define YUV

#ifdef GRB//grb 422
    uint_16 type=0;
    uint_16 depth=8;
#endif
#ifdef RGB565//rgb 565
    uint_16 type=1;
    uint_16 depth=8;
#endif
#ifdef RGB555//rgb 555
    uint_16 type=2;
    uint_16 depth=15;
#endif
#ifdef YUV//yuv 422
    uint_16 type=3;
    uint_16 depth=8;
#endif
#ifdef YCBCR//ycbcr 422
    uint_16 type=4;
    uint_16 depth=8;
#endif
   
/* RGB 565 output
byte 1 = 5 bits/Red, 3bits/Green
byte 2 = 3 bits/Green, 5bits/Blue
byte 3 = 5 bits/Red, 3bits/Green
byte 4 = 3 bits/Green, 5bits/Blu
...
*/

/* RGB 565 output
byte 1 = first bit useless, 5 bits/Red, 3bits/Green
byte 2 = 2 bits/Green, 5bits/Blue
byte 3 = first bit useless, 5 bits/Red, 3bits/Green
byte 4 = 2 bits/Green, 5bits/Blue
...
*/

/*
YCBCR output
like this?
byte 1 = Cb0
byte 2 = Y0
byte 3 = Cr0
byte 4 = Y1
byte 5 = Cb2
byte 6 = Y2
...

or like this?
byte 1 = 2 bits/Cb0, 4 bits/Y0, 2 bits/Cr0
byte 2 = 2 bits/Cb0, 4 bits/Y0, 2 bits/Cr0
...
*/


void delay(void){
    volatile uint_16 counter=1000; //1000
    while(counter--);
}


void main(void){
    
    set_registers();
  
    
    uint_16 href_counter=0; //calculate with the format and color enconding
    uint_16 chunks=0; //calculate how many parts should you divide image for output
    
    
    uint_16 new_frame=0;
    //to force new frame, reset and wait for new HREF? or wait for vsync
    
    // pull low /WRST AND /RRST 
    // /RE locks the data in place when HIGH
    
    for(;;){
        //ov7670 handling code
        
        //wait for VSYNC pulled high, and enable WEN
        
        if(){ //vsync high
            //reset fifo positions
            //WEN high
        }
        
        
        //still need to set a pin for href and see if its pulled high
        if( GPIOA->IDR>=0x1 ){ //when href pulled high
            get_frame(counter,chunks);
        }
        
    }//for end
}//main end

void get_frame(uint_16 cycles, uint16 chunks){
    
    while(cycles){
        
        if(){ //when CLOCK pulled low a new byte was written
                
            //capture ov7670 data
            //maybe store memory address and bitshift the values onto it?
        }
        
        
    }

    if(counter<=0){ //depending on the image size divide it in chunks
            //export image, maybe by usb?
    }
}

void output_chunk(void){

}

void set_registers(void){
    
    
    //set registers
    RCC->CFGR|=0xA000000; //set clock to external clock, 1010 0000 0000 0000 0000 0000 0000

    //RCC->APB2ENR|=0x1C //enable gpio A/B/C
    RCC->APB2ENR|=0xC; //enable gpio A/B

    
    //need to set a pin for 

    
    GPIOA->CRL|=0x88888888; //set 8 pins as input, with pull-up/down

    GPIOA->ODR|=0xFF; //set pin15 to high, first 8 pins set to pull_down



    GPIOB->CRL|=0x33333033; //set 8 pins as outputs with max 50mhx speed, in push/pull configuration (pb2 has special function, BOOT)

    GPIOB->ODR|=0x1; //set pin0 high
    

}
