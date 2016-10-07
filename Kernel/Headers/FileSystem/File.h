#pragma once

#include "DllExport.h"

#include <string>
#include <vector>

namespace Kernel
{

class DllExport File
{
  public:
    /// \brief Automatically creates the file in the constructor and can optionally clear it too if specified.
    /// By default it does not clear the file if it exists already
    File(const std::string& filePath, bool clearIfAlreadyExists = false);
    ~File();

    /// \brief Returns true if the file exists
    static bool exists(const std::string& fullFilePath);
    bool exists() const { return exists(m_filePath); }

    /// \brief Opens a file and adds the inputted string to the end of it followed by std::endl
    /// Therefore, every call to this function will append the input onto a new line
    /// Will create the file if it does not exist
    static void append(const std::string& fullFilePath, const std::string& stringToAppend);
    void append(const std::string& stringToAppend) const { append(m_filePath, stringToAppend); }

    /// \brief Creates a file if it does not exist.
    /// Does nothing if it does exist
    static void create(const std::string& fullFilePath, bool clearIfAlreadyExists = true);
    void create(bool clearIfAlreadyExists = true) const { create(m_filePath, clearIfAlreadyExists); }

    /// \brief Creates a file within the inputted directory
    /// Does nothing if it does exist
    static void createInDirectory(const std::string& directoryFullPath, const std::string& relativeFilePath, bool clearIfAlreadyExists = true);
    void createInDirectory(const std::string& directoryFullPath, bool clearIfAlreadyExists = true) { createInDirectory(directoryFullPath, m_filePath, clearIfAlreadyExists); }

    /// \brief Deletes a file if it exists
    static void remove(const std::string& fullFilePath);
    void remove() const { remove(m_filePath); }

    /// \brief Opens a file if it exists and stores the contents in the outFileContents parameter
    static void read(const std::string& fullFilePath, std::string& outFileContents);
    void read(std::string& outFileContents) const { read(m_filePath, outFileContents); }

    /// \brief Adds all the lines for the file onto the end of the inputted vector, without altering any contents that might already be inside it
    static void readLines(const std::string& fullFilePath, std::vector<std::string>& outLines);
    void readLines(std::vector<std::string>& outLines) const { readLines(m_filePath, outLines); }

  private:
    std::string m_filePath;
};

};