#include <rockets_client.h>

int RELAY_PIN = 5; // GPIO2

void setup()
{
    Serial.begin(115200); // baud rate: 115200

    pinMode(RELAY_PIN, OUTPUT);

    rockets_client::init(rockets_client::serverConfigPresets.MECHE, "0", "DummyRelayTest");
}

void loop()
{
    rockets_client::StaticJsonDoc message =
        rockets_client::getLatestMessage();

    auto data = message["data"];
    if (data.isNull())
    {
        // no new message
        return;
    }

    // sample response: {"data":{"command":"relay-on"}}

    const char *command = data["command"];
    if (command == NULL)
    {
        // no command
        return;
    }

    std::string commandStr(command);

    Serial.print("Received command: ");
    Serial.println(commandStr.c_str());

    if (commandStr == "relay-on")
    {
        Serial.println("Turning on relay");
        digitalWrite(RELAY_PIN, HIGH);
    }
    else if (commandStr == "relay-off")
    {
        Serial.println("Turning off relay");
        digitalWrite(RELAY_PIN, LOW);
    }
}
