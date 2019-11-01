//
// Created by wangziwen on 2018-12-14.
//

#pragma once
#include <fstream>
#include <dirent.h>
#include <string.h>
#include <list>
#include <utility>
#include <set>
#include <vector>
using std::set;
using std::pair;
using std::make_pair;
using std::list;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::string;
using std::vector;


namespace utils_file {
    inline string GetFileName(const char* absolute_path) {
        string result(absolute_path);
        return result.substr(result.rfind("/") + 1);
    }

    inline void ListDir(const string& path, list<pair<string, string>>& files, const set<string>& filters = {}) {
        struct dirent *ent;
        char absolute_path[512];
        auto dir = opendir(path.c_str());
        while ((ent = readdir(dir)) != nullptr) {

            sprintf(absolute_path, "%s/%s", path.c_str(), ent->d_name);


            if (ent->d_type & DT_DIR)
                if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                    continue;
                else
                    ListDir(absolute_path, files, filters);
            else {
                const string str(ent->d_name);

                auto const position = str.rfind(".");
                if (string::npos == position)
                    continue;
                auto const prefix_str = str.substr(position + 1);
                if (!filters.size() || filters.find(prefix_str) != filters.end()) {



//                    size_t found=absolute_path.c_str().find_last_of("/\\");//Point
//                    cout<<absolute_path.substr(0,found)<<endl;
//                    cout<<absolute_path.substr(found+1)<<endl;
                    files.push_back(make_pair(ent->d_name, absolute_path));
                }
            }
        }
        closedir(dir);
    }

    inline auto LoadFiles(const string file_path, const set<string>& filters = {}) {
        vector<pair<string, string>> file_name_and_content;
        list<pair<string, string>> files;
        ListDir(file_path, files, filters);
        for (auto&& element : files) {
            string content;
            ifstream f(element.second, ios::in | ios::binary );
            if (!f) {
//                    LOG(ERROR) << "open file " << file << " error";
                break;
            }
            f.seekg(0, ifstream::end);
            content.resize(f.tellg());
            f.seekg(0, ifstream::beg);
            f.read(&content[0], content.size());
            f.close();
            file_name_and_content.push_back(make_pair(element.second, move(content)));
        }
        return move(file_name_and_content);
    }

    inline auto LoadFile(const string file_name) {
        string content;
        ifstream f(file_name, ios::in | ios::binary );
        if (f) {
            f.seekg(0, ifstream::end);
            content.resize(f.tellg());
            f.seekg(0, ifstream::beg);
            f.read(&content[0], content.size());
            f.close();
        }
        return move(content);
    }

    inline void WriteFile(const string& file_name, const char* buffer, const int length) {
        ofstream f(file_name);
        f.write(buffer, length);
        f.close();
    }
}

