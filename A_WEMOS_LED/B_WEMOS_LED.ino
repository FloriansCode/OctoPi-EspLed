//http request to get Job Information
void API_JOB_CHECK (){
    HTTPClient http;                        //Preparing the HTTP request.
      http.begin(octoip_files);             //HTTP link
      http.addHeader("X-Api-Key", APIKEY);  //add API KEY
        int httpCode = http.GET();          //Send the request
        String payload = http.getString();  //Get the request response payload
      http.end();   //Close connection

        // Just used: https://arduinojson.org/v6/assistant/ and striped that down
        StaticJsonDocument<768> doc;
        deserializeJson(doc, payload);      
          JsonObject job = doc["job"];
          JsonObject progress = doc["progress"];    
            progress_completion = progress["completion"]; //Progressbar in %
            String state = doc["state"]; // State of the Printer
            String pre_state = "waiting";
          //Serial Print status.
          Serial.print("Status: ");
          Serial.println(state);
                    Serial.print("URL: ");
          Serial.println(octoip_files);

            if((state == "Operational") or (state == "Paused"))
              {
              if(pre_state != state){
                  FadeOut();
                }
                
              Operational();
              pre_state= state;
              }
            else if(state == "Printing")
              {
              if(pre_state != state){
                  FadeOut();
                }
                
              Printing();
              pre_state= state;
              }
            else if(state == "Cancelling")
              {
              if(pre_state != state){
                  FadeOut();
                }
                
              Cancelling();
              pre_state= state;
              }
            else
              {
              if(pre_state != state){
                  FadeOut();
                }
                
              Offline();
              pre_state= state;
              }
  }
