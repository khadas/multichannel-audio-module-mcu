#ifndef __STM8S_H
#define __STM8S_H
#define STM8S003


#if defined(__CSMC__)
    #define _COSMIC_
#elif defined(__RCST7__)
    #define _RAISONANCE_
#elif defined(__ICCSTM8__)
    #define _IAR_
#elif defined(__SDCC__)
    #define _SDCC_
#else
    #error "Unsupported Compiler!"
#endif


#if !defined  USE_STDPERIPH_DRIVER
    #define USE_STDPERIPH_DRIVER
#endif


#define HSE_VALUE   ((uint32_t)16000000)    // Value of the External oscillator in Hz
#define HSI_VALUE   ((uint32_t)16000000)    // Typical Value of the HSI in Hz
#define LSI_VALUE   ((uint32_t)128000)      // Typical Value of the LSI in Hz

#ifdef _COSMIC_
    #define FAR  @far
    #define NEAR @near
    #define TINY @tiny
    #define EEPROM @eeprom
    #define CONST  const
#elif defined (_RAISONANCE_)
    #define FAR  far
    #define NEAR data
    #define TINY page0
    #define EEPROM eeprom
    #define CONST  code
    #define MEMCPY memcpy                   // Used with memory Models for code less than 64K
#elif defined (_SDCC_)
    #define FAR  __far
    #define NEAR                            //hack SDCC gets confused by __near
    #define TINY __tiny
    #define EEPROM __eeprom
    #define CONST  const
#elif defined (_IAR_)
    #define FAR  __far
    #define NEAR __near
    #define TINY __tiny
    #define EEPROM __eeprom
    #define CONST  const
#endif


// Used with memory Models for code smaller than 64K
#define PointerAttr NEAR
#define MemoryAddressCast uint16_t
#define IN_RAM(a) a

// [31:16] STM8S Standard Peripheral Library main version V2.2.0
#define __STM8S_STDPERIPH_VERSION_MAIN   ((uint8_t)0x02) // [31:24] main version
#define __STM8S_STDPERIPH_VERSION_SUB1   ((uint8_t)0x02) // [23:16] sub1 version
#define __STM8S_STDPERIPH_VERSION_SUB2   ((uint8_t)0x00) // [15:8]  sub2 version
#define __STM8S_STDPERIPH_VERSION_RC     ((uint8_t)0x00) // [7:0]  release candidate
#define __STM8S_STDPERIPH_VERSION        ((__STM8S_STDPERIPH_VERSION_MAIN << 24)\
                                         |(__STM8S_STDPERIPH_VERSION_SUB1 << 16)\
                                         |(__STM8S_STDPERIPH_VERSION_SUB2 << 8)\
                                         |(__STM8S_STDPERIPH_VERSION_RC))


#define __I     volatile const
#define __O     volatile
#define __IO    volatile

#if defined(_SDCC_)
	#include <stdint.h>

#else
typedef signed		char    int8_t;
typedef signed		short   int16_t;
typedef signed		long    int32_t;
typedef unsigned	char    uint8_t;
typedef unsigned	short   uint16_t;
typedef unsigned	long    uint32_t;

#endif

typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;


typedef enum
{
    FALSE = 0,
    TRUE = !FALSE
} bool;

typedef enum
{
    RESET = 0,
    SET = !RESET
} FlagStatus, ITStatus, BitStatus, BitAction;

typedef enum
{
    DISABLE = 0,
    ENABLE = !DISABLE
} FunctionalState;

#define IS_FUNCTIONALSTATE_OK(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
    ERROR = 0,
    SUCCESS = !ERROR
} ErrorStatus;

#define U8_MAX     (255)
#define S8_MAX     (127)
#define S8_MIN     (-128)
#define U16_MAX    (65535u)
#define S16_MAX    (32767)
#define S16_MIN    (-32768)
#define U32_MAX    (4294967295uL)
#define S32_MAX    (2147483647)
#define S32_MIN    (-2147483648uL)

typedef struct GPIO_struct
{
    __IO uint8_t ODR;  	 // Output Data Register
    __IO uint8_t IDR;  	 // Input Data Register
    __IO uint8_t DDR;  	 // Data Direction Register
    __IO uint8_t CR1;  	 // Configuration Register 1
    __IO uint8_t CR2;  	 // Configuration Register 2
} gpio_reg;

#define GPIO_ODR_RESET_VALUE ((uint8_t)0x00)
#define GPIO_DDR_RESET_VALUE ((uint8_t)0x00)
#define GPIO_CR1_RESET_VALUE ((uint8_t)0x00)
#define GPIO_CR2_RESET_VALUE ((uint8_t)0x00)


typedef struct ADC_struct
{
    __IO uint8_t DB0RH;         // ADC Data Buffer Register (MSB)
    __IO uint8_t DB0RL;         // ADC Data Buffer Register (LSB)
    __IO uint8_t DB1RH;         // ADC Data Buffer Register (MSB)
    __IO uint8_t DB1RL;         // ADC Data Buffer Register (LSB)
    __IO uint8_t DB2RH;         // ADC Data Buffer Register (MSB)
    __IO uint8_t DB2RL;         // ADC Data Buffer Register (LSB)
    __IO uint8_t DB3RH;         // ADC Data Buffer Register (MSB)
    __IO uint8_t DB3RL;         // ADC Data Buffer Register (LSB)
    __IO uint8_t DB4RH;         // ADC Data Buffer Register (MSB)
    __IO uint8_t DB4RL;         // ADC Data Buffer Register (LSB)
    __IO uint8_t DB5RH;         // ADC Data Buffer Register (MSB)
    __IO uint8_t DB5RL;         // ADC Data Buffer Register (LSB)
    __IO uint8_t DB6RH;         // ADC Data Buffer Register (MSB)
    __IO uint8_t DB6RL;         // ADC Data Buffer Register (LSB)
    __IO uint8_t DB7RH;         // ADC Data Buffer Register (MSB)
    __IO uint8_t DB7RL;         // ADC Data Buffer Register (LSB)
    __IO uint8_t DB8RH;         // ADC Data Buffer Register (MSB)
    __IO uint8_t DB8RL;         // ADC Data Buffer Register (LSB)
    __IO uint8_t DB9RH;         // ADC Data Buffer Register (MSB)
    __IO uint8_t DB9RL;         // ADC Data Buffer Register (LSB)
    uint8_t RESERVED[12];       // Reserved byte
    __IO uint8_t CSR;           // ADC control status register
    __IO uint8_t CR1;           // ADC configuration register 1
    __IO uint8_t CR2;           // ADC configuration register 2
    __IO uint8_t CR3;           // ADC configuration register 3
    __IO uint8_t DRH;           // ADC Data high
    __IO uint8_t DRL;           // ADC Data low
    __IO uint8_t TDRH;          // ADC Schmitt trigger disable register high
    __IO uint8_t TDRL;          // ADC Schmitt trigger disable register low
    __IO uint8_t HTRH;          // ADC high threshold register High
    __IO uint8_t HTRL;          // ADC high threshold register Low
    __IO uint8_t LTRH;          // ADC low threshold register high
    __IO uint8_t LTRL;          // ADC low threshold register low
    __IO uint8_t AWSRH;         // ADC watchdog status register high
    __IO uint8_t AWSRL;         // ADC watchdog status register low
    __IO uint8_t AWCRH;         // ADC watchdog control register high
    __IO uint8_t AWCRL;         // ADC watchdog control register low
} ADC_TypeDef;


#define ADC_CSR_RESET_VALUE    ((uint8_t)0x00)
#define ADC_CR1_RESET_VALUE    ((uint8_t)0x00)
#define ADC_CR2_RESET_VALUE    ((uint8_t)0x00)
#define ADC_CR3_RESET_VALUE    ((uint8_t)0x00)
#define ADC_TDRL_RESET_VALUE   ((uint8_t)0x00)
#define ADC_TDRH_RESET_VALUE   ((uint8_t)0x00)
#define ADC_HTRL_RESET_VALUE   ((uint8_t)0x03)
#define ADC_HTRH_RESET_VALUE   ((uint8_t)0xFF)
#define ADC_LTRH_RESET_VALUE   ((uint8_t)0x00)
#define ADC_LTRL_RESET_VALUE   ((uint8_t)0x00)
#define ADC_AWCRH_RESET_VALUE  ((uint8_t)0x00)
#define ADC_AWCRL_RESET_VALUE  ((uint8_t)0x00)

#define ADC_CSR_EOC     ((uint8_t)0x80)	 // End of Conversion mask
#define ADC_CSR_AWD     ((uint8_t)0x40)	 // Analog Watch Dog Status mask
#define ADC_CSR_EOCIE   ((uint8_t)0x20)	 // Interrupt Enable for EOC mask
#define ADC_CSR_AWDIE   ((uint8_t)0x10)	 // Analog Watchdog interrupt enable mask
#define ADC_CSR_CH      ((uint8_t)0x0F)	 // Channel selection bits mask
#define ADC_CR1_SPSEL   ((uint8_t)0x70)	 // Prescaler selection mask
#define ADC_CR1_CONT    ((uint8_t)0x02)	 // Continuous conversion mask
#define ADC_CR1_ADON    ((uint8_t)0x01)	 // A/D Converter on/off mask
#define ADC_CR2_EXTTRIG ((uint8_t)0x40)	 // External trigger enable mask
#define ADC_CR2_EXTSEL  ((uint8_t)0x30)	 // External event selection mask
#define ADC_CR2_ALIGN   ((uint8_t)0x08)	 // Data Alignment mask
#define ADC_CR2_SCAN    ((uint8_t)0x02)	 // Scan mode mask
#define ADC_CR3_DBUF    ((uint8_t)0x80)	 // Data Buffer Enable mask
#define ADC_CR3_OVR     ((uint8_t)0x40)	 // Overrun Status Flag mask


typedef struct AWU_struct
{
  __IO uint8_t CSR;	 // AWU Control status register
  __IO uint8_t APR;	 // AWU Asynchronous prescaler buffer
  __IO uint8_t TBR;	 // AWU Time base selection register
} AWU_TypeDef;


#define AWU_CSR_RESET_VALUE ((uint8_t)0x00)
#define AWU_APR_RESET_VALUE ((uint8_t)0x3F)
#define AWU_TBR_RESET_VALUE ((uint8_t)0x00)

#define AWU_CSR_AWUF    ((uint8_t)0x20)		 // Interrupt flag mask
#define AWU_CSR_AWUEN   ((uint8_t)0x10)		 // Auto Wake-up enable mask
#define AWU_CSR_MSR     ((uint8_t)0x01)		 // LSI Measurement enable mask
#define AWU_APR_APR     ((uint8_t)0x3F)		 // Asynchronous Prescaler divider mask
#define AWU_TBR_AWUTB   ((uint8_t)0x0F)		 // Timebase selection mask


typedef struct BEEP_struct
{
    __IO uint8_t CSR;	// BEEP Control status register
} BEEP_TypeDef;


#define BEEP_CSR_RESET_VALUE ((uint8_t)0x1F)
#define BEEP_CSR_BEEPSEL ((uint8_t)0xC0)	// Beeper frequency selection mask
#define BEEP_CSR_BEEPEN  ((uint8_t)0x20)	// Beeper enable mask
#define BEEP_CSR_BEEPDIV ((uint8_t)0x1F)	// Beeper Divider prescalar mask

typedef struct CLK_struct
{
    __IO uint8_t ICKR;     		// Internal Clocks Control Register
    __IO uint8_t ECKR;     		// External Clocks Control Register
    uint8_t RESERVED;      		// Reserved byte
    __IO uint8_t CMSR;     		// Clock Master Status Register
    __IO uint8_t SWR;      		// Clock Master Switch Register
    __IO uint8_t SWCR;     		// Switch Control Register
    __IO uint8_t CKDIVR;   		// Clock Divider Register
    __IO uint8_t PCKENR1;  		// Peripheral Clock Gating Register 1
    __IO uint8_t CSSR;     		// Clock Security System Register
    __IO uint8_t CCOR;     		// Configurable Clock Output Register
    __IO uint8_t PCKENR2;  		// Peripheral Clock Gating Register 2
    uint8_t RESERVED1;     		// Reserved byte
    __IO uint8_t HSITRIMR; 		// HSI Calibration Trimmer Register
    __IO uint8_t SWIMCCR;  		// SWIM clock control register
} CLK_TypeDef;


#define CLK_ICKR_RESET_VALUE     ((uint8_t)0x01)
#define CLK_ECKR_RESET_VALUE     ((uint8_t)0x00)
#define CLK_CMSR_RESET_VALUE     ((uint8_t)0xE1)
#define CLK_SWR_RESET_VALUE      ((uint8_t)0xE1)
#define CLK_SWCR_RESET_VALUE     ((uint8_t)0x00)
#define CLK_CKDIVR_RESET_VALUE   ((uint8_t)0x18)
#define CLK_PCKENR1_RESET_VALUE  ((uint8_t)0xFF)
#define CLK_PCKENR2_RESET_VALUE  ((uint8_t)0xFF)
#define CLK_CSSR_RESET_VALUE     ((uint8_t)0x00)
#define CLK_CCOR_RESET_VALUE     ((uint8_t)0x00)
#define CLK_HSITRIMR_RESET_VALUE ((uint8_t)0x00)
#define CLK_SWIMCCR_RESET_VALUE  ((uint8_t)0x00)

#define CLK_ICKR_SWUAH       ((uint8_t)0x20) 	// Slow Wake-up from Active Halt/Halt modes
#define CLK_ICKR_LSIRDY      ((uint8_t)0x10) 	// Low speed internal oscillator ready
#define CLK_ICKR_LSIEN       ((uint8_t)0x08) 	// Low speed internal RC oscillator enable
#define CLK_ICKR_FHWU        ((uint8_t)0x04) 	// Fast Wake-up from Active Halt/Halt mode
#define CLK_ICKR_HSIRDY      ((uint8_t)0x02) 	// High speed internal RC oscillator ready
#define CLK_ICKR_HSIEN       ((uint8_t)0x01) 	// High speed internal RC oscillator enable
#define CLK_ECKR_HSERDY      ((uint8_t)0x02) 	// High speed external crystal oscillator ready
#define CLK_ECKR_HSEEN       ((uint8_t)0x01) 	// High speed external crystal oscillator enable
#define CLK_CMSR_CKM         ((uint8_t)0xFF) 	// Clock master status bits
#define CLK_SWR_SWI          ((uint8_t)0xFF) 	// Clock master selection bits
#define CLK_SWCR_SWIF        ((uint8_t)0x08) 	// Clock switch interrupt flag
#define CLK_SWCR_SWIEN       ((uint8_t)0x04) 	// Clock switch interrupt enable
#define CLK_SWCR_SWEN        ((uint8_t)0x02) 	// Switch start/stop
#define CLK_SWCR_SWBSY       ((uint8_t)0x01) 	// Switch busy flag
#define CLK_CKDIVR_HSIDIV    ((uint8_t)0x18) 	// High speed internal clock prescaler
#define CLK_CKDIVR_CPUDIV    ((uint8_t)0x07) 	// CPU clock prescaler
#define CLK_PCKENR1_TIM1     ((uint8_t)0x80) 	// Timer 1 clock enable
#define CLK_PCKENR1_TIM3     ((uint8_t)0x40) 	// Timer 3 clock enable
#define CLK_PCKENR1_TIM2     ((uint8_t)0x20) 	// Timer 2 clock enable
#define CLK_PCKENR1_TIM5     ((uint8_t)0x20) 	// Timer 5 clock enable
#define CLK_PCKENR1_TIM4     ((uint8_t)0x10) 	// Timer 4 clock enable
#define CLK_PCKENR1_TIM6     ((uint8_t)0x10) 	// Timer 6 clock enable
#define CLK_PCKENR1_UART    ((uint8_t)0x04) 	// UART clock enable
#define CLK_PCKENR1_SPI      ((uint8_t)0x02) 	// SPI clock enable
#define CLK_PCKENR1_I2C      ((uint8_t)0x01) 	// I2C clock enable
#define CLK_PCKENR2_CAN      ((uint8_t)0x80) 	// CAN clock enable
#define CLK_PCKENR2_ADC      ((uint8_t)0x08) 	// ADC clock enable
#define CLK_PCKENR2_AWU      ((uint8_t)0x04) 	// AWU clock enable
#define CLK_CSSR_CSSD        ((uint8_t)0x08) 	// Clock security system detection
#define CLK_CSSR_CSSDIE      ((uint8_t)0x04) 	// Clock security system detection interrupt enable
#define CLK_CSSR_AUX         ((uint8_t)0x02) 	// Auxiliary oscillator connected to master clock
#define CLK_CSSR_CSSEN       ((uint8_t)0x01) 	// Clock security system enable
#define CLK_CCOR_CCOBSY      ((uint8_t)0x40) 	// Configurable clock output busy
#define CLK_CCOR_CCORDY      ((uint8_t)0x20) 	// Configurable clock output ready
#define CLK_CCOR_CCOSEL      ((uint8_t)0x1E) 	// Configurable clock output selection
#define CLK_CCOR_CCOEN       ((uint8_t)0x01) 	// Configurable clock output enable
#define CLK_HSITRIMR_HSITRIM ((uint8_t)0x07) 	// High speed internal oscillator trimmer
#define CLK_SWIMCCR_SWIMDIV  ((uint8_t)0x01) 	// SWIM Clock Dividing Factor

typedef struct TIM1_struct
{
  __IO uint8_t CR1;   	// control register 1
  __IO uint8_t CR2;   	// control register 2
  __IO uint8_t SMCR;  	// Synchro mode control register
  __IO uint8_t ETR;   	// external trigger register
  __IO uint8_t IER;   	// interrupt enable register
  __IO uint8_t SR1;   	// status register 1
  __IO uint8_t SR2;   	// status register 2
  __IO uint8_t EGR;   	// event generation register
  __IO uint8_t CCMR1; 	// CC mode register 1
  __IO uint8_t CCMR2; 	// CC mode register 2
  __IO uint8_t CCMR3; 	// CC mode register 3
  __IO uint8_t CCMR4; 	// CC mode register 4
  __IO uint8_t CCER1; 	// CC enable register 1
  __IO uint8_t CCER2; 	// CC enable register 2
  __IO uint8_t CNTRH; 	// counter high
  __IO uint8_t CNTRL; 	// counter low
  __IO uint8_t PSCRH; 	// prescaler high
  __IO uint8_t PSCRL; 	// prescaler low
  __IO uint8_t ARRH;  	// auto-reload register high
  __IO uint8_t ARRL;  	// auto-reload register low
  __IO uint8_t RCR;   	// Repetition Counter register
  __IO uint8_t CCR1H; 	// capture/compare register 1 high
  __IO uint8_t CCR1L; 	// capture/compare register 1 low
  __IO uint8_t CCR2H; 	// capture/compare register 2 high
  __IO uint8_t CCR2L; 	// capture/compare register 2 low
  __IO uint8_t CCR3H; 	// capture/compare register 3 high
  __IO uint8_t CCR3L; 	// capture/compare register 3 low
  __IO uint8_t CCR4H; 	// capture/compare register 3 high
  __IO uint8_t CCR4L; 	// capture/compare register 3 low
  __IO uint8_t BKR;   	// Break Register
  __IO uint8_t DTR;   	// dead-time register
  __IO uint8_t OISR;  	// Output idle register
} TIM1_TypeDef;

#define TIM1_CR1_RESET_VALUE   ((uint8_t)0x00)
#define TIM1_CR2_RESET_VALUE   ((uint8_t)0x00)
#define TIM1_SMCR_RESET_VALUE  ((uint8_t)0x00)
#define TIM1_ETR_RESET_VALUE   ((uint8_t)0x00)
#define TIM1_IER_RESET_VALUE   ((uint8_t)0x00)
#define TIM1_SR1_RESET_VALUE   ((uint8_t)0x00)
#define TIM1_SR2_RESET_VALUE   ((uint8_t)0x00)
#define TIM1_EGR_RESET_VALUE   ((uint8_t)0x00)
#define TIM1_CCMR1_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCMR2_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCMR3_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCMR4_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCER1_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCER2_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CNTRH_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CNTRL_RESET_VALUE ((uint8_t)0x00)
#define TIM1_PSCRH_RESET_VALUE ((uint8_t)0x00)
#define TIM1_PSCRL_RESET_VALUE ((uint8_t)0x00)
#define TIM1_ARRH_RESET_VALUE  ((uint8_t)0xFF)
#define TIM1_ARRL_RESET_VALUE  ((uint8_t)0xFF)
#define TIM1_RCR_RESET_VALUE   ((uint8_t)0x00)
#define TIM1_CCR1H_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCR1L_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCR2H_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCR2L_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCR3H_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCR3L_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCR4H_RESET_VALUE ((uint8_t)0x00)
#define TIM1_CCR4L_RESET_VALUE ((uint8_t)0x00)
#define TIM1_BKR_RESET_VALUE   ((uint8_t)0x00)
#define TIM1_DTR_RESET_VALUE   ((uint8_t)0x00)
#define TIM1_OISR_RESET_VALUE  ((uint8_t)0x00)

#define TIM1_CR1_ARPE    ((uint8_t)0x80) 	// Auto-Reload Preload Enable mask.
#define TIM1_CR1_CMS     ((uint8_t)0x60) 	// Center-aligned Mode Selection mask.
#define TIM1_CR1_DIR     ((uint8_t)0x10) 	// Direction mask.
#define TIM1_CR1_OPM     ((uint8_t)0x08) 	// One Pulse Mode mask.
#define TIM1_CR1_URS     ((uint8_t)0x04) 	// Update Request Source mask.
#define TIM1_CR1_UDIS    ((uint8_t)0x02) 	// Update DIsable mask.
#define TIM1_CR1_CEN     ((uint8_t)0x01) 	// Counter Enable mask.
#define TIM1_CR2_TI1S    ((uint8_t)0x80) 	// TI1S Selection mask.
#define TIM1_CR2_MMS     ((uint8_t)0x70) 	// MMS Selection mask.
#define TIM1_CR2_COMS    ((uint8_t)0x04) 	// Capture/Compare Control Update Selection mask.
#define TIM1_CR2_CCPC    ((uint8_t)0x01) 	// Capture/Compare Preloaded Control mask.
#define TIM1_SMCR_MSM    ((uint8_t)0x80) 	// Master/Slave Mode mask.
#define TIM1_SMCR_TS     ((uint8_t)0x70) 	// Trigger Selection mask.
#define TIM1_SMCR_SMS    ((uint8_t)0x07) 	// Slave Mode Selection mask.
#define TIM1_ETR_ETP     ((uint8_t)0x80) 	// External Trigger Polarity mask.
#define TIM1_ETR_ECE     ((uint8_t)0x40) 	// External Clock mask.
#define TIM1_ETR_ETPS    ((uint8_t)0x30) 	// External Trigger Prescaler mask.
#define TIM1_ETR_ETF     ((uint8_t)0x0F) 	// External Trigger Filter mask.
#define TIM1_IER_BIE     ((uint8_t)0x80) 	// Break Interrupt Enable mask.
#define TIM1_IER_TIE     ((uint8_t)0x40) 	// Trigger Interrupt Enable mask.
#define TIM1_IER_COMIE   ((uint8_t)0x20) 	//  Commutation Interrupt Enable mask.
#define TIM1_IER_CC4IE   ((uint8_t)0x10) 	// Capture/Compare 4 Interrupt Enable mask.
#define TIM1_IER_CC3IE   ((uint8_t)0x08) 	// Capture/Compare 3 Interrupt Enable mask.
#define TIM1_IER_CC2IE   ((uint8_t)0x04) 	// Capture/Compare 2 Interrupt Enable mask.
#define TIM1_IER_CC1IE   ((uint8_t)0x02) 	// Capture/Compare 1 Interrupt Enable mask.
#define TIM1_IER_UIE     ((uint8_t)0x01) 	// Update Interrupt Enable mask.
#define TIM1_SR1_BIF     ((uint8_t)0x80) 	// Break Interrupt Flag mask.
#define TIM1_SR1_TIF     ((uint8_t)0x40) 	// Trigger Interrupt Flag mask.
#define TIM1_SR1_COMIF   ((uint8_t)0x20) 	// Commutation Interrupt Flag mask.
#define TIM1_SR1_CC4IF   ((uint8_t)0x10) 	// Capture/Compare 4 Interrupt Flag mask.
#define TIM1_SR1_CC3IF   ((uint8_t)0x08) 	// Capture/Compare 3 Interrupt Flag mask.
#define TIM1_SR1_CC2IF   ((uint8_t)0x04) 	// Capture/Compare 2 Interrupt Flag mask.
#define TIM1_SR1_CC1IF   ((uint8_t)0x02) 	// Capture/Compare 1 Interrupt Flag mask.
#define TIM1_SR1_UIF     ((uint8_t)0x01) 	// Update Interrupt Flag mask.
#define TIM1_SR2_CC4OF   ((uint8_t)0x10) 	// Capture/Compare 4 Overcapture Flag mask.
#define TIM1_SR2_CC3OF   ((uint8_t)0x08) 	// Capture/Compare 3 Overcapture Flag mask.
#define TIM1_SR2_CC2OF   ((uint8_t)0x04) 	// Capture/Compare 2 Overcapture Flag mask.
#define TIM1_SR2_CC1OF   ((uint8_t)0x02) 	// Capture/Compare 1 Overcapture Flag mask.
#define TIM1_EGR_BG      ((uint8_t)0x80) 	// Break Generation mask.
#define TIM1_EGR_TG      ((uint8_t)0x40) 	// Trigger Generation mask.
#define TIM1_EGR_COMG    ((uint8_t)0x20) 	// Capture/Compare Control Update Generation mask.
#define TIM1_EGR_CC4G    ((uint8_t)0x10) 	// Capture/Compare 4 Generation mask.
#define TIM1_EGR_CC3G    ((uint8_t)0x08) 	// Capture/Compare 3 Generation mask.
#define TIM1_EGR_CC2G    ((uint8_t)0x04) 	// Capture/Compare 2 Generation mask.
#define TIM1_EGR_CC1G    ((uint8_t)0x02) 	// Capture/Compare 1 Generation mask.
#define TIM1_EGR_UG      ((uint8_t)0x01) 	// Update Generation mask.
#define TIM1_CCMR_ICxPSC ((uint8_t)0x0C) 	// Input Capture x Prescaler mask.
#define TIM1_CCMR_ICxF   ((uint8_t)0xF0) 	// Input Capture x Filter mask.
#define TIM1_CCMR_OCM    ((uint8_t)0x70) 	// Output Compare x Mode mask.
#define TIM1_CCMR_OCxPE  ((uint8_t)0x08) 	// Output Compare x Preload Enable mask.
#define TIM1_CCMR_OCxFE  ((uint8_t)0x04) 	// Output Compare x Fast Enable mask.
#define TIM1_CCMR_CCxS   ((uint8_t)0x03) 	// Capture/Compare x Selection mask.
#define CCMR_TIxDirect_Set ((uint8_t)0x01)
#define TIM1_CCER1_CC2NP ((uint8_t)0x80) 	// Capture/Compare 2 Complementary output Polarity mask.
#define TIM1_CCER1_CC2NE ((uint8_t)0x40) 	// Capture/Compare 2 Complementary output enable mask.
#define TIM1_CCER1_CC2P  ((uint8_t)0x20) 	// Capture/Compare 2 output Polarity mask.
#define TIM1_CCER1_CC2E  ((uint8_t)0x10) 	// Capture/Compare 2 output enable mask.
#define TIM1_CCER1_CC1NP ((uint8_t)0x08) 	// Capture/Compare 1 Complementary output Polarity mask.
#define TIM1_CCER1_CC1NE ((uint8_t)0x04) 	// Capture/Compare 1 Complementary output enable mask.
#define TIM1_CCER1_CC1P  ((uint8_t)0x02) 	// Capture/Compare 1 output Polarity mask.
#define TIM1_CCER1_CC1E  ((uint8_t)0x01) 	// Capture/Compare 1 output enable mask.
#define TIM1_CCER2_CC4P  ((uint8_t)0x20) 	// Capture/Compare 4 output Polarity mask.
#define TIM1_CCER2_CC4E  ((uint8_t)0x10) 	// Capture/Compare 4 output enable mask.
#define TIM1_CCER2_CC3NP ((uint8_t)0x08) 	// Capture/Compare 3 Complementary output Polarity mask.
#define TIM1_CCER2_CC3NE ((uint8_t)0x04) 	// Capture/Compare 3 Complementary output enable mask.
#define TIM1_CCER2_CC3P  ((uint8_t)0x02) 	// Capture/Compare 3 output Polarity mask.
#define TIM1_CCER2_CC3E  ((uint8_t)0x01) 	// Capture/Compare 3 output enable mask.
#define TIM1_CNTRH_CNT   ((uint8_t)0xFF) 	// Counter Value (MSB) mask.
#define TIM1_CNTRL_CNT   ((uint8_t)0xFF) 	// Counter Value (LSB) mask.
#define TIM1_PSCH_PSC    ((uint8_t)0xFF) 	// Prescaler Value (MSB) mask.
#define TIM1_PSCL_PSC    ((uint8_t)0xFF) 	// Prescaler Value (LSB) mask.
#define TIM1_ARRH_ARR    ((uint8_t)0xFF) 	// Autoreload Value (MSB) mask.
#define TIM1_ARRL_ARR    ((uint8_t)0xFF) 	// Autoreload Value (LSB) mask.
#define TIM1_RCR_REP     ((uint8_t)0xFF) 	// Repetition Counter Value mask.
#define TIM1_CCR1H_CCR1  ((uint8_t)0xFF) 	// Capture/Compare 1 Value (MSB) mask.
#define TIM1_CCR1L_CCR1  ((uint8_t)0xFF) 	// Capture/Compare 1 Value (LSB) mask.
#define TIM1_CCR2H_CCR2  ((uint8_t)0xFF) 	// Capture/Compare 2 Value (MSB) mask.
#define TIM1_CCR2L_CCR2  ((uint8_t)0xFF) 	// Capture/Compare 2 Value (LSB) mask.
#define TIM1_CCR3H_CCR3  ((uint8_t)0xFF) 	// Capture/Compare 3 Value (MSB) mask.
#define TIM1_CCR3L_CCR3  ((uint8_t)0xFF) 	// Capture/Compare 3 Value (LSB) mask.
#define TIM1_CCR4H_CCR4  ((uint8_t)0xFF) 	// Capture/Compare 4 Value (MSB) mask.
#define TIM1_CCR4L_CCR4  ((uint8_t)0xFF) 	// Capture/Compare 4 Value (LSB) mask.
#define TIM1_BKR_MOE     ((uint8_t)0x80) 	// Main Output Enable mask.
#define TIM1_BKR_AOE     ((uint8_t)0x40) 	// Automatic Output Enable mask.
#define TIM1_BKR_BKP     ((uint8_t)0x20) 	// Break Polarity mask.
#define TIM1_BKR_BKE     ((uint8_t)0x10) 	// Break Enable mask.
#define TIM1_BKR_OSSR    ((uint8_t)0x08) 	// Off-State Selection for Run mode mask.
#define TIM1_BKR_OSSI    ((uint8_t)0x04) 	// Off-State Selection for Idle mode mask.
#define TIM1_BKR_LOCK    ((uint8_t)0x03) 	// Lock Configuration mask.
#define TIM1_DTR_DTG     ((uint8_t)0xFF) 	// Dead-Time Generator set-up mask.
#define TIM1_OISR_OIS4   ((uint8_t)0x40) 	// Output Idle state 4 (OC4 output) mask.
#define TIM1_OISR_OIS3N  ((uint8_t)0x20) 	// Output Idle state 3 (OC3N output) mask.
#define TIM1_OISR_OIS3   ((uint8_t)0x10) 	// Output Idle state 3 (OC3 output) mask.
#define TIM1_OISR_OIS2N  ((uint8_t)0x08) 	// Output Idle state 2 (OC2N output) mask.
#define TIM1_OISR_OIS2   ((uint8_t)0x04) 	// Output Idle state 2 (OC2 output) mask.
#define TIM1_OISR_OIS1N  ((uint8_t)0x02) 	// Output Idle state 1 (OC1N output) mask.
#define TIM1_OISR_OIS1   ((uint8_t)0x01) 	// Output Idle state 1 (OC1 output) mask.

typedef struct TIM2_struct
{
    __IO uint8_t CR1;   	// control register 1
    uint8_t RESERVED1;  	// Reserved register
    uint8_t RESERVED2;  	// Reserved register
    __IO uint8_t IER;   	// interrupt enable register
    __IO uint8_t SR1;   	// status register 1
    __IO uint8_t SR2;   	// status register 2
    __IO uint8_t EGR;   	// event generation register
    __IO uint8_t CCMR1; 	// CC mode register 1
    __IO uint8_t CCMR2; 	// CC mode register 2
    __IO uint8_t CCMR3; 	// CC mode register 3
    __IO uint8_t CCER1; 	// CC enable register 1
    __IO uint8_t CCER2; 	// CC enable register 2
    __IO uint8_t CNTRH; 	// counter high
    __IO uint8_t CNTRL; 	// counter low
    __IO uint8_t PSCR;  	// prescaler register
    __IO uint8_t ARRH;  	// auto-reload register high
    __IO uint8_t ARRL;  	// auto-reload register low
    __IO uint8_t CCR1H; 	// capture/compare register 1 high
    __IO uint8_t CCR1L; 	// capture/compare register 1 low
    __IO uint8_t CCR2H; 	// capture/compare register 2 high
    __IO uint8_t CCR2L; 	// capture/compare register 2 low
    __IO uint8_t CCR3H; 	// capture/compare register 3 high
    __IO uint8_t CCR3L; 	// capture/compare register 3 low
} TIM2_TypeDef;

#define TIM2_CR1_RESET_VALUE   ((uint8_t)0x00)
#define TIM2_IER_RESET_VALUE   ((uint8_t)0x00)
#define TIM2_SR1_RESET_VALUE   ((uint8_t)0x00)
#define TIM2_SR2_RESET_VALUE   ((uint8_t)0x00)
#define TIM2_EGR_RESET_VALUE   ((uint8_t)0x00)
#define TIM2_CCMR1_RESET_VALUE ((uint8_t)0x00)
#define TIM2_CCMR2_RESET_VALUE ((uint8_t)0x00)
#define TIM2_CCMR3_RESET_VALUE ((uint8_t)0x00)
#define TIM2_CCER1_RESET_VALUE ((uint8_t)0x00)
#define TIM2_CCER2_RESET_VALUE ((uint8_t)0x00)
#define TIM2_CNTRH_RESET_VALUE ((uint8_t)0x00)
#define TIM2_CNTRL_RESET_VALUE ((uint8_t)0x00)
#define TIM2_PSCR_RESET_VALUE  ((uint8_t)0x00)
#define TIM2_ARRH_RESET_VALUE  ((uint8_t)0xFF)
#define TIM2_ARRL_RESET_VALUE  ((uint8_t)0xFF)
#define TIM2_CCR1H_RESET_VALUE ((uint8_t)0x00)
#define TIM2_CCR1L_RESET_VALUE ((uint8_t)0x00)
#define TIM2_CCR2H_RESET_VALUE ((uint8_t)0x00)
#define TIM2_CCR2L_RESET_VALUE ((uint8_t)0x00)
#define TIM2_CCR3H_RESET_VALUE ((uint8_t)0x00)
#define TIM2_CCR3L_RESET_VALUE ((uint8_t)0x00)

#define TIM2_CR1_ARPE    ((uint8_t)0x80) 	// Auto-Reload Preload Enable mask.
#define TIM2_CR1_OPM     ((uint8_t)0x08) 	// One Pulse Mode mask.
#define TIM2_CR1_URS     ((uint8_t)0x04) 	// Update Request Source mask.
#define TIM2_CR1_UDIS    ((uint8_t)0x02) 	// Update DIsable mask.
#define TIM2_CR1_CEN     ((uint8_t)0x01) 	// Counter Enable mask.
#define TIM2_IER_CC3IE   ((uint8_t)0x08) 	// Capture/Compare 3 Interrupt Enable mask.
#define TIM2_IER_CC2IE   ((uint8_t)0x04) 	// Capture/Compare 2 Interrupt Enable mask.
#define TIM2_IER_CC1IE   ((uint8_t)0x02) 	// Capture/Compare 1 Interrupt Enable mask.
#define TIM2_IER_UIE     ((uint8_t)0x01) 	// Update Interrupt Enable mask.
#define TIM2_SR1_CC3IF   ((uint8_t)0x08) 	// Capture/Compare 3 Interrupt Flag mask.
#define TIM2_SR1_CC2IF   ((uint8_t)0x04) 	// Capture/Compare 2 Interrupt Flag mask.
#define TIM2_SR1_CC1IF   ((uint8_t)0x02) 	// Capture/Compare 1 Interrupt Flag mask.
#define TIM2_SR1_UIF     ((uint8_t)0x01) 	// Update Interrupt Flag mask.
#define TIM2_SR2_CC3OF   ((uint8_t)0x08) 	// Capture/Compare 3 Overcapture Flag mask.
#define TIM2_SR2_CC2OF   ((uint8_t)0x04) 	// Capture/Compare 2 Overcapture Flag mask.
#define TIM2_SR2_CC1OF   ((uint8_t)0x02) 	// Capture/Compare 1 Overcapture Flag mask.
#define TIM2_EGR_CC3G    ((uint8_t)0x08) 	// Capture/Compare 3 Generation mask.
#define TIM2_EGR_CC2G    ((uint8_t)0x04) 	// Capture/Compare 2 Generation mask.
#define TIM2_EGR_CC1G    ((uint8_t)0x02) 	// Capture/Compare 1 Generation mask.
#define TIM2_EGR_UG      ((uint8_t)0x01) 	// Update Generation mask.
#define TIM2_CCMR_ICxPSC ((uint8_t)0x0C) 	// Input Capture x Prescaler mask.
#define TIM2_CCMR_ICxF   ((uint8_t)0xF0) 	// Input Capture x Filter mask.
#define TIM2_CCMR_OCM    ((uint8_t)0x70) 	// Output Compare x Mode mask.
#define TIM2_CCMR_OCxPE  ((uint8_t)0x08) 	// Output Compare x Preload Enable mask.
#define TIM2_CCMR_CCxS   ((uint8_t)0x03) 	// Capture/Compare x Selection mask.
#define TIM2_CCER1_CC2P  ((uint8_t)0x20) 	// Capture/Compare 2 output Polarity mask.
#define TIM2_CCER1_CC2E  ((uint8_t)0x10) 	// Capture/Compare 2 output enable mask.
#define TIM2_CCER1_CC1P  ((uint8_t)0x02) 	// Capture/Compare 1 output Polarity mask.
#define TIM2_CCER1_CC1E  ((uint8_t)0x01) 	// Capture/Compare 1 output enable mask.
#define TIM2_CCER2_CC3P  ((uint8_t)0x02) 	// Capture/Compare 3 output Polarity mask.
#define TIM2_CCER2_CC3E  ((uint8_t)0x01) 	// Capture/Compare 3 output enable mask.
#define TIM2_CNTRH_CNT   ((uint8_t)0xFF) 	// Counter Value (MSB) mask.
#define TIM2_CNTRL_CNT   ((uint8_t)0xFF) 	// Counter Value (LSB) mask.
#define TIM2_PSCR_PSC    ((uint8_t)0xFF) 	// Prescaler Value (MSB) mask.
#define TIM2_ARRH_ARR    ((uint8_t)0xFF) 	// Autoreload Value (MSB) mask.
#define TIM2_ARRL_ARR    ((uint8_t)0xFF) 	// Autoreload Value (LSB) mask.
#define TIM2_CCR1H_CCR1  ((uint8_t)0xFF) 	// Capture/Compare 1 Value (MSB) mask.
#define TIM2_CCR1L_CCR1  ((uint8_t)0xFF) 	// Capture/Compare 1 Value (LSB) mask.
#define TIM2_CCR2H_CCR2  ((uint8_t)0xFF) 	// Capture/Compare 2 Value (MSB) mask.
#define TIM2_CCR2L_CCR2  ((uint8_t)0xFF) 	// Capture/Compare 2 Value (LSB) mask.
#define TIM2_CCR3H_CCR3  ((uint8_t)0xFF) 	// Capture/Compare 3 Value (MSB) mask.
#define TIM2_CCR3L_CCR3  ((uint8_t)0xFF) 	// Capture/Compare 3 Value (LSB) mask.

typedef struct TIM3_struct
{
    __IO uint8_t CR1;   	// control register 1
    __IO uint8_t IER;   	// interrupt enable register
    __IO uint8_t SR1;   	// status register 1
    __IO uint8_t SR2;   	// status register 2
    __IO uint8_t EGR;   	// event generation register
    __IO uint8_t CCMR1; 	// CC mode register 1
    __IO uint8_t CCMR2; 	// CC mode register 2
    __IO uint8_t CCER1; 	// CC enable register 1
    __IO uint8_t CNTRH; 	// counter high
    __IO uint8_t CNTRL; 	// counter low
    __IO uint8_t PSCR;  	// prescaler register
    __IO uint8_t ARRH;  	// auto-reload register high
    __IO uint8_t ARRL;  	// auto-reload register low
    __IO uint8_t CCR1H; 	// capture/compare register 1 high
    __IO uint8_t CCR1L; 	// capture/compare register 1 low
    __IO uint8_t CCR2H; 	// capture/compare register 2 high
    __IO uint8_t CCR2L; 	// capture/compare register 2 low
} TIM3_TypeDef;

#define TIM3_CR1_RESET_VALUE   ((uint8_t)0x00)
#define TIM3_IER_RESET_VALUE   ((uint8_t)0x00)
#define TIM3_SR1_RESET_VALUE   ((uint8_t)0x00)
#define TIM3_SR2_RESET_VALUE   ((uint8_t)0x00)
#define TIM3_EGR_RESET_VALUE   ((uint8_t)0x00)
#define TIM3_CCMR1_RESET_VALUE ((uint8_t)0x00)
#define TIM3_CCMR2_RESET_VALUE ((uint8_t)0x00)
#define TIM3_CCER1_RESET_VALUE ((uint8_t)0x00)
#define TIM3_CNTRH_RESET_VALUE ((uint8_t)0x00)
#define TIM3_CNTRL_RESET_VALUE ((uint8_t)0x00)
#define TIM3_PSCR_RESET_VALUE  ((uint8_t)0x00)
#define TIM3_ARRH_RESET_VALUE  ((uint8_t)0xFF)
#define TIM3_ARRL_RESET_VALUE  ((uint8_t)0xFF)
#define TIM3_CCR1H_RESET_VALUE ((uint8_t)0x00)
#define TIM3_CCR1L_RESET_VALUE ((uint8_t)0x00)
#define TIM3_CCR2H_RESET_VALUE ((uint8_t)0x00)
#define TIM3_CCR2L_RESET_VALUE ((uint8_t)0x00)

#define TIM3_CR1_ARPE    ((uint8_t)0x80) 	// Auto-Reload Preload Enable mask.
#define TIM3_CR1_OPM     ((uint8_t)0x08) 	// One Pulse Mode mask.
#define TIM3_CR1_URS     ((uint8_t)0x04) 	// Update Request Source mask.
#define TIM3_CR1_UDIS    ((uint8_t)0x02) 	// Update DIsable mask.
#define TIM3_CR1_CEN     ((uint8_t)0x01) 	// Counter Enable mask.
#define TIM3_IER_CC2IE   ((uint8_t)0x04) 	// Capture/Compare 2 Interrupt Enable mask.
#define TIM3_IER_CC1IE   ((uint8_t)0x02) 	// Capture/Compare 1 Interrupt Enable mask.
#define TIM3_IER_UIE     ((uint8_t)0x01) 	// Update Interrupt Enable mask.
#define TIM3_SR1_CC2IF   ((uint8_t)0x04) 	// Capture/Compare 2 Interrupt Flag mask.
#define TIM3_SR1_CC1IF   ((uint8_t)0x02) 	// Capture/Compare 1 Interrupt Flag mask.
#define TIM3_SR1_UIF     ((uint8_t)0x01) 	// Update Interrupt Flag mask.
#define TIM3_SR2_CC2OF   ((uint8_t)0x04) 	// Capture/Compare 2 Overcapture Flag mask.
#define TIM3_SR2_CC1OF   ((uint8_t)0x02) 	// Capture/Compare 1 Overcapture Flag mask.
#define TIM3_EGR_CC2G    ((uint8_t)0x04) 	// Capture/Compare 2 Generation mask.
#define TIM3_EGR_CC1G    ((uint8_t)0x02) 	// Capture/Compare 1 Generation mask.
#define TIM3_EGR_UG      ((uint8_t)0x01) 	// Update Generation mask.
#define TIM3_CCMR_ICxPSC ((uint8_t)0x0C) 	// Input Capture x Prescaler mask.
#define TIM3_CCMR_ICxF   ((uint8_t)0xF0) 	// Input Capture x Filter mask.
#define TIM3_CCMR_OCM    ((uint8_t)0x70) 	// Output Compare x Mode mask.
#define TIM3_CCMR_OCxPE  ((uint8_t)0x08) 	// Output Compare x Preload Enable mask.
#define TIM3_CCMR_CCxS   ((uint8_t)0x03) 	// Capture/Compare x Selection mask.
#define TIM3_CCER1_CC2P  ((uint8_t)0x20) 	// Capture/Compare 2 output Polarity mask.
#define TIM3_CCER1_CC2E  ((uint8_t)0x10) 	// Capture/Compare 2 output enable mask.
#define TIM3_CCER1_CC1P  ((uint8_t)0x02) 	// Capture/Compare 1 output Polarity mask.
#define TIM3_CCER1_CC1E  ((uint8_t)0x01) 	// Capture/Compare 1 output enable mask.
#define TIM3_CNTRH_CNT   ((uint8_t)0xFF) 	// Counter Value (MSB) mask.
#define TIM3_CNTRL_CNT   ((uint8_t)0xFF) 	// Counter Value (LSB) mask.
#define TIM3_PSCR_PSC    ((uint8_t)0xFF) 	// Prescaler Value (MSB) mask.
#define TIM3_ARRH_ARR    ((uint8_t)0xFF) 	// Autoreload Value (MSB) mask.
#define TIM3_ARRL_ARR    ((uint8_t)0xFF) 	// Autoreload Value (LSB) mask.
#define TIM3_CCR1H_CCR1  ((uint8_t)0xFF) 	// Capture/Compare 1 Value (MSB) mask.
#define TIM3_CCR1L_CCR1  ((uint8_t)0xFF) 	// Capture/Compare 1 Value (LSB) mask.
#define TIM3_CCR2H_CCR2  ((uint8_t)0xFF) 	// Capture/Compare 2 Value (MSB) mask.
#define TIM3_CCR2L_CCR2  ((uint8_t)0xFF) 	// Capture/Compare 2 Value (LSB) mask.

typedef struct TIM4_struct
{
    __IO uint8_t CR1;  	// control register 1
    uint8_t RESERVED1; 	// Reserved register
    uint8_t RESERVED2; 	// Reserved register
    __IO uint8_t IER;  	// interrupt enable register
    __IO uint8_t SR1;  	// status register 1
    __IO uint8_t EGR;  	// event generation register
    __IO uint8_t CNTR; 	// counter register
    __IO uint8_t PSCR; 	// prescaler register
    __IO uint8_t ARR;  	// auto-reload register
} TIM4_TypeDef;

#define TIM4_CR1_RESET_VALUE  ((uint8_t)0x00)
#define TIM4_IER_RESET_VALUE  ((uint8_t)0x00)
#define TIM4_SR1_RESET_VALUE  ((uint8_t)0x00)
#define TIM4_EGR_RESET_VALUE  ((uint8_t)0x00)
#define TIM4_CNTR_RESET_VALUE ((uint8_t)0x00)
#define TIM4_PSCR_RESET_VALUE ((uint8_t)0x00)
#define TIM4_ARR_RESET_VALUE  ((uint8_t)0xFF)

#define TIM4_CR1_ARPE ((uint8_t)0x80) 	// Auto-Reload Preload Enable mask.
#define TIM4_CR1_OPM  ((uint8_t)0x08) 	// One Pulse Mode mask.
#define TIM4_CR1_URS  ((uint8_t)0x04) 	// Update Request Source mask.
#define TIM4_CR1_UDIS ((uint8_t)0x02) 	// Update DIsable mask.
#define TIM4_CR1_CEN  ((uint8_t)0x01) 	// Counter Enable mask.
#define TIM4_IER_UIE  ((uint8_t)0x01) 	// Update Interrupt Enable mask.
#define TIM4_SR1_UIF  ((uint8_t)0x01) 	// Update Interrupt Flag mask.
#define TIM4_EGR_UG   ((uint8_t)0x01) 	// Update Generation mask.
#define TIM4_CNTR_CNT ((uint8_t)0xFF) 	// Counter Value (LSB) mask.
#define TIM4_PSCR_PSC ((uint8_t)0x07) 	// Prescaler Value  mask.
#define TIM4_ARR_ARR  ((uint8_t)0xFF) 	// Autoreload Value mask.


typedef struct I2C_struct
{
    __IO uint8_t CR1;       	// I2C control register 1
    __IO uint8_t CR2;       	// I2C control register 2
    __IO uint8_t FREQR;     	// I2C frequency register
    __IO uint8_t OARL;      	// I2C own address register LSB
    __IO uint8_t OARH;      	// I2C own address register MSB
    uint8_t RESERVED1;      	// Reserved byte
    __IO uint8_t DR;        	// I2C data register
    __IO uint8_t SR1;       	// I2C status register 1
    __IO uint8_t SR2;       	// I2C status register 2
    __IO uint8_t SR3;       	// I2C status register 3
    __IO uint8_t ITR;       	// I2C interrupt register
    __IO uint8_t CCRL;      	// I2C clock control register low
    __IO uint8_t CCRH;      	// I2C clock control register high
    __IO uint8_t TRISER;    	// I2C maximum rise time register
    uint8_t RESERVED2;      	// Reserved byte
} I2C_TypeDef;

#define I2C_CR1_RESET_VALUE    ((uint8_t)0x00)
#define I2C_CR2_RESET_VALUE    ((uint8_t)0x00)
#define I2C_FREQR_RESET_VALUE  ((uint8_t)0x00)
#define I2C_OARL_RESET_VALUE   ((uint8_t)0x00)
#define I2C_OARH_RESET_VALUE   ((uint8_t)0x00)
#define I2C_DR_RESET_VALUE     ((uint8_t)0x00)
#define I2C_SR1_RESET_VALUE    ((uint8_t)0x00)
#define I2C_SR2_RESET_VALUE    ((uint8_t)0x00)
#define I2C_SR3_RESET_VALUE    ((uint8_t)0x00)
#define I2C_ITR_RESET_VALUE    ((uint8_t)0x00)
#define I2C_CCRL_RESET_VALUE   ((uint8_t)0x00)
#define I2C_CCRH_RESET_VALUE   ((uint8_t)0x00)
#define I2C_TRISER_RESET_VALUE ((uint8_t)0x02)

#define I2C_CR1_NOSTRETCH   ((uint8_t)0x80)     	// Clock Stretching Disable (Slave mode)
#define I2C_CR1_ENGC        ((uint8_t)0x40)     	// General Call Enable
#define I2C_CR1_PE          ((uint8_t)0x01)     	// Peripheral Enable
#define I2C_CR2_SWRST       ((uint8_t)0x80)     	// Software Reset
#define I2C_CR2_POS         ((uint8_t)0x08)     	// Acknowledge
#define I2C_CR2_ACK         ((uint8_t)0x04)     	// Acknowledge Enable
#define I2C_CR2_STOP        ((uint8_t)0x02)     	// Stop Generation
#define I2C_CR2_START       ((uint8_t)0x01)     	// Start Generation
#define I2C_FREQR_FREQ      ((uint8_t)0x3F)     	// Peripheral Clock Frequency
#define I2C_OARL_ADD        ((uint8_t)0xFE)     	// Interface Address bits [7..1]
#define I2C_OARL_ADD0       ((uint8_t)0x01)     	// Interface Address bit0
#define I2C_OARH_ADDMODE    ((uint8_t)0x80)     	// Addressing Mode (Slave mode)
#define I2C_OARH_ADDCONF    ((uint8_t)0x40)     	// Address Mode Configuration
#define I2C_OARH_ADD        ((uint8_t)0x06)     	// Interface Address bits [9..8]
#define I2C_DR_DR           ((uint8_t)0xFF)     	// Data Register
#define I2C_SR1_TXE         ((uint8_t)0x80)     	// Data Register Empty (transmitters)
#define I2C_SR1_RXNE        ((uint8_t)0x40)     	// Data Register not Empty (receivers)
#define I2C_SR1_STOPF       ((uint8_t)0x10)     	// Stop detection (Slave mode)
#define I2C_SR1_ADD10       ((uint8_t)0x08)     	// 10-bit header sent (Master mode)
#define I2C_SR1_BTF         ((uint8_t)0x04)     	// Byte Transfer Finished
#define I2C_SR1_ADDR        ((uint8_t)0x02)     	// Address sent (master mode)/matched (slave mode)
#define I2C_SR1_SB          ((uint8_t)0x01)     	// Start Bit (Master mode)
#define I2C_SR2_WUFH        ((uint8_t)0x20)     	// Wake-up from Halt
#define I2C_SR2_OVR         ((uint8_t)0x08)     	// Overrun/Underrun
#define I2C_SR2_AF          ((uint8_t)0x04)     	// Acknowledge Failure
#define I2C_SR2_ARLO        ((uint8_t)0x02)     	// Arbitration Lost (master mode)
#define I2C_SR2_BERR        ((uint8_t)0x01)     	// Bus Error
#define I2C_SR3_GENCALL     ((uint8_t)0x10)     	// General Call Header (Slave mode)
#define I2C_SR3_TRA         ((uint8_t)0x04)     	// Transmitter/Receiver
#define I2C_SR3_BUSY        ((uint8_t)0x02)     	// Bus Busy
#define I2C_SR3_MSL         ((uint8_t)0x01)     	// Master/Slave
#define I2C_ITR_ITBUFEN     ((uint8_t)0x04)     	// Buffer Interrupt Enable
#define I2C_ITR_ITEVTEN     ((uint8_t)0x02)     	// Event Interrupt Enable
#define I2C_ITR_ITERREN     ((uint8_t)0x01)     	// Error Interrupt Enable
#define I2C_CCRL_CCR        ((uint8_t)0xFF)     	// Clock Control Register (Master mode)
#define I2C_CCRH_FS         ((uint8_t)0x80)     	// Master Mode Selection
#define I2C_CCRH_DUTY       ((uint8_t)0x40)     	// Fast Mode Duty Cycle
#define I2C_CCRH_CCR        ((uint8_t)0x0F)     	// Clock Control Register in Fast/Standard mode (Master mode) bits [11..8]
#define I2C_TRISER_TRISE    ((uint8_t)0x3F)     	// Maximum Rise Time in Fast/Standard mode (Master mode)

typedef struct ITC_struct
{
    __IO uint8_t ISPR1;     // Interrupt Software Priority register 1
    __IO uint8_t ISPR2;     // Interrupt Software Priority register 2
    __IO uint8_t ISPR3;     // Interrupt Software Priority register 3
    __IO uint8_t ISPR4;     // Interrupt Software Priority register 4
    __IO uint8_t ISPR5;     // Interrupt Software Priority register 5
    __IO uint8_t ISPR6;     // Interrupt Software Priority register 6
    __IO uint8_t ISPR7;     // Interrupt Software Priority register 7
    __IO uint8_t ISPR8;     // Interrupt Software Priority register 8
} ITC_TypeDef;

#define ITC_SPRX_RESET_VALUE ((uint8_t)0xFF) 	// Reset value of Software Priority registers
#define CPU_CC_I1I0 ((uint8_t)0x28) 			// Condition Code register, I1 and I0 bits mask

typedef struct EXTI_struct
{
    __IO uint8_t CR1; 		// External Interrupt Control Register for PORTA to PORTD
    __IO uint8_t CR2; 		// External Interrupt Control Register for PORTE and TLI
} EXTI_TypeDef;

#define EXTI_CR1_RESET_VALUE ((uint8_t)0x00)
#define EXTI_CR2_RESET_VALUE ((uint8_t)0x00)

#define EXTI_CR1_PDIS ((uint8_t)0xC0)	 // PORTD external interrupt sensitivity bits mask
#define EXTI_CR1_PCIS ((uint8_t)0x30)	 // PORTC external interrupt sensitivity bits mask
#define EXTI_CR1_PBIS ((uint8_t)0x0C)	 // PORTB external interrupt sensitivity bits mask
#define EXTI_CR1_PAIS ((uint8_t)0x03)	 // PORTA external interrupt sensitivity bits mask
#define EXTI_CR2_TLIS ((uint8_t)0x04)	 // Top level interrupt sensitivity bit mask
#define EXTI_CR2_PEIS ((uint8_t)0x03)	 // PORTE external interrupt sensitivity bits mask

typedef struct FLASH_struct
{
    __IO uint8_t CR1;       // Flash control register 1
    __IO uint8_t CR2;       // Flash control register 2
    __IO uint8_t NCR2;      // Flash complementary control register 2
    __IO uint8_t FPR;       // Flash protection register
    __IO uint8_t NFPR;      // Flash complementary protection register
    __IO uint8_t IAPSR;     // Flash in-application programming status register
    uint8_t RESERVED1;      // Reserved byte
    uint8_t RESERVED2;      // Reserved byte
    __IO uint8_t PUKR;      // Flash program memory unprotection register
    uint8_t RESERVED3;      // Reserved byte
    __IO uint8_t DUKR;      // Data EEPROM unprotection register
} FLASH_TypeDef;

#define FLASH_CR1_RESET_VALUE   ((uint8_t)0x00)
#define FLASH_CR2_RESET_VALUE   ((uint8_t)0x00)
#define FLASH_NCR2_RESET_VALUE  ((uint8_t)0xFF)
#define FLASH_IAPSR_RESET_VALUE ((uint8_t)0x40)
#define FLASH_PUKR_RESET_VALUE  ((uint8_t)0x00)
#define FLASH_DUKR_RESET_VALUE  ((uint8_t)0x00)

#define FLASH_CR1_HALT        ((uint8_t)0x08) 	// Standby in Halt mode mask
#define FLASH_CR1_AHALT       ((uint8_t)0x04) 	// Standby in Active Halt mode mask
#define FLASH_CR1_IE          ((uint8_t)0x02) 	// Flash Interrupt enable mask
#define FLASH_CR1_FIX         ((uint8_t)0x01) 	// Fix programming time mask
#define FLASH_CR2_OPT         ((uint8_t)0x80) 	// Select option byte mask
#define FLASH_CR2_WPRG        ((uint8_t)0x40) 	// Word Programming mask
#define FLASH_CR2_ERASE       ((uint8_t)0x20) 	// Erase block mask
#define FLASH_CR2_FPRG        ((uint8_t)0x10) 	// Fast programming mode mask
#define FLASH_CR2_PRG         ((uint8_t)0x01) 	// Program block mask
#define FLASH_NCR2_NOPT       ((uint8_t)0x80) 	// Select option byte mask
#define FLASH_NCR2_NWPRG      ((uint8_t)0x40) 	// Word Programming mask
#define FLASH_NCR2_NERASE     ((uint8_t)0x20) 	// Erase block mask
#define FLASH_NCR2_NFPRG      ((uint8_t)0x10) 	// Fast programming mode mask
#define FLASH_NCR2_NPRG       ((uint8_t)0x01) 	// Program block mask
#define FLASH_IAPSR_HVOFF     ((uint8_t)0x40) 	// End of high voltage flag mask
#define FLASH_IAPSR_DUL       ((uint8_t)0x08) 	// Data EEPROM unlocked flag mask
#define FLASH_IAPSR_EOP       ((uint8_t)0x04) 	// End of operation flag mask
#define FLASH_IAPSR_PUL       ((uint8_t)0x02) 	// Flash Program memory unlocked flag mask
#define FLASH_IAPSR_WR_PG_DIS ((uint8_t)0x01) 	// Write attempted to protected page mask
#define FLASH_PUKR_PUK        ((uint8_t)0xFF) 	// Flash Program memory unprotection mask
#define FLASH_DUKR_DUK        ((uint8_t)0xFF) 	// Data EEPROM unprotection mask

typedef struct OPT_struct
{
    __IO uint8_t OPT0;  	// Option byte 0: Read-out protection (not accessible in IAP mode)
    __IO uint8_t OPT1;  	// Option byte 1: User boot code
    __IO uint8_t NOPT1; 	// Complementary Option byte 1
    __IO uint8_t OPT2;  	// Option byte 2: Alternate function remapping
    __IO uint8_t NOPT2; 	// Complementary Option byte 2
    __IO uint8_t OPT3;  	// Option byte 3: Watchdog option
    __IO uint8_t NOPT3; 	// Complementary Option byte 3
    __IO uint8_t OPT4;  	// Option byte 4: Clock option
    __IO uint8_t NOPT4; 	// Complementary Option byte 4
    __IO uint8_t OPT5;  	// Option byte 5: HSE clock startup
    __IO uint8_t NOPT5; 	// Complementary Option byte 5
    uint8_t RESERVED1;  	// Reserved Option byte
    uint8_t RESERVED2;  	// Reserved Option byte
    __IO uint8_t OPT7;  	// Option byte 7: flash wait states
    __IO uint8_t NOPT7; 	// Complementary Option byte 7
} OPT_TypeDef;

typedef struct IWDG_struct
{
    __IO uint8_t KR;  	// Key Register
    __IO uint8_t PR;  	// Prescaler Register
    __IO uint8_t RLR; 	// Reload Register
} IWDG_TypeDef;

#define IWDG_PR_RESET_VALUE  ((uint8_t)0x00)
#define IWDG_RLR_RESET_VALUE ((uint8_t)0xFF)

typedef struct WWDG_struct
{
    __IO uint8_t CR; 	// Control Register
    __IO uint8_t WR; 	// Window Register
} WWDG_TypeDef;

#define WWDG_CR_RESET_VALUE ((uint8_t)0x7F)
#define WWDG_WR_RESET_VALUE ((uint8_t)0x7F)

#define WWDG_CR_WDGA ((uint8_t)0x80) 	// WDGA bit mask
#define WWDG_CR_T6   ((uint8_t)0x40) 	// T6 bit mask
#define WWDG_CR_T    ((uint8_t)0x7F) 	// T bits mask
#define WWDG_WR_MSB  ((uint8_t)0x80) 	// MSB bit mask
#define WWDG_WR_W    ((uint8_t)0x7F) 	// W bits mask

typedef struct RST_struct
{
    __IO uint8_t SR; 	// Reset status register
} RST_TypeDef;

#define RST_SR_EMCF   ((uint8_t)0x10) 	// EMC reset flag bit mask
#define RST_SR_SWIMF  ((uint8_t)0x08) 	// SWIM reset flag bit mask
#define RST_SR_ILLOPF ((uint8_t)0x04) 	// Illegal opcode reset flag bit mask
#define RST_SR_IWDGF  ((uint8_t)0x02) 	// IWDG reset flag bit mask
#define RST_SR_WWDGF  ((uint8_t)0x01) 	// WWDG reset flag bit mask

typedef struct SPI_struct
{
    __IO uint8_t CR1;    	// SPI control register 1
    __IO uint8_t CR2;    	// SPI control register 2
    __IO uint8_t ICR;    	// SPI interrupt control register
    __IO uint8_t SR;     	// SPI status register
    __IO uint8_t DR;     	// SPI data I/O register
    __IO uint8_t CRCPR;  	// SPI CRC polynomial register
    __IO uint8_t RXCRCR; 	// SPI Rx CRC register
    __IO uint8_t TXCRCR; 	// SPI Tx CRC register
} SPI_TypeDef;

#define SPI_CR1_RESET_VALUE    ((uint8_t)0x00) 	// Control Register 1 reset value
#define SPI_CR2_RESET_VALUE    ((uint8_t)0x00) 	// Control Register 2 reset value
#define SPI_ICR_RESET_VALUE    ((uint8_t)0x00) 	// Interrupt Control Register reset value
#define SPI_SR_RESET_VALUE     ((uint8_t)0x02) 	// Status Register reset value
#define SPI_DR_RESET_VALUE     ((uint8_t)0x00) 	// Data Register reset value
#define SPI_CRCPR_RESET_VALUE  ((uint8_t)0x07) 	// Polynomial Register reset value
#define SPI_RXCRCR_RESET_VALUE ((uint8_t)0x00) 	// RX CRC Register reset value
#define SPI_TXCRCR_RESET_VALUE ((uint8_t)0x00) 	// TX CRC Register reset value

#define SPI_CR1_LSBFIRST ((uint8_t)0x80) 	// Frame format mask
#define SPI_CR1_SPE      ((uint8_t)0x40) 	// Enable bits mask
#define SPI_CR1_BR       ((uint8_t)0x38) 	// Baud rate control mask
#define SPI_CR1_MSTR     ((uint8_t)0x04) 	// Master Selection mask
#define SPI_CR1_CPOL     ((uint8_t)0x02) 	// Clock Polarity mask
#define SPI_CR1_CPHA     ((uint8_t)0x01) 	// Clock Phase mask
#define SPI_CR2_BDM      ((uint8_t)0x80) 	// Bi-directional data mode enable mask
#define SPI_CR2_BDOE     ((uint8_t)0x40) 	// Output enable in bi-directional mode mask
#define SPI_CR2_CRCEN    ((uint8_t)0x20) 	// Hardware CRC calculation enable mask
#define SPI_CR2_CRCNEXT  ((uint8_t)0x10) 	// Transmit CRC next mask
#define SPI_CR2_RXONLY   ((uint8_t)0x04) 	// Receive only mask
#define SPI_CR2_SSM      ((uint8_t)0x02) 	// Software slave management mask
#define SPI_CR2_SSI      ((uint8_t)0x01) 	// Internal slave select mask
#define SPI_ICR_TXEI     ((uint8_t)0x80) 	// Tx buffer empty interrupt enable mask
#define SPI_ICR_RXEI     ((uint8_t)0x40) 	// Rx buffer empty interrupt enable mask
#define SPI_ICR_ERRIE    ((uint8_t)0x20) 	// Error interrupt enable mask
#define SPI_ICR_WKIE     ((uint8_t)0x10) 	// Wake-up interrupt enable mask
#define SPI_SR_BSY       ((uint8_t)0x80) 	// Busy flag
#define SPI_SR_OVR       ((uint8_t)0x40) 	// Overrun flag
#define SPI_SR_MODF      ((uint8_t)0x20) 	// Mode fault
#define SPI_SR_CRCERR    ((uint8_t)0x10) 	// CRC error flag
#define SPI_SR_WKUP      ((uint8_t)0x08) 	// Wake-Up flag
#define SPI_SR_TXE       ((uint8_t)0x02) 	// Transmit buffer empty
#define SPI_SR_RXNE      ((uint8_t)0x01) 	// Receive buffer not empty

typedef struct UART_struct
{
    __IO uint8_t SR;   	// UART status register
    __IO uint8_t DR;   	// UART data register
    __IO uint8_t BRR1; 	// UART baud rate register
    __IO uint8_t BRR2; 	// UART DIV mantissa[11:8] SCIDIV fraction
    __IO uint8_t CR1;  	// UART control register 1
    __IO uint8_t CR2;  	// UART control register 2
    __IO uint8_t CR3;  	// UART control register 3
    __IO uint8_t CR4;  	// UART control register 4
    __IO uint8_t CR5;  	// UART control register 5
    __IO uint8_t GTR;  	// UART guard time register
    __IO uint8_t PSCR; 	// UART prescaler register
} UART_TypeDef;

#define UART_SR_RESET_VALUE   ((uint8_t)0xC0)
#define UART_BRR1_RESET_VALUE ((uint8_t)0x00)
#define UART_BRR2_RESET_VALUE ((uint8_t)0x00)
#define UART_CR1_RESET_VALUE  ((uint8_t)0x00)
#define UART_CR2_RESET_VALUE  ((uint8_t)0x00)
#define UART_CR3_RESET_VALUE  ((uint8_t)0x00)
#define UART_CR4_RESET_VALUE  ((uint8_t)0x00)
#define UART_CR5_RESET_VALUE  ((uint8_t)0x00)
#define UART_GTR_RESET_VALUE  ((uint8_t)0x00)
#define UART_PSCR_RESET_VALUE ((uint8_t)0x00)

#define UART_SR_TXE        ((uint8_t)0x80) 	// Transmit Data Register Empty mask
#define UART_SR_TC         ((uint8_t)0x40) 	// Transmission Complete mask
#define UART_SR_RXNE       ((uint8_t)0x20) 	// Read Data Register Not Empty mask
#define UART_SR_IDLE       ((uint8_t)0x10) 	// IDLE line detected mask
#define UART_SR_OR         ((uint8_t)0x08) 	// OverRun error mask
#define UART_SR_NF         ((uint8_t)0x04) 	// Noise Flag mask
#define UART_SR_FE         ((uint8_t)0x02) 	// Framing Error mask
#define UART_SR_PE         ((uint8_t)0x01) 	// Parity Error mask
#define UART_BRR1_DIVM     ((uint8_t)0xFF) 	// LSB mantissa of UARTDIV [7:0] mask
#define UART_BRR2_DIVM     ((uint8_t)0xF0) 	// MSB mantissa of UARTDIV [11:8] mask
#define UART_BRR2_DIVF     ((uint8_t)0x0F) 	// Fraction bits of UARTDIV [3:0] mask
#define UART_CR1_R8        ((uint8_t)0x80) 	// Receive Data bit 8
#define UART_CR1_T8        ((uint8_t)0x40) 	// Transmit data bit 8
#define UART_CR1_UARTD     ((uint8_t)0x20) 	// UART Disable (for low power consumption)
#define UART_CR1_M         ((uint8_t)0x10) 	// Word length mask
#define UART_CR1_WAKE      ((uint8_t)0x08) 	// Wake-up method mask
#define UART_CR1_PCEN      ((uint8_t)0x04) 	// Parity Control Enable mask
#define UART_CR1_PS        ((uint8_t)0x02) 	// UART Parity Selection
#define UART_CR1_PIEN      ((uint8_t)0x01) 	// UART Parity Interrupt Enable mask
#define UART_CR2_TIEN      ((uint8_t)0x80) 	// Transmitter Interrupt Enable mask
#define UART_CR2_TCIEN     ((uint8_t)0x40) 	// Transmission Complete Interrupt Enable mask
#define UART_CR2_RIEN      ((uint8_t)0x20) 	// Receiver Interrupt Enable mask
#define UART_CR2_ILIEN     ((uint8_t)0x10) 	// IDLE Line Interrupt Enable mask
#define UART_CR2_TEN       ((uint8_t)0x08) 	// Transmitter Enable mask
#define UART_CR2_REN       ((uint8_t)0x04) 	// Receiver Enable mask
#define UART_CR2_RWU       ((uint8_t)0x02) 	// Receiver Wake-Up mask
#define UART_CR2_SBK       ((uint8_t)0x01) 	// Send Break mask
#define UART_CR3_LINEN     ((uint8_t)0x40) 	// Alternate Function output mask
#define UART_CR3_STOP      ((uint8_t)0x30) 	// STOP bits [1:0] mask
#define UART_CR3_CKEN      ((uint8_t)0x08) 	// Clock Enable mask
#define UART_CR3_CPOL      ((uint8_t)0x04) 	// Clock Polarity mask
#define UART_CR3_CPHA      ((uint8_t)0x02) 	// Clock Phase mask
#define UART_CR3_LBCL      ((uint8_t)0x01) 	// Last Bit Clock pulse mask
#define UART_CR4_LBDIEN    ((uint8_t)0x40) 	// LIN Break Detection Interrupt Enable mask
#define UART_CR4_LBDL      ((uint8_t)0x20) 	// LIN Break Detection Length mask
#define UART_CR4_LBDF      ((uint8_t)0x10) 	// LIN Break Detection Flag mask
#define UART_CR4_ADD       ((uint8_t)0x0F) 	// Address of the UART node mask
#define UART_CR5_SCEN      ((uint8_t)0x20) 	// Smart Card Enable mask
#define UART_CR5_NACK      ((uint8_t)0x10) 	// Smart Card Nack Enable mask
#define UART_CR5_HDSEL     ((uint8_t)0x08) 	// Half-Duplex Selection mask
#define UART_CR5_IRLP      ((uint8_t)0x04) 	// Irda Low Power Selection mask
#define UART_CR5_IREN      ((uint8_t)0x02) 	// Irda Enable mask


typedef struct CFG_struct
{
    __IO uint8_t GCR; 	// Global Configuration register
} CFG_TypeDef;

#define CFG_GCR_RESET_VALUE ((uint8_t)0x00)
#define CFG_GCR_SWD ((uint8_t)0x01) 	// Swim disable bit mask
#define CFG_GCR_AL  ((uint8_t)0x02) 	// Activation Level bit mask

#define OPT_BaseAddress         0x4800
#define GPIOA_BaseAddress       0x5000
#define GPIOB_BaseAddress       0x5005
#define GPIOC_BaseAddress       0x500A
#define GPIOD_BaseAddress       0x500F
#define FLASH_BaseAddress       0x505A
#define EXTI_BaseAddress        0x50A0
#define RST_BaseAddress         0x50B3
#define CLK_BaseAddress         0x50C0
#define WWDG_BaseAddress        0x50D1
#define IWDG_BaseAddress        0x50E0
#define AWU_BaseAddress         0x50F0
#define BEEP_BaseAddress        0x50F3
#define SPI_BaseAddress         0x5200
#define I2C_BaseAddress         0x5210
#define UART_BaseAddress       0x5230
#define TIM1_BaseAddress        0x5250
#define TIM2_BaseAddress        0x5300
#define TIM3_BaseAddress        0x5320
#define TIM4_BaseAddress        0x5340
#define ADC_BaseAddress        0x53E0
#define CFG_BaseAddress         0x7F60
#define ITC_BaseAddress         0x7F70
#define DM_BaseAddress          0x7F90

#define ADC ((ADC_TypeDef *)  ADC_BaseAddress)
#define AWU ((AWU_TypeDef *)    AWU_BaseAddress)
#define BEEP ((BEEP_TypeDef *)  BEEP_BaseAddress)
#define CLK ((CLK_TypeDef *)    CLK_BaseAddress)
#define EXTI ((EXTI_TypeDef *)  EXTI_BaseAddress)
#define FLASH ((FLASH_TypeDef *) FLASH_BaseAddress)
#define OPT ((OPT_TypeDef *)    OPT_BaseAddress)
#define GPIOA ((gpio_reg *) GPIOA_BaseAddress)
#define GPIOB ((gpio_reg *) GPIOB_BaseAddress)
#define GPIOC ((gpio_reg *) GPIOC_BaseAddress)
#define GPIOD ((gpio_reg *) GPIOD_BaseAddress)

#define RST ((RST_TypeDef *)    RST_BaseAddress)
#define WWDG ((WWDG_TypeDef *)  WWDG_BaseAddress)
#define IWDG ((IWDG_TypeDef *)  IWDG_BaseAddress)
#define SPI ((SPI_TypeDef *)    SPI_BaseAddress)
#define I2C ((I2C_TypeDef *)    I2C_BaseAddress)
#define UART ((UART_TypeDef *) UART_BaseAddress)
#define TIM1 ((TIM1_TypeDef *)  TIM1_BaseAddress)
#define TIM2 ((TIM2_TypeDef *)  TIM2_BaseAddress)
#define TIM4 ((TIM4_TypeDef *)  TIM4_BaseAddress)
#define ITC ((ITC_TypeDef *)    ITC_BaseAddress)
#define CFG ((CFG_TypeDef *)    CFG_BaseAddress)
#define DM ((DM_TypeDef *)      DM_BaseAddress)


#ifdef USE_STDPERIPH_DRIVER
    #include "clk.h"
    #include "gpio.h"
    #include "uart.h"
    #define assert_param(expr) ((void)0)
#endif


#ifdef _RAISONANCE_
    #include <intrins.h>
    #define enableInterrupts()    _rim_()  	// enable interrupts
    #define disableInterrupts()   _sim_()  	// disable interrupts
    #define rim()                 _rim_()  	// enable interrupts
    #define sim()                 _sim_()  	// disable interrupts
    #define nop()                 _nop_()  	// No Operation
    #define trap()                _trap_() 	// Trap (soft IT)
    #define wfi()                 _wfi_()  	// Wait For Interrupt
    #define halt()                _halt_() 	// Halt

    #define INTERRUPT_HANDLER(a,b)      void a(void) interrupt b
    #define INTERRUPT_HANDLER_TRAP(a)   void a(void) trap

#elif defined(_COSMIC_)
    #define enableInterrupts()    {_asm("rim\n");}  	// enable interrupts
    #define disableInterrupts()   {_asm("sim\n");}  	// disable interrupts
    #define rim()                 {_asm("rim\n");}  	// enable interrupts
    #define sim()                 {_asm("sim\n");}  	// disable interrupts
    #define nop()                 {_asm("nop\n");}  	// No Operation
    #define trap()                {_asm("trap\n");} 	// Trap (soft IT)
    #define wfi()                 {_asm("wfi\n");}  	// Wait For Interrupt
    #define halt()                {_asm("halt\n");} 	// Halt

    #define INTERRUPT_HANDLER(a,b)      @far @interrupt void a(void)
    #define INTERRUPT_HANDLER_TRAP(a)   void @far @interrupt a(void)
    #define INTERRUPT                   @far @interrupt

#elif defined(_SDCC_)
    #define enableInterrupts()    {__asm__("rim\n");}  	// enable interrupts
    #define disableInterrupts()   {__asm__("sim\n");}  	// disable interrupts
    #define rim()                 {__asm__("rim\n");}  	// enable interrupts
    #define sim()                 {__asm__("sim\n");}  	// disable interrupts
    #define nop()                 {__asm__("nop\n");}  	// No Operation
    #define trap()                {__asm__("trap\n");} 	// Trap (soft IT)
    #define wfi()                 {__asm__("wfi\n");}  	// Wait For Interrupt
    #define halt()                {__asm__("halt\n");} 	// Halt

    #define INTERRUPT_HANDLER(a,b)      void a(void) __interrupt(b)
    #define INTERRUPT_HANDLER_TRAP(a)   void a(void) __trap

#elif defined(_IAR_)
    #include <intrinsics.h>
    #define enableInterrupts()    __enable_interrupt()   	// enable interrupts
    #define disableInterrupts()   __disable_interrupt()  	// disable interrupts
    #define rim()                 __enable_interrupt()   	// enable interrupts
    #define sim()                 __disable_interrupt()  	// disable interrupts
    #define nop()                 __no_operation()       	// No Operation
    #define trap()                __trap()               	// Trap (soft IT)
    #define wfi()                 __wait_for_interrupt() 	// Wait For Interrupt
    #define halt()                __halt()               	// Halt

    #define STRINGVECTOR(x) #x
    #define VECTOR_ID(x) STRINGVECTOR( vector = (x) )
    #define INTERRUPT_HANDLER( a, b )  \
    _Pragma( VECTOR_ID( (b)+2 ) )        \
    __interrupt void (a)( void )

    #define INTERRUPT_HANDLER_TRAP(a) \
    _Pragma( VECTOR_ID( 1 ) ) \
    __interrupt void (a) (void)

    #define INTERRUPT __interrupt

#endif


/*-----------------------------------------------------------------------------
Method : I
Description : Handle the bit from the character variables.
Comments :    The different parameters of commands are
              - VAR : Name of the character variable where the bit is located.
              - Place : Bit position in the variable (7 6 5 4 3 2 1 0)
              - Value : Can be 0 (reset bit) or not 0 (set bit)
              The "MskBit" command allows to select some bits in a source
              variables and copy it in a destination var (return the value).
              The "ValBit" command returns the value of a bit in a char
              variable: the bit is reset if it returns 0 else the bit is set.
              This method generates not an optimised code yet.
-----------------------------------------------------------------------------*/
#define SetBit(VAR,Place)         ( (VAR) |= (uint8_t)((uint8_t)1<<(uint8_t)(Place)) )
#define ClrBit(VAR,Place)         ( (VAR) &= (uint8_t)((uint8_t)((uint8_t)1<<(uint8_t)(Place))^(uint8_t)255) )
#define ChgBit(VAR,Place)         ( (VAR) ^= (uint8_t)((uint8_t)1<<(uint8_t)(Place)) )
#define AffBit(VAR,Place,Value)   ((Value) ? \
                                   ((VAR) |= ((uint8_t)1<<(Place))) : \
                                   ((VAR) &= (((uint8_t)1<<(Place))^(uint8_t)255)))
#define MskBit(Dest,Msk,Src)      ( (Dest) = ((Msk) & (Src)) | ((~(Msk)) & (Dest)) )
#define ValBit(VAR,Place)         ((uint8_t)(VAR) & (uint8_t)((uint8_t)1<<(uint8_t)(Place)))

#define BYTE_0(n)                 ((uint8_t)((n) & (uint8_t)0xFF))        	// Returns the low byte of the 32-bit value
#define BYTE_1(n)                 ((uint8_t)(BYTE_0((n) >> (uint8_t)8)))  	// Returns the second byte of the 32-bit value
#define BYTE_2(n)                 ((uint8_t)(BYTE_0((n) >> (uint8_t)16))) 	// Returns the third byte of the 32-bit value
#define BYTE_3(n)                 ((uint8_t)(BYTE_0((n) >> (uint8_t)24))) 	// Returns the high byte of the 32-bit value

#define IS_STATE_VALUE_OK(SensitivityValue) \
  (((SensitivityValue) == ENABLE) || \
   ((SensitivityValue) == DISABLE))

/*-----------------------------------------------------------------------------
Method : II
Description : Handle directly the bit.
Comments :    The idea is to handle directly with the bit name. For that, it is
              necessary to have RAM area descriptions (example: HW register...)
              and the following command line for each area.
              This method generates the most optimized code.
-----------------------------------------------------------------------------*/

#define AREA 0x00     // The area of bits begins at address 0x10.

#define BitClr(BIT)  ( *((uint8_t *) (AREA+(BIT)/8)) &= (~(1<<(7-(BIT)%8))) )
#define BitSet(BIT)  ( *((uint8_t *) (AREA+(BIT)/8)) |= (1<<(7-(BIT)%8)) )
#define BitVal(BIT)  ( *((uint8_t *) (AREA+(BIT)/8)) & (1<<(7-(BIT)%8)) )


#endif /* __STM8S_H  */

