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
//#define GPIOB (struct GPIO*) 0x40010C00
//#define GPIOC (struct GPIO*) 0x40011000

void delay(void){
    volatile int counter=1000; //1000
    while(counter--);
}



void main(void){
    //set registers
    RCC->CFGR|=0xA000000; //set clock to external clock, 1010 0000 0000 0000 0000 0000 0000

    //RCC->APB2ENR|=0x1C //enable gpio A/B/C
    RCC->APB2ENR|=0x4; //enable gpioA


    GPIOA->CRL|=0x8; //input, with pull-up/down, 1000
    GPIOA->ODR|=0x1; //set output to 1, putting pin to pull_down

    //RCC->IDR first bit == first pin input, 15 = last pin input

    



    for(;;){
        //ov7670 handling code
    }
}