#include "../keyboard/keyboard.h"
#include "../../kernel/values.h"
#include "../../kernel/types.h"
#include "../../kernel/utils.h"
#include "../../kernel/io/io.h"

#include "console.h"

uint32 vga_index;
static uint32 next_line_index = 1;

uint8 g_fore_color = WHITE;
uint8 g_back_color = BLUE;

int digit_ascii_codes[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) 
{
  uint16 ax = 0;
  uint8  ah = 0;
  uint8  al = 0;

  ah = back_color;

  ah <<= 4;
  ah |= fore_color;

  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
  for(uint32 i = 0; i < BUFSIZE; i++){
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
  }
  next_line_index = 1;
  vga_index = 0;
}

void init_vga(uint8 fore_color, uint8 back_color)
{  
  vga_buffer = (uint16*)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
  g_fore_color = fore_color;
  g_back_color = back_color;
}

void clear_screen(uint8 fore_color, uint8 back_color)
{
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
}

void print_new_line()
{
  if(next_line_index >= 55){
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  }
  vga_index = 80*next_line_index;
  next_line_index++;
}

void print_char(char ch)
{
  vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
  vga_index++;
}

void print_string(char *str)
{
  uint32 index = 0;
  while(str[index]){
    print_char(str[index]);
    index++;
  }
}

void print_color_string(char *str, uint8 fore_color, uint8 back_color)
{
  uint32 index = 0;
  uint8 fc;
  uint8 bc;

  fc = g_fore_color;
  bc = g_back_color;

  g_fore_color = fore_color;
  g_back_color = back_color;

  while(str[index]){
    print_char(str[index]);
    index++;
  }
  
  g_fore_color = fc;
  g_back_color = bc;
}

void print_int(int num)
{
  char str_num[digit_count(num)+1];
  itoa(num, str_num);
  print_string(str_num);
}

void gotoxy(uint16 x, uint16 y)
{
  vga_index = 80*y;
  vga_index += x;
}

// print string in new line
void print(char *str, uint8 fore_color, uint8 back_color){
  print_color_string(str, fore_color, back_color);
  print_new_line();
}

// logging functions

void pr_alert(char *str){
  print(str, YELLOW, BLACK);
}

void pr_err(char *str){
  print(str, RED, BLACK);
}

void pr_info(char *str){
  print(str, LIGHT_BLUE, BLACK);
}