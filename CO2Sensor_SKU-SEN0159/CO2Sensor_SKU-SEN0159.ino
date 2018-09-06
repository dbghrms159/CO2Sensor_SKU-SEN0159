 /*******************Demo for MG-811 Gas Sensor Module V1.1*****************************

Author:  Tiequan Shao: tiequan.shao@sandboxelectronics.com

         Peng Wei:     peng.wei@sandboxelectronics.com

          

Lisence: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)

 

Note:    This piece of source code is supposed to be used as a demostration ONLY. More

         sophisticated calibration is required for industrial field application. 

          

                                                    Sandbox Electronics    2012-05-31

************************************************************************************/

 

/************************Hardware Related Macros************************************/

#define         MG_PIN                       (0)     //아날로그 값을 입력받을 핀을 정의 

#define         BOOL_PIN                     (2)    //디지털값을 입력받을 핀을 정의

#define         DC_GAIN                      (8.5)   //증폭회로의 전압이득 정의(변경 X)

 

 

/***********************Software Related Macros************************************/

#define         READ_SAMPLE_INTERVAL         (50)    //샘플 값 추출 간격

#define         READ_SAMPLE_TIMES            (5)     //추출할 샘플값의 갯수 

                                                     //추출할 샘플값들의 평균값이 측정값입니다.

 

/**********************Application Related Macros**********************************/

//These two values differ from sensor to sensor. user should derermine this value.

#define         ZERO_POINT_VOLTAGE           (0.324) //이산화 탄소가 400ppm일때의 전압값 (수정 X)

#define         REACTION_VOLTGAE             (0.020) //이산화 탄소가 1000ppm일때의 전압값(수정 X)

 

/*****************************Globals***********************************************/

float           CO2Curve[3]  =  {2.602,ZERO_POINT_VOLTAGE,(REACTION_VOLTGAE/(2.602-3))};   

                                                     //위의 두 값들은 곡선위에 존제합니다.

                                                     //이 두점에서 라인이 생성이 되는데,

                                                     //원래의 곡선과 가깝습니다.

                                                     //번역된 부분으로 읽는데 잘 파악이 되지는 않네요, 센서값 곡선 그래프에 맞추어 계산을 하기 위한 설정값들이라고 생각하면 될듯합니다.

                                                     //data format:{ x, y, slope}; point1: (lg400, 0.324), point2: (lg4000, 0.280) 

                                                     //slope = ( reaction voltage ) / (log400 –log1000) 

 

 

void setup()

{

    Serial.begin(9600);                              //UART setup, baudrate = 9600bps

    pinMode(BOOL_PIN, INPUT);                        //set pin to input

    digitalWrite(BOOL_PIN, HIGH);                    //turn on pullup resistors

 

   Serial.print("MG-811 Demostration\n");                

}

 

void loop()

{

    int percentage;

    float volts;

     

    

    volts = MGRead(MG_PIN);

    Serial.print( "SEN0159:" );

    Serial.print(volts); 

    Serial.print( "V           " );

     

    percentage = MGGetPercentage(volts,CO2Curve);

    Serial.print("CO2:");

    if (percentage == -1) {

        Serial.print( "<400" );

    } else {

        Serial.print(percentage);

    }

    Serial.print( "ppm" );  

    Serial.print( "       Time point:" );

    Serial.print(millis());

    Serial.print("\n");

     

    if (digitalRead(BOOL_PIN) ){

        Serial.print( "=====BOOL is HIGH======" );

    } else {

        Serial.print( "=====BOOL is LOW======" );

    }

       

    Serial.print("\n");

     

    delay(200);

}

 

 

 

/*****************************  MGRead *********************************************

Input:   mg_pin - analog channel

Output:  output of SEN-000007

Remarks: This function reads the output of SEN-000007

************************************************************************************/

float MGRead(int mg_pin)

{

    int i;

    float v=0;

 
    //셈플 추출 횟수 5회
    for (i=0;i<READ_SAMPLE_TIMES;i++) {

        v += analogRead(mg_pin);

        //셈플 추출 간격 0.05초
        delay(READ_SAMPLE_INTERVAL);

    }// 셈플 추출을 5회를 하는데 한회당 0.05초 의 아날로그 값을 v에 누적 

    v = (v/READ_SAMPLE_TIMES) *5/1024 ;
    // 5회동안 추출한 값으로 평균을 구하고  동작 전원 / 아날로그 최대 값 5/1024를 곱한다
    
    return v;  

}

 

/*****************************  MQGetPercentage **********************************

Input:   volts   - SEN-000007 output measured in volts

         pcurve  - pointer to the curve of the target gas

Output:  ppm of the target gas

Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm) 

         of the line could be derived if y(MG-811 output) is provided. As it is a 

         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic 

         value.

************************************************************************************/

int  MGGetPercentage(float volts, float *pcurve)

{
  // ppm 이 400 미만인 경우 -1 반환
   if ((volts/DC_GAIN )>=ZERO_POINT_VOLTAGE) {

      return -1;

   } else { 
      //ppm 계산 10 ^ (((입력받은 전력 / 전압 이득 8.5) - 400ppm 인경우 0.324)/ 0.324/(2.602-3) + 2.602)
      return pow(10, ((volts/DC_GAIN)-pcurve[1])/pcurve[2]+pcurve[0]);

   }
}
