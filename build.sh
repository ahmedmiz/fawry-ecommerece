
#!/bin/bash

# Configure build type (Debug or Release)
BUILD_TYPE=${1:-Debug}
BUILD_DIR="build_${BUILD_TYPE}"

# Function to check if CMake is installed
check_cmake() {
    if ! command -v cmake &> /dev/null; then
        echo "Error: CMake is not installed."
        echo "Please install CMake first:"
        echo "  macOS: brew install cmake"
        echo "  Ubuntu/Debian: sudo apt-get install cmake"
        echo "  CentOS/RHEL: sudo yum install cmake"
        exit 1
    fi
}

# Function to check if compiler is installed
check_compiler() {
    if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
        echo "Error: No C++ compiler found."
        echo "Please install a C++ compiler:"
        echo "  macOS: xcode-select --install"
        echo "  Ubuntu/Debian: sudo apt-get install build-essential"
        echo "  CentOS/RHEL: sudo yum groupinstall 'Development Tools'"
        exit 1
    fi
}

# Check dependencies
check_cmake
check_compiler

if [ "$1" == "test" ]; then
    if [ -d "build_debug_test" ]; then
        echo "Running tests in build_debug_test..."
        cd "build_debug_test"
        ctest -V
        exit 0
    else
        echo "Error: Build directory build_debug_test does not exist. Run the build first."
        exit 1
    fi
fi

# Create build directory
mkdir -p $BUILD_DIR 2>/dev/null 
cd $BUILD_DIR

echo "Configuring build with CMake..."
# Configure via CMake
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..  || {
    echo "Error: CMake configuration failed."
    exit 1
}

# Get number of CPU cores for parallel build
if [ -f /proc/cpuinfo ]; then
    # Linux
    CORES=$(grep -c ^processor /proc/cpuinfo)
elif [ "$(uname)" == "Darwin" ]; then
    # macOS
    CORES=$(sysctl -n hw.ncpu)
else
    # Default to 2 cores
    CORES=2
fi

echo "Building with $CORES cores..."
# Build with multiple cores
cmake --build . -- -j$CORES 

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "Build successful!"
    
    # Run tests if requested
    if [ "$2" == "test" ]; then
        echo "Running tests..."
        ctest -V
    fi
    
    echo "Build complete: $BUILD_TYPE configuration"
    echo "Executable location: $BUILD_DIR/fawry-eCommerce"
else
    echo "Build failed!"
    exit 1
fi