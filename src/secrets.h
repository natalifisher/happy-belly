#include <pgmspace.h>

#define SECRET
#define THINGNAME "ESP32_CS147"

// const char WIFI_SSID[] = "LeWifi";
// const char WIFI_PASSWORD[] = "Hamster1!";
const char WIFI_SSID[] = "UCInet Mobile Access";
const char WIFI_PASSWORD[] = "";
const char AWS_IOT_ENDPOINT[] = "a3q4wtgayp0zr4-ats.iot.us-east-2.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUGlsXRcBSXSJ8K0XR0dB/fFYpszYwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIzMDUyMjA1MzEx
N1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAN5FaoVqbIzfFvdr6o67
j/jTaDenBmo9+KHX/dlGMVoMX8F1l5RxPbvxO8e+dPvA6rsNjCr16H5qCGxgvyeI
7mbyFd/Dt+VI6xTA+CABvOeOfbZeZzwE2FTrdnePDrrOjOUp28ycOpTJqRORUJzA
9gs5v8swLCXVkZWJj4eZ77l6IuVTBkyGgxkbf8wLVmceb9PJGnZB9oRTnRnRZoaQ
maRe5JctMp7s62yW5GiXDK68S3BiJ+mBmIyxInB6bQrm9HoLwAnqOdALV9UAunTA
qSH09xPj4eA0cwLhxSxQ3Ppm/EDTsjEhZeBRMFO9CPIuDL1AUH11n3n7jXOAngrQ
ywMCAwEAAaNgMF4wHwYDVR0jBBgwFoAUpYqOAcI0yvcKW9/noYzaZBjS1tEwHQYD
VR0OBBYEFL3JxRf1G53kTYMTUzc9bBPdAOSrMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQC+MO80nYvrPewoPnDGZO4MeRwK
9UADPiy1wplnZ3K6AssKj26OkVXLmp9yzRdR1W/n2F1smEMadRVEt6kBRi7mgKgw
7BrEJblLJpWVyWBNax1oz+jOmAXYU5bTRZPGkCXEbjHqnZgqa1yEgKbqcRldDNBO
wfQTWZUc/fgC2UmXjzj/UNZHE9jbpVsDNXk6smycHqF9KOCRsBCWWXvZUFYwbTiK
Hv0Mx8sjwxcQTX+iD7GDpugw6FuDdRYscHg10HOhzOxaHNcLjiQPm2sUQUR4SaTC
dBCef7KS57iwaYzi/Pq98j97bkCGrumdTmpgriGiurKpuI80hMVJK4AhhInz
-----END CERTIFICATE-----
 
 
)KEY";

// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA3kVqhWpsjN8W92vqjruP+NNoN6cGaj34odf92UYxWgxfwXWX
lHE9u/E7x750+8Dquw2MKvXofmoIbGC/J4juZvIV38O35UjrFMD4IAG85459tl5n
PATYVOt2d48Ous6M5SnbzJw6lMmpE5FQnMD2Czm/yzAsJdWRlYmPh5nvuXoi5VMG
TIaDGRt/zAtWZx5v08kadkH2hFOdGdFmhpCZpF7kly0ynuzrbJbkaJcMrrxLcGIn
6YGYjLEicHptCub0egvACeo50AtX1QC6dMCpIfT3E+Ph4DRzAuHFLFDc+mb8QNOy
MSFl4FEwU70I8i4MvUBQfXWfefuNc4CeCtDLAwIDAQABAoIBAQDLzsDO1vfz7/fC
JYztFeT81vR/20JRlsNtu3zDhs5n8GK5JJc6AOAHfjo/fE8OLSXPIKv/FH77s0RI
BCojGTbo5F/UT0VHE6ai4BJkXtOVS53P5B4q9ZJbw5BcLqvl9NFSrCAkLLi2h3bm
P1+4bGLvhiNsL567jmowwPL/9tHOsg3f4hZvkOWouHwWLXA7NYNq2EXk/DnwhW6e
GnTqau7hhNA01U7bBrwv8qz7Hr4H+4B1aa7z4Je04NNYKS4pc4IiJVuKevF87bn1
S0GOh8cOJIVLy1ysRT95i87nE8+BbFLrHZ+SreuzU0b4npMWucf6XOYte/mMaR8e
YcoevwNxAoGBAP+SS8vrpaMt49wT1mzUyBB1PK63O9IWitS2YgUBX3UQBpdiKZHw
VFjYkQX5pVtCsCrHtQvonxm2jYfByPxpRxkctlxFnK4A7ce5fKvwIFVQHLRBLnke
Ir0H9Z1SO9ysxGQzNWe+p+yvd6z27yKgZiExAWTz1ZFJKTSiH5S4+IdbAoGBAN6k
02yfg0ErTzPoODmYG0qTDhxxqjxrGDlNqnSFTJJ5cryIVr0S7BcX1YnsUJBkBOaP
fXewvxIO2d2nqFOJY+2XMibcgsNSjfgtLnFel0w/+k0jvaImtqlfCpITuebI1BCK
/4p2O+nzC3T0lomCKKVnwBZPrvYU1Ie0zY0FhEN5AoGADdr/kvmejD8zqD3HFTVf
90xz0sEKVDR2qFuO6tiNNUp+IPzoZgoSeJKdIibLqSvvYxJapV+iKIG2IJMH8289
tIXS+SOo/+H7AiXzNVsaVaW3OKqD+3r/xSHGVhYcOrV/HDOOhKZYckN9CHqGsmjh
wJDok3GItYyy2DCl56kziBsCgYBUCYDoMjlXwuItZIy8aIZ8mo8r+1dXYNEO6Brb
ymjBrOe68/dRfK/yc4OdgL5UEfyrjiO8ptEoHsTrXlox1d0LFBPRCVCuKx39PAiY
sCyJkmiG72OnrdcqjP4vbxSvYMRyzhRwjfpFbwC3D482rhNrg4LEqSUQK4KhCoS/
owJueQKBgDJ09lAB4r0kZaXAffCsol2/sFAaV185QiKjb0mzo/r+PKgTnmFBux8F
VkmzxHddoYZxYODQ4IhByQupi61CpBdoLHufuxQOxV+k8gOv66vKec/jL2vT8tIT
haw9D2dEGwy/GMoXmlaNy5bEE17k2wm6DSbDu8GN0V3ia/tdZ18s
-----END RSA PRIVATE KEY-----
 
 
)KEY";