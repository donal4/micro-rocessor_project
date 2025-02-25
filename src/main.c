//test
#include <stm32f031x6.h>
#include "display.h"
void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);

volatile uint32_t milliseconds;

const uint16_t lilguy[]={16384,0,0,24584,8,57600,48959,48903,65287,56895,16640,16656,8192,32768,32768,16384,0,24576,0,0,49152,33024,48967,65303,40727,65351,8704,0,24576,32776,16384,32768,32768,0,264,0,24832,25344,45314,46082,5122,29186,8960,24832,8448,0,40960,40960,16384,16384,0,512,1024,32662,16246,40797,48997,49005,24470,1024,512,8456,24576,49152,49152,0,57600,1024,46097,14592,47872,23552,7168,7168,56064,62993,1024,0,57344,57344,256,256,1024,2048,6161,6912,39944,48400,56592,7440,31744,30992,2048,768,256,16640,768,1536,2816,46352,13841,40910,3328,55072,54816,65478,3840,63248,30232,2816,1536,1024,1280,53553,30496,63512,46873,57294,57302,54313,62249,16350,24526,55056,31000,22048,12585,1536,1280,28985,2816,5656,38928,63504,5665,30001,13361,46368,39448,64016,54808,2816,62009,1536,1024,1280,1792,38193,30736,4096,3584,3072,2816,3328,39688,47624,38185,1792,1280,1280,16640,256,512,1536,30489,4096,3840,63520,3072,3840,15368,64024,1536,256,8704,512,32768,16384,16384,768,61985,47137,63496,6416,22545,46600,63768,46368,768,32768,8192,16384,0,40960,16384,256,768,1792,30489,30984,14600,55329,2304,1024,256,49152,8192,0,264,0,16384,57344,0,1024,5153,3584,3840,62488,1024,256,0,0,16384,8192,0,8192,16384,0,768,52801,12345,1792,2048,4145,3641,768,256,8192,0,0,0,0,40960,256,1024,1280,1024,1024,1280,1536,1280,1024,256,0,40960,0,};

const uint32_t sprite[]={0,0,0,0,18457,18977,53322,20562,28754,11049,0,0,0,0,0,0,0,0,0,0,58120,50448,6284,31124,22932,35897,0,0,0,0,0,0,0,0,0,0,0,16904,53082,5235,61010,25352,0,0,0,0,0,61307,0,0,0,18721,20025,3377,19249,52529,36409,20025,36409,52529,16384,0,22197,28804,0,0,42520,28217,52273,43561,3377,3377,44857,35369,44353,53338,16384,7134,22990,0,0,0,30339,46723,16904,2081,34848,20025,28217,2857,43049,63628,11363,16119,58136,0,0,0,14476,46459,0,44601,53049,3897,44601,51753,0,31124,23774,53644,0,0,0,0,22932,34857,0,44081,44081,34592,59945,58904,0,63628,22676,32768,0,0,0,0,45939,0,57352,17753,1658,18042,9850,41776,0,49672,47244,0,0,0,0,0,0,0,0,34417,9850,9561,33873,17481,0,0,0,0,0,0,0,0,0,0,0,9850,9017,0,8480,49976,0,0,0,0,0,0,0,0,0,0,0,9850,41240,0,8480,25953,0,0,0,0,0,0,0,0,0,0,0,9850,16656,0,49432,50249,0,0,0,0,0,0,0,0,0,0,0,58713,280,0,8704,20017,18977,49928,0,0,0,0,0,0,0,0,33024,2593,43297,49408,0,60721,3113,10265,0,0,0,0,0,0,0,0,41736,11825,44849,17936,0,0,0,0,0,0,0,0,};

const uint16_t deco1[]=
{
0,0,0,0,4,4,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,18457,18977,53322,20562,28754,11049,0,0,0,0,0,0,0,0,0,0,58120,50448,6284,31124,22932,35897,0,0,0,0,0,0,0,0,0,0,0,16904,53082,5235,61010,25352,0,0,0,0,0,61307,0,0,0,18721,20025,3377,19249,52529,36409,20025,36409,52529,16384,0,22197,28804,0,0,42520,28217,52273,43561,3377,3377,44857,35369,44353,53338,16384,7134,22990,0,0,0,30339,46723,16904,2081,34848,20025,28217,2857,43049,63628,11363,16119,58136,0,0,0,14476,46459,0,44601,53049,3897,44601,51753,0,31124,23774,53644,0,0,0,0,22932,34857,0,44081,44081,34592,59945,58904,0,63628,22676,32768,0,0,0,0,45939,0,57352,17753,1658,18042,9850,41776,0,49672,47244,0,0,0,0,0,0,0,0,34417,9850,9561,33873,17481,0,0,0,0,0,0,0,0,0,0,0,9850,9017,0,8480,49976,0,0,0,0,0,0,0,0,0,0,0,9850,41240,0,8480,25953,0,0,0,0,0,0,0,0,0,0,0,9850,16656,0,49432,50249,0,0,0,0,0,0,0,0,0,0,0,58713,280,0,8704,20017,18977,49928,0,0,0,0,0,0,0,0,33024,2593,43297,49408,0,60721,3113,10265,0,0,0,0,0,0,0,0,41736,11825,44849,17936,0,0,0,0,0,0,0,0,0,0,0,0,0,65415,65415,65415,248,65415,0,0,0,0,0,0,0,65415,65415,65415,65415,65415,8068,0,0,0,0,0,0,65415,65415,65415,4096,4096,0,0,0,0,0,0,0,0,65415,65415,65415,0,0,0,0,0,0,0,0,0,7936,7936,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,7936,7936,7936,0,0,0,0,0,7936,7936,65535,65535,65535,65535,7936,0,0,0,0,0,7936,7936,7936,7936,7936,7936,7936,0,0,0,0,0,7936,7936,7936,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7940,7940,7940,7940,0,0,0,
};
const uint16_t deco2[]= 
	{
0,0,0,0,0,4,4,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,65415,65415,65415,248,65415,0,0,0,0,0,0,0,65415,65415,65415,65415,65415,8068,0,0,0,0,0,0,65415,65415,65415,4096,4096,0,0,0,0,0,0,0,0,65415,65415,65415,0,0,0,0,0,0,0,0,7936,7936,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,7936,7936,7936,0,0,0,0,0,7936,7936,65535,65535,65535,65535,7936,0,0,0,0,0,7936,7936,7936,7936,7936,7936,7936,0,0,0,0,0,7936,7936,7936,7936,0,0,0,0,0,0,0,0,0,40224,7936,65535,7936,0,0,0,0,0,0,0,40224,40224,7936,65535,7936,0,0,0,0,0,0,65315,40224,40224,7936,65535,40224,0,0,0,0,0,0,0,65315,0,65315,65315,65315,65315,0,0,
	};
const uint16_t deco3[]= 
{
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,0,7936,7936,4,4,4,4,4,4,7936,7936,0,0,65535,65535,4,4,4,4,4,4,65535,65535,0,0,7936,7936,4,4,4,4,4,4,7936,7936,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,24327,24327,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
const uint16_t dg1[]=
{
	0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,16142,16142,16142,0,0,0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,1994,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,
};

int main()
{
	int hinverted = 0;
	int vinverted = 0;
	int toggle = 0;
	int hmoved = 0;
	int vmoved = 0;
	uint16_t x = 50;
	uint16_t y = 50;
	uint16_t oldx = x;
	uint16_t oldy = y;
	initClock();
	initSysTick();
	setupIO();
	putImage(20,80,12,16,dg1,0,0);
	putImage(40,120,16,16,lilguy,0,0);
	while(1)
	{
		hmoved = vmoved = 0;
		hinverted = vinverted = 0;
		if ((GPIOB->IDR & (1 << 4))==0) // right pressed
		{					
			if (x < 110)
			{
				x = x + 1;
				hmoved = 1;
				hinverted=0;
			}						
		}
		if ((GPIOB->IDR & (1 << 5))==0) // left pressed
		{			
			
			if (x > 10)
			{
				x = x - 1;
				hmoved = 1;
				hinverted=1;
			}			
		}
		if ( (GPIOA->IDR & (1 << 11)) == 0) // down pressed
		{
			if (y < 140)
			{
				y = y + 1;			
				vmoved = 1;
				vinverted = 0;
			}
		}
		if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
		{			
			if (y > 16)
			{
				y = y - 1;
				vmoved = 1;
				vinverted = 1;
			}
		}
		if ((vmoved) || (hmoved))
		{
			// only redraw if there has been some movement (reduces flicker)
			fillRectangle(oldx,oldy,12,16,0);
			oldx = x;
			oldy = y;					
			if (hmoved)
			{
				if (toggle)
					putImage(x,y,12,16,deco1,hinverted,0);
				else
					putImage(x,y,12,16,deco2,hinverted,0);
				
				toggle = toggle ^ 1;
			}
			else
			{
				putImage(x,y,12,16,deco3,0,vinverted);
			}
			
			// Now check for an overlap by checking to see if ANY of the 4 corners of deco are within the target area
			if (isInside(20,80,12,16,x,y) || isInside(20,80,12,16,x+12,y) || isInside(20,80,12,16,x,y+16) || isInside(20,80,12,16,x+12,y+16) )
			{
				printTextX2("GLUG!", 10, 20, RGBToWord(0xff,0xff,0), 0);
			}
		}		
		delay(50);
	}
	return 0;
}
void initSysTick(void)
{
	SysTick->LOAD = 48000;
	SysTick->CTRL = 7;
	SysTick->VAL = 10;
	__asm(" cpsie i "); // enable interrupts
}
void SysTick_Handler(void)
{
	milliseconds++;
}
void initClock(void)
{
// This is potentially a dangerous function as it could
// result in a system with an invalid clock signal - result: a stuck system
        // Set the PLL up
        // First ensure PLL is disabled
        RCC->CR &= ~(1u<<24);
        while( (RCC->CR & (1 <<25))); // wait for PLL ready to be cleared
        
// Warning here: if system clock is greater than 24MHz then wait-state(s) need to be
// inserted into Flash memory interface
				
        FLASH->ACR |= (1 << 0);
        FLASH->ACR &=~((1u << 2) | (1u<<1));
        // Turn on FLASH prefetch buffer
        FLASH->ACR |= (1 << 4);
        // set PLL multiplier to 12 (yielding 48MHz)
        RCC->CFGR &= ~((1u<<21) | (1u<<20) | (1u<<19) | (1u<<18));
        RCC->CFGR |= ((1<<21) | (1<<19) ); 

        // Need to limit ADC clock to below 14MHz so will change ADC prescaler to 4
        RCC->CFGR |= (1<<14);

        // and turn the PLL back on again
        RCC->CR |= (1<<24);        
        // set PLL as system clock source 
        RCC->CFGR |= (1<<1);
}
void delay(volatile uint32_t dly)
{
	uint32_t end_time = dly + milliseconds;
	while(milliseconds != end_time)
		__asm(" wfi "); // sleep
}

void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
	Port->PUPDR = Port->PUPDR &~(3u << BitNumber*2); // clear pull-up resistor bits
	Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); // set pull-up bit
}
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode)
{
	/*
	*/
	uint32_t mode_value = Port->MODER;
	Mode = Mode << (2 * BitNumber);
	mode_value = mode_value & ~(3u << (BitNumber * 2));
	mode_value = mode_value | Mode;
	Port->MODER = mode_value;
}
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py)
{
	// checks to see if point px,py is within the rectange defined by x,y,w,h
	uint16_t x2,y2;
	x2 = x1+w;
	y2 = y1+h;
	int rvalue = 0;
	if ( (px >= x1) && (px <= x2))
	{
		// ok, x constraint met
		if ( (py >= y1) && (py <= y2))
			rvalue = 1;
	}
	return rvalue;
}

void setupIO()
{
	RCC->AHBENR |= (1 << 18) + (1 << 17); // enable Ports A and B
	display_begin();
	pinMode(GPIOB,4,0);
	pinMode(GPIOB,5,0);
	pinMode(GPIOA,8,0);
	pinMode(GPIOA,11,0);
	enablePullUp(GPIOB,4);
	enablePullUp(GPIOB,5);
	enablePullUp(GPIOA,11);
	enablePullUp(GPIOA,8);
}