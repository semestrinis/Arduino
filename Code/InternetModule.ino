  /*
    Repeating Web client
  
   This sketch connects to a a web server and makes a request
   using a Wiznet Ethernet shield. You can use the Arduino Ethernet shield, or
   the Adafruit Ethernet shield, either one will work, as long as it's got
   a Wiznet Ethernet module on board.
  
   This example uses DNS, by assigning the Ethernet client with a MAC address,
   IP address, and DNS address.
  
   Circuit:
   * Ethernet shield attached to pins 10, 11, 12, 13
  
   created 19 Apr 2012
   by Tom Igoe
   modified 21 Jan 2014
   by Federico Vanzati
  
   http://www.arduino.cc/en/Tutorial/WebClientRepeating
   This code is in the public domain.
  
   */
  
  #include <SPI.h>
  #include <Ethernet.h>
  
  // assign a MAC address for the ethernet controller.
  // fill in your address here:
  byte mac[] = {
    0x70, 0x5D, 0x7B, 0x7E, 0x1A, 0x7C
    //70-4D-7B-3E-8A-7C
  };
  // Set the static IP address to use if the DHCP fails to assign
  IPAddress ip(192, 168, 0, 177);
  IPAddress myDns(192, 168, 1, 1);
  
  // initialize the library instance:
  EthernetClient client;
  
  //char server[] = "http://webhook.site/9c31004d-d6b8-437f-9853-a3190cdfc55c";  // also change the Host line in httpRequest()
  IPAddress server(188,226,137,35);//188.226.137.35:80
  //IPAddress server(192,168,1,102);
  
  unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
  const unsigned long postingInterval = 10*1000;  // delay between updates, in milliseconds
  
  void setup() 
  {
    // You can use Ethernet.init(xpin) to configure the CS pin
    //Ethernet.init(10);  // Most Arduino shields
    //Ethernet.init(5);   // MKR ETH shield
    //Ethernet.init(0);   // Teensy 2.0
    //Ethernet.init(20);  // Teensy++ 2.0
    //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
    //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet
  
    // start serial port:
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
  
    // start the Ethernet connection:
    Serial.println("Initialize Ethernet with DHCP:");
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      // Check for Ethernet hardware present
      if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        while (true) {
          delay(1); // do nothing, no point running without Ethernet hardware
        }
      }
      if (Ethernet.linkStatus() == LinkOFF) {
        Serial.println("Ethernet cable is not connected.");
      }
      // try to congifure using IP address instead of DHCP:
      Ethernet.begin(mac, ip, myDns);
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
    } else {
      Serial.print("  DHCP assigned IP ");
      Serial.println(Ethernet.localIP());
    }
    // give the Ethernet shield a second to initialize:
    delay(1000);
  }
  
  void loop() {
    // if there's incoming data from the net connection.
    // send it out the serial port.  This is for debugging
    // purposes only:
    if (client.available()) 
    {
      char c = client.read();
      Serial.write(c);
    }
  
    // if ten seconds have passed since your last connection,
    // then connect again and send data:
    if (millis() - lastConnectionTime > postingInterval) 
    {
      httpRequest();
    }
  
  }
  
  // this method makes a HTTP connection to the server:
  void httpRequest() 
  {
    // close any connection before send a new request.
    // This will free the socket on the WiFi shield
    client.stop();
  
    // if there's a successful connection:
    if (client.connect(server, 80)) 
    {
      Serial.println("connecting...");
      // send the HTTP GET request:
      //client.println("get http://webhook.site/9c31004d-d6b8-437f-9853-a3190cdfc55c");
      //client.println("application/x-www-form-urlencoded");
      //client.println("Host: webhook.site");
      //client.println("User-Agent: Aplinkos_Oro_Stebejimo_Stotele");
      //client.println("Connection: close");

        //client.print("GET / HTTP/1.1"); 
        //client.print("Host: webhook.site");
        //client.print("User-Agent: test");
        //client.print("Accept: text/html,application/xhtml+xml");
        //client.print("Accept-Language: en-US,en;q=0.5");
        //cl/ient.print("Accept-Encoding: gzip, deflate");
        //client.print("DNT: 1");
        //client.print("Connection: close\n");
        //client.print("Upgrade-Insecure-Requests: 1");
        //client.println();
String PostData="appData={\"itemID\":";
String itemID = "A56654S";
PostData += itemID + ",";

//  unsigned char i;
//  for(i=0;i<6;i++)
//  {
//    PostData=PostData+"\"channel-";
//    PostData=String(PostData+i);
//    PostData=PostData+"\":";
//    PostData=String(PostData + String(analogRead(i)));
//    if(i!=5)
//      PostData=PostData+",";
//  }

int temperature1 = 0;
int temperature2 = 0;
int humidity = 0;
int presure = 0;
int Ligth = 0;

    PostData += "\"Temperature1\":";
    PostData += temperature1;
    PostData += ",\"Humidity\":";
    PostData += humidity;
    PostData += ",\"Presure\":";
    PostData += presure;
    PostData += ",\"Temperature2\":";
    PostData += temperature2;
    PostData += ",\"Ligth\":";
    PostData += Ligth;

    PostData += "}";  
  Serial.println(PostData);



    client.println("POST /9c31004d-d6b8-437f-9853-a3190cdfc55c HTTP/1.1");
    client.println("Host: someRandom.com");
    client.println("User-Agent: AplinkosOroStebejimoStotele_1.0");  
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(PostData.length());
  client.println();
  client.println(PostData);
    //client.println("Data: someRandom data");
    client.println();



                      
      
      //client.println("Host: webhook.site");
      //client.println("User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:66.0) Gecko/20100101 Firefox/66.0");
      //client.println("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
      //client.println("Accept-Language: en-US,en;q=0.5");
      //client.println("Accept-Encoding: gzip, deflate");
      //client.println("DNT: 1");
      //client.println("Connection: close");
      //client.println("Upgrade-Insecure-Requests: 0");
      
      //client.println("Upgrade-Insecure-Requests: 0");
      //client.println("Data: asdasdasdasdasd");
      //  Host: webhook.site
      //User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:66.0) Gecko/20100101 Firefox/66.0
      //Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
      //Accept-Language: en-US,en;q=0.5
      //Accept-Encoding: gzip, deflate
      //DNT: 1
      //Connection: keep-alive
      //Upgrade-Insecure-Requests: 1

      
      // note the time that the connection was made:
      lastConnectionTime = millis();
      Serial.println("Request sent");
    } 
    else 
    {
      // if you couldn't make a connection:
      Serial.println("connection failed");
    }
  }
