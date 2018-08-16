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

void delay(void){
    volatile int counter=1000; //1000
    while(counter--);
}



void main(void){
    //set registers
    RCC->CFGR|=0xA000000; //set clock to external clock, 1010 0000 0000 0000 0000 0000 0000

    //RCC->APB2ENR|=0x1C //enable gpio A/B/C
    RCC->APB2ENR|=0xC; //enable gpio A/B

    

    GPIOA->CRL|=0x88888888; //set 8 pins as input, with pull-up/down

    GPIOA->ODR|=0xFF; //set pin15 to high, first 8 pins set to pull_down



    GPIOB->CRL|=0x33333033; //set 8 pins as outputs with max 50mhx speed, in push/pull configuration (pb2 has special function, BOOT)

    GPIOB->ODR|=0x1; //set pin0 high
    

    //153600 hrefs?
    uint_16 counter=0;

    for(;;){
        //ov7670 handling code
        if(RCC->IDR>0x1){ //href Pulled high?
            counter++;
        
            if(){
            //capture ov7670 data
            }
        
            if(counter>=153599){
                //export image, maybe by usb?
            }
        }   
    }//for end
}
