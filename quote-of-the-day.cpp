#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "arduino_secrets.h"
#include "common.h"
#include "quote-of-the-day.h"

QuoteOfTheDay QuoteOfTheDayService::get() {
  HTTPClient http;
  String quoteOfTheDayUrl = "https://zenquotes.io/api/random";
  http.begin(quoteOfTheDayUrl);

  int httpCode;
  int retry = 0;

  do {
    httpCode = http.GET();
    retry ++;
    Serial.println("...");
  } while (httpCode <= 0 && retry < HTTP_RETRY);

  if (httpCode > 0) {
    String response = http.getString();
    http.end();

    Serial.println("OK");
    Serial.println("");

    DynamicJsonDocument doc(8192);
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return {"", ""};
    }

    return {
      doc[0]["q"],
      doc[0]["a"]
    };

  } else {
    String error;
    error += F("KO -> code erreur = ");
    error += String(httpCode);
    Serial.println(error);
    Serial.println("");
    return {error, "La direction"};
  }
}