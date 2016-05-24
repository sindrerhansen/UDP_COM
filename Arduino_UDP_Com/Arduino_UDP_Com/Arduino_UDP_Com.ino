


#include <UIPEthernet.h>
// The connection_data struct needs to be defined in an external file.
#include <UIPServer.h>
#include <UIPClient.h>


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 88, 159);

unsigned int localPort = 8888;      // local port to listen on
unsigned long timer;

// buffers for receiving and sending data
char packetBuffer[100]; //buffer to hold incoming packet,
char ReplyBuffer[100];
// a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
	// start the Ethernet and UDP:
	Ethernet.begin(mac, ip);
	Udp.begin(localPort);
	timer = millis();
	Serial.begin(9600);
}

void loop()
{
	// if there's data available, read a packet
	int packetSize = Udp.parsePacket();
	if (packetSize)
	{
		//Serial.print("Received packet of size ");
		//Serial.println(packetSize);
		//Serial.print("From ");
		//IPAddress remote = Udp.remoteIP();
		//for (int i =0; i < 4; i++)
		//{
		//Serial.print(remote[i], DEC);
		//if (i < 3)
		//{
		//Serial.print(".");
		//}
		//}
		//Serial.print(", port ");

		//Serial.println(Udp.remotePort());

		// read the packet into packetBufffer

		Udp.read(packetBuffer, 100);
		//Serial.println("Contents:");

		Serial.println(packetBuffer);
		String reply = "acknowledged at: " + String(millis());
		reply.toCharArray(ReplyBuffer, 100);
		// send a reply, to the IP address and port that sent us the packet we received
		Udp.beginPacket(IPAddress(192, 168, 88, 126), 6000);
		Udp.write(ReplyBuffer);
		Udp.endPacket();
	}

	if ((millis() - timer)>500)
	{
		String reply = "Sending data " + String(millis());
		reply.toCharArray(ReplyBuffer, 100);
		// send a reply, to the IP address and port that sent us the packet we received
		Udp.beginPacket(IPAddress(192, 168, 88, 126), 6000);
		Udp.write(ReplyBuffer);
		Udp.endPacket();
		timer = millis();
	}

	delay(10);
}