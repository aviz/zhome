//
// Created by Avi Zrachya on 02/07/2018.
//

#ifndef ZSWITCH_UTILS_H
#define ZSWITCH_UTILS_H

#include <string>
#include <vector>

class Utils {
public:
    static std::string getUniqueDeviceId();
    static std::vector<std::string> split(const std::string &s, char delim);
};




#endif //ZSWITCH_UTILS_H
