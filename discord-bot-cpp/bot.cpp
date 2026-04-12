#include <dpp/dpp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <map>
#include <mutex>

// Helper function to convert string to lowercase
std::string toLower(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

// Load environment variables from .env file
std::string getEnvVar(const std::string& key) {
    std::ifstream file(".env");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(key) != std::string::npos) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                return line.substr(pos + 1);
            }
        }
    }
    return "";
}

// Generate natural responses based on message content
std::string generateResponse(const std::string& message) {
    std::string lowerMsg = message;
    std::transform(lowerMsg.begin(), lowerMsg.end(), lowerMsg.begin(), ::tolower);
    
    if (lowerMsg.find("hello") != std::string::npos || lowerMsg.find("hi") != std::string::npos) {
        std::vector<std::string> responses = {"yo whats up", "hey there!", "sup", "heyy 👋"};
        return responses[rand() % responses.size()];
    }
    
    if (lowerMsg.find("how are you") != std::string::npos) {
        std::vector<std::string> responses = {"doing pretty good", "im vibing 😎", "cant complain", "all good fr"};
        return responses[rand() % responses.size()];
    }
    
    if (lowerMsg.find("thanks") != std::string::npos) {
        std::vector<std::string> responses = {"np", "anytime", "got u", "all good"};
        return responses[rand() % responses.size()];
    }
    
    if (lowerMsg.find("?") != std::string::npos) {
        std::vector<std::string> responses = {"no idea fr", "good question", "uh... probably", "maybe lol"};
        return responses[rand() % responses.size()];
    }
    
    std::vector<std::string> defaultResponses = {
        "true true", "ikr", "fr fr", "nah i feel that", "lol same", "facts", "not me tho", "what", "huh?"
    };
    return defaultResponses[rand() % defaultResponses.size()];
}

static std::string lastBotResponse;
static std::map<dpp::snowflake, std::vector<std::chrono::steady_clock::time_point>> userMessageTimes;
static std::mutex userMessageMutex;

int main() {
    std::string token = getEnvVar("DISCORD_TOKEN");
    
    if (token.empty()) {
        std::cerr << "Error: DISCORD_TOKEN not found in .env file!" << std::endl;
        return 1;
    }
    
    if (!token.empty() && token.back() == '\n') {
        token.pop_back();
    }
    
    dpp::cluster bot(token);
    
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct _ready_check>()) {
            std::cout << "✓ Bot is online and ready to chat!" << std::endl;
        }
    });
    
    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        try {
            if (event.msg.author.is_bot()) return;
            
            std::string userMessage = event.msg.content;
            dpp::snowflake userId = event.msg.author.id;
            auto now = std::chrono::steady_clock::now();
            bool isSpam = false;
            
            {
                std::lock_guard<std::mutex> lock(userMessageMutex);
                auto& timestamps = userMessageTimes[userId];
                timestamps.erase(std::remove_if(timestamps.begin(), timestamps.end(), [&](const auto& ts) {
                    return std::chrono::duration_cast<std::chrono::seconds>(now - ts).count() > 10;
                }), timestamps.end());
                timestamps.push_back(now);
                if (timestamps.size() > 3) {
                    isSpam = true;
                }
            }
            
            std::thread([&bot, event, userMessage, isSpam]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(400 + (rand() % 1600)));
                
                std::string response;
                if (isSpam) {
                    response = "stop my pc is lagging bro :sob:";
                } else {
                    std::string lowerUserMessage = toLower(userMessage);
                    std::string lowerLast = toLower(lastBotResponse);
                    if (!lastBotResponse.empty() && lowerUserMessage == lowerLast) {
                        response = "stop copying my message gng ik you feel me :broken_heart: :wilted_rose:";
                    } else {
                        response = generateResponse(userMessage);
                    }
                }
                lastBotResponse = response;
                
                dpp::message msg;
                msg.channel_id = event.msg.channel_id;
                msg.content = response;
                msg.message_reference.message_id = event.msg.id;
                
                bot.message_create(msg);
                
                if (rand() % 100 < 25) {  // 25% chance to react
                    std::vector<std::string> emojis = {"👀", "💀", "😂", "🔥", "💯"};
                    bot.message_add_reaction(event.msg.channel_id, event.msg.id, emojis[rand() % emojis.size()]);
                }
            }).detach();
            
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    });
    
    bot.on_message_reaction_add([&bot](const dpp::message_reaction_add_t& event) {
        if (rand() % 100 < 35) {  // 35% chance to react back
            std::vector<std::string> emojis = {"👀", "💀", "😂", "🔥"};
            bot.message_add_reaction(event.channel_id, event.message_id, emojis[rand() % emojis.size()]);
        }
    });
    
    bot.start(dpp::st_wait);
    
    return 0;
}
