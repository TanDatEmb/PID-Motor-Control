/*
 * File: waijung_hwdrvlib.h
 *
 * Created with Waijung Blockset
 *
 * Real-Time Workshop code generated for Simulink model CodeMATLAB.
 *
 * Model version                        : 1.27
 * Real-Time Workshop file version      : 9.3 (R2020a) 18-Nov-2019
 * Real-Time Workshop file generated on : Sat Dec 17 13:26:25 2022
 * TLC version                          : 9.3 (Jan 23 2020)
 * C/C++ source code generated on       : Sat Dec 17 13:26:26 2022
 *
 * Target selection: stm32f4.tlc
 * Embedded hardware selection: ARM Compatible->Cortex - M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_waijung_hwdrvlib_h_
#define RTW_HEADER_waijung_hwdrvlib_h_
#include <string.h>
#include "rtwtypes.h"
#include "stm32f4xx.h"

/*
 * Define PWM Generation Scale Factor
 * From TIMx_CCRx = TIMx_ARR * (Duty Cycle / 100)
 * TIMx_CCRx = (TIMx_ARR/100) * Duty Cycle
 */
#define Subsystem2XuattinhieuBasicPWM_TIM2_ARR 8400
#define Subsystem2XuattinhieuBasicPWM_SF ((float)Subsystem2XuattinhieuBasicPWM_TIM2_ARR / 100)

/* ########################################################################
 * Name: <S11>/Digital Output
 * Id: Subsystem2XuattinhieuDigitalOutput
 * ########################################################################
 */
#define Subsystem2XuattinhieuDigitalOutput_A4 Peripheral_BB(GPIOA->ODR, 4) /* Output pin */

/* Subsystem3DigitalInput */
#define Subsystem3DigitalInput_D0      Peripheral_BB(GPIOD->IDR, 0) /* Output pin */
#define Subsystem3DigitalInput_D2      Peripheral_BB(GPIOD->IDR, 2) /* Output pin */
#define Subsystem3DigitalInput_D4      Peripheral_BB(GPIOD->IDR, 4) /* Output pin */

/*
 * Bit banding
 *
 * The Cortex memory map includes two bit-band regions.
 * These regions map each word in an alias region of memory to a bit in
 * a bit-band region of memory. Writing to a word in the alias region
 * has the same effect as a read-modify-write operation on the targeted bit
 * in the bit-band region.
 *
 * In the STM32F4xxx both peripheral registers and SRAM are mapped in
 * a bit-band region. This allows single bit-band write and read operations
 * to be performed.
 *
 * A mapping formula shows how to reference each word in the alias region
 * to a corresponding bit in the bit-band region. The mapping formula is:
 * bit_word_addr = bit_band_base + (byte_offset x 32) + (bit_number × 4)
 *
 * BB_base      is the base address of the bit-band region for a register. (PERIPH_BB_BASE at 0x42000000 or SRAM_BB_BASE at 0x22000000)
 * Reg_base     is the base address of a register in the memory region. (PERIPH_BASE at 0x40000000 or SRAM_BASE at 0x20000000)
 * Register     is a register in the memory region that contains the targeted bit.
 * Bit_number   is the targeted bit number (0 - 31).
 *
 * PERIPH_BB_BASE, SRAM_BB_BASE, PERIPH_BASE, and SRAM_BASE are defined in stm32f10x.h
 *
 * Example for determining bit banding bit.
 * Determine DMA Transfer Complete Flag using bit banding.
 * TCIFx is the flag for DMA Channel x
 * This bit is set by hardware. It is cleared by software writing 1 to
 * the corresponding bit in the DMA_IFCR register.
 * TCIFx = 0: No transfer complete (TC) event on channel x
 * TCIFx = 1: A transfer complete (TC) event occurred on channel x
 *
 * DMA Channel:       1 2 3  4  5  6  7
 * Flag bit position: 1 5 9 13 17 21 25 (in DMA_ISR register)
 * (For DMA2 Channel 6 and 7 is irrelevant since it only has 5 channels.)
 *
 * CTCIFx: Channel x transfer complete clear (x = 1 ..7)
 * This bit is set and cleared by software.
 * CTCIFx = 0: No effect
 * CTCIFx = 1: Clear the corresponding TCIF flag in the DMA_ISR register
 *
 */
#define BitBanding(Register, Bit_number, Reg_base, BB_base) ((volatile uint32_t*) ((BB_base) + (((uint32_t) &(Register)) - ((Reg_base))<<5) + ((Bit_number)<<2)))
#define Peripheral_BB(Register, Bit_number) BitBanding(Register, Bit_number, PERIPH_BASE, PERIPH_BB_BASE)
#define SRAM_BB(Register, Bit_number)  BitBanding(Register, Bit_number, SRAM_BASE, SRAM_BB_BASE)

/*
 * Sample usage:
 * USART1->SR can be found from "stm32f4xx.h" and USART_FLAG_TC (6) can be found from "stm32f4xx_usart.h"
 * #define USART1_TC Peripheral_BB(USART1->SR, 6) USART_SR.TC bit
 *
 * Another example:
 * #define GPIOC_8 Peripheral_BB(GPIOC->ODR, 8)
 * *GPIOC_8 = 1;
 */

/*
 * Systick is configured such that the SysTick interrupt every 0.05 sec
 * which is the base sample time of the system.
 */
#define SYSTICKRELOADVALUE             8400000

/*
 * HCLK (Hz)
 */
#define HCLK                           168000000

/*
 * Each Systick counter is TIMEPERSYSTICK sec.
 */
#define TIMEPERSYSTICK                 0.05 / 8400000

/* ########################################################################
 * Timer
 * ########################################################################
 */
#define SYS_CURRENT_TICK               (SysTick->VAL)
#define SYS_TICKSTEP                   0.05f

typedef struct {
  uint32_t start;
  uint32_t length;
} SYS_TIMER_STRUCT;

#define SYSTIMER_FLAGS_TIMEOUT         0x01

typedef struct {
  uint8_t flags;
  uint32_t tid;                        /* Tick count */
  uint32_t tick;                       /* Capture cuttent tick */
  uint32_t target_us;                  /* Target of systick */
} SYS_TIMER_uS_STRUCT;

extern volatile unsigned int systick_count;
void SysTimer_Start(SYS_TIMER_STRUCT* timer, uint32_t ms);
void SysTimer_uS_Start(SYS_TIMER_uS_STRUCT *timer, uint32_t us);
int SysTimer_IsTimeout(SYS_TIMER_STRUCT* timer);
int SysTimer_uS_IsTimeout(SYS_TIMER_uS_STRUCT* timer);
void SysTimer_delay_us(uint32_t us);
extern volatile unsigned int systick_count;
void enable_SubsystemDocencoderEncoderRead(void);/* SubsystemDocencoderEncoderRead */

/* ########################################################################
 * Name: <S15>/System Reset
 * Id: Subsystem3SubsystemSystemReset
 * ########################################################################
 */
void Subsystem3SubsystemSystemReset_Exec(void);
void enable_SubsystemTimerTimeBaseIRQ(void);/* SubsystemTimerTimeBaseIRQ */
void disable_SubsystemTimerTimeBaseIRQ(void);/* SubsystemTimerTimeBaseIRQ */

/* ########################################################################
 * UART Utilities for packet processing
 * ########################################################################
 */
/* UART packet process struct */
typedef enum {
  txIdle = 0,
  txBusy
} UART_TX_STATE;

/* Data read structure */
typedef struct {
  uint16_t index;                      /* Index of data in buffer */
  uint16_t count;                      /* Return data count */
  uint8_t *buffer;                     /* Return buffer pointer of valid data */
} UARTRX_BUFFER_READ_STRUCT;

/* ########################################################################
 * Name: <S2>/UART Rx
 * Id: Subsystem1UARTRx
 * ########################################################################
 */
extern UARTRX_BUFFER_READ_STRUCT Subsystem1UARTRx_read_structure;
uint8_t Subsystem1UARTRx_Receive(uint8_t *buffer, uint16_t size);

/* Data */
extern float Subsystem1UARTRx_data0;
extern float Subsystem1UARTRx_data1;
extern float Subsystem1UARTRx_data2;
extern float Subsystem1UARTRx_data3;

#define Subsystem1UARTRx_terminator_SIZE 1

extern const char Subsystem1UARTRx_terminator[];
void enable_Subsystem1UARTRx(void);

/* ########################################################################
 * Name: <S2>/UART Tx1
 * Id: Subsystem1UARTTx1
 * ########################################################################
 */
void enable_Subsystem1UARTTx1(void);
void enable_Subsystem2XuattinhieuBasicPWM(void);/* Subsystem2XuattinhieuBasicPWM */

/* Subsystem2XuattinhieuDigitalOutput */
void enable_Subsystem2XuattinhieuDigitalOutput(void);

/* ########################################################################
 * Name: <S4>/Digital Input
 * Id: Subsystem3DigitalInput
 * ########################################################################
 */
void enable_Subsystem3DigitalInput(void);

/* ########################################################################
 * Name: <S5>/UART Setup1
 * Id: Subsystem4UARTSetup1
 * ########################################################################
 */
#define UTX6_BUFFER_SIZE               2048

extern uint8_t UART6_Tx_Buffer[];
extern UART_TX_STATE Subsystem4UARTSetup1_Tx_State;
extern void UART6_TxUpdate(uint16_t count);

#define URX6_BUFFER_SIZE               2048

extern uint8_t UART6_Rx_Buffer[];
extern uint8_t UART6_Temp_Buffer[];
uint16_t UART6_ReadLine(UARTRX_BUFFER_READ_STRUCT *read_struct, const char
  *terminator, uint16_t terminator_count, uint8_t *buffer, uint16_t buffer_size);
uint8_t UART6_ReadBinary(UARTRX_BUFFER_READ_STRUCT *read_struct, const char
  *header, uint16_t header_count, const char *terminator, uint16_t
  terminator_count, uint8_t *buffer, uint16_t data_count);
void UART6_RestoreBytes(UARTRX_BUFFER_READ_STRUCT *read_struct, uint16_t count);
extern uint16_t UART6_GetInitNDTR(void);
void UART6_Read(UARTRX_BUFFER_READ_STRUCT *read_struct);
void UART6_ReadEx(UARTRX_BUFFER_READ_STRUCT *read_struct, uint8_t *buffer,
                  uint16_t buffer_size, uint16_t*reading_count);
extern void UART6_Write(uint8_t* data, uint16_t count);
extern UART_TX_STATE UART6_FlushTxBuffer(void);
void waijung_usart6_initial(void);

#define WAIJUNG_USARt6_INIT()          waijung_usart6_initial()

void enable_Subsystem4UARTSetup1(void);

#endif                                 /* RTW_HEADER_waijung_hwdrvlib_h_ */

/* [EOF] */
