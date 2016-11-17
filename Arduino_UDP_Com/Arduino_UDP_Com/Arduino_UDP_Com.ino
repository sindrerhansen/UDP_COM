


#include "Persjon.h"

#include <UIPEthernet.h>
// The connection_data struct needs to be defined in an external file.
#include <UIPServer.h>
#include <UIPClient.h>
#include <TimeLib.h>
#include <ArduinoJson.h>



// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 3, 89);

unsigned int localPort = 6500;      // local port to listen on
unsigned long timer;

// buffers for receiving and sending data
char packetBuffer[1000]; //buffer to hold incoming packet,
char ReplyBuffer[1000];
// a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
long randNumber;



void setup() {
	// start the Ethernet and UDP:
	Ethernet.begin(mac, ip);
	Udp.begin(localPort);
	timer = millis();
	Serial.begin(9600);
	randomSeed(analogRead(0));
}



void loop()
{
	// if there's data available, read a packet
	int packetSize = Udp.parsePacket();
	if (packetSize)
	{
		Udp.read(packetBuffer, 100);

		Serial.println(packetBuffer);
		String reply = "acknowledged at: " + String(millis());
		reply.toCharArray(ReplyBuffer, 200);
		// send a reply, to the IP address and port that sent us the packet we received
		
		Udp.beginPacket(IPAddress(192, 168, 3, 119), 6000);
		Udp.write(ReplyBuffer);
		Udp.endPacket();
	}
	int dif = millis() - timer;
	if (dif>=250)
	{
		randNumber = random(300);
		String reply = "Dette er bare masse data for aa se om den kan takle saa mye data. Dette er bare masse data for aa se om den kan takle saa mye data.Dette er bare masse data for aa se om den kan takle saa mye data.Dette er bare masse data for aa se om den kan takle saa mye data.Dette er bare masse data for aa se om den kan takle saa mye data. yyyyyyyyeeeeeeee   Sending random number: " + String(randNumber)+" Dif Time: " + dif;
		reply.toCharArray(ReplyBuffer, 1000);
		// send a reply, to the IP address and port that sent us the packet we received
		Udp.beginPacket(IPAddress(192, 168, 3, 80), 7000);
		Udp.write(ReplyBuffer);
		Udp.endPacket();
		Udp.beginPacket(IPAddress(192, 168, 3, 119), 7000);
		Udp.write(ReplyBuffer);
		Udp.endPacket();
		//Serial.println(reply);
		timer = millis();
	}

	delay(2);
}