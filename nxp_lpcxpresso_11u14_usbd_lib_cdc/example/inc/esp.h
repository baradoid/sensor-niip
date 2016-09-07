#pragma once

//#define mus


#define AP0_SSID         "Polden"
#define AP0_PASS         "studio123"
#define AP0_SERVER_IP    "192.168.0.22"
#define AP0_LOCAL_IP     "192.168.0.42"

#define AP1_SSID         "TL-WR842ND"
#define AP1_PASS         "kkkknnnn"
#define AP1_SERVER_IP    "192.168.0.103"
#define AP1_LOCAL_IP     "192.168.0.90"


#define AP2_SSID 		 "My ASUS"
#define AP2_PASS         "kkkknnnn"
#define AP2_LOCAL_IP     "192.168.43.5"
#define AP2_SERVER_IP    "192.168.43.1"


#define localPort   "80"
#define serverPort   "1488"


extern SemaphoreHandle_t xEspMutex;

void vEspTask(void *pvParameters);
//bool espSendCommand(const char *cmdStr, uint32_t to);
bool espSend(const char *cmd);

void lockEsp();
void unLockEsp();
bool isConnected();
