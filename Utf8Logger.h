#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <filesystem>

class Utf8Logger {
public:
    Utf8Logger(const std::string& filename) {
        createDirectories(filename);
        logFile.open(filename, std::ios::out | std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("파일을 열 수 없습니다.");
        }
    }

    ~Utf8Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> guard(logMutex);
        logFile << message << std::endl;
    }

private:
    std::ofstream logFile;
    std::mutex logMutex;

    void createDirectories(const std::string& filename) {
        std::filesystem::path filePath(filename);
        std::filesystem::path dirPath = filePath.parent_path();
        if (!dirPath.empty() && !std::filesystem::exists(dirPath)) {
            std::filesystem::create_directories(dirPath);
        }
    }
};

int main() {
    try {
        Utf8Logger logger("C:\Users\sakim\source\repos\XGraph\MFCApplication1\logs\log.xtx");
        logger.log("첫 번째 로그 메시지");
        logger.log("두 번째 로그 메시지");
    }
    catch (const std::exception& e) {
        std::cerr << "예외 발생: " << e.what() << std::endl;
    }

    return 0;
}