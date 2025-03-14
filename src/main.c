//main includes 
#include <stm32f031x6.h>
#include "display.h"

//sound 
#include "sound.h"
#include "musical_notes.h"
#include "serial.h"

void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
//serial 
void initSerial();

//sound 
void playNote(uint32_t Freq);
void initSound(void);


//main menu 
void menu_start();
void game_over(int);
void p2_game_over(int);

//Reset
void reset(void);

//random functions 
int randomevil(uint16_t x2 ,uint16_t y2, uint16_t hmoved2, uint16_t hinverted2,uint16_t  vmoved2 , uint16_t vinverted2 , int oldx2, int oldy2 , int toggle2); 
int random_y(void);
int random_x(void);



					//x   co-ord   y co -ord   width        height 		player x      player y 
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);

void item_gen(int hinverted ,int randx,int randy );
void coins(int randx , int randy , uint16_t x , uint16_t y ,int hinverted); 
void touch_evil(uint16_t x2, uint16_t y2 , uint16_t x , uint16_t y); 

//controls the movement of lilguy 
void lil_guy_movement(int oldx , int oldy, uint16_t  hmoved,  uint16_t hinverted, uint16_t x , uint16_t y  ,uint16_t vmoved,uint16_t vinverted ,int toggle);

volatile uint32_t milliseconds;


//tune 
uint32_t my_tune_notes[]={C4,G4,E4};
uint32_t my_tune_times[]={600,800,200};
// Variables to handle background tunes
uint32_t * background_tune_notes=0;
uint32_t * background_tune_times;
uint32_t background_note_count;
uint32_t background_tune_repeat;



// 				sprites 



//player 1
const uint16_t lilguy[]={0,0,0,0,0,38406,6663,22791,64263,37125,36612,0,0,0,0,0,0,0,0,0,0,45573,47623,64263,64263,55303,37637,0,0,0,0,0,0,0,0,0,0,65535,65519,65535,65231,57327,57343,0,0,0,0,0,0,0,0,5382,39175,14855,14343,46854,38919,63495,22279,13830,12292,0,0,0,0,0,0,0,0,7936,48648,7936,24072,7936,7936,0,0,0,0,0,0,512,0,0,16128,7936,7936,57096,23824,56840,7688,16128,0,0,1024,0,0,7936,0,7936,65032,43765,16383,48656,40712,40959,17917,7936,7936,0,0,0,0,24320,0,7936,7936,16103,16103,57096,40712,32495,32495,24320,7936,0,256,0,0,7936,7936,16128,7936,7936,24320,7936,65032,7936,7936,7936,7936,7936,7424,0,0,512,0,7936,16128,16896,512,512,512,8704,33536,7936,40448,0,6912,0,0,0,0,7936,32008,25344,512,56600,16128,17152,8704,24320,7936,0,6656,0,0,0,0,0,24320,7936,23816,7936,7936,7936,64784,7936,0,0,0,0,0,0,0,0,0,7936,16128,7936,7688,7936,7936,0,0,0,0,0,0,0,0,0,0,0,16128,0,0,65032,0,0,0,0,0,0,0,0,0,0,7936,7936,7936,0,0,7936,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24320,7936,7936,0,0,0,0,          };
const uint16_t lilguy2[]={0,0,0,0,0,38406,6663,22791,64263,37125,36612,0,0,0,0,0,0,0,0,0,0,45573,47623,64263,64263,55303,37637,0,0,0,0,0,0,0,0,0,0,65535,65519,65535,65231,57327,57343,0,0,0,0,0,0,0,0,5382,39175,14855,14343,46854,38919,63495,22279,13830,12292,0,0,0,0,0,0,0,0,7936,48648,7936,24072,7936,7936,0,0,0,0,0,0,0,0,0,16128,7936,7936,57096,23824,56840,7688,16128,0,0,1024,0,0,0,0,7936,65032,43765,16383,48656,40712,40959,17917,7936,7936,0,7680,0,0,41992,0,7936,7936,16103,16103,57096,40712,32495,32495,24320,7936,0,7936,0,0,7936,7936,16128,7936,7936,24320,7936,65032,7936,7936,7936,7936,7936,7424,0,0,7936,0,7936,16128,16896,512,512,512,8704,33536,7936,40448,0,0,0,0,7936,0,7936,32008,25344,512,56600,16128,17152,8704,24320,7936,0,0,0,0,0,0,0,24320,7936,23816,7936,7936,7936,64784,7936,0,0,0,0,0,0,0,0,0,7936,16128,7936,7688,7936,7936,0,0,0,0,0,0,0,0,0,0,0,15632,0,0,7680,0,0,0,0,0,0,0,0,0,0,0,0,7936,0,0,7936,7680,6656,0,0,0,0,0,0,0,0,40712,7936,24320,0,0,512,0,0,0,0,0,0,          };
const uint16_t lilguy4[]= 
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8192,0,0,0,0,0,0,0,0,7424,7936,47872,7936,7936,7424,256,0,0,0,0,7936,7936,64263,64263,64263,64263,6912,7936,0,0,0,0,7936,64263,64263,64263,64263,64263,64263,7936,0,0,7936,7936,7936,64263,64263,64263,64263,64263,64263,7936,7168,7936,7680,7424,7936,64263,64263,64263,64263,64263,64263,7936,6656,6656,0,0,7936,64263,64263,64263,64263,64263,64263,7936,512,0,0,0,7936,7936,64263,64263,64263,64263,7936,7936,0,0,0,0,0,7936,7936,7936,7936,7936,7424,0,0,0,0,0,0,0,0,7936,7936,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };


//badguy 
const uint16_t superevilguy1[] ={0,0,0,0,0,4912,4912,4912,4912,4912,4912,0,0,0,0,0,0,0,0,0,0,4912,4912,24334,24334,4912,4912,0,0,0,0,0,0,0,0,0,24334,4912,4912,4912,4912,4912,4912,24334,0,0,0,0,0,0,54559,54559,54559,24334,24334,24334,24334,24334,24334,54559,54559,54559,0,0,0,54559,54559,54559,9293,9293,54559,54559,54559,54559,9293,9293,54559,54559,54559,0,0,54559,54559,9293,65535,0,9293,54559,54559,9293,65535,0,9293,54559,54559,0,0,54559,54559,54559,9293,9293,54559,54559,54559,54559,9293,9293,54559,54559,54559,0,0,54559,9293,9293,54559,54559,54559,54559,54559,54559,54559,54559,9293,9293,54559,0,0,54559,54559,9293,65535,54559,54559,54559,54559,54559,54559,65535,9293,54559,54559,0,0,0,54559,9293,65535,9293,54559,54559,54559,54559,9293,65535,9293,54559,0,0,0,54559,54559,54559,9293,9293,65535,9293,9293,65535,9293,9293,54559,54559,54559,0,0,54559,0,0,54559,9293,65535,9293,9293,65535,9293,54559,0,0,54559,0,0,54559,0,0,54559,54559,9293,4912,4912,9293,54559,54559,0,0,54559,0,0,0,0,0,54559,0,54559,4912,4912,54559,0,54559,0,0,0,0,0,0,0,0,54559,0,0,4912,4912,0,0,54559,54559,54559,0,0,0,0,54559,54559,54559,0,0,0,0,0,0,0,0,0,0,0,};
const uint16_t superevilguy2[] = {0,0,0,0,0,4912,4912,4912,4912,4912,4912,0,0,0,0,0,0,0,0,0,0,4912,4912,24334,24334,4912,4912,0,0,0,0,0,0,0,0,0,24334,4912,4912,4912,4912,4912,4912,24334,0,0,0,0,0,0,54559,54559,54559,24334,24334,24334,24334,24334,24334,54559,54559,54559,0,0,0,54559,54559,54559,9293,9293,54559,54559,54559,54559,9293,9293,54559,54559,54559,0,0,54559,54559,9293,0,65535,9293,54559,54559,9293,0,65535,9293,54559,54559,0,0,54559,54559,54559,9293,9293,54559,54559,54559,54559,9293,9293,54559,54559,54559,0,0,54559,9293,9293,54559,54559,54559,54559,54559,54559,54559,54559,9293,9293,54559,0,0,54559,54559,9293,65535,54559,54559,54559,54559,54559,54559,65535,9293,54559,54559,0,0,0,54559,9293,65535,9293,54559,54559,54559,54559,9293,65535,9293,54559,0,0,0,0,54559,54559,9293,9293,65535,9293,9293,65535,9293,9293,54559,54559,0,0,0,0,54559,0,54559,9293,65535,9293,9293,65535,9293,54559,0,54559,0,0,0,54559,54559,0,54559,54559,9293,4912,4912,9293,54559,54559,0,54559,54559,0,0,0,0,0,54559,0,54559,4912,4912,54559,0,54559,0,0,0,0,0,0,54559,54559,54559,0,0,4912,4912,0,0,54559,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,54559,54559,54559,0,0,};

//items
const uint16_t coin[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8191,32767,8191,55758,1321,17441,57344,0,0,0,0,0,0,0,40695,40431,38917,14853,63749,13828,54276,63749,8720,24576,0,0,0,0,0,24311,55045,14597,32239,15062,7663,0,38917,23045,6661,33032,0,0,0,0,0,15855,6149,23302,40695,54788,30469,0,47109,39942,47621,8192,0,0,0,0,56022,0,64005,64005,56815,62980,62468,0,6149,55557,5380,8192,0,0,0,0,31975,0,22533,15110,56551,22277,30725,0,39173,15110,38661,8192,0,0,0,0,39902,0,39173,22789,15855,23045,30981,0,63749,14597,38917,16384,0,0,0,0,23518,0,22789,30469,48887,23045,38661,0,22789,56069,14597,0,0,0,0,0,57079,0,39173,55045,31446,54532,6661,0,47109,6405,62980,0,0,0,0,0,24047,0,55813,38917,47830,13316,62724,0,31237,23045,63237,0,0,0,0,50209,0,32239,22789,39173,7927,37123,28931,0,47365,56069,38661,0,0,0,0,0,49944,7663,64005,6405,0,0,0,0,63749,30725,0,0,0,0,0,0,9513,0,40695,30469,6661,14853,38917,31237,39173,54788,0,0,0,0,0,0,0,17441,0,0,30725,38917,6149,46853,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};


//global var(player )
int hp = 3; 
int score = 0;
int player_mode; 



	
//------------------------------------------------main------------------------------------------------------------
int main()
{
		
	//positioning 
	uint16_t x = 50;
	uint16_t y = 50;
	uint16_t x2 = 100;
	uint16_t y2 = 100;


	//variables 
	int hinverted = 0;
	int vinverted = 0;
	int toggle = 0;
	int hmoved = 0;
	int vmoved = 0;



	int hinverted2 = 0;
	int vinverted2 = 0;
	int toggle2 = 0;
	int hmoved2 = 0;
	int vmoved2 = 0;

	//positioning variables 
	uint16_t oldx = x;
	uint16_t oldy = y;
	uint16_t oldx2 = x2;
	uint16_t oldy2 = y2;

	
	//random x and y 
	int randx = random_x();
	int randy = random_y();
	
	//random values for evilguy 
	randomevil(x2 , y2 , hmoved2, hinverted2, vmoved2 ,  vinverted2 , oldx2 , oldy2 , toggle2);

	
	//startup 
	initClock();
	initSysTick();
	setupIO();
	//serial 
	initSerial(); 
	
	//sound 
	initSound();

	//start menu 
	menu_start();
	
	

	//Draws the coin onto the screen
	item_gen(hinverted ,randy,randx);
	putImage(x2,y2,16,16,superevilguy1,hinverted,0);
	
	//checks if the "lilguy" is inside the coin 
	
	//gameplay loop 
	while(1)
	{
		//checks the health 	
		health();

		//shows the current score 
		printTextX2("score", 0, 0, RGBToWord(0xff,0xff,0), 0);
		printNumber(score, 60, 0, RGBToWord(0xff,0xff,0), 0);


		//movement 
		hmoved = vmoved = 0;
		hinverted = vinverted = 0;
		
		//movement of superevilguy 
		randomevil( x2 ,y2,  hmoved2,  hinverted2,  vmoved2 ,  vinverted2 , oldx2 , oldy2, toggle2);

		//controls the movement for lilguy 
		lil_guy_movement( oldx ,  oldy,   hmoved,  hinverted,  x ,  y  , vmoved, vinverted , toggle); 
		
		//is lilguy touching super evil guy 
		touch_evil( x2,  y2 ,  x ,  y);

		//test serial
		printDecimal(score);

		//checks if the character is touching a coin 
		coins(randx, randy , x , y , hinverted);

		
		//sleeps 10 seconds  
		delay(100);
	}
	//exit code 
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------


void initSysTick(void)
{
	SysTick->LOAD = 48000;
	SysTick->CTRL = 7;
	SysTick->VAL = 10;
	__asm(" cpsie i "); // enable interrupts
}

//added background music stuff to systick handler (do not mess with)
void SysTick_Handler(void)
{
	static int index = 0;
	static int current_note_time=0;
	milliseconds++;
	if (background_tune_notes != 0)
	{
		if (current_note_time == 0)
		{
			index++;
			if (index >= background_note_count)
			{
				if (background_tune_repeat != 0)
				{
					index = 0;
				}
				else
				{
					background_tune_notes=0;
					playNote(0);
				}
			}
			current_note_time = background_tune_times[index];
			playNote(background_tune_notes[index]);
		}
		else
		{
			current_note_time--;
		}
	}
}

//dangerous (dont touch cause its still working) 
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

//added leds to the setup 
void setupIO()
{
	RCC->AHBENR |= (1 << 18) + (1 << 17); // enable Ports A and B

	display_begin();
	pinMode(GPIOA,0,0); //reset button
	pinMode(GPIOB,4,0);
	pinMode(GPIOB,5,0);
	pinMode(GPIOA,8,0);
	pinMode(GPIOA,11,0);
	enablePullUp(GPIOA,0); //reset button
	enablePullUp(GPIOB,4);
	enablePullUp(GPIOB,5);
	enablePullUp(GPIOA,11);
	enablePullUp(GPIOA,8);

	//leds
	pinMode(GPIOA,2,1); 
	pinMode(GPIOA,1,1); 
	pinMode(GPIOA,3,1); 
	
}

//function to give ramdom x co-ords in screen
int random_x(){

	int rand_x = rand() % 118 + 1 ;

	//if x is on the edges 
	if(rand_x == 0 || rand_x == 118){
		random_x();
	}

	return rand_x; 
}
//function to give ramdom y co-ords in screen
int random_y(/*int , int*/){

	int rand_y = rand() % 150 + 1 ;

	//if y is on the edges 
	if(rand_y == 0 || rand_y == 150){
		random_y();
	}
	return rand_y; 
}

//controls movement for "lil_guy"
void lil_guy_movement(int oldx , int oldy, uint16_t  hmoved,  uint16_t hinverted, uint16_t x , uint16_t y  ,uint16_t vmoved,uint16_t vinverted,int toggle){

	//Lilguy code
	if ((GPIOB->IDR & (1 << 4))==0) // right pressed
	{					
		if (x < 110)
		{
			x = x + 3;
			hmoved = 1;
			hinverted=0;
		}						
	}
	if ((GPIOB->IDR & (1 << 5))==0) // left pressed
	{				
		if (x > 10)
		{
			x = x - 3;
			hmoved = 1;
			hinverted=1;
		}			
	}
	if ( (GPIOA->IDR & (1 << 11)) == 0) // down pressed
	{
		if (y < 140)
		{
			y = y + 3;			
			vmoved = 1;
			vinverted = 0;
		}
	}
	if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
	{			
		if (y > 16)
		{
			y = y - 3;
			vmoved = 1;
			vinverted = 1;
		}
	}
	if ( (GPIOA->IDR & (1 << 0)) == 0) // if reset button pressed
	{
		reset();
	}

	//drawing character to the screen (i think)
	if ((vmoved) || (hmoved))
		{
			// only redraw if there has been some movement (reduces flicker)
			fillRectangle(oldx,oldy,16,16,0);
			oldx = x;
			oldy = y;					
			if (hmoved)
			{
				//draws charactar to the screen 
				if (toggle)
					putImage(x,y,16,16,lilguy,hinverted,0);
				else
					putImage(x,y,16,16,lilguy2,hinverted,0);
				
				toggle = toggle ^ 1;
			}
			else
			{
				//topdown lilguy 
				putImage(x,y,12,16,lilguy4,0,vinverted);
			}
		
}
}
//generates random movement for the evilguy 
int randomevil(uint16_t x2 ,uint16_t y2, uint16_t hmoved2, uint16_t hinverted2,uint16_t  vmoved2 , uint16_t vinverted2 , int oldx2 , int oldy2 , int toggle2){
	
	//code for directions (random)
	int randevil = rand() % 4 + 1 ;

	//chooses which direction to move the "super evilguy "based off of the random int 
	switch(randevil) {
		case 1:
			if (x2 < 110)
			{
				//moves charactar right 
				x2 = x2 + 3;
				hmoved2 = 1;
				hinverted2=0;
			}				
			break;
		case 2:
			//left 
			if (x2 > 10)
			{
				x2 = x2 - 3;
				hmoved2 = 1;
				hinverted2=1;
			}				
			break;
		case 3:
		//up 
			if (y2 < 140)
			{
				y2 = y2 + 3;			
				vmoved2 = 1;
				vinverted2 = 0;
			}
			break;
		case 4:
		//down 
			if (y2 > 16)
			{
				y2 = y2 - 3;
				vmoved2 = 1;
				vinverted2 = 1;
			}
		
	}
	
		//movement for evilguy 
	if ((vmoved2) || (hmoved2))
	{
		// only redraw if there has been some movement (reduces flicker)
		fillRectangle(oldx2,oldy2,16,16,0);
		oldx2 = x2;
		oldy2 = y2;					
		if (hmoved2)
		{
			//draws charactar to the screen 
			if (toggle2)
				putImage(x2,y2,16,16,superevilguy1,hinverted2,0);
			else
				putImage(x2,y2,16,16,superevilguy2,hinverted2,0);
				
			toggle2 = toggle2 ^ 1;
			}
		else
		{
		//adds an image of the badguy 
		putImage(x2,y2,16,16,superevilguy1,0,vinverted2);
		}
	}

	//nolonger needed 
	return randevil;
}

void touch_evil(uint16_t x2, uint16_t y2 , uint16_t x , uint16_t y ){
	//is character touching any of the four corners of the evilguy
	if (isInside(x2,y2,16,16,x,y) || isInside(x2,y2,16,16,x+16,y) || isInside(x2,y2,16,16,x,y+16) || isInside(x2,y2,16,16,x+16,+16) )
	{
		//play sound 
		playNote(B6);//coin sound 
		delay(5);//delay
		playNote(B7);//octave above 
		delay(10);//delay
		playNote(0);//stops sound

		hp--; //minus one health 
		health();//updates the lights relative to health 
	}
}

void menu_start(){
	//positioning 

	//loop for menu 
	while (1)
	{	
		//start music 
		playBackgroundTune(my_tune_notes,my_tune_times,3,0);

		//				gui
		//text
		printTextX2("lilguy", 30, 10, RGBToWord(0xff,0xff,0), 0);
		printTextX2("V", 60, 30, RGBToWord(0xff,0xff,0), 0);
		printTextX2("super evil", 10, 50, RGBToWord(0xff,0xff,0), 0);
		printTextX2("guy", 47, 70, RGBToWord(0xff,0xff,0), 0);

		printText("up start P1", 10, 120, RGBToWord(0xff,0x0,0), 0);
		printText("down start p2",10, 128, RGBToWord(0xff,0x0,0), 0); 
		//characters 
		putImage(80,100,16,16,superevilguy1,0,0);
		putImage(40,100,16,16,lilguy,0,0);


		__asm("wfi");//sleep 
		//player 1 
		if ( (GPIOA->IDR & (1 << 8)) == 0)//up
		{
			fillRectangle(0,0,128, 160, 0x0);  // black out the screen
			//sets the game to be player 1 
			player_mode = 1; 

			//stop music 
			playNote(0);

			//escape the loop 
			break;
		}
		//player 2 
		if ( (GPIOA->IDR & (1 << 11)) == 0)//down
		{
			fillRectangle(0,0,128, 160, 0x0);  // black out the screen
			//sets the game to be player 2 
			player_mode = 2 ; 

			//stop music 
			playNote(0);
				
			//escape the loop 
			break;
		}
		if ( (GPIOA->IDR & (1 << 0)) == 0) // if reset button pressed
			{
				//reset function 
				reset();
			}
	}
}

//function to draw coin to the screen 
void item_gen(int hinverted ,int randy,int randx){
	//draws coin
	//putImage(x,y,12,16,coin,0,0);//
	putImage(randx,randy,16,16,coin,hinverted,0);
}

//checks if the character is in the coin 
void coins(int randx,int randy , uint16_t x , uint16_t y ,int hinverted){
	
	// Now check for an overlap by checking to see if ANY of the 4 corners of Coin are within the target area
	if ((isInside(randx,randy,16,16,x,y) || isInside(randx,randy,16,16,x+16,y) || isInside(randx,randy,16,16,x,y+16) || isInside(randx,randy,16,16,x+16,+16) )== 1 )
	{
		//adds one to the score 
		score+=1;

		//play sound 
		playNote(B6);//coin sound 
		delay(10);//delay
		playNote(B7);//octave above 
		delay(10);//delay
		delay(10);//delay
		playNote(0);//stops sound


		fillRectangle(randx,randy,16,16,0);// covers scren with black pixels 
			

		//resets the random x and y co -ords 
		randx = random_x();
		randy = random_y();

		//calls the item gen function 
		item_gen(hinverted ,randy,randx);

		
			
	}		
	
	
}

//function to check player health 
void health(void){
	while(1){
		if(hp == 3){

			GPIOA->ODR = GPIOA->ODR| (1<<2);

			GPIOA->ODR = GPIOA->ODR| (1<<1);

			GPIOA->ODR = GPIOA->ODR| (1<<3);
			break; 
		}
		if(hp == 2){

			GPIOA->ODR = GPIOA->ODR| (0<<2);

			GPIOA->ODR = GPIOA->ODR| (1<<1);

			GPIOA->ODR = GPIOA->ODR| (1<<3);
			break;
		}
		if(hp == 1){

			GPIOA->ODR = GPIOA->ODR| (0<<2);

			GPIOA->ODR = GPIOA->ODR| (0<<1);

			GPIOA->ODR = GPIOA->ODR| (1<<3);
			break;
		}
		if(hp == 0){

			GPIOA->ODR = GPIOA->ODR| (0<<2);

			GPIOA->ODR = GPIOA->ODR| (0<<1);

			GPIOA->ODR = GPIOA->ODR| (0<<3);
			// game over screen 
			game_over(score); 
		}
	}

}	

//------------------------------------------------------------------------------------------------------------------------
//game over screen for players 
void game_over(score){
	//fillRectangle(0,0,128, 160, 0x0);  // black out the screen
	//loop for menu 
	
	// text 
	printTextX2("Game", 20 ,10 ,RGBToWord(0xff,0xff,0), 0);
	printTextX2("Over", 20 ,30 ,RGBToWord(0xff,0xff,0), 0);
	printTextX2("score", 20, 50, RGBToWord(0xff,0xff,0), 0);
	printNumberX2(score,20, 70, RGBToWord(0xff,0xff,0), 0);
	
	//prompt 
	printText("Play again?: ^", 10, 120, RGBToWord(0xff,0x0,0), 0);
	printText("Main Menu?  >",10, 128, RGBToWord(0xff,0x0,0), 0); 

	__asm("wfi");//sleep 
	
	//play again 
	if ( (GPIOA->IDR & (1 << 8)) == 0)//up
	{
		fillRectangle(0,0,128, 160, 0x0);  // black out the screen
		//prints the players score ro the screen 
		eputs("\nplayer high score:");                         
		printDecimal(score);
			
	}
		//menu 
	if ( (GPIOA->IDR & (1 << 4)) == 0)//right
	{
		fillRectangle(0,0,128, 160, 0x0);  // black out the screen

			//sends score to pc 
		eputs("\nplayer high score:"); 
		printDecimal(score);
	}
	delay(30);//waits 3 seconds 
	 
	
	__asm("wfi");//sleep 
	reset(); // resets the game 
		
}

//resets the game 
void reset()
{
	fillRectangle(0,0,128,160,0x0);//fills screen with the colour black 
	hp = 3; //resets health
	score = 0; //sets score back to 0 
	delay(10);//sleeps 1 second 
	menu_start(); //calls the main menu 
}


//background music 
void playBackgroundTune(uint32_t * notes, uint32_t * times, uint32_t count, uint32_t repeat)
{
	//music functions 
	background_tune_notes=notes;
	background_tune_times=times;
	background_note_count=count;
	background_tune_repeat=repeat;
}
