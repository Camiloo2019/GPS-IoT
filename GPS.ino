#include <TinyGPS++.h> // Library for GPS module
#include <SoftwareSerial.h> //  Allows you to use a regular Arduino serial port as a second serial port
#include <WiFi.h>  //  Allows you to connect your Arduino to a WiFi network
TinyGPSPlus gps;  // The TinyGPS++ object (For GPS neo 6m)
SoftwareSerial ss(21, 22); // The serial connection to the GPS device

const char *ssid =  "*name";     // Enter your WiFi Name
const char *pass =  "*password"; // Enter your WiFi Password
float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;                         // Variables
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass); //Connecting to wifi
  while (WiFi.status() != WL_CONNECTED)// While wifi not connected
  {
    delay(500);
    Serial.print("."); //print "...."
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());  // Print the IP address
}


void loop()
{
  while (ss.available() > 0) //While data is available
    if (gps.encode(ss.read())) //Read gps data (In this case we used GPS neo 6m)
    {
      if (gps.location.isValid()) //Check whether gps location is valid
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6); // Latitude location is stored in a string
        longitude = gps.location.lng();
        lng_str = String(longitude , 6); //Longitude location is stored in a string
      }
      if (gps.date.isValid()) //Check whether gps date is valid
      {
        date_str = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();
        if (date < 10)
          date_str = '0';
        date_str += String(date);// Values of date,month and year are stored in a string
        date_str += " / ";

        if (month < 10)
          date_str += '0';
        date_str += String(month); // Values of date,month and year are stored in a string
        date_str += " / ";
        if (year < 10)
          date_str += '0';
        date_str += String(year); // Values of date,month and year are stored in a string
      }
      if (gps.time.isValid())  //Check whether gps time is valid
      {
        time_str = "";
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();
        minute = (minute + 30); // Converting to IST
        if (minute > 59)
        {
          minute = minute - 60;
          hour = hour + 1;
        }
        hour = (hour + 5) ;
        if (hour > 23)
          hour = hour - 24;   // Converting to IST
        if (hour >= 12)  // Checking whether AM or PM
          pm = 1;
        else
          pm = 0;
        hour = hour % 12;
        if (hour < 10)
          time_str = '0';
        time_str += String(hour); //Values of hour,minute and time are stored in a string
        time_str += " : ";
        if (minute < 10)
          time_str += '0';
        time_str += String(minute); //Values of hour,minute and time are stored in a string
        time_str += " : ";
        if (second < 10)
          time_str += '0';
        time_str += String(second); //Values of hour,minute and time are stored in a string
        if (pm == 1)
          time_str += " PM ";
        else
          time_str += " AM ";
      }
    }
 
 WiFiClient client = server.available(); // Check if a client has connected
  if (!client)
  {
    return;
  }
  // Prepare the response with a little interface 
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html> <html> <head> <title>GPS DATA</title> <style>";
  s += "a:link {background-color: YELLOW;text-decoration: none;}";
  s += "table, th, td </style> </head> <body> <h1  style=";
  s += "font-size:300%;";
  s += " ALIGN=CENTER> GPS DATA</h1>";
  s += "<p ALIGN=CENTER style=""font-size:150%;""";
  s += "> <b>Location Details</b></p> <table ALIGN=CENTER style=";
  s += "width:50%";
  s += "> <tr> <th>Latitude</th>";
  s += "<td ALIGN=CENTER >";
  s += lat_str;
  s += "</td> </tr> <tr> <th>Longitude</th> <td ALIGN=CENTER >";
  s += lng_str;
  s += "</td> </tr> <tr>  <th>Date</th> <td ALIGN=CENTER >";
  s += date_str;
  s += "</td></tr> <tr> <th>Time</th> <td ALIGN=CENTER >";
  s += time_str;
  s += "</td>  </tr> </table> ";
 
  s += "</body> </html>";

  client.print(s); // All the values are send to the webpage
  delay(100);
}