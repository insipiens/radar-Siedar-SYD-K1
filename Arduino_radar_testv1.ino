
//                       {strt(2),Protocolx10,op,update,fastvpower,direct, sens,min ,max , correction, n/a, end 
byte query_device[16] =  {0x7E,0x7E,0x02,0x10,0x00,0x01,0x01,      0x01,   0x04,0x04,0xDC,0x03,0xE8,0x00,0xEF,0xEF};
byte reset_device[16] =  {0x7E,0x7E,0x02,0x10,0x08,0x01,0x01,0x01,0x04,0x04,0xDC,0x03,0xE8,0x00,0xEF,0xEF};
byte restart_device[16] ={0x7E,0x7E,0x02,0x10,0x07,0x01,0x02,0x01,0x04,0x0F,0xDC,0x03,0xE8,0x00,0xEF,0xEF};
byte set_device[16] =    {0x7E,0x7E,0x02,0x10,0x01,0x01,0x02,0x01,0x04,0x05,0xDC,0x05,0xE8,0x00,0xEF,0xEF};


int inspeed;
int outspeed;
int in_bytes[14];
int arrivingdatabyte = 0;
int temp_byte;
int error_bytes;
int n= 0;
int y=0;


void setup() 
{
  // initialize both serial ports:
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1);
  Serial.println(" set up completed!!!!!");
  Serial.println("type 1 = restart, 2 = reset to factory, 3 = set device to settings, 4 = query device settings");
}

void loop() 
{
if(Serial.available() != 0)
{
  {
    int arrivingdatabyte= Serial.read(); // can be -1 if read error
    switch(arrivingdatabyte) { 
      case '1': //restart device
        writeCommand(restart_device,16);
        Serial.print("restarting device: ");
        Serial.println();
        break;
      case '2': //reset device to factory
        writeCommand(reset_device,16);
        Serial.print("resetting device: ");
        Serial.println();
        break;
      case '3': //set device
        writeCommand(set_device,16);
        Serial.print("set device to: ");
        Serial.println();
        break;
      case '4': //set device
        writeCommand(query_device,16);
        Serial.print("query device result: ");
        Serial.println();
        break;        
      default:
        break;
   }
  }
}


//    getInput();
  readSerial();
} 



void writeCommand( byte b[], int sizeOfArray ) 
{
//        Serial.println(arrivingdatabyte, DEC);
        Serial.print(Serial1.availableForWrite());
        Serial.print("Sending: ");
        for(int n=0; n<sizeOfArray; n++)
        {
          Serial.print(b[n],HEX);
          Serial.print(" ");
      
        }
        size_t wx = Serial1.write(b,16); 
        Serial.print(wx);

} 


void readSerialtest(){
   if(Serial1.available() > 0)
   {
   in_bytes[n] = Serial1.read(); // Then: Get them.
   Serial.print( in_bytes[n],HEX);
   }
}
//////////////////////get device message/////////////////////////////
void readSerial(){
   if(Serial1.available() > 0)
    ///////////////////////////////////////Receiving////////////////////////////////
   {  
     temp_byte=Serial1.read();
     if(temp_byte == 126)
     { 
       Serial.print(temp_byte,HEX);
       Serial.print(" ");
       n = 0;
     }
     else
     {
       if(temp_byte == 239)
       {
         Serial.print(temp_byte,HEX);
         Serial.print(" ");
         y++;
         n++;
         if(n==14)
         {
            switch(in_bytes[2]) 
            { 
             case 16:
               queryCommand();
               break;
             case 34:
               outSpeed();
               break;
             case 17:
               Serial.println("Settings updated!!");
               break;
             case 0xF1:
               Serial.println("Error!: ");
               break;
             default:
               Serial.print("Unknown Response: ");
               Serial.println(in_bytes[2]);
               break;         
             }
          }
       }
       else
       {
         in_bytes[n] = temp_byte;
         Serial.print(n);
         Serial.print("=");
         Serial.print(in_bytes[n],HEX);
         Serial.print(" ");
         n++;
          
       }
     }
   }      
}

void queryCommand()
{
Serial.print("update rate [1/10s] :"); 
Serial.println(in_bytes[3]);
Serial.print("Pattern [fast/power] :"); 
Serial.println(in_bytes[4]);
Serial.print("Direction [Both|in|out] :"); 
Serial.println(in_bytes[5]);
Serial.print("Sensitivity :"); 
Serial.println(in_bytes[6]);
Serial.print("Min speed [kph] :"); 
Serial.println(in_bytes[7]);
Serial.print("Max speed [kph] :"); 
Serial.println(in_bytes[8]);
Serial.print("Correction factor :"); 
Serial.print(in_bytes[9]);
Serial.println(in_bytes[10]);
Serial.println();
//update,fastvpower,direct, sens,min ,max , correction, n/a, end 

} 
void outSpeed()
{
  inspeed = ((in_bytes[5])+(in_bytes[4]));//*0.621371;
  outspeed = ((in_bytes[8])+(in_bytes[7]));//*0.621371;
  Serial.print("  Incoming: ");
  Serial.print( inspeed);
  Serial.print("  Outgoing: ");
  Serial.print(outspeed);
  Serial.println();
}

void replyResult()
{
  switch(in_bytes[2]) 
  { 
    case 17:
      Serial.println("Settings updated!!");
      break;
    case 0xF1:
      Serial.println("Error!: ");
      
      break;
    default:
      break;
               
  }
}  
