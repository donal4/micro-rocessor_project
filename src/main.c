<<<<<<< HEAD

//test 
=======
//test
>>>>>>> refs/remotes/origin/main
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

const uint16_t lilguy[]={0,0,0,0,0,38406,6663,22791,64263,37125,36612,0,0,0,0,0,0,0,0,0,0,45573,47623,64263,64263,55303,37637,0,0,0,0,0,0,0,0,0,0,65535,65519,65535,65231,57327,57343,0,0,0,0,0,0,0,0,5382,39175,14855,14343,46854,38919,63495,22279,13830,12292,0,0,0,0,0,0,0,0,7936,48648,7936,24072,7936,7936,0,0,0,0,0,0,512,0,0,16128,7936,7936,57096,23824,56840,7688,16128,0,0,1024,0,0,7936,0,7936,65032,43765,16383,48656,40712,40959,17917,7936,7936,0,0,0,0,24320,0,7936,7936,16103,16103,57096,40712,32495,32495,24320,7936,0,256,0,0,7936,7936,16128,7936,7936,24320,7936,65032,7936,7936,7936,7936,7936,7424,0,0,512,0,7936,16128,16896,512,512,512,8704,33536,7936,40448,0,6912,0,0,0,0,7936,32008,25344,512,56600,16128,17152,8704,24320,7936,0,6656,0,0,0,0,0,24320,7936,23816,7936,7936,7936,64784,7936,0,0,0,0,0,0,0,0,0,7936,16128,7936,7688,7936,7936,0,0,0,0,0,0,0,0,0,0,0,16128,0,0,65032,0,0,0,0,0,0,0,0,0,0,7936,7936,7936,0,0,7936,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24320,7936,7936,0,0,0,0,          };
const uint16_t lilguy2[]={0,0,0,0,0,38406,6663,22791,64263,37125,36612,0,0,0,0,0,0,0,0,0,0,45573,47623,64263,64263,55303,37637,0,0,0,0,0,0,0,0,0,0,65535,65519,65535,65231,57327,57343,0,0,0,0,0,0,0,0,5382,39175,14855,14343,46854,38919,63495,22279,13830,12292,0,0,0,0,0,0,0,0,7936,48648,7936,24072,7936,7936,0,0,0,0,0,0,0,0,0,16128,7936,7936,57096,23824,56840,7688,16128,0,0,1024,0,0,0,0,7936,65032,43765,16383,48656,40712,40959,17917,7936,7936,0,7680,0,0,41992,0,7936,7936,16103,16103,57096,40712,32495,32495,24320,7936,0,7936,0,0,7936,7936,16128,7936,7936,24320,7936,65032,7936,7936,7936,7936,7936,7424,0,0,7936,0,7936,16128,16896,512,512,512,8704,33536,7936,40448,0,0,0,0,7936,0,7936,32008,25344,512,56600,16128,17152,8704,24320,7936,0,0,0,0,0,0,0,24320,7936,23816,7936,7936,7936,64784,7936,0,0,0,0,0,0,0,0,0,7936,16128,7936,7688,7936,7936,0,0,0,0,0,0,0,0,0,0,0,15632,0,0,7680,0,0,0,0,0,0,0,0,0,0,0,0,7936,0,0,7936,7680,6656,0,0,0,0,0,0,0,0,40712,7936,24320,0,0,512,0,0,0,0,0,0,          };
const uint32_t sprite[]={0,0,0,0,18457,18977,53322,20562,28754,11049,0,0,0,0,0,0,0,0,0,0,58120,50448,6284,31124,22932,35897,0,0,0,0,0,0,0,0,0,0,0,16904,53082,5235,61010,25352,0,0,0,0,0,61307,0,0,0,18721,20025,3377,19249,52529,36409,20025,36409,52529,16384,0,22197,28804,0,0,42520,28217,52273,43561,3377,3377,44857,35369,44353,53338,16384,7134,22990,0,0,0,30339,46723,16904,2081,34848,20025,28217,2857,43049,63628,11363,16119,58136,0,0,0,14476,46459,0,44601,53049,3897,44601,51753,0,31124,23774,53644,0,0,0,0,22932,34857,0,44081,44081,34592,59945,58904,0,63628,22676,32768,0,0,0,0,45939,0,57352,17753,1658,18042,9850,41776,0,49672,47244,0,0,0,0,0,0,0,0,34417,9850,9561,33873,17481,0,0,0,0,0,0,0,0,0,0,0,9850,9017,0,8480,49976,0,0,0,0,0,0,0,0,0,0,0,9850,41240,0,8480,25953,0,0,0,0,0,0,0,0,0,0,0,9850,16656,0,49432,50249,0,0,0,0,0,0,0,0,0,0,0,58713,280,0,8704,20017,18977,49928,0,0,0,0,0,0,0,0,33024,2593,43297,49408,0,60721,3113,10265,0,0,0,0,0,0,0,0,41736,11825,44849,17936,0,0,0,0,0,0,0,0,};

const uint16_t deco1[]=
{
0,0,0,0,4,4,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,18457,18977,53322,20562,28754,11049,0,0,0,0,0,0,0,0,0,0,58120,50448,6284,31124,22932,35897,0,0,0,0,0,0,0,0,0,0,0,16904,53082,5235,61010,25352,0,0,0,0,0,61307,0,0,0,18721,20025,3377,19249,52529,36409,20025,36409,52529,16384,0,22197,28804,0,0,42520,28217,52273,43561,3377,3377,44857,35369,44353,53338,16384,7134,22990,0,0,0,30339,46723,16904,2081,34848,20025,28217,2857,43049,63628,11363,16119,58136,0,0,0,14476,46459,0,44601,53049,3897,44601,51753,0,31124,23774,53644,0,0,0,0,22932,34857,0,44081,44081,34592,59945,58904,0,63628,22676,32768,0,0,0,0,45939,0,57352,17753,1658,18042,9850,41776,0,49672,47244,0,0,0,0,0,0,0,0,34417,9850,9561,33873,17481,0,0,0,0,0,0,0,0,0,0,0,9850,9017,0,8480,49976,0,0,0,0,0,0,0,0,0,0,0,9850,41240,0,8480,25953,0,0,0,0,0,0,0,0,0,0,0,9850,16656,0,49432,50249,0,0,0,0,0,0,0,0,0,0,0,58713,280,0,8704,20017,18977,49928,0,0,0,0,0,0,0,0,33024,2593,43297,49408,0,60721,3113,10265,0,0,0,0,0,0,0,0,41736,11825,44849,17936,0,0,0,0,0,0,0,0,0,0,0,0,0,65415,65415,65415,248,65415,0,0,0,0,0,0,0,65415,65415,65415,65415,65415,8068,0,0,0,0,0,0,65415,65415,65415,4096,4096,0,0,0,0,0,0,0,0,65415,65415,65415,0,0,0,0,0,0,0,0,0,7936,7936,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,7936,7936,7936,0,0,0,0,0,7936,7936,65535,65535,65535,65535,7936,0,0,0,0,0,7936,7936,7936,7936,7936,7936,7936,0,0,0,0,0,7936,7936,7936,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7940,7940,7940,7940,0,0,0,
};
const uint16_t deco2[]= 
	{
0,0,0,0,0,4,4,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,65415,65415,65415,248,65415,0,0,0,0,0,0,0,65415,65415,65415,65415,65415,8068,0,0,0,0,0,0,65415,65415,65415,4096,4096,0,0,0,0,0,0,0,0,65415,65415,65415,0,0,0,0,0,0,0,0,7936,7936,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,7936,7936,7936,0,0,0,0,0,7936,7936,65535,65535,65535,65535,7936,0,0,0,0,0,7936,7936,7936,7936,7936,7936,7936,0,0,0,0,0,7936,7936,7936,7936,0,0,0,0,0,0,0,0,0,40224,7936,65535,7936,0,0,0,0,0,0,0,40224,40224,7936,65535,7936,0,0,0,0,0,0,65315,40224,40224,7936,65535,40224,0,0,0,0,0,0,0,65315,0,65315,65315,65315,65315,0,0,
	};
const uint16_t lilguy4[]= 
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8192,0,0,0,0,0,0,0,0,7424,7936,47872,7936,7936,7424,256,0,0,0,0,7936,7936,64263,64263,64263,64263,6912,7936,0,0,0,0,7936,64263,64263,64263,64263,64263,64263,7936,0,0,7936,7936,7936,64263,64263,64263,64263,64263,64263,7936,7168,7936,7680,7424,7936,64263,64263,64263,64263,64263,64263,7936,6656,6656,0,0,7936,64263,64263,64263,64263,64263,64263,7936,512,0,0,0,7936,7936,64263,64263,64263,64263,7936,7936,0,0,0,0,0,7936,7936,7936,7936,7936,7424,0,0,0,0,0,0,0,0,7936,7936,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };
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
	//putImage(40,120,16,16,lilguy,0,0);
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
			fillRectangle(oldx,oldy,16,16,0);
			oldx = x;
			oldy = y;					
			if (hmoved)
			{
				if (toggle)
					putImage(x,y,16,16,lilguy,hinverted,0);
				else
					putImage(x,y,16,16,lilguy2,hinverted,0);
				
				toggle = toggle ^ 1;
			}
			else
			{
				putImage(x,y,12,16,lilguy4,0,vinverted);
			}
			
			// Now check for an overlap by checking to see if ANY of the 4 corners of deco are within the target area
			if (isInside(20,80,12,16,x,y) || isInside(20,80,12,16,x+12,y) || isInside(20,80,12,16,x,y+16) || isInside(20,80,12,16,x+12,y+16) )
			{
				printTextX2("GLUG!", 10, 20, RGBToWord(0xff,0xff,0), 0);
			}
		}		
		delay(100);
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