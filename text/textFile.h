#ifndef TEXT_FILE_H_
#define TEXT_FILE_H_

#include <fstream>
#include <vector>

class textFile
{
private:
    /* data */
public:
    textFile(/* args */);
    ~textFile();

    void ReadText();
    void ReadText2();
    void WriteText();
    void DeleteText();
    void UpdateText();
    void ParseInfo(const std::string& line);
    void SplitString(const std::string& s, std::vector<std::string>& v, const char& c);
};

#endif
