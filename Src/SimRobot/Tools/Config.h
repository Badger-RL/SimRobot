#ifndef RL_CONFIG
#define RL_CONFIG

#include <stdio.h>
#include <string>
#include <unistd.h>
#include <fstream>
#include "json.h"


#include <libgen.h>         // dirname
#include <linux/limits.h>   // PATH_MAX

#include <mutex>


//derived from https://stackoverflow.com/questions/23943239/how-to-get-path-to-current-exe-file-on-linux
static std::string getConfigDirectory(){

    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    const char *path;
    if (count != -1) {
        path = dirname(result);
    }
    std::string output(path);
    output = output + "/../../../../Config/rl_config.json";
    std::cout << "Config Directory: " << output << std::endl;
    return output;
}


namespace RLConfig{
static std::string  configPath = getConfigDirectory();
static std::ifstream configFile(configPath);
static json::value configData = json::parse(configFile);
static std::string mode = to_string(configData["mode"]);
static bool train_mode = to_bool(configData["train_mode"]);
static bool deterministic = to_bool(configData["deterministic"]);
static bool referee_enabled = to_bool(configData["referee_enabled"]);
static int action_steps = std::stoi(to_string(configData["action_steps"]));
static int episode_length = std::stoi(to_string(configData["episode_length"]));
static int batch_size = std::stoi(to_string(configData["batch_size"]));
static int epoch_count = std::stoi(to_string(configData["epoch_count"]));
static int seed = std::stoi(to_string(configData["seed"]));
static bool normalization = to_bool(configData["normalization"]);
static bool debug_print = to_bool(configData["debug_print"]);
static bool visualization_mode = to_bool(configData["visualization_mode"]);


extern std::mutex resetLock;
extern bool resetting;


}

#endif