int serInLen=500;
int redPin = 9;
int greenPin = 10;
char serInString[500];
String totalstr;
int postotal;
char totalchars[500];

void setup() {
  pinMode(redPin, INPUT);
  pinMode(greenPin, INPUT);
  Serial.begin(9600);
  delay(1000);
}
void loop() {
  char buffer[5];
  long openCases=0;
  int lineNr=0;
  for(lineNr=1;lineNr<=1;lineNr++) {
      Serial.print("#S|RDDESK|[");
      Serial.print(itoa((lineNr), buffer, 10));
      Serial.println("]#");
      readSerialString (serInString, 10000);
      Serial.println(serInString);
        totalstr = serInString;
        postotal = totalstr.lastIndexOf("total");
        totalstr.substring(postotal+7).toCharArray(totalchars,serInLen);
      Serial.println(totalchars);
        openCases=atoi(totalchars);
      Serial.println(openCases);
      if(openCases <= 100) {
          analogWrite(greenPin, 1);
          analogWrite(redPin, 255-(255*(openCases)/100));
        }
        else {
          if(openCases <= 200) {
            analogWrite(redPin, 1);
            analogWrite(greenPin, 255*((openCases)-100)/100);
          }
          else {
            analogWrite(redPin, 1);
           // analogWrite(greenPin, 255);
          }
       }
        delay(2000);
      }
}

void readSerialString (char *strArray,long timeOut) {
   long startTime=millis();
   int i;
   while (!Serial.available()) {
      if (millis()-startTime >= timeOut) {
         return;
      }
   }
   while (Serial.available() && i < serInLen) {
      strArray[i] = Serial.read();
      i++;
   }
}
