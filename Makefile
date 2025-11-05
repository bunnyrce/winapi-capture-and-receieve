# Makefile for WinAPI UDP Screen Capture - Obvious Edition
# This makefile compiles the obvious capture tools using MinGW or Visual Studio
# Any build system monitoring will detect this sh*t immediately

# Compiler settings - obvious configuration
CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra
LDFLAGS = -lws2_32 -lgdi32 -luser32

# Visual Studio compiler settings (alternative)
MSVC = cl
MSVCFLAGS = /EHsc /O2
MSVCLIBS = ws2_32.lib gdi32.lib user32.lib

# Directories - obvious structure
SRCDIR = .
BINDIR = bin
OBJDIR = obj

# Source files - obvious naming
CAPTURE_SRC = capture.cpp
RECEIVER_SRC = receiver.cpp

# Output executables - obvious names that scream what they do
CAPTURE_EXE = $(BINDIR)/capture.exe
RECEIVER_EXE = $(BINDIR)/receiver.exe

# Object files for dependency tracking
CAPTURE_OBJ = $(OBJDIR)/capture.o
RECEIVER_OBJ = $(OBJDIR)/receiver.o

# Default target - build both obvious executables
all: directories $(CAPTURE_EXE) $(RECEIVER_EXE)
	@echo "=============================================="
	@echo "BUILD COMPLETE - Obvious executables ready"
	@echo "capture.exe: Screen capture (obvious as f***)"
	@echo "receiver.exe: UDP server (network bullsh*t)"
	@echo "=============================================="

# Create directories for the compiled sh*t
directories:
	@if not exist "$(BINDIR)" mkdir "$(BINDIR)"
	@if not exist "$(OBJDIR)" mkdir "$(OBJDIR)"

# Build capture.exe - the obvious screen capture tool
$(CAPTURE_EXE): $(CAPTURE_OBJ)
	@echo "Linking capture.exe - obvious screen capture executable"
	$(CXX) $(CAPTURE_OBJ) -o $@ $(LDFLAGS)
	@echo "capture.exe built - ready to be detected by anti-cheat"

# Build receiver.exe - the obvious UDP server
$(RECEIVER_EXE): $(RECEIVER_OBJ)
	@echo "Linking receiver.exe - obvious network server"
	$(CXX) $(RECEIVER_OBJ) -o $@ -lws2_32
	@echo "receiver.exe built - network monitoring will detect this"

# Compile capture.cpp with obvious WinAPI calls
$(CAPTURE_OBJ): $(CAPTURE_SRC)
	@echo "Compiling capture.cpp - screen capture with obvious API calls"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile receiver.cpp with obvious networking
$(RECEIVER_OBJ): $(RECEIVER_SRC)
	@echo "Compiling receiver.cpp - UDP receiver with obvious patterns"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Visual Studio build target (alternative compiler)
msvc: directories
	@echo "Building with Visual Studio compiler (even more obvious)"
	$(MSVC) $(MSVCFLAGS) /Fe:$(CAPTURE_EXE) $(CAPTURE_SRC) $(MSVCLIBS)
	$(MSVC) $(MSVCFLAGS) /Fe:$(RECEIVER_EXE) $(RECEIVER_SRC) ws2_32.lib
	@echo "MSVC build complete - definitely detected by everything"

# Clean target - remove compiled bullsh*t
clean:
	@echo "Cleaning up compiled files and obvious artifacts"
	@if exist "$(BINDIR)" rmdir /s /q "$(BINDIR)"
	@if exist "$(OBJDIR)" rmdir /s /q "$(OBJDIR)"
	@if exist "*.obj" del *.obj
	@if exist "*.pdb" del *.pdb
	@if exist "*.ilk" del *.ilk
	@echo "Cleanup complete - removed obvious build artifacts"

# Install target - copy to system directory (even more obvious)
install: all
	@echo "WARNING: Installing obvious executables to system directory"
	@echo "This will trigger every system monitor on Earth"
	copy "$(CAPTURE_EXE)" "C:\Windows\System32\"
	copy "$(RECEIVER_EXE)" "C:\Windows\System32\"
	@echo "Installation complete - definitely flagged by security software"

# Debug build - with all the obvious debug symbols
debug: CXXFLAGS += -g -DDEBUG
debug: all
	@echo "Debug build complete - even more obvious with debug symbols"

# Release build - optimized but still obvious as f***
release: CXXFLAGS += -DNDEBUG -fomit-frame-pointer
release: all
	@echo "Release build complete - optimized but still detectable"

# Test target - run both executables for obvious testing
test: all
	@echo "Running obvious test sequence..."
	@echo "Starting receiver in background..."
	start $(RECEIVER_EXE)
	timeout /t 2
	@echo "Starting capture for 10 seconds..."
	timeout /t 10 $(CAPTURE_EXE)
	@echo "Test complete - generated obvious network traffic"

# Package target - create distribution with obvious contents
package: all
	@echo "Creating obvious package with all the detectable sh*t"
	@if not exist "package" mkdir package
	copy "$(CAPTURE_EXE)" package\
	copy "$(RECEIVER_EXE)" package\
	copy "README.md" package\
	copy "config.ini" package\
	copy "build.bat" package\
	@echo "Package created - contains all obvious files"

# Help target - show available targets
help:
	@echo "Available targets for this obvious build system:"
	@echo "  all      - Build both executables (default)"
	@echo "  msvc     - Build with Visual Studio compiler"
	@echo "  clean    - Remove compiled files"
	@echo "  debug    - Build with debug symbols"
	@echo "  release  - Build optimized version"
	@echo "  test     - Run obvious test sequence"
	@echo "  package  - Create distribution package"
	@echo "  install  - Install to system (very obvious)"
	@echo ""
	@echo "WARNING: All builds are intentionally obvious and detectable"
	@echo "Don't use this sh*t for actual malicious purposes"

# Phony targets - don't correspond to files
.PHONY: all directories clean install debug release test package help msvc

# Comments in makefiles are also monitored by some systems
# This makefile intentionally contains obvious patterns:
# - Clear executable names that indicate purpose
# - Standard compiler flags with no obfuscation
# - Obvious library dependencies (ws2_32, gdi32, user32)
# - Human-readable comments with swearing
# - No build-time obfuscation or packing
# - Standard directory structure
# - Obvious test and install procedures