/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    App/custom_app.c
  * @author  MCD Application Team
  * @brief   Custom Example Application (Server)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "custom_app.h"
#include "custom_stm.h"
#include "stm32_seq.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  /* Channel1 */
  uint8_t               Data1_Notification_Status;
  /* Channel2 */
  uint8_t               Data2_Notification_Status;
  /* USER CODE BEGIN CUSTOM_APP_Context_t */
  uint8_t data1[128];
  uint8_t data2[128];
  /* USER CODE END CUSTOM_APP_Context_t */

  uint16_t              ConnectionHandle;
} Custom_App_Context_t;

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/**
 * START of Section BLE_APP_CONTEXT
 */

PLACE_IN_SECTION("BLE_APP_CONTEXT") static Custom_App_Context_t Custom_App_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

uint8_t UpdateCharData[247];
uint8_t NotifyCharData[247];

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* Channel1 */
static void Custom_Data1_Update_Char(void);
static void Custom_Data1_Send_Notification(void);
/* Channel2 */
static void Custom_Data2_Update_Char(void);
static void Custom_Data2_Send_Notification(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_1 */

  /* USER CODE END CUSTOM_STM_App_Notification_1 */
  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* USER CODE END CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* Channel1 */
    case CUSTOM_STM_DATA1_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA1_READ_EVT */

      /* USER CODE END CUSTOM_STM_DATA1_READ_EVT */
      break;

    case CUSTOM_STM_DATA1_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA1_WRITE_NO_RESP_EVT */

      /* USER CODE END CUSTOM_STM_DATA1_WRITE_NO_RESP_EVT */
      break;

    case CUSTOM_STM_DATA1_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA1_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_DATA1_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_DATA1_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA1_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_DATA1_NOTIFY_DISABLED_EVT */
      break;

    /* Channel2 */
    case CUSTOM_STM_DATA2_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA2_READ_EVT */

      /* USER CODE END CUSTOM_STM_DATA2_READ_EVT */
      break;

    case CUSTOM_STM_DATA2_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA2_NOTIFY_ENABLED_EVT */

      /* USER CODE END CUSTOM_STM_DATA2_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_DATA2_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_DATA2_NOTIFY_DISABLED_EVT */

      /* USER CODE END CUSTOM_STM_DATA2_NOTIFY_DISABLED_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_STM_App_Notification_default */

      /* USER CODE END CUSTOM_STM_App_Notification_default */
      break;
  }
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_2 */

  /* USER CODE END CUSTOM_STM_App_Notification_2 */
  return;
}

void Custom_APP_Notification(Custom_App_ConnHandle_Not_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_APP_Notification_1 */

  /* USER CODE END CUSTOM_APP_Notification_1 */

  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_APP_Notification_Custom_Evt_Opcode */

    /* USER CODE END P2PS_CUSTOM_Notification_Custom_Evt_Opcode */
    case CUSTOM_CONN_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_CONN_HANDLE_EVT */

      /* USER CODE END CUSTOM_CONN_HANDLE_EVT */
      break;

    case CUSTOM_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_DISCON_HANDLE_EVT */

      /* USER CODE END CUSTOM_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_APP_Notification_default */

      /* USER CODE END CUSTOM_APP_Notification_default */
      break;
  }

  /* USER CODE BEGIN CUSTOM_APP_Notification_2 */

  /* USER CODE END CUSTOM_APP_Notification_2 */

  return;
}

void Custom_APP_Init(void)
{
  /* USER CODE BEGIN CUSTOM_APP_Init */
	UTIL_SEQ_RegTask(1<< CFG_CHANNEL_1_DATA_UPDATED_ID, UTIL_SEQ_RFU, Custom_Data1_Send_Notification);
	UTIL_SEQ_RegTask(1<< CFG_CHANNEL_2_DATA_UPDATED_ID, UTIL_SEQ_RFU, Custom_Data2_Send_Notification);
  /* USER CODE END CUSTOM_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

/* Channel1 */
void Custom_Data1_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Data1_UC_1*/

  /* USER CODE END Data1_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_DATA1, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Data1_UC_Last*/

  /* USER CODE END Data1_UC_Last*/
  return;
}

void Custom_Data1_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Data1_NS_1*/
  updateflag = TRUE;
  static uint8_t counterValue = 0;
  for (int i= 0; i < 128; ++i)
  {
	  Custom_App_Context.data1[i] = counterValue;
  }
  counterValue++;

  memcpy(NotifyCharData, Custom_App_Context.data1, 128);
  /* USER CODE END Data1_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_DATA1, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Data1_NS_Last*/

  /* USER CODE END Data1_NS_Last*/

  return;
}

/* Channel2 */
void Custom_Data2_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Data2_UC_1*/
  /* USER CODE END Data2_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_DATA2, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Data2_UC_Last*/

  /* USER CODE END Data2_UC_Last*/
  return;
}

void Custom_Data2_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Data2_NS_1*/
  updateflag = TRUE;
  static uint8_t counterValue = 50;
  for (int i= 0; i < 128; ++i)
  {
	  Custom_App_Context.data2[i] = counterValue;
  }
  counterValue++;

  memcpy(NotifyCharData, Custom_App_Context.data2, 128);
  /* USER CODE END Data2_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_DATA2, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Data2_NS_Last*/

  /* USER CODE END Data2_NS_Last*/

  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/
void P2PS_APP_Data_from_adc_update_Action(uint8_t channelNumber)
{
    UTIL_SEQ_SetTask(1<<CFG_CHANNEL_1_DATA_UPDATED_ID, CFG_SCH_PRIO_0);
    UTIL_SEQ_SetTask(1<<CFG_CHANNEL_2_DATA_UPDATED_ID, CFG_SCH_PRIO_0);
}
/* USER CODE END FD_LOCAL_FUNCTIONS*/
