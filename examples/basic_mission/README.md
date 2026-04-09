# Thingsat :: Basic Mission

This application illustrates a simple mission for the [Thingsat in-orbit gateway](https://gricad-gitlab.univ-grenoble-alpes.fr/thingsat/public/-/tree/master/cubesat_mission_3).

* [ ] LoRaWAN repeater (with devaddr filtering)
* [ ] add App Clock Sync
* [ ] add 5.9 DeviceTime commands (DeviceTimeReq, DeviceTimeAns) introduced in lorawan specification v1.0.3
* [ ] Chirpstack Mesk Relay (Very simple implementation) (SHOULD BE TESTED)
* [ ] Meshtastic Router (Very simple implementation)
* [ ] MeshCore Router (Very simple implementation)
* [ ] Enable Public SyncWord for SF5 and SF6
* [ ] GNSS on UART parsing when a GNSS module is present on Mikrobus or on MiniPCIe module (as into the RAK5146 module) with TinyGPS++
* [ ] Periodic telemetry (with GNSS position and temperature) using LoRaWAN with Cayenne LPP (and XOR redundancy)
* [ ] Periodic telemetry (with GNSS position and temperature) using Meshtastic telemetry and position (protobuf)
* [ ] Periodic telemetry (with GNSS position and temperature) using APRS format (not fake)
* [ ] Print periodcally GNSS data (position, speed, quality, cog ...)
* [ ] Periodic two-way ranging with other Thingsat boards
* [ ] Spectral scan when the SX1262 module is present on Mikrobus and not into the SX1303 module (using RadioLib)
* [ ] CAD when the SX1262 module is present on Mikrobus and not into the SX1303 module (using RadioLib)
* [ ] LoRa 2G4 backhaul when the SX1280 module is present (using RadioLib)
* [ ] LoRa 2G4 backhaul when the LR2021 module is present (using RadioLib)
* [ ] Send [AIS](https://en.wikipedia.org/wiki/Automatic_identification_system) messages over LoRa/LoRaWAN/Meshtastic ([see spec](https://www.itu.int/dms_pubrec/itu-r/rec/m/R-REC-M.1371-5-201402-I!!PDF-F.pdf))
* [ ] Receive and decode [AIS](https://en.wikipedia.org/wiki/Automatic_identification_system) messages over LoRa/LoRaWAN/Meshtastic ([see spec](https://www.itu.int/dms_pubrec/itu-r/rec/m/R-REC-M.1371-5-201402-I!!PDF-F.pdf))


## Tested boards

* [x] [Thingsat INISAT](https://github.com/csu-grenoble/flatsat/tree/main/Hardware/Thingsat_INISAT) with Nucleo32 L432KC and RAK5134
* [x] [Thingsat ProtoSEED](https://gricad-gitlab.univ-grenoble-alpes.fr/thingsat/seed/-/tree/main/seed_thingsat_protoseed?ref_type=heads) with Nucleo32 L432KC and RAK5134
* [ ] [Thingsat ProtoSEED](https://gricad-gitlab.univ-grenoble-alpes.fr/thingsat/seed/-/tree/main/seed_thingsat_protoseed?ref_type=heads) with Arduino Nano ESP32 and RAK5134

[Other supported SX1302/SX1303 modules](https://github.com/thingsat/sx1302_modules)


