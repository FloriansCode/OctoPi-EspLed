void Operational()
{
          //Fade Out
          strip.fill(strip.Color(LED_R,LED_G,LED_B), 0, 0);
        for(LED_R, LED_G, LED_B; LED_R>=1,LED_G>=1, LED_B>=1 ; LED_R--,LED_G--,LED_B-- ){
          strip.fill(strip.Color(LED_R,LED_G,LED_B), 0, 0);
          strip.show();
          delay(50);
          }
          //Reset Color
          LED_R = 0;
          LED_G = 0;
          LED_B = 0;

         //Fade in
         for(LED_R, LED_G, LED_B; LED_R<=50,LED_G<=50, LED_B<=50 ; LED_R++,LED_G++,LED_B++ ){
          strip.fill(strip.Color(LED_R,LED_G,LED_B), 0, 0);
          strip.show();
          delay(50);
          }
          
}
void Printing()
{
        strip.show();
        led_calc = (NUM_LEDS*  progress_completion) /100;
        //Debug Progress
        //Serial.print("Progress: "); 
        //  Serial.println(progress_completion);
        //Serial.print("Leds: ");
        //  Serial.println(NUM_LEDS);
        //Serial.print("Leds Clac: ");
        //  Serial.println(led_calc);
        
        if(led_calc >=1){
        strip.fill(strip.Color(50,50,50), 0, led_calc);
        strip.show();
        }
        else{
          strip.clear();
          strip.fill(strip.Color(50,50,50), 0, 1);
          strip.show();
          }
}
void Cancelling(){
          strip.fill(strip.Color(LED_R,LED_G,LED_B), 0, 0);
          
        for(LED_R; LED_R >=0; LED_R--){
          strip.fill(strip.Color(LED_R,0,0), 0, 0);
          strip.show();
          Serial.println(LED_R);
          delay(50);
          }
          LED_R = 0;
          
        for(LED_R; LED_R<=50; LED_R++){
          strip.fill(strip.Color(LED_R,0,0), 0, 0);
          strip.show();
          Serial.println(LED_R);
          delay(50);
          }
          LED_R = 50;
}
void Offline(){
          strip.clear();
          strip.show();
}
void FadeOut(){
        for(LED_R, LED_G, LED_B; LED_R>=1,LED_G>=1, LED_B>=1 ; LED_R--,LED_G--,LED_B-- ){
          strip.fill(strip.Color(LED_R,LED_G,LED_B), 0, 0);
          strip.show();
          delay(50);
          }
          //Reset Color
          LED_R = 0;
          LED_G = 0;
          LED_B = 0;
}
