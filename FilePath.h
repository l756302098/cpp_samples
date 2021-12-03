#pragma once

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

namespace swr {
namespace util {

class FilePath {
public:
    // [brief] Gets the full path of the current process.
    // [note] Returns an empty string on failure.
    // e.g. "/home/ubuntu/sample"
    static inline std::string GetCurExeWholePath() {
        std::string path;
        std::string::size_type pathsize = 1024;

        do {
            path.resize(pathsize);
            auto ret = readlink("/proc/self/exe", &path[0], pathsize);
            if (-1 == ret) {
                return std::move("");
            } else if (ret < static_cast<ssize_t>(pathsize)) {
                break;
            } else {
                pathsize *= 2;
            }
        } while (true);

        return std::move(path);
    }

    // [brief] Gets the path where the current process file is located.
    // [note] Returns an empty string on failure.
    // e.g. "/home/ubuntu/sample" => "/home/ubuntu/"
    static inline std::string GetCurExePath() {
        auto&& path = GetCurExeWholePath();
        auto idx = path.find_last_of('/');
        if (std::string::npos == idx) {
            return std::move("");
        }
        return std::move(path.substr(0, idx + 1));
    }

    // [brief] Get current process name.
    // e.g. "/home/ubuntu/sample" => "sample"
    static inline std::string GetCurExeName() {
        auto&& path = GetCurExeWholePath();
        auto idx = path.find_last_of('/');
        if (std::string::npos == idx) {
            return std::move("");
        }
        return std::move(path.substr(idx + 1));
    }

    static inline bool IsFileExisted(const char* filePath) {
        return (0 == access(filePath, F_OK));
    }

    static inline bool IsDirExisted(const char* dirPath) {
        return (0 == access(dirPath, F_OK));
    }

    static inline bool IsFileExisted(std::string& filePath) {
        return (0 == access(filePath.c_str(), F_OK));
    }

    static inline bool IsDirExisted(std::string& dirPath) {
        return (0 == access(dirPath.c_str(), F_OK));
    }

    // no support recursive creation
    static inline bool CreateDir(const char* dirPath) {
        return !mkdir(dirPath, S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }

    // support recursive creation
    static inline bool CreateDirR(const char* dirPath) {
        if (!access(dirPath, F_OK)) {
            return true;
        }
        bool success = false;
        std::string tmpDirPath(dirPath);
        size_t idx = tmpDirPath.find_last_of('/');
        if (std::string::npos != idx &&
            FilePath::CreateDirR(tmpDirPath.substr(0, idx).c_str())) {
            success = CreateDir(dirPath);
        }
        return success;
    }

    // no support recursive creation
    static inline bool CreateFile(const char* filePath) {
        FILE* pfile = fopen(filePath, "w+");
        if (pfile) {
            fclose(pfile);
            return true;
        }
        return false;
    }

    // support recursive creation
    static inline bool CreateFileR(const char* filePath) {
        bool success = false;
        std::string tmpFilePath(filePath);
        size_t idx = tmpFilePath.find_last_of('/');
        if (std::string::npos != idx &&
            util::FilePath::CreateDirR(tmpFilePath.substr(0, idx).c_str())) {
            success = FilePath::CreateFile(filePath);
        }
        return success;
    }

    // no support recursive remove
    static inline bool DeleteFile(const char* filePath) {
        return 0 == remove(filePath);
    }

    // no support recursive remove
    static inline bool DeleteDir(const char* dirPath) {
        return 0 == rmdir(dirPath);
    }

    // support recursive remove
    static inline bool DeleteDirR(const char* dirPath) {
        DIR* dirp = opendir(dirPath);
        if (nullptr == dirp) {
            return false;
        }

        bool success = true;
        struct dirent* dir = nullptr;
        struct stat st;
        while (nullptr != (dir = readdir(dirp))) {
            if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
                continue;

            std::string subPath = std::string(dirPath) + '/' + dir->d_name;
            if (-1 == lstat(subPath.c_str(), &st))
                continue;

            if (S_ISDIR(st.st_mode)) {
                if (!DeleteDirR(subPath.c_str())) {
                    success = false;
                    break;
                }
                rmdir(subPath.c_str());
            } else if (S_ISREG(st.st_mode)) {
                unlink(subPath.c_str());
            } else {
                continue;
            }
        }

        closedir(dirp);
        return success ? 0 == rmdir(dirPath) : false;
    }

    // get file size
    // return size on success, return -1 failure
    static inline int GetFileSize(const char* filePath) {
        struct stat statbuf;
        return (0 == stat(filePath, &statbuf)) ? statbuf.st_size : -1;
    }

    // move fileOld to fileNew
    static inline bool MoveFile(const char* fileOld, const char* fileNew) {
        return 0 == rename(fileOld, fileNew);
    }

    // move dirOld to dirNew
    static inline bool MoveDir(const char* dirOld, const char* dirNew) {
        return 0 == rename(dirOld, dirNew);
    }

    // rename fileOld to fileNew
    static inline bool RenameFile(const char* fileOld, const char* fileNew) {
        return 0 == rename(fileOld, fileNew);
    }

    // rename dirOld to dirNew
    static inline bool RenameDir(const char* dirOld, const char* dirNew) {
        return 0 == rename(dirOld, dirNew);
    }

    // copy file to other dir
    static inline bool CopyFile(const char* source, const char* dest) {
        std::string cmd("cp ");
        cmd += source;
        cmd += " ";
        cmd += dest;
        return 0 == system(cmd.c_str());
    }

    // copy dir to other dir
    static inline bool CopyDir(const char* source, const char* dest) {
        std::string cmd("cp -r ");
        cmd += source;
        cmd += " ";
        cmd += dest;
        return 0 == system(cmd.c_str());
    }

    // get file list by dir.  'depth': Recursive lookup depth.
    static inline std::vector<std::string> GetFileList(const std::string& dirPath, size_t depth) {
        std::vector<std::string> flist;

        DIR* dp = opendir(dirPath.c_str());
        if (nullptr == dp) {
            std::cerr << "cannot open directory(" << dirPath << ").\n";
            return std::move(flist);
        }

        auto ret = chdir(dirPath.c_str());
        (void)ret;

        struct dirent* entry = nullptr;
        while (nullptr != (entry = readdir(dp))) {
            struct stat statbuf;
            lstat(entry->d_name, &statbuf);
            if (S_ISDIR(statbuf.st_mode)) {
                if (0 == strcmp(".", entry->d_name) ||
                    0 == strcmp("..", entry->d_name)) {
                    continue;
                }

                if (0 < depth - 1) {
                    std::string dirPathChild = dirPath;
                    dirPathChild += entry->d_name;
                    dirPathChild += "/";
                    auto&& fileList = GetFileList(dirPathChild, depth - 1);
                    flist.insert(flist.end(), fileList.begin(), fileList.end());
                }
            } else {
                flist.emplace_back(std::move(dirPath + '/' + entry->d_name));
            }
        }

        ret = chdir("..");
        (void)ret;
        ret = closedir(dp);
        (void)ret;

        return std::move(flist);
    }

    static std::vector<std::string> GetAllDirs(std::string path, bool recursive = false)
    {
        std::vector<std::string> fileList;
        DIR* p_dir = opendir(path.c_str());
        if (nullptr == p_dir)
        {
            return fileList;
        }

        struct dirent* p_dirent;
        while ( (p_dirent = readdir(p_dir)) != nullptr)
        {
            std::string fileName = p_dirent->d_name;
            if( fileName == "." || fileName == "..")
            {
                continue;
            }

            std::string tmpFileName = path + "/" + fileName;
            if (p_dirent->d_type == DT_DIR)
            {
                fileList.push_back(tmpFileName);
                if (recursive)
                {
                    std::vector<std::string> tmpFiles = GetAllDirs(tmpFileName, recursive);
                    for(std::string str : tmpFiles)
                    {
                        fileList.push_back(str);
                    }
                }
            }
        }

        closedir(p_dir);
        return fileList;
    }

    static std::string GetFileNameFromPath(std::string path)
    {
        int pos = path.find_last_of('/');
        std::string fileName(path.substr(pos + 1));
        return fileName;
    }
};

}  // namespace util
}  // namespace swr
