# CO2Sensor_SKU-SEN0159
Arduino Uno를 이용하여 CO2Sensor_SKU-SEN0159 로 co2의 ppm 출력

# CO2Sensor_SKU-SEN0159 원리
    
    센서 내부에 히터와 금속판이 있는데 히터로 공기를 가열하면 공기의 입자가 금속판에 달ㅏ게 된다.라붙게 되는데 입자가 달라 붙는 정도에 따라
    저항 값이 변하게 된다.

# CO2 측정단위
  
    CO2는 PPM이라는 단위를 사용하고 있으며 실내의 이산화 탄소의 농도를 의미 합니다.
    PPM은 Parts Per Million으로 100만분율을 의미합니다.
    어떤 양의 전체의 100만분의 몇을 차지하는가를 나타낼때 사용한다.
  
# CO2Sensor_SKU-SEN0159 값을 불러오기

    일반적으로 저항의 값을 받아오게 되면 0~1024 값으로 받아오기 때문에 analog값을 가지고 연산으 따로 해줘야 한다.
    첫번째로 저항값을 계산을 하는데 5번으 샘플링을 0.05초 간격으로 나온 값들의 합을 평균을 내서 5/1024 값을 곱을 해준다.
    두번째로 전압갑을 구한 값으로 ppm을 연산하는데 ppm이 400미만 일 때 -1을 반환을 하고 400ppm 이상이 경우에 ppm을 출력을 한다.
    ppm을 계산 하는 공식은 10 ^ (((입력받은 전력 / 전압 이득 8.5) - 400ppm 인경우 0.324)/ 0.324/(2.602-3) + 2.602) 이다.

# Arduino Uno connection

![co2](https://user-images.githubusercontent.com/38156821/45142121-a8faa280-b1f2-11e8-867d-c4af44b0ca00.jpeg)
<br> 위의 사진과 같이 검은선은 GND, 붉은선은 VCC, 파란선은 Input(Analog pin)으로 연결을 해준다.  

# 출력 결과

![2018-09-06 3 18 21](https://user-images.githubusercontent.com/38156821/45142137-b57efb00-b1f2-11e8-90ee-73ff36ff8ff0.png)
<br> 위의 사진과 같이 전달받은 전압, 현재 CO2의 ppm(400ppm미만인 경우 <400ppm으로 출력) 그리고 실행시간(millis)를 출력을 한다.
