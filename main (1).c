//*****************************************************************************
//
//
//main.c
// Author: jkrachey@wisc.edu
// Modified: Allie
//*****************************************************************************
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab_buttons.h"
#include "Card_Ace.h"	
#include "Card_Two.h"
#include "Card_Three.h"
#include "Card_Four.h"
#include "Card_Five.h"
#include "Card_Six.h"
#include "Card_Seven.h"
#include "Card_Eight.h"
#include "Card_Nine.h"
#include "Card_Ten.h"
#include "EndScreen.h"
#include "StartScreen.h"
/******************************************************************************
 * Global Constants and Variables
 *****************************************************************************/
#define MOVE_PIXELS   	1							// Number of Pixels to move each time.
#define LCD_SIZE_X			240						// X Size of LCD screen in pixels
#define LCD_SIZE_Y			320						// Y Size of LCD screen in pixels
#define LCD_MAX_DRAW_X	LCD_SIZE_X-1	// 0 to LCD_MAX_DRAW_X is = LCD_SIZE_X
#define LCD_MAX_DRAW_Y	LCD_SIZE_Y-1	// 0 to LCD_MAX_DRAW_Y is = LCD_SIZE_Y
#define LCD_HALF_SIZE_X	LCD_SIZE_X/2	// X center of screen in pixels
#define LCD_HALF_SIZE_Y	LCD_SIZE_Y/2	// Y center of screen in pixels

int PLAYER_TOTAL	=	0;
int DEALER_TOTAL	=	0;
int	Player_X	=		0;
int	Player_Y	= 288;
int Dealer_X = 0;
int Dealer_Y = 0;
int Dealer_First = 0;
//*****************************************************************************
//*****************************************************************************
int get_card (int X, int Y, int total);
int check_21(int);
int check_17();
void draw_card(int card);

int main(void) {
  srand(55836);
	
  ece210_initialize_board();
	ece210_lcd_draw_image(50 , 147, 75, 117, Start_Screen_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
	ece210_wait_mSec(7000);
	int j =1;
	int i =1;
	int k =1;
	int l =1;
	
  while(i == 1){
		ece210_lcd_draw_rectangle(0, 240, 0, 320, LCD_COLOR_BLACK);
		j =1;
		i =1;
		k =1;
		l =1;
		Player_X = 0;
		Dealer_X = 0;
		PLAYER_TOTAL = 0;
		DEALER_TOTAL = 0;
		PLAYER_TOTAL = PLAYER_TOTAL + get_card(Player_X, Player_Y, PLAYER_TOTAL);
		Player_X = Player_X + 32;
		ece210_wait_mSec(200);
		PLAYER_TOTAL = PLAYER_TOTAL + get_card(Player_X, Player_Y, PLAYER_TOTAL);
		Player_X = Player_X + 32;
		ece210_wait_mSec(200);
		int b = check_21(PLAYER_TOTAL);
	
	
		if(b == 1){
			ece210_lcd_add_msg("You Win!\n\r",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
		}

		DEALER_TOTAL = DEALER_TOTAL + get_card(Dealer_X, Dealer_Y, DEALER_TOTAL);
		Dealer_X = Dealer_X + 32;
		ece210_wait_mSec(200);
		Dealer_First = get_card(Dealer_X, Dealer_Y, DEALER_TOTAL);
		ece210_lcd_draw_rectangle(Dealer_X, 32, Dealer_Y, 32, LCD_COLOR_RED);
		ece210_wait_mSec(200);
		DEALER_TOTAL = DEALER_TOTAL + Dealer_First;
		Dealer_X = Dealer_X + 32;
		
		while( j ==1){
		if(AlertButtons){
			AlertButtons = false;
			if(btn_left_pressed()){
				PLAYER_TOTAL = PLAYER_TOTAL + get_card(Player_X, Player_Y, PLAYER_TOTAL);
					Player_X = Player_X + 32;
				int b = check_21(PLAYER_TOTAL);
				if(b == 1){
					ece210_wait_mSec(2000);
					ece210_lcd_add_msg("You Win!\n\r",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
					j = 2;
					k = 2;
				}
				if(b == 2){
					ece210_wait_mSec(2000);
					ece210_lcd_add_msg("You Bust!\n\r",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
					k = 2;
					j = 2;
				}
			}
			if(btn_right_pressed()){
				j = 2;
			}
		}
  }
	
	
	while (k == 1){
		draw_card(Dealer_First);
		ece210_wait_mSec(200);
		if(DEALER_TOTAL<17){
			DEALER_TOTAL = DEALER_TOTAL + get_card(Dealer_X, Dealer_Y, DEALER_TOTAL);
			Dealer_X = Dealer_X + 32;
			ece210_wait_mSec(200);
			int b = check_21(DEALER_TOTAL);
				if(b == 1){
					ece210_wait_mSec(2000);
					ece210_lcd_add_msg("Dealer Wins!\n\r",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
					k = 2;
				}
				if(b == 2){
					ece210_wait_mSec(2000);
					ece210_lcd_add_msg("Dealer Busted!\n\r",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
					k = 2;
				}
		}
		if(DEALER_TOTAL >=17){
			k =2;
		}
	}
	
	
	if(DEALER_TOTAL > PLAYER_TOTAL && DEALER_TOTAL < 21){
		ece210_wait_mSec(2000);
		ece210_lcd_add_msg("Dealer Wins!\n\r",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
	}
	if(DEALER_TOTAL < PLAYER_TOTAL && PLAYER_TOTAL < 21){
		ece210_wait_mSec(2000);
		ece210_lcd_add_msg("You Win!\n\r",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
	}
	if (DEALER_TOTAL == PLAYER_TOTAL){
		ece210_wait_mSec(2000);
		ece210_lcd_add_msg("Push\n\r",TERMINAL_ALIGN_CENTER,LCD_COLOR_GREEN);
	}
	ece210_lcd_add_msg("Press left button to play again, right button to exit.\n\r",TERMINAL_ALIGN_CENTER,LCD_COLOR_BLUE);
	while( l == 1){ //stuck in loop
		
		if(AlertButtons){
			AlertButtons = false;
			
			if(btn_left_pressed()){
				l = 2;
				j =1;
				i =1;
				k =1; 
			}
			if(btn_right_pressed()){
				ece210_lcd_draw_rectangle(0, 240, 0, 320, LCD_COLOR_BLACK);
				ece210_lcd_draw_image(50 , 147, 75, 117, End_Screen_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
				i = 2;
				l = 2;
			}
		}
			
  }
		
}
}

	
int get_card (int X, int Y, int total){
	int k=rand()%13+1;

		if(k == 1){
			ece210_lcd_draw_image(X,32, Y,32, Card_Ace_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
			X = X + 32;
			int z = total + 11;
			if(check_21(z) == 2){
				k = 1;
			}
			else{
				k = 11;
			}
			return k;
				 }
		if(k == 2){
			ece210_lcd_draw_image(X,32, Y,32, Card_Two_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
			
		}
		
		if(k == 3){
		ece210_lcd_draw_image(X,32, Y,32, Card_Three_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
			
		}
		
		if(k==4){
		ece210_lcd_draw_image(X,32, Y,32, Card_Four_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
		
		}
		
		if(k==5){
		ece210_lcd_draw_image(X,32, Y,32, Card_Five_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
	
		}
		
		if(k==6){
		ece210_lcd_draw_image(X,32, Y,32, Card_Six_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);

		}
		
		if(k==7){
		ece210_lcd_draw_image(X,32, Y,32, Card_Seven_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
	
		}
		
		if(k==8){
		ece210_lcd_draw_image(X,32, Y,32, Card_Eight_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
	
		}
		
		if(k==9){
		ece210_lcd_draw_image(X,32, Y,32, Card_Nine_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
		
		}
		
		if(k==10){
		ece210_lcd_draw_image(X,32, Y,32, Card_Ten_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
	
		}
		if(k >= 11){
			k=10;
			ece210_lcd_draw_image(X,32, Y,32, Card_Ten_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
		
		}
		return k;
		}

int check_21(int Total){
	if(Total > 21){
		return 2;
	}
	if (Total == 21){
		return 1;
	}
	if (Total < 21){
		return 0;
	}
}

void draw_card(int card){
		if(card == 1 || card == 11){
			ece210_lcd_draw_image(32,32, 0,32, Card_Ace_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
		}
		if(card == 2){
			ece210_lcd_draw_image(32,32, 0,32, Card_Two_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
			
		}
		
		if(card == 3){
		ece210_lcd_draw_image(32 ,32, 0,32, Card_Three_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
			
		}
		
		if(card==4){
		ece210_lcd_draw_image(32 ,32, 0,32, Card_Four_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
		
		}
		
		if(card==5){
		ece210_lcd_draw_image(32 ,32, 0,32, Card_Five_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
	
		}
		
		if(card==6){
		ece210_lcd_draw_image(32 ,32, 0,32, Card_Six_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);

		}
		
		if(card==7){
		ece210_lcd_draw_image(32 ,32, 0,32, Card_Seven_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
	
		}
		
		if(card==8){
		ece210_lcd_draw_image(32 ,32, 0,32, Card_Eight_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
	
		}
		
		if(card==9){
		ece210_lcd_draw_image(32 ,32, 0,32, Card_Nine_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
		
		}
		
		if(card==10){
		ece210_lcd_draw_image(32 ,32, 0,32, Card_Ten_bitmap,LCD_COLOR_RED, LCD_COLOR_BLACK);
	
		}
}