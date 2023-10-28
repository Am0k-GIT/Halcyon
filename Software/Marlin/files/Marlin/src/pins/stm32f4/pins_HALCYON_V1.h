/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* Pin Assignments:
 *
 * A0  TM2_CH1 PWM (HOTBED / TTL / 0-10V) | B0  ADC8 (T_HOTBED)                 | C0  X_DIR                             | D0  (N/A)
 * A1  TM2_CH2 PWM (HOTEND)               | B1  ADC9 (T_HOTEND)                 | C1  X_STEP                            | D1  (N/A)
 * A2  TM2_CH3 PWM (FAN0 / FLOOD)         | B2  PS_ON (pulldown)                | C2  Y_DIR                             | D2  (EXP 2-08) SD_DET
 * A3  TM2_CH4 PWM (FAN1 / MIST)          | B3  (EXP 1-03) LCD_D7               | C3  Y_STEP                            | D3  (N/A)
 * A4  (EXP 2-07) SD_SS                   | B4  A_MIN                           | C4  Z_DIR                             | D4  (N/A)
 * A5  (EXP 2-09) SCK                     | B5  Z_MIN                           | C5  Z_STEP                            | D5  (N/A)
 * A6  (EXP 2-10) MISO                    | B6  (EXP 1-07) LCD_RS / SCL / TX    | C6  A_DIR                             | D6  (N/A)
 * A7  (EXP 2-05) MOSI                    | B7  (EXP 1-08) LCD_EN / SDA / RX    | C7  A_STEP                            | D7  (N/A)
 * A8  Enable motors                      | B8  X_MIN                           | C8  B_DIR                             | D8  (N/A)
 * A9  TX                                 | B9  Y_MIN                           | C9  B_STEP                            | D9  (N/A)
 * A10 RX                                 | B10 PROBE_IN (servo0)               | C10 (EXP 1-08) BEEP / CYCLE_START     | D10 (N/A)
 * A11 USB D-                             | B11 (N/A)                           | C11 (EXP 1-08) LCD_D5 / FEED_HOLD     | D11 (N/A)
 * A12 USB D+                             | B12 PROBE_OUT (Z_PROBE)             | C12 (EXP 1-08) LCD_D6                 | D12 (N/A)
 * A13 SWDIO                              | B13 FILAMENT / DOOR                 | C13 (EXP 1-09) BTN_ENC                | D13 (N/A)
 * A14 SWCLK                              | B14 B_MIN                           | C14 (EXP 2-08) BTN_EN1 / SPINDEL_DIR  | D14 (N/A)
 * A15 (EXP 1-06) LCD_D4                  | B15 (EXP 1-08) KILL / RESET         | C15 (EXP 2-06) BTN_EN2 / SPINDEL_EN   | D15 (N/A)
 */

/*
 *                             _________                                                        _________                            
 *                        5V   |  1  2 | GND                              (KILL / RESET)  PB15  |  1  2 | GND                        
 *              (LCD_D7)  PB3  |  3  4 | PC12  (LCD_D6)                                   RESET |  3  4 | PD2  (SD_DET)                        
 *  (LCD_D5 / FEED_HOLD)  PC11 |  5  6 | PA15  (LCD_D4)                           (MOSI)  PA7   |  5  6 | PC15 (BTN_EN2 / SPINDEL_EN)             
 *   (LCD_RS / SCL / TX)  PB6  |  7  8 | PB7   (LCD_EN / SDA / RX)                (SD_SS) PA4   |  7  8 | PC14 (BTN_EN1 / SPINDEL_DIR)             
 *              (BTN_ENC) PC13 |  9  10| PC10  (BEEP / CYCLE_START)               (SCK)   PA5   |  9  10| PA6  (MISO)                
 *                             ---------                                                        ---------                            
 *                               EXP1                                                              EXP2                              
 */
 
#if NOT_TARGET(STM32F4)
  #error "Oops! Select an STM32F4 board in 'Tools > Board.'"
#elif HOTENDS > 1 || E_STEPPERS > 1
  #error "Halcyon boards support one hotend / E-steppers only."
#endif

#define DEFAULT_MACHINE_NAME BOARD_NAME

//
// Limit Switches
//
   
#define X_STOP_PIN      PB8
#define Y_STOP_PIN      PB9
#define Z_STOP_PIN      PB5   
                 
                        
//
// Steppers
//
// X,Y,Z,E0 enable are the same

#define X_STEP_PIN         PC1
#define X_DIR_PIN          PC0
#define X_ENABLE_PIN       PA8
#define X_SERIAL_TX_PIN    PA9
#define X_SERIAL_RX_PIN    PA10

#define Y_STEP_PIN         PC3
#define Y_DIR_PIN          PC2
#define Y_ENABLE_PIN       PA8
#define Y_SERIAL_TX_PIN    PA9
#define Y_SERIAL_RX_PIN    PA10

#define Z_STEP_PIN         PC5
#define Z_DIR_PIN          PC4
#define Z_ENABLE_PIN       PA8
#define Z_SERIAL_TX_PIN    PA9
#define Z_SERIAL_RX_PIN    PA10

#define E0_STEP_PIN        PC7
#define E0_DIR_PIN         PC6
#define E0_ENABLE_PIN      PA8
#define E0_SERIAL_TX_PIN   PA9
#define E0_SERIAL_RX_PIN   PA10

#define TMC_BAUD_RATE 19200
//
// Temperature Sensors
//

#define TEMP_0_PIN         PB1
#define TEMP_BED_PIN       PB0

//
// Heaters / Fans
//

#define HEATER_0_PIN       PA1
#define HEATER_BED_PIN     PA0

//#define FAN0_PIN           PA2
#define FAN_PIN            PA2
#define FAN1_PIN           PA3

#ifdef E0_AUTO_FAN_PIN
  #undef E0_AUTO_FAN_PIN
  #define E0_AUTO_FAN_PIN  FAN1_PIN
#endif

//
// EEPROM settings
// EEPROM Emulation
//

#define FLASH_EEPROM_EMULATION
#define FLASH_EEPROM_LEVELING
#define EEPROM_SIZE           0x4000                                       // 16kB
#define FLASH_SECTOR          (FLASH_SECTOR_TOTAL - 1)
#define FLASH_UNIT_SIZE       0x4000                                       // 16kB

//
// BL-TOUCH
//

#define SERVO0_PIN                          PB10
#define Z_MIN_PROBE_PIN                     PB12
//#define BL_TOUCH_Z_PIN                      PB12

//
// Various
//

#define FIL_RUNOUT1_PIN                     PB13
#define FIL_MOTION1_PIN                     PB13
#define PS_ON_PIN                           PB2

//
// EXP
//

#define EXP_1_01_PIN                         -1
#define EXP_1_02_PIN                         -1
#define EXP_1_03_PIN                         PB3
#define EXP_1_04_PIN                         PC12
#define EXP_1_05_PIN                         PC11
#define EXP_1_06_PIN                         PA15
#define EXP_1_07_PIN                         PB6
#define EXP_1_08_PIN                         PB7
#define EXP_1_09_PIN                         PC13
#define EXP_1_10_PIN                         PC10

#define EXP_2_01_PIN                         PB15
#define EXP_2_02_PIN                         -1
#define EXP_2_03_PIN                         -1
#define EXP_2_04_PIN                         PD2
#define EXP_2_05_PIN                         PA7
#define EXP_2_06_PIN                         PC15
#define EXP_2_07_PIN                         PA4
#define EXP_2_08_PIN                         PC14
#define EXP_2_09_PIN                         PA5
#define EXP_2_10_PIN                         PA6

// SDCard
#ifdef SDSUPPORT
  #define SDSS                       EXP_2_07_PIN
  #define SD_DETECT_PIN              EXP_2_04_PIN
  #define KILL_PIN                   EXP_2_01_PIN
#endif

//
// LCD / Controller
//
#if HAS_WIRED_LCD
  #define BEEPER_PIN                 EXP_1_10_PIN
  #define BTN_ENC                    EXP_1_09_PIN

 #if ENABLED(CR10_STOCKDISPLAY)

   #define LCD_PINS_RS               EXP_1_07_PIN
  
   #define BTN_EN1                   EXP_1_03_PIN
   #define BTN_EN2                   EXP_1_05_PIN
  
   #define LCD_PINS_ENABLE           EXP_1_08_PIN
   #define LCD_PINS_D4               EXP_1_06_PIN

#elif IS_TFTGLCD_PANEL

    #undef BEEPER_PIN
    #undef BTN_ENC

    #if ENABLED(TFTGLCD_PANEL_SPI)
      #define TFTGLCD_CS             EXP_2_08_PIN
    #endif

    #define SD_DETECT_PIN            EXP_2_04_PIN

#else

    #define LCD_PINS_RS              EXP_1_07_PIN

    #define BTN_EN1                  EXP_2_08_PIN
    #define BTN_EN2                  EXP_2_06_PIN

    #define LCD_PINS_ENABLE          EXP_1_08_PIN

    #if ENABLED(FYSETC_MINI_12864)

      #define DOGLCD_CS              EXP_1_08_PIN
      #define DOGLCD_A0              EXP_1_07_PIN
      #define LCD_BACKLIGHT_PIN      -1
      #define LCD_RESET_PIN          EXP_1_06_PIN                              // Must be high or open for LCD to operate normally.

      #define LCD_CONTRAST_INIT      240
      #define LCD_CONTRAST_MIN       200
      #define LCD_CONTRAST_MAX       255
      
      #if EITHER(FYSETC_MINI_12864_1_2, FYSETC_MINI_12864_2_0)
        #ifndef RGB_LED_R_PIN
          #define RGB_LED_R_PIN      EXP_1_05_PIN
        #endif
        #ifndef RGB_LED_G_PIN
          #define RGB_LED_G_PIN      EXP_1_04_PIN
        #endif
        #ifndef RGB_LED_B_PIN
          #define RGB_LED_B_PIN      EXP_1_03_PIN
        #endif
      #elif ENABLED(FYSETC_MINI_12864_2_1)
        #define NEOPIXEL_PIN         EXP_1_05_PIN
      #endif

    #else                                                                      // !FYSETC_MINI_12864

      #define LCD_PINS_D4            EXP_1_06_PIN

      #if IS_ULTIPANEL
        #define LCD_PINS_D5          EXP_1_05_PIN
        #define LCD_PINS_D6          EXP_1_04_PIN
        #define LCD_PINS_D7          EXP_1_03_PIN

        #if ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER)
          #define BTN_ENC_EN         LCD_PINS_D7                               // Detect the presence of the encoder
        #endif
      #endif

    #endif                                                                     // !FYSETC_MINI_12864

#if IS_U8GLIB_ST7920
  #define BOARD_ST7920_DELAY_1                96
  #define BOARD_ST7920_DELAY_2                48
  #define BOARD_ST7920_DELAY_3               640
#endif

  #endif

#endif                                                                         // HAS_WIRED_LCD
