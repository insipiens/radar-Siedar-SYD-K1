# radar-Siedar-SYD-K1
speed radar

Sketch for basic functionality of radar with Arduino mega 2560 pro, using Serial1 hardware pins - rcv 18 & trx 19

Radar unit: https://www.aliexpress.com/item/1005001737289310.html?spm=a2g0o.store_pc_allProduct.8148356.1.435677abMe7quh

The device can be driven via a basic 12 volt supply (it has a wider range but 12 volts seems adequate for an extended distance). You will need to ground your microcontroller with the RS485 converter input ONLY. No need to ground the input & microntroller ground directly with the device - althoug if powering the device and MC from the same source then common ground is ok.

The A+,B- and ground connected to a MAX13487 chip based converter. This avoids the issue of switching from input to output required normally with MAX 485 chips. The converter can be bought cheaply on Amazon or AliExpress etc.


![image](https://user-images.githubusercontent.com/68975498/128780959-dac594ff-e7dd-4862-ad6c-0894299a7a4b.png)

If you do not have a 12v supply then using an ESP32 chip connected to a 2.4A AC/DC usb supply can also supply the required power with a 5v > 12v buck boost (I have this currently over a 25m connection).



