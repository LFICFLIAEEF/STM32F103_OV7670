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
    uint_16 bytes_per_pixel=3;
    uint_16 byte_count=width*height*bytes_per_pixel;
#endif
#ifdef RGB565//rgb 565
    uint_16 type=1;
    uint_16 bytes_per_pixel=2;
    uint_16 byte_count=width*height*bytes_per_pixel;
#endif
#ifdef RGB555//rgb 555
    uint_16 type=2;
    uint_16 bytes_per_pixel=2;
    uint_16 byte_count=width*height*bytes_per_pixel;
#endif
#ifdef YUV//yuv 422
    uint_16 type=3;
    uint_16 bytes_per_pixel=3;
    uint_16 byte_count=width*height*bytes_per_pixel;
#endif
#ifdef YCBCR//ycbcr 422
    uint_16 type=4;
    uint_16 bytes_per_pixel=3;
    uint_16 byte_count=width*height*bytes_per_pixel;
#endif

//byte_count is the amount of times you need to read a byte in order to form a frame
   
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


//with YCbCr you can skip odd bytes for greyscale image

/*
YCBCR/YUV/GRB output
YCbCr like this?
byte 1 = Cb0
byte 2 = Y0
byte 3 = Cr0
byte 4 = Y1
byte 5 = Cb2
byte 6 = Y2
byte 7 = Cr2
byte 8 = Y3
...
*/
   
void delay(void){
    volatile uint_16 counter=1000; //ideally gives 1000ms delay
    while(counter--);
}


void main(void){
    
    
    const uint_16 chunk_size=49152; //after how many bytes should you dump image
    uint_16 frame[chunk_size/2]; //make an array to store data?
    
    set_registers();
  
    
    uint_16 read_counter=0;
    
    
    
    
    //to force new frame, reset and wait for new HREF? or wait for vsync
    while(!vsinc);
    //call reset_fifo();
    
    for(;;){
        //ov7670 handling code
        
        if(){ //!vsync
            //still need to set a pin for href and see if its pulled high
            if( GPIOA->IDR>=0x1 ){ //when href pulled high
                read_counter++;
                get_frame();

            }
            if(read_counter>=chunk_size){
                dump_chunk();
                //dump stm32 data to pc   
                //and clear memory
            }
        }
        else{ //vsync high
            //reset fifo positions
            //WEN high
            reset_fifo();
        }
        
        
    }//for end
    
}//main end

void reset_fifo(){
    // pull low /WRST AND /RRST 
    // /RE locks the position in the fifo when HIGH
}

void get_pixel_greyscale(){
    if(read_counter%2==0){
        //jump Cb/Cr component
    }else{
        //increment read counter
        
    }
}

void get_pixel(){
    if(read_counter%2){
        frame[read_counter]; //=input register<<8
    }else{
        frame[read_counter-1]; //&=input register
    }
    //increment read counter
}

void get_frame(uint_16 cycles, uint16 chunks){
    
    while(GPIOA->IDR>=0x1){ //while href high
        
        if( !CLOCK ){ //when CLOCK pulled low a new byte was written
                
            //capture ov7670 data
            //maybe store memory address and bitshift the values onto it?
        }
        
    }
}

void dump_chunk(void){
    //dump memory to pc
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
