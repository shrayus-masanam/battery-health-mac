# battery-health-mac
A simple CLI program to view the battery health of an Intel-based macOS device. 

Battery health is a measure of a battery's maximum capacity relative to when it was new. On Macs with an Apple Silicon CPU, this percentage can be viewed in System Preferences. On an Intel-based Mac, the percentage is not in System Preferences (on Monterey, at least), but an alternative way to find it would be through I/O Registry. This program calculates battery health by dividng the current amount of maximum charge cycles by the maximum amount of charge cycles when the battery was new.

```
Usage:
batteryhealth [-p | -m | -d | -h]

-p: prints the battery health as a precise percentage
-m: prints the current maximum capacity of the battery (in charge cycles)
-d: prints the original maximum capacity of the battery (in charge cycles)
-h: prints this help message

Supplying no arguments will return the battery health as a truncated percentage.
```
Tested on macOS 12.6.3

## Compiling
```bash
g++ -std=c++17 -o batteryhealth batteryhealth.cpp
```
