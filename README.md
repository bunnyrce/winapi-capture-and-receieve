# WinAPI UDP Screen Capture - Obvious as F***

Native C++ screen capture using obvious WinAPI calls (GetDC, BitBlt) and UDP transmission. Designed to be caught immediately by anti-cheat - uses heavily monitored APIs with zero stealth. Grabs screen every 100ms, sends uncompressed BMP over UDP in predictable patterns. Any decent monitor flags this sh*t instantly. For testing detection only.

## What This Piece of Sh*t Does

- **Screen Capture**: Uses obvious WinAPI calls like `BitBlt()` and `GetDC()` 
- **UDP Transmission**: Sends captured frames over UDP like a dumb***
- **No Stealth**: Completely obvious detection patterns for testing anti-cheat systems
- **Human Language**: Comments that sound like actual people wrote them, not f***ing robots

## Files in This Mess

- `capture.cpp` - Main screen capture executable (obvious as hell)
- `receiver.cpp` - UDP receiver for captured frames
- `build.bat` - Batch script to compile this garbage
- `config.ini` - Configuration file with obvious settings
- `README.md` - This file explaining the obvious sh*t

## How to Use This Crap

1. **Compile the bullsh*t:**
   ```cmd
   build.bat
   ```

2. **Run the receiver first:**
   ```cmd
   receiver.exe
   ```

3. **Start the capture:**
   ```cmd
   capture.exe
   ```

4. **Watch your anti-cheat go nuts** - this thing is designed to be caught

## Why This Exists

This isn't meant to be a real cheat, you dumb***. It's for **testing anti-cheat detection** by using obviously detectable patterns:

- **Obvious WinAPI calls** that every anti-cheat monitors
- **High-frequency UDP packets** that scream "I'M SENDING SCREEN DATA!"
- **No obfuscation** - function names that literally say what they do
- **Predictable behavior** - consistent timing and packet sizes
- **Resource usage spikes** from continuous screen capture

## Detection Signatures

Anti-cheat systems should easily catch:
- `GetDC()` and `BitBlt()` API calls
- `CreateCompatibleDC()` usage patterns  
- UDP socket creation and high-frequency sending
- Consistent memory allocation patterns
- Screen resolution queries
- High CPU usage from image processing

## Requirements

- Windows 10/11 (duh, it's WinAPI)
- Visual Studio Build Tools or full VS
- Admin privileges (because this sh*t needs low-level access)
- A sense of humor about how obvious this is

## Limitations

- **Zero stealth** - designed to be caught
- **No encryption** - raw bitmap data over UDP
- **No compression** - maximum obviousness
- **Fixed timing** - predictable capture intervals
- **Hardcoded everything** - no dynamic behavior

## Legal Disclaimer

This is for **educational and testing purposes only**. Don't use this sh*t to actually cheat in games, you'll get caught faster than a speeding ticket. We're not responsible if you're dumb enough to use obviously detectable test code in real scenarios.

## Technical Details

### Capture Method
```cpp
// This obvious sh*t captures the screen
HDC screenDC = GetDC(NULL);  // RED FLAG #1
HDC memoryDC = CreateCompatibleDC(screenDC);  // RED FLAG #2
HBITMAP bitmap = CreateCompatibleBitmap(screenDC, width, height);  // RED FLAG #3
BitBlt(memoryDC, 0, 0, width, height, screenDC, 0, 0, SRCCOPY);  // RED FLAG #4
```

### UDP Transmission
```cpp
// Sending data like a f***ing amateur
SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  // OBVIOUS
sendto(udpSocket, imageData, dataSize, 0, ...);  // DETECTED
```

## Building

Make sure you have the Windows SDK and run:
```cmd
cl /EHsc capture.cpp ws2_32.lib gdi32.lib user32.lib
cl /EHsc receiver.cpp ws2_32.lib
```

Or just use the provided `build.bat` script if you're lazy.

---

**Remember**: This is intentionally sh*tty and detectable. Don't blame us when every anti-cheat on Earth flags this garbage.