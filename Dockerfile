# Use an image with gcc
FROM gcc:latest

# Set the working directory in the Docker image
WORKDIR /usr/src/app

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Install necessary packages
RUN apt-get update && apt-get install -y \
    build-essential \
    libgtest-dev \
    wget

# Download and install CMake 3.27
RUN wget https://github.com/Kitware/CMake/releases/download/v3.27.0/cmake-3.27.0-Linux-x86_64.sh \
    -q -O /tmp/cmake-install.sh \
    && chmod u+x /tmp/cmake-install.sh \
    && mkdir /opt/cmake-3.27.0 \
    && /tmp/cmake-install.sh --skip-license --prefix=/opt/cmake-3.27.0 \
    && rm /tmp/cmake-install.sh \
    && ln -s /opt/cmake-3.27.0/bin/* /usr/local/bin

# Build Google Test
WORKDIR /usr/src/gtest
RUN cmake CMakeLists.txt
RUN make

# Return to your project folder
WORKDIR /usr/src/app

# Create a build directory and change into it
RUN mkdir build
WORKDIR build

# Run CMake
RUN cmake ..

# Build your project
RUN make

# Run the tests
CMD ["./HTMLizeMDTests"]
