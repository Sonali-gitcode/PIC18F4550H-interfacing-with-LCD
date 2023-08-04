// Include the necessary header files
#include <xc.h>
#include <stdint.h>

// Function prototypes
void LCD_Init();
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_Print(const char* str);
void LCD_Clear();

// Define control pins and data pins
#define LCD_RS RC0
#define LCD_RW RC1
#define LCD_EN RC2

#define LCD_DATA_PORT PORTD

void LCD_Init() {
    // Wait for LCD to power up
    __delay_ms(20);

    // Function Set: 4-bit mode, 2 lines, 5x8 font
    LCD_Command(0x02);
    LCD_Command(0x28);

    // Display ON/OFF Control: Display on, Cursor off, Blink off
    LCD_Command(0x0C);

    // Clear Display
    LCD_Command(0x01);

    // Entry Mode Set: Increment cursor, No shift
    LCD_Command(0x06);
}

void LCD_Command(uint8_t cmd) {
    LCD_RS = 0; // Set RS low for command mode
    LCD_RW = 0; // Set RW low for write mode

    // Send high nibble first
    LCD_DATA_PORT = (cmd & 0xF0);
    LCD_EN = 1;
    __delay_us(1);
    LCD_EN = 0;

    // Send low nibble
    LCD_DATA_PORT = ((cmd & 0x0F) << 4);
    LCD_EN = 1;
    __delay_us(1);
    LCD_EN = 0;

    __delay_ms(2); // Wait for the command to be processed
}

void LCD_Data(uint8_t data) {
    LCD_RS = 1; // Set RS high for data mode
    LCD_RW = 0; // Set RW low for write mode

    // Send high nibble first
    LCD_DATA_PORT = (data & 0xF0);
    LCD_EN = 1;
    __delay_us(1);
    LCD_EN = 0;

    // Send low nibble
    LCD_DATA_PORT = ((data & 0x0F) << 4);
    LCD_EN = 1;
    __delay_us(1);
    LCD_EN = 0;

    __delay_us(40); // Wait for the data to be processed
}

void LCD_Print(const char* str) {
    while (*str != '\0') {
        LCD_Data(*str++);
    }
}

void LCD_Clear() {
    LCD_Command(0x01); // Clear display
    __delay_ms(2);
    LCD_Command(0x80); // Move cursor to the beginning of the first line
}

void main() {
    // Initialize the LCD
    LCD_Init();

    // Display a message
    LCD_Clear();
    LCD_Print("Hello, World!");

    while(1) {
        // Your main code here
    }
}
