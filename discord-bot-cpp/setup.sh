#!/bin/bash

# Discord Bot C++ Setup Script

echo "🤖 Discord Bot C++ Setup"
echo "======================="
echo ""

# Check if .env exists
if [ ! -f ".env" ]; then
    echo "📝 Creating .env file from template..."
    cp .env.example .env
    echo "✓ .env created. Please edit it with your Discord token:"
    echo ""
    echo "  nano .env"
    echo "  # or"
    echo "  code .env"
    echo ""
else
    echo "✓ .env file already exists"
fi

# Check for DPP installation
echo ""
echo "🔍 Checking for DPP installation..."

if dpkg -l | grep -q libdpp-dev; then
    echo "✓ DPP is installed"
else
    echo "❌ DPP not found. Installing dependencies..."
    sudo apt-get update
    sudo apt-get install -y libdpp-dev libssl-dev zlib1g-dev cmake build-essential
    echo "✓ Dependencies installed"
fi

# Build
echo ""
echo "🔨 Building bot..."

if [ ! -d "build" ]; then
    mkdir build
fi

cd build
cmake ..
cmake --build .

if [ -f "./DiscordBot" ]; then
    echo ""
    echo "✓ Build successful!"
    echo ""
    echo "🚀 To start the bot, run:"
    echo "   cd build && ./DiscordBot"
    echo ""
    echo "📖 Don't forget to:"
    echo "   1. Add bot to your Discord server"
    echo "   2. Enable Message Content Intent in Developer Portal"
else
    echo "❌ Build failed"
    exit 1
fi
