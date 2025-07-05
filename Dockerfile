FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && \
    apt-get install -y build-essential cmake && \
    rm -rf /var/lib/apt/lists/*

# Set workdir
WORKDIR /app

# Copy source
COPY . .

# Build
RUN ./build.sh Release

# Set entrypoint
ENTRYPOINT ["./build_Release/fawry-eCommerce"] 