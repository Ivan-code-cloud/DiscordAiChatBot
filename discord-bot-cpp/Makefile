.PHONY: build run clean install-deps help

help:
	@echo "Discord Bot C++ - Available commands:"
	@echo ""
	@echo "  make install-deps    Install required dependencies (Ubuntu/Debian)"
	@echo "  make build          Build the bot"
	@echo "  make run            Build and run the bot"
	@echo "  make clean          Remove build artifacts"
	@echo "  make setup          Setup .env file from template"
	@echo ""

install-deps:
	@echo "Installing DPP dependencies..."
	sudo apt-get update
	sudo apt-get install -y libdpp-dev libssl-dev zlib1g-dev cmake build-essential

setup:
	@if [ ! -f ".env" ]; then \
		cp .env.example .env; \
		echo "Created .env file. Please edit it with your Discord token:"; \
		echo "  nano .env"; \
	else \
		echo ".env file already exists"; \
	fi

build: setup
	@echo "Building Discord Bot..."
	mkdir -p build
	cd build && cmake .. && cmake --build .
	@echo "✓ Build complete! Binary: ./build/DiscordBot"

run: build
	@echo "Starting bot..."
	cd build && ./DiscordBot

clean:
	@echo "Cleaning build artifacts..."
	rm -rf build/
	@echo "✓ Clean complete"

rebuild: clean build
	@echo "✓ Rebuild complete"
