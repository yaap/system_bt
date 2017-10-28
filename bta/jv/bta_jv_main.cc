/******************************************************************************
 *
 *  Copyright 2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  This is the main implementation file for the BTA Java I/F
 *
 ******************************************************************************/

#include "bta_api.h"
#include "bta_jv_api.h"
#include "bta_jv_int.h"
#include "bta_sys.h"

/*****************************************************************************
 * Constants and types
 ****************************************************************************/

tBTA_JV_CB bta_jv_cb;

/* state machine action enumeration list */
#define BTA_JV_NUM_ACTIONS (BTA_JV_MAX_INT_EVT & 0x00ff)

/* type for action functions */
typedef void (*tBTA_JV_ACTION)(tBTA_JV_MSG* p_data);

/* action function list */
const tBTA_JV_ACTION bta_jv_action[] = {
    bta_jv_start_discovery,       /* BTA_JV_API_START_DISCOVERY_EVT */
    bta_jv_l2cap_read,            /* BTA_JV_API_L2CAP_READ_EVT */
    bta_jv_rfcomm_connect,        /* BTA_JV_API_RFCOMM_CONNECT_EVT */
    bta_jv_rfcomm_close,          /* BTA_JV_API_RFCOMM_CLOSE_EVT */
    bta_jv_rfcomm_start_server,   /* BTA_JV_API_RFCOMM_START_SERVER_EVT */
    bta_jv_rfcomm_stop_server,    /* BTA_JV_API_RFCOMM_STOP_SERVER_EVT */
    bta_jv_rfcomm_write,          /* BTA_JV_API_RFCOMM_WRITE_EVT */
    bta_jv_set_pm_profile,        /* BTA_JV_API_SET_PM_PROFILE_EVT */
    bta_jv_change_pm_state,       /* BTA_JV_API_PM_STATE_CHANGE_EVT */
};

/*******************************************************************************
 *
 * Function         bta_jv_sm_execute
 *
 * Description      State machine event handling function for JV
 *
 *
 * Returns          void
 *
 ******************************************************************************/
bool bta_jv_sm_execute(BT_HDR* p_msg) {
  bool ret = false;
  uint16_t action = (p_msg->event & 0x00ff);
  /* execute action functions */

  if (action < BTA_JV_NUM_ACTIONS) {
    (*bta_jv_action[action])((tBTA_JV_MSG*)p_msg);
    ret = true;
  }

  return (ret);
}
