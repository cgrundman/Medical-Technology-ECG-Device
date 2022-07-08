/*
  Library File for Display

  Contains custom commands to implement the screen and
  all its functions. This code uses libraries from the
  LCD Wiki libraries. The display for the buttons, text
  and numbers. 
*/

// Include LCDWiki libraries
#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_KBV.h> // Hardware-specific library

// Define LCD pixel size andpins for communication with LCD Screen
LCDWIKI_KBV my_lcd(320,480,A3,A2,A1,A0,A4); // width,height,cs,cd,wr,rd,reset

// Color Definitions
                             /*  r     g    b */
#define BLACK        0x0000  /*   0,   0,   0 */
#define BLUE         0x001F  /*   0,   0, 255 */
#define RED          0xF800  /* 255,   0,   0 */
#define GREEN        0x07E0  /*   0, 255,   0 */
#define CYAN         0x07FF  /*   0, 255, 255 */
#define MAGENTA      0xF81F  /* 255,   0, 255 */
#define YELLOW       0xFFE0  /* 255, 255,   0 */
#define WHITE        0xFFFF  /* 255, 255, 255 */
#define NAVY         0x000F  /*   0,   0, 128 */
#define DARKGREEN    0x03E0  /*   0, 128,   0 */
#define DARKCYAN     0x03EF  /*   0, 128, 128 */
#define MAROON       0x7800  /* 128,   0,   0 */
#define PURPLE       0x780F  /* 128,   0, 128 */
#define OLIVE        0x7BE0  /* 128, 128,   0 */
#define LIGHTGREY    0xC618  /* 192, 192, 192 */
#define DARKGREY     0x7BEF  /* 128, 128, 128 */
#define ORANGE       0xFD20  /* 255, 165,   0 */
#define GREENYELLOW  0xAFE5  /* 173, 255,  47 */
#define PINK         0xF81F  /* 255,   0, 255 */

// Define Button sizes and spacing
#define BUTTON_W 75 // width of button 
#define BUTTON_H 75 // height of button
#define BUTTON_SPACING_X 4  // the horizontal distance between button
#define BUTTON_SPACING_Y 4  // the vertical distance between button
#define EDG_Y 4 // lower edge distance 
#define EDG_X 2 // left and right distance

// Define data types for Button information
typedef struct _button_info
{
     uint8_t button_name[10];
     uint8_t button_name_size;
     uint16_t button_name_colour;
     uint16_t button_colour;
     uint16_t button_x;
     uint16_t button_y;     
 }button_info;

// Definition of buttons
button_info button[12] = 
{
  // Button Name, Btn Txt Size, Btn Txt Color, Btn Bg Color, Btn width Loc, Btn height Loc  
     "1", 4, RED, BLACK, EDG_X,                               EDG_Y,
     "2", 4, RED, BLACK, EDG_X+BUTTON_W+BUTTON_SPACING_X,     EDG_Y,
     "3", 4, RED, BLACK, EDG_X+2*BUTTON_W+2*BUTTON_SPACING_X, EDG_Y,
     "4", 4, RED, BLACK, EDG_X,                               EDG_Y+BUTTON_H+BUTTON_SPACING_Y, 
     "5", 4, RED, BLACK, EDG_X+BUTTON_W+BUTTON_SPACING_X,     EDG_Y+BUTTON_H+BUTTON_SPACING_Y,
     "6", 4, RED, BLACK, EDG_X+2*BUTTON_W+2*BUTTON_SPACING_X, EDG_Y+BUTTON_H+BUTTON_SPACING_Y,
     "7", 4, RED, BLACK, EDG_X,                               EDG_Y+2*BUTTON_H+2*BUTTON_SPACING_Y,
     "8", 4, RED, BLACK, EDG_X+BUTTON_W+BUTTON_SPACING_X,     EDG_Y+2*BUTTON_H+2*BUTTON_SPACING_Y,
     "9", 4, RED, BLACK, EDG_X+2*BUTTON_W+2*BUTTON_SPACING_X, EDG_Y+2*BUTTON_H+2*BUTTON_SPACING_Y,
     "*", 4, RED, BLACK, EDG_X,                               EDG_Y+3*BUTTON_H+3*BUTTON_SPACING_Y,
     "0", 4, RED, BLACK, EDG_X+BUTTON_W+BUTTON_SPACING_X,     EDG_Y+3*BUTTON_H+3*BUTTON_SPACING_Y,
     "#", 4, RED, BLACK, EDG_X+2*BUTTON_W+2*BUTTON_SPACING_X, EDG_Y+3*BUTTON_H+3*BUTTON_SPACING_Y,  
};

// Display String
void show_string(uint8_t *str,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
{
    my_lcd.Set_Text_Mode(mode);
    my_lcd.Set_Text_Size(csize);
    my_lcd.Set_Text_colour(fc);
    my_lcd.Set_Text_Back_colour(bc);
    my_lcd.Print_String(str,x+37,y+37);
}

// Display updating number
void show_num(long *num,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc,boolean mode)
{
    my_lcd.Fill_Rect(x, y, 180, 28, LIGHTGREY);
    my_lcd.Set_Text_Mode(mode);
    my_lcd.Set_Text_Size(csize);
    my_lcd.Set_Text_colour(fc);
    my_lcd.Set_Text_Back_colour(bc);
    my_lcd.Print_Number_Int(num,x,y,5,0,5);
}
//void Print_Number_Int(long num, int16_t x, int16_t y, int16_t length, uint8_t filler, int16_t system);

// Display the main menu
void show_menu(void)
{
   uint16_t i;
   for(i = 0;i < sizeof(button)/sizeof(button_info);i++)
   {
      // Draw buttons
      my_lcd.Set_Draw_color(button[i].button_colour);
      my_lcd.Fill_Rect(button[i].button_x, button[i].button_y, BUTTON_W, BUTTON_H, BLACK);
      
      // Display button name
      show_string(button[i].button_name,button[i].button_x-strlen(button[i].button_name)*button[i].button_name_size*6/2+button[i].button_name_size/2+1,button[i].button_y-button[i].button_name_size*8/2+button[i].button_name_size/2+1,button[i].button_name_size,button[i].button_name_colour,BLACK,1);
   }
   my_lcd.Set_Draw_color(BLACK);
}

// Clear screen
void DisplaySetup()
{
  Serial.begin(9600);
  my_lcd.Init_LCD();
  my_lcd.Set_Rotation(1);
  Serial.println(my_lcd.Read_ID(), HEX);
  my_lcd.Fill_Screen(LIGHTGREY); 
  show_menu(); 
}
