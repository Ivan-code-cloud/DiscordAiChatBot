# Discord Bot instructions

A human-like Discord bot built with **D++ (DPP)** - the Discord C++ Library. The bot sends natural messages, reacts to user messages, and replies in a conversational manner.

Before Installing, transfer the files: .env and .gitignore to discord-bot-cpp

## Features

✅ **Human-like messaging** - Sends messages with natural variations and casual language
✅ **Auto-replies** - Responds intelligently to user messages
✅ **Reactions** - Reacts to messages with emojis
✅ **Typing indicator** - Shows "is typing..." for realistic behavior
✅ **Random delays** - Simulates human typing speed (0.5-2 seconds)
✅ **Direct messages** - Responds to DMs
✅ **Guild support** - Works in Discord servers

## Prerequisites

- **Ubuntu/Debian**: `sudo apt-get install libdpp-dev libssl-dev zlib1g-dev cmake`
- **Fedora**: `sudo dnf install libdpp-devel openssl-devel zlib-devel cmake`
- **macOS**: `brew install dpp openssl cmake`
- **Windows**: Download pre-built DPP binaries or use vcpkg

## Setup Instructions

### 1. Create Discord Bot

1. Go to [Discord Developer Portal](https://discord.com/developers/applications)
2. Click "New Application"
3. Go to "Bot" and click "Add Bot"
4. Under "TOKEN", click "Copy" to copy your bot token
5. Enable these **Privileged Gateway Intents**:
   - Message Content Intent
   - Server Members Intent (optional)

### 2. Get Bot Invite URL

1. Go to "OAuth2" → "URL Generator"
2. Select scopes: `bot`
3. Select permissions:
   - Send Messages
   - Read Messages/View Channels
   - Add Reactions
4. Copy the generated URL and open it to add bot to your server

### 3. Clone/Setup Project

```bash
cd /home/yourusername/Documents/discord-bot-cpp
cp .env.example .env
```

### 4. Add Your Token to .env

Edit `.env` file and replace `your_discord_bot_token_here` with your actual bot token:

```
DISCORD_TOKEN=your_actual_token_here
```

### 5. Build the Bot

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Compile
cmake --build .
```

### 6. Run the Bot

```bash
# From the build directory
./DiscordBot
```

You should see:
```
Bot is online!
```

## How It Works

### Message Responding
- Bot listens to all messages in servers where it has permissions
- Generates natural responses based on message content
- Adds random variations (emojis, filler words) for human-like behavior
- Shows typing indicator while "composing" response
- Random 0.5-2 second delay before responding

### Reactions
- Randomly reacts to messages (30% chance)
- Reacts back when someone reacts to bot's messages (50% chance)
- Uses common Discord emojis: 👀, 💀, 😂, 🔥, 💯, ✨

### Conversation Patterns
The bot recognizes keywords and responds naturally:
- **"hello/hi"** → `"yo whats up"`, `"hey there!"`, etc.
- **"how are you"** → `"doing pretty good ngl"`, `"im vibing 😎"`, etc.
- **"thanks"** → `"np"`, `"anytime"`, etc.
- **Questions (contains ?)** → Vague responses like `"no idea fr"`, `"good question"`
- **Default** → Casual reactions like `"true true"`, `"fr fr"`, `"facts 📝"`, etc.

## Project Structure

```
discord-bot-cpp/
├── bot.cpp          # Main bot source code
├── CMakeLists.txt   # Build configuration
├── .env.example     # Environment variables template
└── README.md        # This file
```

## Troubleshooting

### Bot doesn't respond
- Check if bot has "Message Content Intent" enabled in Developer Portal
- Verify bot has permission to send messages in the channel
- Check if bot is online: `./DiscordBot` should print "Bot is online!"

### Compilation errors
- Make sure DPP is installed: `apt-cache policy libdpp-dev`
- Try updating CMake: `sudo apt upgrade cmake`
- On macOS: `brew reinstall dpp`

### Token not working
- Ensure `.env` file is in the same directory as the compiled bot
- Check token is copied correctly (no spaces)
- Regenerate token in Developer Portal if needed

## Customization

### Add more responses
Edit the `generateResponse()` function in `bot.cpp` to add more keywords and responses.

### Change reaction emojis
Modify the `emojis` vector in the reaction sections.

### Adjust typing delay
Change the `std::chrono::milliseconds(500 + (rand() % 1500))` value (currently 0.5-2 seconds).

### Add more personality
Add more response variations in the `defaultResponses` vector.

## Advanced Features

### Message Components (buttons, dropdowns)
DPP supports message components. See [DPP documentation](https://dpp.dev/).

### Prefix commands
Add a prefix parser to recognize commands like `!help`, `!ping`.

### Database integration
Connect to SQLite or PostgreSQL to store user data.

## License

MIT - Use freely for personal or commercial projects.

## Resources

- [D++ Documentation](https://dpp.dev/)
- [Discord.com Developer Portal](https://discord.com/developers/applications)
- [DPP GitHub](https://github.com/brainboxdotcc/DPP)
