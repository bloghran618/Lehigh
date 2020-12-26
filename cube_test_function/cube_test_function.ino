void setup() {

}

void loop() {
int delaytime=1000;
int z=0;
int y=0;
volatile unsigned char cube[4][4];
for (z=0;z<4;z++)
{
  for (y=0;y<4;y++)
  {
    cube[z][y]=0x01;
    delay(delaytime);
    cube[z][y]=0x03;
    delay(delaytime);
    cube[z][y]=0x07;
    delay(delaytime);
    cube[z][y]=0x0f;
    delay(delaytime);
  }
}  
}
