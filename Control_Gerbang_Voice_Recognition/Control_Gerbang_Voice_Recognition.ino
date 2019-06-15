  #include <StepperMotor.h>
  #include <ESP8266WiFi.h>
  #include<FirebaseArduino.h>
  
  #define FIREBASE_HOST "misbahunpak2019.firebaseio.com"
  #define FIREBASE_AUTH "5IMeAKambbHqG2ye7a4yi7tlfudDWS8cNiyf8CQ3"
  #define WIFISSID "www.interactiverobotics.club3" // Assign your WiFi SSID
  #define PASSWORD  "cilibur2019" // Assign your WiFi password
  
StepperMotor motor(D3,D4,D5,D1);

void setup(){
  Serial.begin(115200);
  motor.setStepDuration(1);
  WiFi.begin(WIFISSID,PASSWORD);
    Serial.print("connecting");
    while (WiFi.status()!=WL_CONNECTED){
      Serial.print(".");
      delay(500);
    }
    Serial.println();
    Serial.print("connected:");
    Serial.println(WiFi.localIP());
    
    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
    Firebase.set("FB1",0);//the variable in which is used in our Firebase and MIT App Inventor
    Firebase.set("FB2",0);//the variable in which is used in our Firebase and MIT App Inventor
 
}

 void firebasereconnect()
  {
    Serial.println("Trying to reconnect");
      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    }
    
void loop(){
  //motor.step(4500);
  if (Firebase.failed()) {
        Serial.print("setting number failed:");
        Serial.println(Firebase.error());
        firebasereconnect();
        return;
    }
    int FB1coy=Firebase.getString("FB1").toInt();//The value read from the firebase is read in the form of String and is converted into Integer
    if(FB1coy==1){
       motor.step(-4700);
       Serial.println("Maju Jalan");
      }else if (FB1coy==0){
       Serial.println("Maju Berhenti");
      }
      
    int FB2coy=Firebase.getString("FB2").toInt();//The value read from the firebase is read in the form of String and is converted into Integer
    if(FB2coy==1){
       motor.step(4700);
       Serial.println("Mundur Jalan");
      }else if(FB2coy==0){
        Serial.println("Mundur Berhenti");
      }
}
