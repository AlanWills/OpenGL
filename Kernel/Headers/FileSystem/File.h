#pragma once

#include "DllExport.h"

#include <string>
#include <vector>

namespace Kernel
{

#ifdef WIN32
#define PATH_DELIMITER '\\'
#else
#define PATH_DELIMITER '/'
#endif

class DllExport File
{
  public:
    /// \brief Automatically creates the file in the constructor and can optionally clear it too if specified.
    /// By default it does not clear the file if it exists already
    File(const std::string& fullFilePath, bool clearIfAlreadyExists = false);
    ~File();

    /// \brief Appends a PATH_DELIMITER and the secondPath onto the firstPath
    /// std::string first("first\\path"), second("second\\path");
    /// e.g. combinePaths(first, second) would change firstPath to "first\\path\\second\\path";
    static void combinePaths(std::string& firstPath, const std::string& secondPath);

    /// \brief Returns true if the file exists
    static bool exists(const std::string& fullFilePath);

    /// \brief Opens a file and adds the inputted string to the end of it followed by std::endl
    /// Therefore, every call to this function will append the input onto a new line
    /// Will create the file if it does not exist
    static void appendToFile(const std::string& fullFilePath, const std::string& stringToAppend);
    // Instance version
    void appendToFile(const std::string& stringToAppend) { appendToFile(m_fullFilePath, stringToAppend); }

    /// \brief Creates a file if it does not exist.
    /// Does nothing if it does exist
    static void createFile(const std::string& fullFilePath, bool clearIfAlreadyExists = true);

    /// \brief Deletes a file if it exists
    static void deleteFile(const std::string& fullFilePath);

    /// \brief Opens a file if it exists and stores the contents in the outFileContents parameter
    static void readFile(const std::string& fullFilePath, std::string& outFileContents);
    // Instance version
    void readFile(std::string& outFileContents) { readFile(m_fullFilePath, outFileContents); }

    /// \brief Adds all the lines for the file onto the end of the inputted vector, without altering any contents that might already be inside it
    static void readLines(const std::string& fullFilePath, std::vector<std::string>& outLines);
    // Instance version
    void readLines(std::vector<std::string>& outLines) { readLines(m_fullFilePath, outLines); }

  private:
    std::string m_fullFilePath;
};

};