// Host regression tests for the ESP8266 TLS adapter. No network is used.
#include <cstdint>
#include <cstring>
#include <ctime>
#include <iostream>
#include <stdexcept>

// Only the Arduino/SDK and protocol interfaces are replaced. The adapter and
// BlynkArduinoClientGen below are included from the production headers.
#define ESP8266
#define PROGMEM
#define BlynkApiArduino_h
#define BlynkProtocol_h
#define BlynkDebug_h
#define BLYNK_TIMEOUT_MS 6000UL
#define BLYNK_DEFAULT_DOMAIN "blynk.cloud"
#define BLYNK_DEFAULT_PORT_SSL 443
#define BLYNK_RUN_YIELD() do {} while (0)
#define BLYNK_F(s) s
#define BLYNK_LOG1(...) do {} while (0)
#define BLYNK_LOG2(...) do {} while (0)
#define BLYNK_LOG4(...) do {} while (0)
#define BLYNK_LOG_IP(...) do {} while (0)

static time_t currentTime;
static unsigned int syncCalls;

static void check(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

static time_t testTime(time_t*) { return currentTime; }
static void testConfigTime(long, int, const char* first, const char* second) {
    check(std::strcmp(first, "pool.ntp.org") == 0, "unexpected NTP server");
    check(std::strcmp(second, "time.nist.gov") == 0, "unexpected fallback server");
    ++syncCalls;
}
static void delay(unsigned long) {
    throw std::runtime_error("adapter blocked waiting for NTP time");
}
static void BlynkDelay(unsigned long ms) { delay(ms); }
static tm* testGmtime(const time_t* value, tm* result) {
    *result = *std::gmtime(value);
    return result;
}

struct String {
    String(const char*) {}
    void trim() {}
};
struct IPAddress {};
struct Client {};
struct X509List { explicit X509List(const char*) {} };

struct WiFiClientSecure {
    unsigned int connectCalls = 0;
    bool connectResult = true;
    X509List* trustAnchors = nullptr;
    void setTimeout(unsigned long) {}
    void setBufferSizes(int, int) {}
    void setFingerprint(const char*) {}
    void setTrustAnchors(X509List* certs) { trustAnchors = certs; }
    int connect(const char*, uint16_t) { ++connectCalls; return connectResult; }
    int connect(IPAddress, uint16_t) { ++connectCalls; return connectResult; }
    int getLastSSLError() { return connectResult ? 0 : -1; }
};

enum { WIFI_STA, WL_CONNECTED };
struct WiFiStub {
    void mode(int) {}
    int status() { return WL_CONNECTED; }
    void begin(const char*, const char* = nullptr) {}
    IPAddress localIP() { return IPAddress(); }
} WiFi;

template <typename Transport>
class BlynkProtocol {
public:
    explicit BlynkProtocol(Transport& transport) : conn(transport) {}
    void begin(const char*) {}
protected:
    Transport& conn;
};

#define time testTime
#define configTime testConfigTime
#define gmtime_r testGmtime
#include <BlynkSimpleEsp8266_SSL.h>
#undef gmtime_r
#undef configTime
#undef time

struct Fixture {
    WiFiClientSecure client;
    BlynkArduinoClientSecure<WiFiClientSecure> adapter;
    Fixture() : adapter(client) {
        currentTime = 0;
        syncCalls = 0;
        adapter.begin("test.invalid", 443);
    }
};

static void missingTime() {
    Fixture f;
    check(!f.adapter.connect(), "must stay disconnected without time");
    check(syncCalls == 1, "must start time synchronization");
    check(f.client.connectCalls == 0, "must not attempt TLS without time");
}

static void repeatedRetries() {
    Fixture f;
    for (int i = 0; i < 10; ++i) {
        check(!f.adapter.connect(), "pending synchronization must return false");
    }
    check(syncCalls == 1, "retries must not restart pending synchronization");
    check(f.client.connectCalls == 0, "retries must not attempt TLS without time");
}

static void timeBecomesReady() {
    Fixture f;
    f.adapter.setTrustAnchors(&BlynkCert);
    currentTime = 99999;
    check(!f.adapter.connect(), "time below the existing threshold is invalid");
    currentTime = 100000;
    check(f.adapter.connect(), "must connect once time is ready");
    check(syncCalls == 1, "must not restart synchronization when time is ready");
    check(f.client.connectCalls == 1, "must use the underlying TLS client");
    check(f.client.trustAnchors == &BlynkCert, "must preserve trust anchors");
}

static void timeAlreadyReady() {
    Fixture f;
    currentTime = 1700000000;
    check(f.adapter.connect(), "must connect with an already valid clock");
    check(syncCalls == 0, "must preserve preconfigured time synchronization");
    check(f.client.connectCalls == 1, "must connect through the TLS client");
}

static void tlsFailure() {
    Fixture f;
    currentTime = 1700000000;
    f.client.connectResult = false;
    check(!f.adapter.connect(), "must propagate TLS connection failure");
    check(f.client.connectCalls == 1, "must attempt TLS with a valid clock");
}

static void clockBecomesInvalid() {
    Fixture f;
    currentTime = 1700000000;
    check(f.adapter.connect(), "initial connection must succeed");
    currentTime = 0;
    check(!f.adapter.connect(), "must reject an invalid clock on reconnection");
    check(!f.adapter.connect(), "must keep returning while time is invalid");
    check(syncCalls == 1, "must start synchronization only once");
    check(f.client.connectCalls == 1, "must not reconnect TLS with invalid time");
    currentTime = 1700000001;
    check(f.adapter.connect(), "must recover when time is restored");
}

int main() {
    struct Test { const char* name; void (*run)(); } tests[] = {
        {"missing time", missingTime},
        {"repeated retries", repeatedRetries},
        {"time becomes ready", timeBecomesReady},
        {"time already ready", timeAlreadyReady},
        {"TLS failure", tlsFailure},
        {"clock becomes invalid", clockBecomesInvalid},
    };
    unsigned int failures = 0;
    for (const auto& test : tests) {
        try {
            test.run();
            std::cout << "PASS: " << test.name << '\n';
        } catch (const std::exception& error) {
            ++failures;
            std::cout << "FAIL: " << test.name << ": " << error.what() << '\n';
        }
    }
    std::cout << "6 tests, " << failures << " failures\n";
    return failures ? 1 : 0;
}
