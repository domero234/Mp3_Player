/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "usb_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "audioI2S.h"
#include "MY_CS43L22.h"
#include "wav_player.h"


#include "stdio.h"
#include "stdbool.h"


#include "Nextion.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern ApplicationTypeDef Appli_state;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

I2S_HandleTypeDef hi2s3;
DMA_HandleTypeDef hdma_spi3_tx;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

#define WAV_FILE1 "islak.wav"
#define WAV_FILE2 "sertap.wav"
#define WAV_FILE3 "deneme.wav"
#define WAV_FILE4 "bring_me.wav"
#define WAV_FILE5 "savage_21.wav"

#define WAV_FILE6 "yorgunum.wav"
#define WAV_FILE7 "sonne.wav"
#define WAV_FILE8 "rolling.wav"
#define WAV_FILE9 "back_to_black.wav"
#define WAV_FILE10 "nothing_else.wav"

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2S3_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART2_UART_Init(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
Nextion nextion;

NexComp basla;
NexComp dur;
NexComp ileri;
NexComp geri;
NexComp ses_azalt;
NexComp ses_artir;
NexComp devam;

NexComp nexText1;
NexComp nexText2;
NexComp nexText3;
NexComp nexText4;
NexComp nexText5;

int basla_durum, dur_durum, ileri_durum, geri_durum, ses_azalt_durum, ses_artir_durum, devam_durum;

bool test_1, test_2, test_3, test_4, test_5, test_6, test_7, test_8, test_9 = false;



uint8_t yazi_sayac;

uint8_t sarki_numarasi = 1;
char sarki_numarasi_c[5];

bool button_sayac = false;

uint16_t ses_seviye = 150;
char ses_seviye_c[5];


uint8_t Rx_Data[4];

bool pause_state = false;
bool devam_durum_b = false;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    NextionUpdate(huart, &nextion);



}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{

	if (htim->Instance == TIM1){
		yazi_sayac++;

		if(yazi_sayac == 4) yazi_sayac =0;
	}


}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_I2S3_Init();
  MX_USB_HOST_Init();
  MX_FATFS_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  NextionInit(&nextion, &huart2);
  HAL_Delay(40);

  NextionAddComp(&nextion, &nexText1, "t0", 0, 7, NULL, NULL);
  NextionAddComp(&nextion, &nexText2, "t1", 0, 8, NULL, NULL);
  NextionAddComp(&nextion, &nexText3, "t2", 0, 9, NULL, NULL);
  NextionAddComp(&nextion, &nexText4, "t3", 0, 10, NULL, NULL);
  NextionAddComp(&nextion, &nexText5, "t4", 0, 12, NULL, NULL);

  NextionAddComp(&nextion, &basla, "basla", 0, 1, NULL, NULL);
  NextionAddComp(&nextion, &dur, "dur", 0, 2, NULL, NULL);
  NextionAddComp(&nextion, &ileri, "ileri", 0, 7, NULL, NULL);
  NextionAddComp(&nextion, &geri, "geri", 0, 6, NULL, NULL);
  NextionAddComp(&nextion, &ses_azalt, "ses_eksi", 0, 4, NULL, NULL);
  NextionAddComp(&nextion, &ses_artir, "ses_arti", 0, 3, NULL, NULL);
  NextionAddComp(&nextion, &devam, "devam", 0, 11, NULL, NULL);


  HAL_TIM_Base_Start_IT(&htim1);




	CS43_Init(hi2c1, MODE_I2S);
  CS43_SetVolume(ses_seviye);//0-255 Ses -> ses_seviye
  CS43_Enable_RightLeft(CS43_RIGHT_LEFT);

  HAL_Delay(50);
  sprintf(ses_seviye_c, "%u", ses_seviye);
	NextionSetText(&nextion, &nexText5, ses_seviye_c);

  audioI2S_setHandle(&hi2s3);

  bool isSdCardMounted=0;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */


	if(yazi_sayac == 1){
	    NextionSetText(&nextion, &nexText1, "MP3");
	}
	if(yazi_sayac == 2){
	    NextionSetText(&nextion, &nexText1, "UYGAR");
	}
	if(yazi_sayac == 3){
		NextionSetText(&nextion, &nexText1, "BERAT");
	}

    NextionGetVal(&nextion, &basla, &basla_durum);
    NextionGetVal(&nextion, &dur, &dur_durum);
    NextionGetVal(&nextion, &ileri, &ileri_durum);
    NextionGetVal(&nextion, &geri, &geri_durum);
    NextionGetVal(&nextion, &ses_azalt, &ses_azalt_durum);
    NextionGetVal(&nextion, &ses_artir, &ses_artir_durum);
    NextionGetVal(&nextion, &devam, &devam_durum);

    if(ileri_durum == 1){
	    sarki_numarasi++;
	    sprintf(sarki_numarasi_c, "%u", sarki_numarasi);
	    NextionSetText(&nextion, &nexText2, sarki_numarasi_c);
	    test_5 = true;
    }

    if(geri_durum == 1){
	    sarki_numarasi--;
	    sprintf(sarki_numarasi_c, "%u", sarki_numarasi);
	    NextionSetText(&nextion, &nexText2, sarki_numarasi_c);

    }


    if(ses_artir_durum == 1){
 	   ses_seviye = ses_seviye + 20;
 	   CS43_SetVolume(ses_seviye);//0-255 Ses

	    sprintf(ses_seviye_c, "%u", ses_seviye);
	    NextionSetText(&nextion, &nexText5, ses_seviye_c);

 	   if(ses_seviye > 245){
 		ses_seviye=150;
 	   }
    }

    if(ses_azalt_durum == 1){
 	   ses_seviye = ses_seviye - 20;
 	   CS43_SetVolume(ses_seviye);//0-255 Ses

	    sprintf(ses_seviye_c, "%u", ses_seviye);
	    NextionSetText(&nextion, &nexText5, ses_seviye_c);

 	   if(ses_seviye < 50){
 		ses_seviye=150;
 	   }
    }

    if(devam_durum == true){
    	test_6 = true;
    	devam_durum_b = true;
    }






     if(Appli_state == APPLICATION_START)
         {
    	 test_1 = true;
           HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
         }
         else if(Appli_state == APPLICATION_DISCONNECT)
         {
           HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
           f_mount(NULL, (TCHAR const*)"", 0);
           isSdCardMounted = 0;
         }



     if(Appli_state == APPLICATION_READY)
     {
    	 test_2 = true;

    	 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);

     	if(!isSdCardMounted)
     	      {
     	        f_mount(&USBHFatFS, (const TCHAR*)USBHPath, 0);
     	        isSdCardMounted = 1;
     	      }

       	if(basla_durum == 1)
       	{

           	HAL_Delay(500);
           	test_3 = true;

           	if(pause_state == true){
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
                wavPlayer_pause();
                pause_state = false;
                test_7 = true;
           	}

           	if(devam_durum_b == true){
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
              	  test_8 = true;
                  wavPlayer_stop();
                  HAL_Delay(50);
             		if(sarki_numarasi == 1) {
             			wavPlayer_fileSelect(WAV_FILE1);
             	   		NextionSetText(&nextion, &nexText4, WAV_FILE1);
             		}
             		HAL_Delay(50);
             		if(sarki_numarasi == 2) {
             			wavPlayer_fileSelect(WAV_FILE2);
             			NextionSetText(&nextion, &nexText4, WAV_FILE2);
             		}
             		HAL_Delay(50);
             		if(sarki_numarasi == 3) {
             			wavPlayer_fileSelect(WAV_FILE3);
             			NextionSetText(&nextion, &nexText4, WAV_FILE3);
             		}
             		HAL_Delay(50);
             		if(sarki_numarasi == 4) {
             			wavPlayer_fileSelect(WAV_FILE4);
             			NextionSetText(&nextion, &nexText4, WAV_FILE4);
             		}
             		HAL_Delay(50);
             		if(sarki_numarasi == 5) {
             			wavPlayer_fileSelect(WAV_FILE5);
             			NextionSetText(&nextion, &nexText4, WAV_FILE5);
             		}
             		HAL_Delay(50);
             		if(sarki_numarasi == 6) {
             			wavPlayer_fileSelect(WAV_FILE6);
             			NextionSetText(&nextion, &nexText4, WAV_FILE6);
             		}
             		if(sarki_numarasi == 7) {
             			wavPlayer_fileSelect(WAV_FILE7);
             			NextionSetText(&nextion, &nexText4, WAV_FILE7);
             		}
             		if(sarki_numarasi == 8) {
             			wavPlayer_fileSelect(WAV_FILE8);
             			NextionSetText(&nextion, &nexText4, WAV_FILE8);
             		}
             		if(sarki_numarasi == 9) {
             			wavPlayer_fileSelect(WAV_FILE9);
             			NextionSetText(&nextion, &nexText4, WAV_FILE9);
             		}
             		if(sarki_numarasi == 10) {
             			wavPlayer_fileSelect(WAV_FILE10);
             			NextionSetText(&nextion, &nexText4, WAV_FILE10);
             		}
                      wavPlayer_play();

              	  wavPlayer_resume();
              	  pause_state = false;
              	devam_durum_b = false;
           	}

       		while(!wavPlayer_isFinished()){

       			test_9 = true;
       		          wavPlayer_process();

       		          if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
       		          {
       		        	  pause_state = true;
       		        	  break;
       		          }

       		    }



                    }





  }






   }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2S3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S3_Init(void)
{

  /* USER CODE BEGIN I2S3_Init 0 */

  /* USER CODE END I2S3_Init 0 */

  /* USER CODE BEGIN I2S3_Init 1 */

  /* USER CODE END I2S3_Init 1 */
  hi2s3.Instance = SPI3;
  hi2s3.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s3.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
  hi2s3.Init.AudioFreq = I2S_AUDIOFREQ_44K;
  hi2s3.Init.CPOL = I2S_CPOL_LOW;
  hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S3_Init 2 */

  /* USER CODE END I2S3_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 8400-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1000-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15
                           PD4 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
