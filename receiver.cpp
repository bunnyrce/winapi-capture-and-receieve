/*
 * WinAPI UDP Screen Capture Receiver - Obvious Detection Edition
 * 
 * This receives the screen capture data sent by the capture.exe and displays it.
 * Just as obvious as the sender because it opens UDP sockets and processes
 * large amounts of image data like a f***ing amateur.
 * 
 * Author: Same dumb*** who made the capture tool
 * Purpose: Receive and process obvious screen capture packets
 * Stealth Level: Also negative infinity
 */

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")  // More UDP socket bullsh*t

// Configuration - same obvious sh*t as the sender
#define LISTEN_PORT 12345           // Same port the sender uses
#define MAX_PACKET_SIZE 65536       // Max UDP packet size
#define FRAME_TIMEOUT_MS 5000       // Timeout for incomplete frames

// Global variables because we don't give a f*** about good practices
SOCKET g_listenSocket = INVALID_SOCKET;
bool g_isReceiving = false;
DWORD g_framesReceived = 0;
DWORD g_totalBytesReceived = 0;
DWORD g_packetsReceived = 0;

// Structure for packet headers (same as sender)
struct PacketHeader {
    DWORD frameNumber;     // Frame sequence number
    DWORD packetIndex;     // Packet index in frame  
    DWORD totalPackets;    // Total packets for this frame
    DWORD dataSize;        // Data size in this packet
    DWORD totalFrameSize;  // Total frame size
};

// Structure to track incomplete frames
struct FrameData {
    std::vector<BYTE> data;
    std::vector<bool> receivedPackets;
    DWORD totalPackets;
    DWORD totalSize;
    std::chrono::steady_clock::time_point lastUpdate;
    
    FrameData() : totalPackets(0), totalSize(0), lastUpdate(std::chrono::steady_clock::now()) {}
};

// Map to store incomplete frames
std::map<DWORD, FrameData> g_incompleteFrames;

/*
 * Initialize UDP socket for receiving screen data
 * This will show up in every network monitor as obvious server activity
 */
bool InitializeUDPListener() {
    // Initialize Winsock - obvious network setup
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed with error: " << result << std::endl;
        return false;
    }
    
    // Create UDP socket - this will trigger network monitoring
    g_listenSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (g_listenSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }
    
    // Set up listener address
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces - obvious
    serverAddr.sin_port = htons(LISTEN_PORT);
    
    // Bind socket - this creates obvious listening activity
    if (bind(g_listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(g_listenSocket);
        WSACleanup();
        return false;
    }
    
    std::cout << "[OBVIOUS] UDP listener initialized on port " << LISTEN_PORT << std::endl;
    std::cout << "[WARNING] This creates obvious network server activity" << std::endl;
    return true;
}

/*
 * Save received frame as BMP file
 * Creates obvious file I/O patterns that anti-cheat can detect
 */
bool SaveFrameAsBMP(const std::vector<BYTE>& frameData, DWORD frameNumber) {
    if (frameData.size() < 54) {  // Minimum BMP file size
        std::cerr << "Frame data too small to be valid BMP" << std::endl;
        return false;
    }
    
    // Create obvious filename pattern
    char filename[256];
    sprintf_s(filename, sizeof(filename), "captured_frame_%06d.bmp", frameNumber);
    
    // Write file - obvious disk activity
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to create output file: " << filename << std::endl;
        return false;
    }
    
    file.write((char*)&frameData[0], frameData.size());
    file.close();
    
    std::cout << "[SAVED] Frame " << frameNumber << " saved as " << filename 
              << " (" << frameData.size() << " bytes)" << std::endl;
    return true;
}

/*
 * Process a complete frame once all packets are received
 * This function handles the obvious image processing
 */
void ProcessCompleteFrame(DWORD frameNumber, const std::vector<BYTE>& frameData) {
    std::cout << "[COMPLETE] Frame " << frameNumber << " assembled (" 
              << frameData.size() << " bytes)" << std::endl;
    
    // Save frame to disk - creates obvious file patterns
    if (SaveFrameAsBMP(frameData, frameNumber)) {
        g_framesReceived++;
        std::cout << "[SUCCESS] Frame " << frameNumber << " processed and saved" << std::endl;
    } else {
        std::cerr << "[ERROR] Failed to save frame " << frameNumber << std::endl;
    }
    
    // Print stats every 10 frames
    if (g_framesReceived % 10 == 0) {
        std::cout << "[STATS] Frames received: " << g_framesReceived 
                  << ", Packets: " << g_packetsReceived
                  << ", Total bytes: " << g_totalBytesReceived << std::endl;
        std::cout << "[REMINDER] This obvious activity is definitely being monitored" << std::endl;
    }
}

/*
 * Clean up timed-out incomplete frames
 * Prevents memory leaks from lost packets
 */
void CleanupTimedOutFrames() {
    auto now = std::chrono::steady_clock::now();
    auto it = g_incompleteFrames.begin();
    
    while (it != g_incompleteFrames.end()) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - it->second.lastUpdate);
        
        if (elapsed.count() > FRAME_TIMEOUT_MS) {
            std::cout << "[TIMEOUT] Frame " << it->first << " timed out, discarding" << std::endl;
            it = g_incompleteFrames.erase(it);
        } else {
            ++it;
        }
    }
}

/*
 * Process incoming packet data
 * This handles the obvious packet reassembly bullsh*t
 */
void ProcessPacket(const std::vector<BYTE>& packetData) {
    if (packetData.size() < sizeof(PacketHeader)) {
        std::cerr << "Packet too small for header" << std::endl;
        return;
    }
    
    // Extract packet header
    PacketHeader header;
    memcpy(&header, &packetData[0], sizeof(PacketHeader));
    
    g_packetsReceived++;
    g_totalBytesReceived += packetData.size();
    
    // Validate packet data
    if (header.dataSize != packetData.size() - sizeof(PacketHeader)) {
        std::cerr << "Packet data size mismatch for frame " << header.frameNumber << std::endl;
        return;
    }
    
    // Check if this is a single-packet frame
    if (header.totalPackets == 1) {
        // Single packet frame - process immediately
        std::vector<BYTE> frameData(header.dataSize);
        memcpy(&frameData[0], &packetData[sizeof(PacketHeader)], header.dataSize);
        ProcessCompleteFrame(header.frameNumber, frameData);
        return;
    }
    
    // Multi-packet frame - need to reassemble
    auto& frameData = g_incompleteFrames[header.frameNumber];
    
    // Initialize frame data if this is the first packet
    if (frameData.totalPackets == 0) {
        frameData.totalPackets = header.totalPackets;
        frameData.totalSize = header.totalFrameSize;
        frameData.data.resize(header.totalFrameSize);
        frameData.receivedPackets.resize(header.totalPackets, false);
        
        std::cout << "[NEW FRAME] Frame " << header.frameNumber 
                  << " expects " << header.totalPackets << " packets" << std::endl;
    }
    
    // Validate packet index
    if (header.packetIndex >= frameData.totalPackets) {
        std::cerr << "Invalid packet index " << header.packetIndex 
                  << " for frame " << header.frameNumber << std::endl;
        return;
    }
    
    // Check if we already have this packet
    if (frameData.receivedPackets[header.packetIndex]) {
        std::cout << "[DUPLICATE] Packet " << header.packetIndex 
                  << " of frame " << header.frameNumber << " already received" << std::endl;
        return;
    }
    
    // Copy packet data to frame buffer
    DWORD offset = header.packetIndex * MAX_PACKET_SIZE;
    if (offset + header.dataSize <= frameData.totalSize) {
        memcpy(&frameData.data[offset], &packetData[sizeof(PacketHeader)], header.dataSize);
        frameData.receivedPackets[header.packetIndex] = true;
        frameData.lastUpdate = std::chrono::steady_clock::now();
        
        std::cout << "[PACKET] Frame " << header.frameNumber 
                  << " packet " << header.packetIndex << "/" << header.totalPackets << std::endl;
    }
    
    // Check if frame is complete
    bool isComplete = true;
    for (bool received : frameData.receivedPackets) {
        if (!received) {
            isComplete = false;
            break;
        }
    }
    
    if (isComplete) {
        // Frame is complete - process it
        ProcessCompleteFrame(header.frameNumber, frameData.data);
        g_incompleteFrames.erase(header.frameNumber);
    }
}

/*
 * Main receiving loop - listens for UDP packets continuously
 * This creates obvious network activity patterns
 */
void ReceiveLoop() {
    std::cout << "[LISTENING] Starting UDP receiver - this is obvious as f***" << std::endl;
    std::cout << "[WARNING] Continuous network monitoring will be visible" << std::endl;
    
    std::vector<BYTE> buffer(MAX_PACKET_SIZE);
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    
    auto lastCleanup = std::chrono::steady_clock::now();
    
    while (g_isReceiving) {
        // Receive packet - obvious network activity
        int bytesReceived = recvfrom(g_listenSocket, (char*)&buffer[0], MAX_PACKET_SIZE, 
                                   0, (sockaddr*)&clientAddr, &clientAddrSize);
        
        if (bytesReceived == SOCKET_ERROR) {
            int error = WSAGetLastError();
            if (error != WSAEWOULDBLOCK) {
                std::cerr << "Receive failed with error: " << error << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        
        if (bytesReceived > 0) {
            // Process received packet
            std::vector<BYTE> packetData(bytesReceived);
            memcpy(&packetData[0], &buffer[0], bytesReceived);
            ProcessPacket(packetData);
        }
        
        // Periodic cleanup of timed-out frames
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastCleanup);
        if (elapsed.count() >= 5) {
            CleanupTimedOutFrames();
            lastCleanup = now;
        }
    }
    
    std::cout << "[STOPPED] Receive loop ended" << std::endl;
}

/*
 * Cleanup function - close sockets and sh*t
 */
void Cleanup() {
    if (g_listenSocket != INVALID_SOCKET) {
        closesocket(g_listenSocket);
        g_listenSocket = INVALID_SOCKET;
    }
    WSACleanup();
    std::cout << "[CLEANUP] Network resources cleaned up" << std::endl;
}

/*
 * Main function - entry point for this receiving bullsh*t
 */
int main() {
    std::cout << "=== WinAPI UDP Screen Capture Receiver - Obvious Edition ===" << std::endl;
    std::cout << "WARNING: This tool creates obvious network server activity" << std::endl;
    std::cout << "Any network monitoring will detect this sh*t immediately" << std::endl;
    std::cout << "============================================================" << std::endl;
    
    // Initialize UDP listener
    if (!InitializeUDPListener()) {
        std::cerr << "Failed to initialize UDP listener - this sh*t is broken" << std::endl;
        return 1;
    }
    
    // Set socket to non-blocking mode for cleaner shutdown
    u_long mode = 1;
    if (ioctlsocket(g_listenSocket, FIONBIO, &mode) != 0) {
        std::cerr << "Failed to set non-blocking mode" << std::endl;
    }
    
    std::cout << "Listening for screen capture data on port " << LISTEN_PORT << "..." << std::endl;
    std::cout << "Press ENTER to stop receiving" << std::endl;
    
    // Start receiving in a separate thread
    g_isReceiving = true;
    std::thread receiveThread(ReceiveLoop);
    
    // Wait for user input to stop
    std::cin.get();
    
    // Stop receiving
    std::cout << "Stopping receiver..." << std::endl;
    g_isReceiving = false;
    
    if (receiveThread.joinable()) {
        receiveThread.join();
    }
    
    std::cout << "=== Final Statistics ===" << std::endl;
    std::cout << "Frames received: " << g_framesReceived << std::endl;
    std::cout << "Packets received: " << g_packetsReceived << std::endl;
    std::cout << "Total bytes received: " << g_totalBytesReceived << std::endl;
    std::cout << "Incomplete frames: " << g_incompleteFrames.size() << std::endl;
    std::cout << "This obvious network activity was definitely monitored" << std::endl;
    
    Cleanup();
    return 0;
}