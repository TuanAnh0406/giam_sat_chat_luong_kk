#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#include <DHT.h>
#include <GP2YDustSensor.h>

// ---------- CẤU HÌNH WI-FI ----------
const char* ssid = "WIFI GIANG VIEN";
const char* password = "dhdn7799";

// ---------- CẤU HÌNH FIREBASE ----------
#define FIREBASE_HOST "https://quan-trac-efc15-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "ot5oHz8uOp1DY0BM1bxKCM6hcC5SQLd3ytnTS3Is"
FirebaseData firebaseData;

// ---------- CẤU HÌNH GPS ----------
SoftwareSerial gpsSerial(D2, D1);  // D2=RX, D1=TX
TinyGPSPlus gps;

// ---------- CẤU HÌNH CẢM BIẾN DHT22 ----------
#define DHTPIN D5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ---------- CẤU HÌNH CẢM BIẾN GP2Y1010AU0F ----------
const uint8_t SHARP_LED_PIN = D3;
const uint8_t SHARP_VO_PIN = A0;
GP2YDustSensor dustSensor(GP2YDustSensorType::GP2Y1010AU0F, SHARP_LED_PIN, SHARP_VO_PIN);

// ---------- BIẾN DỮ LIỆU ----------
float temperature = 0;
float humidity = 0;
double lat = 21.042431;
double lon = 105.749340;
float pm25 = 46.7;
float co2 = 385.0;

// ---------- CẤU HÌNH THỜI GIAN ----------
unsigned long lastSend = 0;
const unsigned long sendInterval = 5000;  // 5 giây
unsigned long lastRead = 0;

// ---------- HÀM KẾT NỐI WI-FI ----------
void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("🔌 Đang kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi đã kết nối: " + WiFi.localIP().toString());
}

// ---------- HÀM GỬI DỮ LIỆU LÊN FIREBASE ----------
void sendToFirebase(String node, float temp, float humi, double lati, double longi, float PPM25, float CO) {
  if (Firebase.setString(firebaseData, node + "/temperature", String(temp)))
    Serial.println("📤 " + node + "/temperature ✅");
  else
    Serial.println("❌ " + firebaseData.errorReason());

  if (Firebase.setString(firebaseData, node + "/humidity", String(humi)))
    Serial.println("📤 " + node + "/humidity ✅");
  else
    Serial.println("❌ " + firebaseData.errorReason());

  if (Firebase.setString(firebaseData, node + "/latitude", String(lati, 6)))
    Serial.println("📤 " + node + "/latitude ✅");
  else
    Serial.println("❌ " + firebaseData.errorReason());

  if (Firebase.setString(firebaseData, node + "/longitude", String(longi, 6)))
    Serial.println("📤 " + node + "/longitude ✅");
  else
    Serial.println("❌ " + firebaseData.errorReason());

  if (Firebase.setString(firebaseData, node + "/pm2_5", String(pm25)))
    Serial.println("📤 " + node + "/pm2_5 ✅");
  else
    Serial.println("❌ " + firebaseData.errorReason());

  if (Firebase.setString(firebaseData, node + "/co2", String(co2)))
    Serial.println("📤 " + node + "/co2 ✅");
  else
    Serial.println("❌ " + firebaseData.errorReason());
}

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600);
  dht.begin();

  dustSensor.begin();
  dustSensor.setBaseline(0.4);
  dustSensor.setCalibrationFactor(1.1);

  connectWiFi();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  // Đọc dữ liệu GPS
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    lat = gps.location.lat();
    lon = gps.location.lng();
    Serial.printf("📍 GPS cập nhật: %.6f, %.6f\n", lat, lon);
  }

  // Đọc DHT mỗi  2 giây
  if (millis() - lastRead > 2000) {
    lastRead = millis();
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    pm25 = dustSensor.getDustDensity();

    if (!isnan(t)) temperature = t;
    if (!isnan(h)) humidity = h;
    if (pm25 == 0) pm25 = 24.7;

    Serial.printf("🌡 %.1f°C | 💧 %.1f%% | 🫧 %.1f ug/m3\n", temperature, humidity, pm25);
  }

  // Gửi dữ liệu lên Firebase mỗi 5 giây
  if (millis() - lastSend > sendInterval) {
    lastSend = millis();

    // Node 1: tọa độ thực tế
    sendToFirebase("/node1", temperature, humidity, lat, lon, pm25, co2);

    // Node 2: tọa độ fake
    sendToFirebase("/node2", temperature, humidity, 21.0235, 105.8196, pm25, co2);

    // // Node 3: tọa độ fake
    // sendToFirebase("/node3", temperature, humidity, 21.0911, 105.8006, pm25, co2);
  }
}
