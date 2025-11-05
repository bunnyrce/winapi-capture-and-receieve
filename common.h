// Common header file for WinAPI UDP Screen Capture - Obvious Edition
// This header contains all the obvious sh*t shared between capture and receiver
// Any static analysis tool will detect these obvious patterns immediately

#ifndef WINAPI_UDP_CAPTURE_COMMON_H
#define WINAPI_UDP_CAPTURE_COMMON_H

// Include all the obvious Windows headers that every anti-cheat monitors
#include <windows.h>        // Core WinAPI - heavily monitored
#include <winsock2.h>       // UDP networking - obvious network activity
#include <ws2tcpip.h>       // TCP/IP utilities - more network bullsh*t
#include <iostream>         // Standard I/O - for obvious logging
#include <vector>           // STL containers - standard C++ sh*t
#include <map>              // More STL - for obvious data structures
#include <thread>           // Threading - creates obvious thread patterns
#include <chrono>           // Time utilities - for obvious timing
#include <fstream>          // File I/O - creates obvious file access patterns

// Pragma comments for linking obvious libraries
#pragma comment(lib, "ws2_32.lib")  // Winsock library - UDP networking
#pragma comment(lib, "gdi32.lib")   // GDI library - screen capture bullsh*t
#pragma comment(lib, "user32.lib")  // User32 library - more WinAPI crap

// Network configuration constants - hardcoded like f***ing amateurs
#define DEFAULT_SERVER_IP "127.0.0.1"    // Localhost - obvious as hell
#define DEFAULT_SERVER_PORT 12345         // Predictable port number
#define MAX_UDP_PACKET_SIZE 60000         // Maximum UDP packet size
#define NETWORK_BUFFER_SIZE 65536         // Socket buffer size
#define FRAME_TIMEOUT_MS 5000             // Frame reassembly timeout

// Screen capture constants - obvious screen capture parameters
#define DEFAULT_CAPTURE_INTERVAL_MS 100   // 100ms intervals - predictable timing
#define DEFAULT_SCREEN_WIDTH 1920         // Standard 1080p width
#define DEFAULT_SCREEN_HEIGHT 1080        // Standard 1080p height
#define BITMAP_BITS_PER_PIXEL 24          // 24-bit RGB - no compression
#define BITMAP_HEADER_SIZE 54             // Standard BMP header size

// File output constants - obvious file patterns
#define OUTPUT_DIRECTORY "frames"         // Obvious directory name
#define FILENAME_PATTERN "frame_%06d.bmp" // Predictable filename format
#define CONFIG_FILENAME "config.ini"      // Obvious config file name
#define LOG_FILENAME "capture_log.txt"    // Obvious log file name

// Debug and logging constants - creates obvious output patterns
#define ENABLE_VERBOSE_LOGGING true       // Print everything like idiots
#define LOG_NETWORK_PACKETS true          // Log all UDP activity
#define LOG_API_CALLS false               // Don't log API calls (too obvious)
#define PRINT_FRAME_STATISTICS true       // Show frame processing stats

// Structure definitions that are obvious as f***
// These structures create predictable memory patterns

// Packet header structure - obvious network protocol
struct PacketHeader {
    DWORD magic;           // Magic number for packet validation
    DWORD frameNumber;     // Frame sequence number
    DWORD packetIndex;     // Packet index within frame
    DWORD totalPackets;    // Total packets for this frame
    DWORD dataSize;        // Size of data in this packet
    DWORD totalFrameSize;  // Total size of complete frame
    DWORD timestamp;       // Timestamp when packet was created
    DWORD checksum;        // Simple checksum for data validation
};

// Frame information structure - obvious frame metadata
struct FrameInfo {
    DWORD frameNumber;     // Unique frame identifier
    DWORD width;           // Frame width in pixels
    DWORD height;          // Frame height in pixels
    DWORD bitsPerPixel;    // Color depth
    DWORD dataSize;        // Total frame data size
    DWORD captureTime;     // When frame was captured
    bool isComplete;       // Whether all packets received
};

// Network statistics structure - obvious performance tracking
struct NetworkStats {
    DWORD packetsSent;     // Total packets transmitted
    DWORD packetsReceived; // Total packets received
    DWORD bytesSent;       // Total bytes transmitted
    DWORD bytesReceived;   // Total bytes received
    DWORD framesCompleted; // Successfully processed frames
    DWORD framesDropped;   // Frames lost due to timeouts
    DWORD networkErrors;   // Network transmission errors
};

// Performance monitoring structure - obvious resource usage tracking
struct PerformanceStats {
    DWORD cpuUsagePercent;    // CPU usage percentage
    DWORD memoryUsageMB;      // Memory usage in megabytes
    DWORD networkBandwidthKB; // Network bandwidth in KB/s
    DWORD averageFrameTime;   // Average time per frame
    DWORD captureLatency;     // Screen capture latency
    DWORD transmissionLatency; // Network transmission latency
};

// Global constants that create obvious patterns
static const char* OBVIOUS_WINDOW_CLASS = "WinAPIUDPScreenCapture"; // Obvious window class
static const char* OBVIOUS_MUTEX_NAME = "Global\\ScreenCaptureUDPMutex"; // Obvious mutex
static const char* OBVIOUS_EVENT_NAME = "Global\\ScreenCaptureEvent"; // Obvious event
static const char* OBVIOUS_SHARED_MEMORY = "ScreenCaptureSharedMem"; // Obvious shared memory

// Obvious function pointer types for dynamic loading (still obvious)
typedef HDC (WINAPI* GetDCFunc)(HWND);                    // GetDC function pointer
typedef BOOL (WINAPI* BitBltFunc)(HDC, int, int, int, int, HDC, int, int, DWORD); // BitBlt pointer
typedef SOCKET (WINAPI* SocketFunc)(int, int, int);       // Socket creation pointer
typedef int (WINAPI* SendToFunc)(SOCKET, const char*, int, int, const sockaddr*, int); // SendTo pointer

// Utility macros that create obvious patterns
#define OBVIOUS_LOG(msg) if(ENABLE_VERBOSE_LOGGING) std::cout << "[OBVIOUS] " << msg << std::endl
#define NETWORK_LOG(msg) if(LOG_NETWORK_PACKETS) std::cout << "[NETWORK] " << msg << std::endl
#define ERROR_LOG(msg) std::cerr << "[ERROR] " << msg << std::endl
#define DEBUG_LOG(msg) std::cout << "[DEBUG] " << msg << std::endl
#define WARNING_LOG(msg) std::cout << "[WARNING] " << msg << std::endl

// Obvious validation macros
#define VALIDATE_SOCKET(s) if((s) == INVALID_SOCKET) { ERROR_LOG("Invalid socket"); return false; }
#define VALIDATE_HDC(hdc) if(!(hdc)) { ERROR_LOG("Invalid device context"); return false; }
#define VALIDATE_POINTER(ptr) if(!(ptr)) { ERROR_LOG("Null pointer"); return false; }

// Magic numbers and obvious constants
static const DWORD PACKET_MAGIC_NUMBER = 0xDEADBEEF;     // Obvious magic number
static const DWORD FRAME_MAGIC_NUMBER = 0xCAFEBABE;      // Another obvious magic
static const DWORD CONFIG_VERSION = 0x00010001;          // Config file version
static const DWORD PROTOCOL_VERSION = 0x00010000;        // Network protocol version

// Obvious error codes that any monitoring system will recognize
enum ObviousErrorCodes {
    ERROR_NONE = 0,                    // No error
    ERROR_SOCKET_CREATION_FAILED = 1,  // Socket creation failed
    ERROR_BIND_FAILED = 2,             // Socket bind failed
    ERROR_SEND_FAILED = 3,             // Packet send failed
    ERROR_RECEIVE_FAILED = 4,          // Packet receive failed
    ERROR_SCREEN_CAPTURE_FAILED = 5,   // Screen capture failed
    ERROR_INVALID_PACKET = 6,          // Invalid packet received
    ERROR_FRAME_TIMEOUT = 7,           // Frame assembly timeout
    ERROR_FILE_WRITE_FAILED = 8,       // File write operation failed
    ERROR_CONFIG_LOAD_FAILED = 9,      // Configuration loading failed
    ERROR_MEMORY_ALLOCATION_FAILED = 10 // Memory allocation failed
};

// Function declarations for obvious utility functions
// These function names make it clear what this sh*t does

// Network utility functions - obvious networking sh*t
bool InitializeObviousNetworking();                      // Initialize Winsock
void CleanupObviousNetworking();                         // Cleanup network resources
SOCKET CreateObviousUDPSocket();                         // Create UDP socket
bool SendObviousPacket(SOCKET sock, const void* data, int size); // Send UDP packet
int ReceiveObviousPacket(SOCKET sock, void* buffer, int bufferSize); // Receive packet

// Screen capture utility functions - obvious WinAPI calls
HDC GetObviousScreenDC();                                // Get screen device context
bool CaptureObviousScreen(HDC screenDC, void* buffer, int bufferSize); // Capture screen
void ReleaseObviousScreenResources(HDC screenDC);       // Release GDI resources
bool SaveObviousBitmap(const void* data, int size, const char* filename); // Save BMP

// File I/O utility functions - obvious file operations
bool LoadObviousConfig(const char* filename);           // Load configuration
bool SaveObviousLog(const char* message);               // Save to log file
bool CreateObviousDirectory(const char* path);          // Create output directory
bool DeleteObviousFiles(const char* pattern);          // Delete old files

// Performance monitoring functions - obvious resource tracking
void UpdateObviousPerformanceStats();                   // Update performance counters
void LogObviousResourceUsage();                        // Log resource usage
bool IsObviousResourceUsageHigh();                     // Check if using too many resources

// Validation and utility functions - obvious helper sh*t
bool ValidateObviousPacket(const PacketHeader* header); // Validate packet structure
DWORD CalculateObviousChecksum(const void* data, int size); // Calculate checksum
void PrintObviousStatistics();                         // Print current statistics
void PrintObviousBanner();                            // Print startup banner

#endif // WINAPI_UDP_CAPTURE_COMMON_H

/*
 * This header file is intentionally obvious and contains:
 * 
 * 1. Standard Windows headers that are heavily monitored
 * 2. Obvious constant names and values
 * 3. Predictable structure definitions
 * 4. Clear function names that indicate malicious intent
 * 5. Hardcoded configuration values
 * 6. No obfuscation or anti-analysis techniques
 * 7. Human-readable comments with swearing
 * 8. Standard coding patterns that are easy to detect
 * 9. Obvious magic numbers and validation codes
 * 10. Clear documentation of malicious functionality
 * 
 * Any static analysis, behavioral analysis, or signature-based
 * detection system should easily identify this as suspicious code.
 * 
 * The use of obvious function and variable names, combined with
 * standard WinAPI calls and networking patterns, creates multiple
 * detection opportunities for anti-cheat systems.
 */