#include "WebLogger.h"

WebLogger::WebLogger(std::string message) {

	std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string CurTim = std::ctime(&tt);

	std::ofstream ofs;
	ofs.open(WebLogger::Path, std::ios::app);
	ofs << message << " Time:" << CurTim;
	ofs.close();
}