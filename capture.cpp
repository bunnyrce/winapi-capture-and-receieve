/*
 * WinAPI UDP Screen Capture - Obvious as F*** Edition
 * 
 * This is the main capture executable that grabs screen data and sends it over UDP.
 * Any anti-cheat worth a damn will catch this sh*t immediately because it uses
 * the most obvious WinAPI calls possible.
 * 
 * Author: Some dumb*** who wanted to test anti-cheat detection
 * Purpose: Get flagged by every detection system on Earth
 * Stealth Level: Negative infinity
 */

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#pragma comment(lib, "ws2_32.lib")  // UDP socket bullsh*t
#pragma comment(lib, "gdi32.lib")   // Screen capture garbage
#pragma comment(lib, "user32.lib")  // More obvious WinAPI crap

// Configuration constants - hardcoded like a f***ing amateur
#define SERVER_IP "127.0.0.1"      // Localhost because we're obvious
#define SERVER_PORT 12345          // Random port that'll get detected
#define CAPTURE_INTERVAL 100       // 100ms intervals - predictable as hell
#define MAX_PACKET_SIZE 60000      // UDP packet size limit
#define BITMAP_HEADER_SIZE 54      // BMP header size because we're lazy

// Global variables because screw good programming practices
SOCKET g_udpSocket = INVALID_SOCKET;
sockaddr_in g_serverAddr;
bool g_isCapturing = false;
int g_screenWidth = 0;
int g_screenHeight = 0;
DWORD g_framesSent = 0;
DWORD g_totalBytesSent = 0;

/*
 * Initialize the UDP socket for sending screen data
 * This function is obvious as f*** and will trigger every network monitor
 */
bool InitializeUDPSocket() {
    // Initialize Winsock - obvious network activity
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed with error: " << result << std::endl;
        return false;
    }
    
    // Create UDP socket - this will show up in every process monitor
    g_udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (g_udpSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }
    
    // Set up server address - hardcoded like a dumb***
    memset(&g_serverAddr, 0, sizeof(g_serverAddr));
    g_serverAddr.sin_family = AF_INET;
    g_serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &g_serverAddr.sin_addr);
    
    std::cout << "[OBVIOUS] UDP socket initialized - any network monitor will see this sh*t" << std::endl;
    return true;
}

/*
 * Get screen dimensions using obvious WinAPI calls
 * This function screams "I'M CAPTURING THE SCREEN!"
 */
void GetScreenDimensions() {
    // Get screen dimensions - super f***ing obvious
    g_screenWidth = GetSystemMetrics(SM_CXSCREEN);   // RED FLAG
    g_screenHeight = GetSystemMetrics(SM_CYSCREEN);  // ANOTHER RED FLAG
    
    std::cout << "[DETECTED] Screen dimensions: " << g_screenWidth << "x" << g_screenHeight << std::endl;
    std::cout << "[WARNING] GetSystemMetrics() calls are monitored by anti-cheat" << std::endl;
}

/*
 * Capture screen using the most obvious WinAPI method possible
 * This function will trigger every API monitor in existence
 */
std::vector<BYTE> CaptureScreen() {
    // Get desktop device context - obvious as hell
    HDC screenDC = GetDC(NULL);  // MAJOR RED FLAG - monitored by everything
    if (!screenDC) {
        std::cerr << "Failed to get screen DC - this sh*t is broken" << std::endl;
        return std::vector<BYTE>();
    }
    
    // Create compatible DC - another obvious call
    HDC memoryDC = CreateCompatibleDC(screenDC);  // DETECTED BY ALL ANTI-CHEAT
    if (!memoryDC) {
        std::cerr << "Failed to create compatible DC" << std::endl;
        ReleaseDC(NULL, screenDC);
        return std::vector<BYTE>();
    }
    
    // Create bitmap - more obvious bullsh*t
    HBITMAP bitmap = CreateCompatibleBitmap(screenDC, g_screenWidth, g_screenHeight);
    if (!bitmap) {
        std::cerr << "Failed to create bitmap" << std::endl;
        DeleteDC(memoryDC);
        ReleaseDC(NULL, screenDC);
        return std::vector<BYTE>();
    }
    
    // Select bitmap into memory DC
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memoryDC, bitmap);
    
    // Copy screen to bitmap - THE MOST OBVIOUS CALL EVER
    if (!BitBlt(memoryDC, 0, 0, g_screenWidth, g_screenHeight, screenDC, 0, 0, SRCCOPY)) {
        std::cerr << "BitBlt failed - screen capture sh*t broke" << std::endl;
        SelectObject(memoryDC, oldBitmap);
        DeleteObject(bitmap);
        DeleteDC(memoryDC);
        ReleaseDC(NULL, screenDC);
        return std::vector<BYTE>();
    }
    
    // Get bitmap data - more obvious API calls
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = g_screenWidth;
    bi.biHeight = -g_screenHeight;  // Negative for top-down bitmap
    bi.biPlanes = 1;
    bi.biBitCount = 24;  // 24-bit RGB because we're predictable
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;
    
    // Calculate image size
    int imageSize = ((g_screenWidth * 3 + 3) & ~3) * g_screenHeight;
    std::vector<BYTE> imageData(BITMAP_HEADER_SIZE + imageSize);
    
    // Create BMP header - because we're too lazy for compression
    BITMAPFILEHEADER bf;
    bf.bfType = 0x4D42;  // "BM"
    bf.bfSize = BITMAP_HEADER_SIZE + imageSize;
    bf.bfReserved1 = 0;
    bf.bfReserved2 = 0;
    bf.bfOffBits = BITMAP_HEADER_SIZE;
    
    // Copy headers to buffer
    memcpy(&imageData[0], &bf, sizeof(BITMAPFILEHEADER));
    memcpy(&imageData[sizeof(BITMAPFILEHEADER)], &bi, sizeof(BITMAPINFOHEADER));
    
    // Get bitmap bits - final obvious API call
    if (!GetDIBits(screenDC, bitmap, 0, g_screenHeight, &imageData[BITMAP_HEADER_SIZE], (BITMAPINFO*)&bi, DIB_RGB_COLORS)) {
        std::cerr << "GetDIBits failed - this capture sh*t is f***ed" << std::endl;
        imageData.clear();
    }
    
    // Clean up resources like we should have done from the start
    SelectObject(memoryDC, oldBitmap);
    DeleteObject(bitmap);
    DeleteDC(memoryDC);
    ReleaseDC(NULL, screenDC);
    
    return imageData;
}

/*
 * Send image data over UDP in chunks
 * This function will flood the network with obvious packets
 */
bool SendImageData(const std::vector<BYTE>& imageData) {
    if (imageData.empty()) {
        std::cerr << "No image data to send, you dumb***" << std::endl;
        return false;
    }
    
    // Calculate number of packets needed
    int totalSize = (int)imageData.size();
    int packetsNeeded = (totalSize + MAX_PACKET_SIZE - 1) / MAX_PACKET_SIZE;
    
    std::cout << "[SENDING] Image size: " << totalSize << " bytes in " << packetsNeeded << " packets" << std::endl;
    
    // Send packets with obvious headers
    for (int i = 0; i < packetsNeeded; i++) {
        // Create packet with obvious structure
        struct PacketHeader {
            DWORD frameNumber;     // Frame sequence number
            DWORD packetIndex;     // Packet index in frame
            DWORD totalPackets;    // Total packets for this frame
            DWORD dataSize;        // Data size in this packet
            DWORD totalFrameSize;  // Total frame size
        };
        
        PacketHeader header;
        header.frameNumber = g_framesSent;
        header.packetIndex = i;
        header.totalPackets = packetsNeeded;
        header.totalFrameSize = totalSize;
        
        // Calculate data size for this packet
        int offset = i * MAX_PACKET_SIZE;
        int remainingBytes = totalSize - offset;
        int packetDataSize = (remainingBytes > MAX_PACKET_SIZE) ? MAX_PACKET_SIZE : remainingBytes;
        header.dataSize = packetDataSize;
        
        // Create packet buffer
        std::vector<BYTE> packet(sizeof(PacketHeader) + packetDataSize);
        memcpy(&packet[0], &header, sizeof(PacketHeader));
        memcpy(&packet[sizeof(PacketHeader)], &imageData[offset], packetDataSize);
        
        // Send packet - obvious network activity
        int result = sendto(g_udpSocket, (char*)&packet[0], (int)packet.size(), 0, 
                           (sockaddr*)&g_serverAddr, sizeof(g_serverAddr));
        
        if (result == SOCKET_ERROR) {
            std::cerr << "Packet " << i << " failed to send: " << WSAGetLastError() << std::endl;
            return false;
        }
        
        g_totalBytesSent += packet.size();
        
        // Small delay to avoid flooding - still obvious as f***
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
    g_framesSent++;
    std::cout << "[OBVIOUS] Frame " << g_framesSent << " sent (" << totalSize << " bytes)" << std::endl;
    return true;
}

/*
 * Main capture loop - runs continuously and obviously
 * This will peg CPU usage and network activity
 */
void CaptureLoop() {
    std::cout << "[STARTING] Screen capture loop - anti-cheat should detect this now" << std::endl;
    std::cout << "[WARNING] High CPU and network usage incoming" << std::endl;
    
    auto lastCapture = std::chrono::high_resolution_clock::now();
    
    while (g_isCapturing) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCapture);
        
        // Capture at fixed intervals - predictable as hell
        if (elapsed.count() >= CAPTURE_INTERVAL) {
            // Capture screen with obvious API calls
            std::vector<BYTE> imageData = CaptureScreen();
            if (!imageData.empty()) {
                // Send over UDP - obvious network patterns
                if (!SendImageData(imageData)) {
                    std::cerr << "Failed to send frame " << g_framesSent << std::endl;
                }
            }
            
            lastCapture = now;
            
            // Print obvious status every 50 frames
            if (g_framesSent % 50 == 0) {
                std::cout << "[STATUS] Frames sent: " << g_framesSent 
                         << ", Total bytes: " << g_totalBytesSent << std::endl;
                std::cout << "[REMINDER] This is obvious as f*** and will be detected" << std::endl;
            }
        }
        
        // Small sleep to prevent 100% CPU usage (still obvious though)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    std::cout << "[STOPPED] Capture loop ended" << std::endl;
}

/*
 * Cleanup function - close sockets and sh*t
 */
void Cleanup() {
    if (g_udpSocket != INVALID_SOCKET) {
        closesocket(g_udpSocket);
        g_udpSocket = INVALID_SOCKET;
    }
    WSACleanup();
    std::cout << "[CLEANUP] Resources cleaned up" << std::endl;
}

/*
 * Main function - entry point for this obvious bullsh*t
 */
int main() {
    std::cout << "=== WinAPI UDP Screen Capture - Obvious Edition ===" << std::endl;
    std::cout << "WARNING: This tool is designed to be detected by anti-cheat" << std::endl;
    std::cout << "Don't use this sh*t for actual cheating, you'll get banned" << std::endl;
    std::cout << "=================================================" << std::endl;
    
    // Initialize UDP socket
    if (!InitializeUDPSocket()) {
        std::cerr << "Failed to initialize UDP socket - this sh*t is broken" << std::endl;
        return 1;
    }
    
    // Get screen dimensions
    GetScreenDimensions();
    if (g_screenWidth == 0 || g_screenHeight == 0) {
        std::cerr << "Invalid screen dimensions - something's f***ed" << std::endl;
        Cleanup();
        return 1;
    }
    
    std::cout << "Press ENTER to start capturing (Ctrl+C to stop)..." << std::endl;
    std::cin.get();
    
    // Start capture loop
    g_isCapturing = true;
    std::thread captureThread(CaptureLoop);
    
    std::cout << "Capturing... Press ENTER to stop" << std::endl;
    std::cin.get();
    
    // Stop capturing
    g_isCapturing = false;
    if (captureThread.joinable()) {
        captureThread.join();
    }
    
    std::cout << "=== Final Statistics ===" << std::endl;
    std::cout << "Frames captured: " << g_framesSent << std::endl;
    std::cout << "Total bytes sent: " << g_totalBytesSent << std::endl;
    std::cout << "Average bytes per frame: " << (g_framesSent > 0 ? g_totalBytesSent / g_framesSent : 0) << std::endl;
    std::cout << "This was obvious as f*** and definitely got detected" << std::endl;
    
    Cleanup();
    return 0;
}