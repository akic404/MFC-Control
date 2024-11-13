#include <Arduino.h>
#include "arduinoFFT.h"

#define PIN_ADC_IN    0
#define SAMPLES        64

arduinoFFT FFT;
/*
#define PIN_ADC2_CH2 0   //定义adc引脚宏 
int delaytime =50;//默认delay，可通过串口传入数据改变
int receivedValue;
int avg_3_flag=0;
*/
double avg_data_1=0;
double avg_data_2=0;
double avg_data_3=0;
double avg_data=0;

double fft_in[SAMPLES];
double fft_out[SAMPLES];

void setup() {

  Serial.begin(115200);      //初始化配置串口
  analogReadResolution(12);  //设置ADC的分辨率为12位(0-4096)
  analogSetAttenuation(ADC_11db);


for (int i=0;i<SAMPLES;i++){
fft_in[i]=0;
fft_out[i]=0;
}
  /*
衰减倍数
0dB衰减（ADC_ATTEN_0db）表示参考电压为1.1V    
2.5dB衰减（ADC_ATTEN_2_5db）表示参考电压为1.5V
6dB衰减（ADC_ATTEN_6db）表示参考电压为2.2V
11dB衰减（ADC_ATTEN_11db）表示参考电压为3.9V
ADC_ATTEN_DB_0    0 mV ~ 750 mV

ADC_ATTEN_DB_2_5  0 mV ~ 1050 mV

ADC_ATTEN_DB_6    0 mV ~ 1300 mV

ADC_ATTEN_DB_11   0 mV ~ 2500 mV
*/  
}


void loop() {
  /*
  //定义两个变量用于保存ADC采集的原始值和电压值（单位毫伏）
  int analogOriginalValue = 0;
  int analogVoltsValue = 0;
  int flag=Serial.available();
  int trashcan;
  float avg_3[4]={0,0,0,0};
  if (flag) { // 如果有可用的串口数据
  delaytime = Serial.parseInt();//读取串口数据
  trashcan = Serial.parseInt();//去掉串口数据末尾不知道是回车还是啥，如果不去掉就默认13ms了
  }
  analogOriginalValue = analogRead(PIN_ADC2_CH2);         //读取ADC原始值
  analogVoltsValue = analogReadMilliVolts(PIN_ADC2_CH2);  //读取ADC电压值（范围毫伏）

  

  
  // 上传A读取的ADC值:
  //Serial.printf("ADC analog value = %d\n",analogOriginalValue);
  Serial.printf("{OriginalValue}%d\n",analogOriginalValue);
  Serial.printf("{analogVoltsValue}%d\n",analogVoltsValue);
  Serial.printf("{analogVoltsValue_0}%d\n",analogVoltsValue-1250);//以0为中心
  Serial.printf("{delaytime}%d\n",delaytime);
  Serial.printf("{avg_3_flag}%d\n",avg_3_flag);
  //Serial.printf("{avg_3_flag}%d\n",avg_3_flag);

  delay(delaytime);  //延时
  */
for(int i=0;i<SAMPLES;i++){
avg_data_1=analogRead(PIN_ADC_IN);
avg_data_2=analogRead(PIN_ADC_IN);
avg_data_3=analogRead(PIN_ADC_IN);
avg_data=(avg_data_1+avg_data_2+avg_data_3)/3;
fft_in[i]=avg_data;

}
FFT = arduinoFFT(fft_in, fft_out, SAMPLES, 50); 
  FFT.Compute(FFT_FORWARD); 
  FFT.ComplexToMagnitude(); 

  for(int i=0;i<SAMPLES;i++){

  }
}
