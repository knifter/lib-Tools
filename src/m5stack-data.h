#define M5STACK_CORE
#define M5STACK_CORE2
#ifdef ARDUINO_M5STACK_CORES3
    #define M5STACK_CORES3
#endif

/******** GPIO to BUS Pin *******************************************************/
#ifdef  M5STACK_CORE
    // 1, 3, 5 = GND
    #define M5_BUS_2                GPIO_NUM_35     // ADC1
    #define M5_BUS_4                GPIO_NUM_36     // ADC
    // 6 = RESET / EN
    #define M5_BUS_7                GPIO_NUM_23     // SPI_MOSI
    #define M5_BUS_8                GPIO_NUM_25     // AUDIO_L / DAC / SPEAKER
    #define M5_BUS_9                GPIO_NUM_19     // SPI_MISO
    #define M5_BUS_10               GPIO_NUM_26     // AUDIO_R / DAC
    #define M5_BUS_11               GPIO_NUM_18     // SPI_SCK
    // 12 = 3V3
    #define M5_BUS_13               GPIO_NUM_3      // RXD1
    #define M5_BUS_14               GPIO_NUM_1      // TXD1
    #define M5_BUS_15               GPIO_NUM_16     // RXD2
    #define M5_BUS_16               GPIO_NUM_17     // TXD2
    #define M5_BUS_17               GPIO_NUM_21     // intSDA
    #define M5_BUS_18               GPIO_NUM_22     // intSCL
    #define M5_BUS_19               GPIO_NUM_2      // IO6
    #define M5_BUS_20               GPIO_NUM_5      // IO7
    #define M5_BUS_21               GPIO_NUM_12     // I2S_SCLK
    #define M5_BUS_22               GPIO_NUM_13     // I2S_WS
    #define M5_BUS_23               GPIO_NUM_15     // I2S_OUT
    #define M5_BUS_24               GPIO_NUM_0      // I2S_LRCLK
    // 25, 27, 29 = HPWR
    #define M5_BUS_26               GPIO_NUM_34     // I2S_EN
    // 28 = 5V
    // 30 = BATTERY
#endif

#ifdef M5STACK_CORE2
    // 1, 3, 5 = GND
    #define M5_BUS_2                GPIO_NUM_35     // ADC
    #define M5_BUS_4                GPIO_NUM_36     // ADC
    // 6 = RESET
    #define M5_BUS_7                GPIO_NUM_23     // SPI_MOSI
    #define M5_BUS_8                GPIO_NUM_25     // AUDIO_L / DAC
    #define M5_BUS_9                GPIO_NUM_38     // SPI_MISO
    #define M5_BUS_10               GPIO_NUM_26     // AUDIO_R / DAC
    #define M5_BUS_11               GPIO_NUM_18     // SPI_SCK
    // 12 = 3.3V
    #define M5_BUS_13               GPIO_NUM_3      // RXD0
    #define M5_BUS_14               GPIO_NUM_1      // TXD0
    #define M5_BUS_15               GPIO_NUM_13     // RXD2
    #define M5_BUS_16               GPIO_NUM_14     // TXD2
    #define M5_BUS_17               GPIO_NUM_21     // intSDA
    #define M5_BUS_18               GPIO_NUM_22     // intSCL
    #define M5_BUS_19               GPIO_NUM_32     // PA_SDA
    #define M5_BUS_20               GPIO_NUM_33     // PA_SCL
    #define M5_BUS_21               GPIO_NUM_27     // GPIO
    #define M5_BUS_22               GPIO_NUM_19     // GPIO
    #define M5_BUS_23               GPIO_NUM_2      // I2S_OUT
    #define M5_BUS_24               GPIO_NUM_0      // I2S_LRCLK
    #define M5_BUS_26               GPIO_NUM_34     // PDM_DAT
    // 25, 27, 29 = HPWR
    // 26 = 
    // 28 = 5V
    // 30 = BAT
#endif

#ifdef M5STACK_CORES3
    // 1, 3, 5 = GND
    #define M5_BUS_2                GPIO_NUM_10    // ADC
    #define M5_BUS_4                GPIO_NUM_8     // ADC
    // 6 = RESET
    #define M5_BUS_7                GPIO_NUM_37    // SPI_MOSI
    #define M5_BUS_8                GPIO_NUM_5     // AUDIO_L / DAC
    #define M5_BUS_9                GPIO_NUM_35    // SPI_MISO
    #define M5_BUS_10               GPIO_NUM_9     // AUDIO_R / DAC
    #define M5_BUS_11               GPIO_NUM_36    // SPI_SCK
    // 12 = 3.3V
    #define M5_BUS_13               GPIO_NUM_44    // RXD0
    #define M5_BUS_14               GPIO_NUM_43    // TXD0
    #define M5_BUS_15               GPIO_NUM_18    // RXD2
    #define M5_BUS_16               GPIO_NUM_17    // TXD2
    #define M5_BUS_17               GPIO_NUM_12    // intSDA
    #define M5_BUS_18               GPIO_NUM_11    // intSCL
    #define M5_BUS_19               GPIO_NUM_2     // PA_SDA
    #define M5_BUS_20               GPIO_NUM_1     // PA_SCL
    #define M5_BUS_21               GPIO_NUM_6     // GPIO
    #define M5_BUS_22               GPIO_NUM_7     // GPIO
    #define M5_BUS_23               GPIO_NUM_13    // I2S_OUT
    #define M5_BUS_24               GPIO_NUM_0     // I2S_LRCLK
    #define M5_BUS_26               GPIO_NUM_14    // PDM_DAT
    // 25, 27, 29 = HPWR
    // 26 = 
    // 28 = 5V
    // 30 = BAT
#endif

/******** Common: Busnames to Pin number *******************************************************/
#define M5_BUS_ADC1             M5_BUS_2
#define M5_BUS_ADC2             M5_BUS_4
#define M5_BUS_SPI_MOSI         M5_BUS_7
#define M5_BUS_DAC0             M5_BUS_8
#define M5_AUDIO_L              M5_BUS_8
#define M5_BUS_SPI_MISO         M5_BUS_9
#define M5_BUS_DAC1             M5_BUS_10
#define M5_AUDIO_R              M5_BUS_10
#define M5_BUS_SPI_SCK          M5_BUS_11
#define M5_BUS_IO0              M5_BUS_13
#define M5_BUS_RXD0             M5_BUS_13 
#define M5_BUS_IO1              M5_BUS_14
#define M5_BUS_TXD0             M5_BUS_14
#define M5_BUS_IO2              M5_BUS_15
#define M5_BUS_RXD2             M5_BUS_15
#define M5_BUS_IO3              M5_BUS_16
#define M5_BUS_TXD2             M5_BUS_16
#define M5_BUS_PC_TX            M5_BUS_16
#define M5_BUS_INT_SDA          M5_BUS_17
#define M5_BUS_INT_SCL          M5_BUS_18
#define M5_BUS_IO6              M5_BUS_19
#define M5_BUS_IO7              M5_BUS_20
#define M5_BUS_IO8              M5_BUS_21
#define M5_BUS_IIS_SCLK         M5_BUS_21
#define M5_BUS_IO9              M5_BUS_22
#define M5_BUS_IIS_WS           M5_BUS_22
#define M5_BUS_IO10             M5_BUS_23
#define M5_BUS_IIS_OUT          M5_BUS_23
#define M5_BUS_IO11             M5_BUS_24
#define M5_BUS_IIS_MCLK         M5_BUS_24
#define M5_BUS_IIS_IN           M5_BUS_26
#define M5_BUS_ADC0             M5_BUS_26

/******** Internal/Special/External Connections *******************************************************/
#ifdef  M5STACK_CORE
    // Additional BUS names
    #define M5_BUS_RXD1             M5_BUS_13 // Core
    #define M5_BUS_TXD1             M5_BUS_14 // Core

    // Internal connections
    // IO 28, 29, 30, 31 = RAMROM
    // Program UART
    // #define M5_U0TXD                M5_BUS_TXD1
    // #define M5_U0RXD                M5_BUS_RXD1

    // Internal:: Flash
    #define M5_FLASH_SCLK           GPIO_NUM_6
    #define M5_FLASH_SO             GPIO_NUM_7
    #define M5_FLASH_SI             GPIO_NUM_8
    #define M5_FLASH_HOLD           GPIO_NUM_9
    #define M5_FLASH_WP             GPIO_NUM_10
    #define M5_FLASH_CS             GPIO_NUM_11

    // Internal: SD/TF
    #define M5_SD_CS                GPIO_NUM_4
    #define M5_SD_CLK               GPIO_NUM_18
    #define M5_SD_DO                GPIO_NUM_19
    #define M5_SD_DI                GPIO_NUM_23

    // Internal: SPK
    #define M5_SPEAKER              GPIO_NUM_25

    // Internal: Touch
    #define M5_TOUCH_SCL            M5_BUS_INT_SCL
    #define M5_TOUCH_SDA            M5_BUS_INT_SDA
    #define M5_TOUCH_INT            GPIO_NUM_39

    // Internal LCD
    #define M5_LCD_CS               GPIO_NUM_14
    #define M5_LCD_RS               GPIO_NUM_27
    #define M5_LCD_BL               GPIO_NUM_32
    #define M5_LCD_RST              GPIO_NUM_33
    #define M5_LCD_SCK              M5_BUS_SPI_SCK
    #define M5_LCD_MISO             M5_BUS_SPI_MISO
    #define M5_LCD_MOSI             M5_BUS_SPI_MOSI

    // Internal: Buttons
    #define M5_BTN_A                GPIO_NUM_37
    #define M5_BTN_B                GPIO_NUM_38
    #define M5_BTN_C                GPIO_NUM_39

    // I2C Addresses
    #define M5_I2C_ADDR_IP5306      (0x75) // Power Mgmt
#endif

#ifdef M5STACK_CORE2
    // Additional BUS names
    #define M5_BUS_PA_SDA           M5_BUS_19 // Core2
    #define M5_BUS_PA_SCL           M5_BUS_20 // Core2

    // Internal:: Flash
    #define M5_FLASH_SCLK           GPIO_NUM_6
    #define M5_FLASH_SO             GPIO_NUM_7
    #define M5_FLASH_SI             GPIO_NUM_8
    #define M5_FLASH_HOLD           GPIO_NUM_9
    #define M5_FLASH_WP             GPIO_NUM_10
    #define M5_FLASH_CS             GPIO_NUM_11

    // Internal: PSRAM
    #define M5_PSRAM_SCLK           GPIO_NUM_17
    #define M5_PSRAM_SIO0           GPIO_NUM_8
    #define M5_PSRAM_SIO1           GPIO_NUM_7
    #define M5_PSRAM_SIO2           GPIO_NUM_10
    #define M5_PSRAM_SIO3           GPIO_NUM_9
    #define M5_PSRAM_CS             GPIO_NUM_16

    // Internal LCD
    #define M5_LCD_CS               GPIO_NUM_5
    #define M5_LCD_DC               GPIO_NUM_15
    // #define M5_LCD_BL               AXP_DCDC3
    // #define M5_LCD_RST              AXP_IO4
    #define M5_LCD_SCK              M5_BUS_SPI_SCK
    #define M5_LCD_MISO             M5_BUS_SPI_MISO
    #define M5_LCD_MOSI             M5_BUS_SPI_MOSI

    // Internal: Touch
    #define M5_TOUCH_SCL            M5_BUS_INT_SCL
    #define M5_TOUCH_SDA            M5_BUS_INT_SDA
    #define M5_TOUCH_INT            GPIO_NUM_39

    // Internal: SD/TF
    #define M5_SD_CS                GPIO_NUM_4
    #define M5_SD_CLK               M5_BUS_SPI_SCK  // G18
    #define M5_SD_DI                M5_BUS_SPI_MOSI // G23
    #define M5_SD_DO                M5_BUS_SPI_MISO // G38

    // Internal: Speaker
    #define M5_SPEAKER_LRCK         GPIO_NUM_0
    #define M5_SPEAKER_BCLK         GPIO_NUM_12
    #define M5_SPEAKER_DATA         GPIO_NUM_2
    // #define M5_SPEAKER_EN        AXP_IO2

    // Add-on: MIC
    #define M5_MIC_CLK              M5_BUS_24 // GPIO_NUM_0
    #define M5_MIC_DAT              M5_BUS_26 // GPIO_NUM_34

    // Add-on: MPU-6886
    #define M5_IMU_SDA              M5_BUS_INT_SDA
    #define M5_IMU_SCL              M5_BUS_INT_SCL

    // Internal: RTC/AXP
    #define M5_RTC_SDA              M5_BUS_INT_SDA
    #define M5_RTC_SCL              M5_BUS_INT_SCL

    // External: PORT A
    #define M5_PORTA_1              M5_BUS_PA_SDA
    #define M5_PORTA_2              M5_BUS_PA_SCL

    // I2C Addresses
    #define M5_I2C_ADDR_MPU6886     (0x68) // IMU
    #define M5_I2C_ADDR_AXP192      (0x23) // Power Mgmt
    #define M5_I2C_ADDR_BM8563      (0x51) // RTC
    #define M5_I2C_ADDR_FT6336      (0x38) // Touch
#endif

#ifdef M5STACK_CORES3
    // Additional BUS names
    #define M5_BUS_PB_IN            M5_BUS_4 // CoreS3
    #define M5_BUS_PB_OUT           M5_BUS_10 // CoreS3
    #define M5_BUS_RXD0             M5_BUS_13 // CoreS3
    #define M5_BUS_TXD0             M5_BUS_14 // CoreS3
    #define M5_BUS_PC_RX            M5_BUS_15 // CoreS3
    #define M5_BUS_PA_SDA           M5_BUS_19 // Core2, CoreS3
    #define M5_BUS_PA_SCL           M5_BUS_20 // Core2, CoreS3

    // // Internal:: Flash
    #define M5_FLASH_CS1            GPIO_NUM_26
    #define M5_FLASH_HD             GPIO_NUM_27
    #define M5_FLASH_WP             GPIO_NUM_28
    #define M5_FLASH_CS0            GPIO_NUM_29
    #define M5_FLASH_CLK            GPIO_NUM_30
    #define M5_FLASH_Q              GPIO_NUM_31
    #define M5_FLASH_D              GPIO_NUM_32

    // // Internal: PSRAM
    // #define M5_PSRAM_SCLK           GPIO_NUM_
    // #define M5_PSRAM_SIO0           GPIO_NUM_
    // #define M5_PSRAM_SIO1           GPIO_NUM_
    // #define M5_PSRAM_SIO2           GPIO_NUM_
    // #define M5_PSRAM_SIO3           GPIO_NUM_
    // #define M5_PSRAM_CS             GPIO_NUM_

    // Internal USB/OTG
    #define M5_USB_DN               GPIO_NUM_19
    #define M5_USB_DP               GPIO_NUM_20
    
    // Internal LCD
    #define M5_LCD_CS               GPIO_NUM_3
    #define M5_LCD_DC               GPIO_NUM_35
    // #define M5_LCD_BL               AXP2101_DLDO1
    // #define M5_LCD_RST              AW9523B_P1_1
    // #define M5_LCD_PWR              AXP2101_LX1
    #define M5_LCD_SCK              M5_BUS_SPI_SCK
    // #define M5_LCD_MISO             N.C.
    #define M5_LCD_MOSI             M5_BUS_SPI_MOSI

    // Internal: Camera GC0308
    #define M5_CAM_SDA              M5_BUS_INT_SDA
    #define M5_CAM_SCL              M5_BUS_INT_SCL
    // #define M5_CAM_RST              AW9523B_P1_0
    #define M5_CAM_PCLK             GPIO_NUM_45
    #define M5_CAM_VSYNC            GPIO_NUM_46
    #define M5_CAM_HREF             GPIO_NUM_38
    #define M5_CAM_D2               GPIO_NUM_39
    #define M5_CAM_D3               GPIO_NUM_40
    #define M5_CAM_D4               GPIO_NUM_41
    #define M5_CAM_D5               GPIO_NUM_42
    #define M5_CAM_D6               GPIO_NUM_15
    #define M5_CAM_D7               GPIO_NUM_16
    #define M5_CAM_D8               GPIO_NUM_48
    #define M5_CAM_D9               GPIO_NUM_47

    // Internal: Proximity Sensor LTR-553ALS-WA
    #define M5_PROXIM_SDA           M5_BUS_INT_SDA
    #define M5_PROXIM_SCL           M5_BUS_INT_SCL

    // Internal: Touch FT6336U
    #define M5_TOUCH_SCL            M5_BUS_INT_SCL
    #define M5_TOUCH_SDA            M5_BUS_INT_SDA
    // #define M5_TOUCH_INT            AW9523B_P1_2
    // #define M5_TOUCH_RST            AW9523B_P0_0

    // Internal: SD/TF
    #define M5_SD_CS                GPIO_NUM_4
    #define M5_SD_CLK               M5_BUS_SPI_SCK  // G36
    #define M5_SD_DI                M5_BUS_SPI_MOSI // G37
    #define M5_SD_DO                M5_BUS_SPI_MISO // G35

    // Internal: Speaker AW88298
    #define M5_AW88298_SCL          M5_BUS_INT_SCL
    #define M5_AW88298_SDA          M5_BUS_INT_SDA
    #define M5_SPEAKER_SCLK         M5_BUS_IIS_SCLK
    #define M5_SPEAKER_WS           M5_BUS_IIS_WS
    #define M5_SPEAKER_SDATA        M5_BUS_IIS_OUT // DAT_I
    #define M5_SPEAKER_MCLK         M5_BUS_IIS_MCLK

    // Internal Microphone ES7210
    #define M5_ES7210_SCL           M5_BUS_INT_SCL
    #define M5_ES7210_SDA           M5_BUS_INT_SDA
    #define M5_MIC_SCLK             M5_BUS_IIS_SCLK
    #define M5_MIC_LRCK             M5_BUS_IIS_WS
    #define M5_MIC_SDATA            M5_BUS_IIS_IN // DAT_O
    #define M5_MIC_MCLK             M5_BUS_IIS_MCLK

    // // Internal: RTC/AXP
    #define M5_RTC_SDA              M5_BUS_INT_SDA
    #define M5_RTC_SCL              M5_BUS_INT_SCL

    // External: PORT A: Red, I2C
    #define M5_PORTA_1              M5_BUS_PA_SDA 
    #define M5_PORTA_2              M5_BUS_PA_SCL 

    // Add-on: PORT B, Black, GPIO
    #define M5_PORTB_1              M5_BUS_PB_IN
    #define M5_PORTB_2              M5_BUS_PB_OUT

    // Add-on: PORT C: Blue, UART
    #define M5_PORTC_1              M5_BUS_PC_RX
    #define M5_PORTC_2              M5_BUS_PC_TX

    // I2C Addresses
    #define M5_I2C_ADDR_GC0308      (0x21) // Camera
    #define M5_I2C_ADDR_LTR553      (0x23) // Light Sensor
    #define M5_I2C_ADDR_AXP2101     (0x34) // Power mgmt
    #define M5_I2C_ADDR_AW88298     (0x36) // AMP
    #define M5_I2C_ADDR_FT6336      (0x38) // Touch
    #define M5_I2C_ADDR_ES7210      (0x40) // MIC ADC
    #define M5_I2C_ADDR_BM8563      (0x51) // RTC
    #define M5_I2C_ADDR_AW9523      (0x58) // IO-Expander
    #define M5_I2C_ADDR_BMI270      (0x69) // IMU
    #define M5_I2C_ADDR_BMM150      (0x10) // Magneto
#endif // ARDUINO_M5CORE_CORES3

// STEPMOTOR DRIVER V1.1 pins on MBUS
#define M5_STEPMOTORDRIVER_DIR_X    M5_BUS_15   // S1:GPIO17 S2:GPIO14 S3:GPIO17 
#define M5_STEPMOTORDRIVER_STP_X    M5_BUS_16   // S1:GPIO16 S2:GPIO13 S3:GPIO18 
#define M5_STEPMOTORDRIVER_DIR_Y    M5_BUS_21   // S1:GPIO13 S2:GPIO19 S3:GPIO7 
#define M5_STEPMOTORDRIVER_STP_Y    M5_BUS_22   // S1:GPIO12 S2:GPIO27 S3:GPIO6
#define M5_STEPMOTORDRIVER_DIR_Z    M5_BUS_23   // S1:GPIO0  S2:GPIO0  S3:GPIO0
#define M5_STEPMOTORDRIVER_STP_Z    M5_BUS_24   // S1:GPIO15 S2:GPIO2  S3:GPIO13
#define M5_STEPMOTORDRIVER_SDA      M5_BUS_18   // S1:GPIO21 S2:GPIO   S3:GPIO11
#define M5_STEPMOTORDRIVER_SCL      M5_BUS_17   // S1:GPIO22 S2:GPIO   S3:GPIO12
