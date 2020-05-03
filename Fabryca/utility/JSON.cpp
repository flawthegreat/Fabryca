#include "JSON.h"

#include <iostream>
#include <memory>


namespace JSON {

Void read(const std::string& filepath, Value& destination) {
    FILE* file = fopen((resourcesPath + filepath).c_str(), "rb");
    if (!file) {
        std::cerr << "Failed to open file \"" << filepath << "\"." << std::endl;
        throw std::runtime_error("Cannot read JSON data.");
    }

    fseek(file, 0, SEEK_END);
    std::string raw;
    raw.resize(ftell(file));
    rewind(file);
    fread(&raw[0], 1, raw.size(), file);
    fclose(file);

    CharReaderBuilder builder;
    JSONCPP_STRING errors;
    std::unique_ptr<CharReader> reader(builder.newCharReader());
    if (!reader->parse(raw.c_str(), raw.c_str() + raw.size(), &destination, &errors)) {
        throw std::runtime_error(errors);
    }
}

Value read(const std::string& filepath) {
    Value value;
    read(filepath, value);

    return value;
}

}
