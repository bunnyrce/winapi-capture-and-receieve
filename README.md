# winapi-capture-and-receieve
Native C++ screen capture using obvious WinAPI calls (GetDC, BitBlt) and UDP transmission. Designed to be caught immediately by anti-cheat - uses heavily monitored APIs with zero stealth. Grabs screen every 100ms, sends uncompressed BMP over UDP in predictable patterns. Any decent monitor flags this sh*t instantly. For testing detection only.
