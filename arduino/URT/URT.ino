#include <Arduino.h>
#define PIN_ADC2_CH2 1   //定义adc引脚宏 
int delaytime =50;//默认delay，可通过串口传入数据改变
int receivedValue;
float avg_3[6]={0,0,0,0,0,1};/*
数据1，数据2，数据3，flag(第几次保存数据了)，平均值,重置模式(1:三次传一次，然后清空所有数据  2:取最新三次平均值)
*/
float offset[2]={0,0};//Origina Volts 的偏移量

void __offset_INIT__(){
  delay(1000);
  Serial.printf("START INIT OFFSET ! PLEASE WAIT!\n");
  for(int i=1;i<=10000;i++){
  offset[0] += float(analogRead(PIN_ADC2_CH2));         //读取ADC原始值
  offset[1] += float(analogReadMilliVolts(PIN_ADC2_CH2));//电压值（单位毫伏）
  }
  offset[1] /= 10000;
  Serial.printf("OFFSET OK ! START OUTPUT !\n");
  delay(1000);
}



void setup() {

  Serial.begin(115200);      //初始化配置串口
  analogReadResolution(12);  //设置ADC的分辨率为12位(0-4096)
  analogSetAttenuation(ADC_11db);//设置衰减
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
  __offset_INIT__();//初始化偏移量
}


void loop() {
  //定义两个变量用于保存ADC采集的原始值和电压值（单位毫伏）
  int analogOriginalValue = 0;
  int analogVoltsValue = 0;

  //##### 改设置 #####
  /*
  目前是发什么delay改成什么
  */
  if (Serial.available()) { // 如果有可用的串口数据
  delaytime = Serial.parseInt();//读取串口数据
 // int trashcan = Serial.parseInt();//去掉串口数据末尾不知道是回车还是啥，如果不去掉就默认13ms了
  }

  //##### 收集数据 #####
  analogOriginalValue = analogRead(PIN_ADC2_CH2);         //读取ADC原始值
  analogVoltsValue = analogReadMilliVolts(PIN_ADC2_CH2);  //读取ADC电压值（范围毫伏）

  //##### 处理数据 #####
  switch(int(avg_3[5])){

    case 1:{//初始化数据和flag，保留平均值（第4项），这个是每三次才传一次，传完后清空数据
      if (avg_3[3]<3){
        avg_3[int(avg_3[3])]=analogVoltsValue;//第 flag 个元素收集数据
        avg_3[3]++;
      }
      else{
        avg_3[4]=(avg_3[0]+avg_3[1]+avg_3[2])/3;
        for(int i=0;i<4;i++){
        avg_3[i]=0;
        }
      }
        break;
    }

    case 2:{//初始化数据，flag初始化，取最新三次求平均值
      avg_3[int(avg_3[3])]=analogVoltsValue;//第 flag 个元素收集数据
      avg_3[3]++;
      avg_3[4]=(avg_3[0]+avg_3[1]+avg_3[2])/3;
      if (avg_3[3]==3){
        avg_3[3]=0;
      }
      break;
    }
  }



        

  //##### 输出数据 #####
  // 上传A读取的ADC值:
  //Serial.printf("ADC analog value = %d\n",analogOriginalValue);
  Serial.printf("{delaytime}%d\n",delaytime);//延迟时间

  Serial.printf("{Ori_Offset}%f\n",offset[0]);//ori偏移量
  Serial.printf("{OriginalValue}%d\n",analogOriginalValue);//原始值
  Serial.printf("{Original_9%d\n",analogOriginalValue-int(offset[0]));//ori修正后

  Serial.printf("{Volts_Offset}%f\n",offset[1]);//Volts偏移量
  Serial.printf("{VoltsValue}%d\n",analogVoltsValue);//毫伏为单位
  Serial.printf("{Volts_0}%d\n",analogVoltsValue-int(offset[1]));//毫伏为单位，以0为中心

  switch (int(avg_3[5])){
    case 1:{
      if (avg_3[3]==0){
        Serial.printf("{avg_3_data}%f\n",avg_3[4]-offset[1]);
      }
      break;
    }
    case 2:{
      Serial.printf("{avg_3_data}%f\n",avg_3[4]-offset[1]);
      break;
    }
  }

  delay(delaytime);  //延时
}