/*
 * File: waijung_hwdrvlib.c
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

#include "waijung_hwdrvlib.h"

void enable_SubsystemDocencoderEncoderRead(void)
{
  /* Block: SubsystemDocencoderEncoderRead */
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;

  /* TIM1 clock source enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  /* GPIOE clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

  /* GPIOE configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* Connect TIM1 pins to AF */
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);

  /* Configure Timer in encoder mode */
  TIM_DeInit(TIM1);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;// No prescaling
  TIM_TimeBaseStructure.TIM_Period = -1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising,
    TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;/* No filter; sampling is done at fDTS */
  TIM_ICInit(TIM1, &TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInit(TIM1, &TIM_ICInitStructure);

  // Clear all pending interrupts
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

  //Reset counter
  TIM1->CNT = 0;
  TIM_Cmd(TIM1, ENABLE);
}

void disable_SubsystemDocencoderEncoderRead(void)
{
  TIM_Cmd(TIM1, DISABLE);
}

void terminate_SubsystemDocencoderEncoderRead(void)
{
  TIM_Cmd(TIM1, DISABLE);
}

/* ########################################################################
 * Name: <S15>/System Reset
 * Id: Subsystem3SubsystemSystemReset
 * ########################################################################
 */
void Subsystem3SubsystemSystemReset_Exec(void)
{
  /* Enable WWDG clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
  WWDG->CR = 0x80;                     /* Gernerate Software reset */
}

void enable_SubsystemTimerTimeBaseIRQ(void)
{
  /* Block: SubsystemTimerTimeBaseIRQ */
  NVIC_InitTypeDef NVIC_InitStructureTimeBaseIRQ_TIM9;

  /* Configure Timer Clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  NVIC_InitStructureTimeBaseIRQ_TIM9.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
  NVIC_InitStructureTimeBaseIRQ_TIM9.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructureTimeBaseIRQ_TIM9.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructureTimeBaseIRQ_TIM9.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructureTimeBaseIRQ_TIM9);

  /* TIM9 Configuration */
  TIM_PrescalerConfig(TIM9, 128, TIM_PSCReloadMode_Update);
  TIM_SetAutoreload(TIM9, 65115);

  /* TIM IT enable */
  TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);

  /* TIM9 enable counter */
  TIM_Cmd(TIM9, ENABLE);
}

void disable_SubsystemTimerTimeBaseIRQ(void)
{
  /* Block: SubsystemTimerTimeBaseIRQ */

  /* TIM IT enable */
  TIM_ITConfig(TIM9, TIM_IT_Update, DISABLE);

  /* TIM9 enable counter */
  TIM_Cmd(TIM9, DISABLE);
}

/* ########################################################################
 * Name: <S2>/UART Rx
 * Id: Subsystem1UARTRx
 * ########################################################################
 */

/* Data read structure */
UARTRX_BUFFER_READ_STRUCT Subsystem1UARTRx_read_structure = { 0, 0, (uint8_t *)0
};

/* Data */
float Subsystem1UARTRx_data0 = 0;
float Subsystem1UARTRx_data1 = 0;
float Subsystem1UARTRx_data2 = 0;
float Subsystem1UARTRx_data3 = 0;

/* Non-Blocking */
uint8_t Subsystem1UARTRx_Receive(uint8_t *buffer, uint16_t size)
{
  uint8_T ready = 0;
  const char terminator[1] = { 10 };   /* Terminator */

  /* Rx Non-Blocking */
  if (UART6_ReadLine(&Subsystem1UARTRx_read_structure, terminator, 1, buffer,
                     size) > 0) {
    ready = (uint8_t)(sscanf((const char*)buffer,"%f,%f,%f,%f\n" ,
      &Subsystem1UARTRx_data0 ,&Subsystem1UARTRx_data1 ,&Subsystem1UARTRx_data2 ,
      &Subsystem1UARTRx_data3 ) == 4);
  }

  return ready;
}

/* Enable UART-DMA module */
void enable_Subsystem1UARTRx(void)
{
  WAIJUNG_USARt6_INIT();
}

/* ########################################################################
 * Name: <S2>/UART Tx1
 * Id: Subsystem1UARTTx1
 * ########################################################################
 */

/* Enable UART-DMA module */
void enable_Subsystem1UARTTx1(void)
{
  WAIJUNG_USARt6_INIT();
}

void enable_Subsystem2XuattinhieuBasicPWM(void)
{
  /* Block: Subsystem2XuattinhieuBasicPWM */
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* GPIOA configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect TIM2 pins to AF */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = Subsystem2XuattinhieuBasicPWM_TIM2_ARR-1;/* 0.0001 sec */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Init OC */
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

  /* PWM1 Mode configuration: Channel 3 */
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* TIM2 configure auto reload */
  TIM_ARRPreloadConfig(TIM2, ENABLE);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}

void disable_Subsystem2XuattinhieuBasicPWM(void)
{
  TIM_Cmd(TIM2, DISABLE);
}

void terminate_Subsystem2XuattinhieuBasicPWM(void)
{
  TIM_Cmd(TIM2, DISABLE);
}

/* ########################################################################
 * Name: <S11>/Digital Output
 * Id: Subsystem2XuattinhieuDigitalOutput
 * ########################################################################
 */
void enable_Subsystem2XuattinhieuDigitalOutput(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* Configure PA in output Push Pull mode for Subsystem2XuattinhieuDigitalOutput Block*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;/* Waijung 14.xx */
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/* ########################################################################
 * Name: <S4>/Digital Input
 * Id: Subsystem3DigitalInput
 * ########################################################################
 */
void enable_Subsystem3DigitalInput(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD in input Pull Down mode for Subsystem3DigitalInput Block*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/* ########################################################################
 * Name: <S5>/UART Setup1
 * Id: Subsystem4UARTSetup1
 * ########################################################################
 */

/* Tx buffer */
uint8_t UART6_Tx_Buffer[UTX6_BUFFER_SIZE];
UART_TX_STATE Subsystem4UARTSetup1_Tx_State;

/* Rx buffer */
uint8_t UART6_Rx_Buffer[URX6_BUFFER_SIZE];
uint8_t UART6_Temp_Buffer[URX6_BUFFER_SIZE];

/* DMA Init struct */
DMA_InitTypeDef Subsystem4UARTSetup1_DMA_Init;

/* Init buffer read */
void UART6_RestoreBytes(UARTRX_BUFFER_READ_STRUCT *read_struct, uint16_t count)
{
  uint16_t roll_count = count;

  /* Remove overflow buffer */
  while (roll_count > URX6_BUFFER_SIZE)
    roll_count -= URX6_BUFFER_SIZE;

  /* Return bytes back into buffer */
  if (roll_count > read_struct->index) {
    read_struct->index = URX6_BUFFER_SIZE - roll_count + read_struct->index;
  } else {
    read_struct->index -= roll_count;
  }
}

/* Read buffer from DMA
 ** Return value: Number of bytes vaiable.
 */
void UART6_Read(UARTRX_BUFFER_READ_STRUCT *read_struct)
{
  __IO uint16_t dma_curr_ndtr;
  __IO uint16_t dma_curr_index;
  uint16_t data_index = 0;
  uint16_t data_count = 0;

  /* Get current NDTR */
  if ((dma_curr_ndtr = DMA2_Stream1->NDTR) == 0) {/* Not initialize or turn-around state*/
    read_struct->count = 0;
    return;
  }

  /* Get current data indexs */
  dma_curr_index = URX6_BUFFER_SIZE - dma_curr_ndtr;
  if (read_struct->index < dma_curr_index) {
    /* Data is available */
    data_index = read_struct->index;
    data_count = dma_curr_index - read_struct->index;
    read_struct->index += data_count;
    read_struct->index &= (URX6_BUFFER_SIZE-1);
  } else if (read_struct->index > dma_curr_index) {
    /* Data is available with overlap */
    data_index = read_struct->index;
    data_count = URX6_BUFFER_SIZE-read_struct->index;
    read_struct->index = 0;
  } else {                             /* No new data */
  }

  /* Return the reading */
  if (data_count > 0) {
    read_struct->buffer = &UART6_Rx_Buffer[data_index];
    read_struct->count = data_count;
  } else {
    read_struct->count = 0;
  }
}

void UART6_ReadEx(UARTRX_BUFFER_READ_STRUCT *read_struct, uint8_t *buffer,
                  uint16_t buffer_size, uint16_t*reading_count)
{
  uint16_t bytes_to_read, data_read_index;
  bytes_to_read = buffer_size;         /* Tracking count of data readings */
  data_read_index = 0;                 /* Increment buffer index */
  do {
    UART6_Read(read_struct);
    if (read_struct->count <= bytes_to_read) {
      memcpy(&buffer[data_read_index], read_struct->buffer, read_struct->count);
      data_read_index += read_struct->count;
      bytes_to_read -= read_struct->count;
    } else {
      /* Return some byte back to buffer */
      //read_struct->index -= (read_struct->count - bytes_to_read);
      UART6_RestoreBytes(read_struct, (read_struct->count - bytes_to_read));/* Fixed: Waijung 14.05a */

      /* Return reading data */
      memcpy(&buffer[data_read_index], read_struct->buffer, bytes_to_read);
      bytes_to_read = 0;
    }
  } while ((bytes_to_read > 0) && (read_struct->count > 0));

  /* Number of reading bytes */
  *reading_count = buffer_size - bytes_to_read;
}

/* Read Ascii packet
 * Return char count, exclude NULL
 * Terminator: "\n", "\r", "\r\n"
 */
uint16_t UART6_ReadLine(UARTRX_BUFFER_READ_STRUCT *read_struct, const char
  *terminator, uint16_t terminator_count, uint8_t *buffer, uint16_t buffer_size)
{
  uint16_t count, packet_len = 0, receive_count = 0;
  uint16_t i;
  uint16_t terminator_found = 0;

  /* Determine maximum number of bytes to read */
  count = buffer_size - 1;
  if (count >= URX6_BUFFER_SIZE)
    count = URX6_BUFFER_SIZE-1;

  /* Ignore terminator is invalid */
  if (terminator_count < 1)
    return 0;

  /* Read packet */
  do {
    terminator_found = 0;
    UART6_Read(read_struct);           /* Check DMA buffer */
    receive_count += read_struct->count;/* Total number of data received */

    /* Search terminator */
    i = 0;
    while (!(terminator_found == terminator_count) && (i < read_struct->count))
    {
      if (read_struct->buffer[i] == (uint8_t)terminator[terminator_found/*terminator_count - 1*/
          ])
        terminator_found ++;
      i++;
    }

    packet_len += i;
    if (terminator_found == terminator_count) {
      terminator_found = 0;

      /* Roll-back buffer index */
      if ((packet_len > count) || (packet_len < terminator_count)) {/* Packet count is invalid, drop it */
        UART6_RestoreBytes(read_struct, (receive_count-packet_len));

        /* Reset */
        packet_len = 0;
        receive_count = 0;
      } else {
        UART6_RestoreBytes(read_struct, receive_count);

        /* Load data into buffer */
        UART6_ReadEx(read_struct, buffer, packet_len, &i);
        buffer[packet_len] = '\0';     /* Append NULL */

        /* Validate terminator */
        if (!strncmp((char *)&buffer[packet_len-terminator_count], terminator,
                     terminator_count)) {
          return packet_len;
                   /* packet reading success, return number of received bytes */
        } else {
          /* Invalid terminator */
          packet_len = 0;
          receive_count = 0;
        }
      }
    }
  } while (read_struct->count > 0);

  /* Could not find the packet terminator, reset reading struct to its original position */
  if (receive_count > 0) {
    UART6_RestoreBytes(read_struct, receive_count);
  }

  /* No byte receive */
  return 0;
}

/* Read Binary packet
 * 0: Not ready, 1: Data is ready
 */
uint8_t UART6_ReadBinary(UARTRX_BUFFER_READ_STRUCT *read_struct, const char
  *header, uint16_t header_count, const char *terminator, uint16_t
  terminator_count, uint8_t *buffer, uint16_t data_count)
{
  uint16_t receive_count = 0, drop_count = 0, binary_state = 0, binary_index = 0;
  uint16_t i;
  do {
    UART6_Read(read_struct);           /* Check DMA buffer */
    receive_count += read_struct->count;/* Total number of data received */

    /* Binary packet processing */
    for (i=0; i<read_struct->count; i++) {
      switch ( binary_state ) {
       case 0:                         /* Search for header */
        if (binary_index < header_count) {
          if (read_struct->buffer[i] == header[binary_index]) {
            binary_index ++;
          } else {
            binary_index = 0;
            drop_count = receive_count - (read_struct->count - i - 1);/* Drop packet */
          }
          break;
        } else {                       /* Change to DATA state */
          binary_index = 0;
          binary_state ++;
        }

       case 1:                         /* Wait for data */
        /* Wait for DATA */
        if (binary_index < data_count) {
          buffer[binary_index] = read_struct->buffer[i];
          binary_index ++;

          /* Check if ready (No terminator) */
          if ((binary_index >= data_count) && (terminator_count == 0)) {
            UART6_RestoreBytes(read_struct, (read_struct->count - i - 1));/* Restore some bytes */
            return 1;                  /* Return success status */
          }
          break;
        } else {                       /* Change to Terminator state */
          binary_index = 0;
          binary_state ++;
        }

       case 2:                         /* Scan for terminator */
        if (binary_index < terminator_count) {
          if (read_struct->buffer[i] == terminator[binary_index]) {
            binary_index ++;
          } else {
            binary_state = 0;
            binary_index = 0;
            drop_count = receive_count - (read_struct->count - i - 1);/* Drop packet */
          }
        }

        if (binary_index >= terminator_count) {/* Success */
          /* Restore some bytes */
          UART6_RestoreBytes(read_struct, (read_struct->count - i - 1));
          return 1;                    /* Return success status */
        }
        break;
      }
    }
  } while (read_struct->count > 0);

  /* Restore bytes */
  UART6_RestoreBytes(read_struct, (receive_count - drop_count));
  return 0;
}

/* Wait for DMA transfer to completion */
UART_TX_STATE UART6_FlushTxBuffer(void)
{
  if (Subsystem4UARTSetup1_Tx_State != txIdle) {
    /* Chehck last DMA transmit */
    while ((DMA_GetFlagStatus(DMA2_Stream6, DMA_FLAG_TCIF6) == RESET)
           || (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET)) {
    }

    /* Clear DMA Streams flags */
    DMA_ClearFlag(DMA2_Stream6, DMA_FLAG_HTIF6 | DMA_FLAG_TCIF6);

    /* Disable the DMA Streams */
    DMA_Cmd(DMA2_Stream6, DISABLE);

    /* Disable the USART Tx DMA request */
    USART_DMACmd(USART6, USART_DMAReq_Tx, DISABLE);

    /* Update state */
    Subsystem4UARTSetup1_Tx_State = txIdle;
  }

  return Subsystem4UARTSetup1_Tx_State;
}

/* Write to DMA buffer */
void UART6_Write(uint8_t* data, uint16_t count)
{
  if (count > 0) {
    /* Wait for Tx state to idle */
    UART6_FlushTxBuffer();

    /* Setup */
    memcpy(UART6_Tx_Buffer, data, count);

    /* Update */
    UART6_TxUpdate(count);
  }
}

/* Update transmit buffer */
void UART6_TxUpdate(uint16_t count)
{
  if (count > 0) {
    /* Wait for Tx state to idle */
    UART6_FlushTxBuffer();
    Subsystem4UARTSetup1_DMA_Init.DMA_BufferSize = (uint16_t)count;
    DMA_Init(DMA2_Stream6, &Subsystem4UARTSetup1_DMA_Init);

    /* Enable */
    USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE);
    USART_ClearFlag(USART6, USART_FLAG_TC);
    DMA_Cmd(DMA2_Stream6, ENABLE);

    /* Tx is busy */
    Subsystem4UARTSetup1_Tx_State = txBusy;
  }
}

static uint8_t waijung_usart6_ready = 0;
void waijung_usart6_initial(void)
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  if (!waijung_usart6_ready) {
    waijung_usart6_ready = 1;

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    /* Enable UART clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

    /* Enable the DMA clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    /* Connect PXx to USARTx_Tx*/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);

    /* Connect PXx to USARTx_Rx*/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

    /* Configure USART pin as alternate function  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

    /* Configure USART Tx */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Configure USART Rx */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* USART Configuration */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Over sampling x8 */
    USART_OverSampling8Cmd(USART6, ENABLE);

    /* USART configuration */
    USART_Init(USART6, &USART_InitStructure);

    /* Enable USART */
    USART_Cmd(USART6, ENABLE);

    /* DMA init struct configuration */
    Subsystem4UARTSetup1_DMA_Init.DMA_PeripheralBaseAddr = (uint32_t)
      (&USART6->DR);
    Subsystem4UARTSetup1_DMA_Init.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    Subsystem4UARTSetup1_DMA_Init.DMA_MemoryInc = DMA_MemoryInc_Enable;
    Subsystem4UARTSetup1_DMA_Init.DMA_PeripheralDataSize =
      DMA_PeripheralDataSize_Byte;
    Subsystem4UARTSetup1_DMA_Init.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    Subsystem4UARTSetup1_DMA_Init.DMA_FIFOMode = DMA_FIFOMode_Disable;
    Subsystem4UARTSetup1_DMA_Init.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    Subsystem4UARTSetup1_DMA_Init.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    Subsystem4UARTSetup1_DMA_Init.DMA_PeripheralBurst =
      DMA_PeripheralBurst_Single;

    /* Configure DMA controller to manage RX DMA request */
    Subsystem4UARTSetup1_DMA_Init.DMA_Channel = DMA_Channel_5;
    Subsystem4UARTSetup1_DMA_Init.DMA_Memory0BaseAddr = (uint32_t)
      UART6_Rx_Buffer;
    Subsystem4UARTSetup1_DMA_Init.DMA_DIR = DMA_DIR_PeripheralToMemory;
    Subsystem4UARTSetup1_DMA_Init.DMA_BufferSize = (uint16_t)URX6_BUFFER_SIZE;
    Subsystem4UARTSetup1_DMA_Init.DMA_Mode = DMA_Mode_Circular;
    Subsystem4UARTSetup1_DMA_Init.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_Init(DMA2_Stream1, &Subsystem4UARTSetup1_DMA_Init);

    /* Enable the USART Rx DMA requests */
    USART_DMACmd(USART6, USART_DMAReq_Rx , ENABLE);

    /* Enable the DMA Stream */
    DMA_Cmd(DMA2_Stream1, ENABLE);

    /* Configure DMA controller to manage TX DMA request */
    Subsystem4UARTSetup1_DMA_Init.DMA_Channel = DMA_Channel_5;
    Subsystem4UARTSetup1_DMA_Init.DMA_Memory0BaseAddr = (uint32_t)
      UART6_Tx_Buffer;
    Subsystem4UARTSetup1_DMA_Init.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    Subsystem4UARTSetup1_DMA_Init.DMA_BufferSize = (uint16_t)UTX6_BUFFER_SIZE;
    Subsystem4UARTSetup1_DMA_Init.DMA_Mode = DMA_Mode_Normal;
    Subsystem4UARTSetup1_DMA_Init.DMA_Priority = DMA_Priority_High;

    /* Init Tx state */
    Subsystem4UARTSetup1_Tx_State = txIdle;
  }
}

/* Enable UART-DMA module */
void enable_Subsystem4UARTSetup1(void)
{
  WAIJUNG_USARt6_INIT();
}

/* ########################################################################
 * Timer
 * ########################################################################
 */

/* Low precision non-Blocking delay timer.
 ** Relolution of timer is one TICK step interrupt.
 */
void SysTimer_Start(SYS_TIMER_STRUCT* timer, uint32_t ms)
{
  /* Calculate amount of tick count */
  timer->length = (uint32_t)((float)ms/(1000*SYS_TICKSTEP));

  /* Capture current tick */
  timer->start = (uint32_t)systick_count;
}

int SysTimer_IsTimeout(SYS_TIMER_STRUCT* timer)
{
  uint32_t Capture;

  /* Capture current tick */
  Capture = (uint32_t)systick_count;

  /* Check */
  if (Capture >= timer->start) {
    if ((Capture - timer->start) >= timer->length)
      return 1;
  } else {
    if (((0xFFFFFFFF - timer->start)+Capture) >= timer->length)
      return 1;
  }

  return 0;
}

/* Improved precision non-Blocking delay timer.
 ** Relolution of timer is 1uS.
 */
void SysTimer_uS_Start(SYS_TIMER_uS_STRUCT *timer, uint32_t us)
{
  /* Tick */
  timer->tick = SYS_CURRENT_TICK;

  /* Tick overflow count */
  timer->tid = (uint32_t)systick_count;

  /* Target */
  timer->target_us = us*((uint32_t)HCLK/1000000);
}

int SysTimer_uS_IsTimeout(SYS_TIMER_uS_STRUCT* timer)
{
  uint32_t curr_tick;
  uint32_t curr_tid;

  /* Already timeout ? */
  if (timer->target_us == 0) {
    return 1;
  }

  /* Capture current tick */
  curr_tick = SYS_CURRENT_TICK;
  curr_tid = systick_count;

  /* Processing TID*/
  while (timer->tid != curr_tid) {
    if (timer->target_us > timer->tick) {
      timer->target_us -= timer->tick;
      timer->tid ++;
      timer->tick = SYSTICKRELOADVALUE-1;
    } else {
      timer->target_us = 0;
      return 1;                        /* Timeout */
    }
  }

  /* Processing Tick */
  if ((timer->tick > curr_tick) && ((timer->tick - curr_tick) > timer->target_us))
  {
    timer->target_us = 0;
    return 1;                          /* Timeout */
  }

  /* Need wait */
  return 0;
}

/* Blocking delay, uS */
void SysTimer_delay_us(uint32_t us)
{
  SYS_TIMER_uS_STRUCT timer;
  SysTimer_uS_Start(&timer, us);
  while (SysTimer_uS_IsTimeout(&timer) == 0) ;
}

/* Blocking delay, mS */
void SysTimer_delay_ms(uint32_t ms)
{
  SYS_TIMER_STRUCT timer;
  SysTimer_Start(&timer, ms);
  while (SysTimer_IsTimeout(&timer) == 0) ;
}

/* [EOF] */
