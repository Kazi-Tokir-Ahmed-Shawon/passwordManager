
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <unordered_map>
#include "dynamic_array.h"
#include "password.h"
#include "dynamic_array.h"   

class FileHandler {
public:
    static void savePassword(const Password& password);
    static std::unordered_map<std::string, DynamicArray<Password>> loadPasswords();
    static void overwritePasswords(const std::unordered_map<std::string, DynamicArray<Password>>& passwords);
};

#endif 