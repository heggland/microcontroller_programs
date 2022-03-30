/*
Anta du har en RFID leser og et relé på en ESP32.
Du kan anta at relé er på pin 14.
Du kan anta at RFID leser er av type MFRC522 for dette eksempelet, med SS pin 5 og RST pin 0.
Logikken som  trengs: Om en ID brikke med idTag= UID17f9bddbb10 blir plassert over RFID skanner, så skrur releet seg på/av.
*/

#include <SPI.h>
#include <MFRC522.h>

// RELAY
#define RELAY_PIN 14
// LED
#define LED_RED_PIN 15
// RFID reader
#define SS_PIN 34
#define RST_PIN 35

// Instance
MFRC522 rfid(SS_PIN, RST_PIN);

String tagID = "";

void setup()
{
    SPI.begin();                  // SPI bus
    mfrc522.PCD_Init();           // MFRC522
    pinMode(LED_RED_PIN, OUTPUT); // LED
    pinMode(RELAY_PIN, OUTPUT);   // RELAY
}

void loop()
{
    while (getID())
    {
        if (tagIsInDatabase(tagID))
        {
            authorized();
        }
        else
        {
            notAuthorized();
        }
    }
    delay(1000);
}

// Read new tag if available
boolean getID()
{
    // Getting ready for Reading PICCs
    if (!mfrc522.PICC_IsNewCardPresent())
    { // If a new PICC placed to RFID reader continue
        return false;
    }
    if (!mfrc522.PICC_ReadCardSerial())
    { // Since a PICC placed get Serial and continue
        return false;
    }
    tagID = "";
    for (uint8_t i = 0; i < 4; i++)
    {
        tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
    }
    mfrc522.PICC_HaltA(); // Stop reading
    return true;
}

void authorized()
{
    digitalWrite(RELAY_PIN, HIGH);
    delay(1000);
    digitalWrite(RELAY_PIN, LOW);
    delay(1000);
}

void notAuthorized()
{
    digitalWrite(LED_RED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_RED_PIN, LOW);
    delay(1000);
}

// simpel database
String tagDatabase[] = {"UID17f9bddbb10", "12345678"};

// check if tag is in the database
bool tagIsInDatabase(String tag)
{
    bool idMatch = false;
    if (tag == "")
        return false;
    for (int i = 0; i < sizeof(tagDatabase); i++)
    {
        if (tag == tagDatabase[i])
        {
            idMatch = true;
        }
    }
    return idMatch;
}
