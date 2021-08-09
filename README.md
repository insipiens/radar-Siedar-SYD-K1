# radar-Siedar-SYD-K1  

Doppler velocity radar

Sketch for basic functionality of the radar with Arduino(tested with mega 2560 pro using Serial1 hardware pins - rcv 18 & trx 19).

These devices are often used in Speed alert signs and traffic monitoring situations.

Radar unit: https://www.aliexpress.com/item/1005001737289310.html?spm=a2g0o.store_pc_allProduct.8148356.1.435677abMe7quh

![image](https://user-images.githubusercontent.com/68975498/128783648-4a6ced84-a2f3-4fd2-8bb7-fcb01851fa94.png)


The device can be driven via a basic 12 volt supply (it has a wider range but 12 volts seems adequate for an extended distance). You will need to ground your microcontroller with the RS485 converter (shown below) input ONLY. No need to ground the input & microntroller ground directly with the end point [device] - although if powering the device and MC from the same source then common ground is ok.

The A+,B- and ground connected to a MAX13487 chip based converter. This avoids the issue of switching from input to output required normally with MAX 485 chips. The converter can be bought cheaply on Amazon or AliExpress etc.


![image](https://user-images.githubusercontent.com/68975498/128780959-dac594ff-e7dd-4862-ad6c-0894299a7a4b.png)

Note: the above RS485 converter does not use common 0.10" pitch - however using headers you can attach it to a perforated board for prototyping...

The above RS485 converter also handles 3.3v supply and input so works well if you use an ESP32 based device instead of an Arduino. Always be careful if using qa 3.3v device!

Some notes:

Device can be powered over cat 5 cable @12v (tested 20 metres)
Can be sensitive to close electromagnetic interference
The range, as advertised, was confirmed. The device works well - even when not in totally clear sight!


