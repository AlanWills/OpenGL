#pragma once

#include "DllExport.h"
#include "Path.h"

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

    /// Be careful passing string literals as the second arg to this constructor as it will convert it to a bool rather than a const std::string&
    /// and so call the first constructor
    File(const std::string& fullParentDirectoryPath, const std::string& relativeFilePath, bool clearIfAlreadyExists = false);
    ~File();

    File(const Path& path);

    /// \brief Returns true if the file exists
    static bool exists(const std::string& fullFilePath);
    bool exists() const { return exists(m_filePath.asString()); }

    /// \brief Opens a file and adds the inputted string to the end of it followed by std::endl
    /// Therefore, every call to this function will append the input onto a new line
    /// Will create the file if it does not exist
    static void append(const std::string& fullFilePath, const std::string& stringToAppend);
    void append(const std::string& stringToAppend) const { append(m_filePath.asString(), stringToAppend); }

    /// \brief Creates a file if it does not exist.
    /// Does nothing if it does exist
    static void create(const std::string& fullFilePath, bool clearIfAlreadyExists = true);
    void create(bool clearIfAlreadyExists = true) const { create(m_filePath.asString(), clearIfAlreadyExists); }

    /// \brief Creates a file within the inputted directory
    /// Does nothing if it does exist
    static void createInDirectory(const std::string& directoryFullPath, const std::string& relativeFilePath, bool clearIfAlreadyExists = true);

    /// \brief Deletes a file if it exists
    static void remove(const std::string& fullFilePath);
    void remove() const { remove(m_filePath.asString()); }

    /// \brief Opens a file if it exists and stores the contents in the outFileContents parameter
    static void read(const std::string& fullFilePath, std::string& outFileContents);
    void read(std::string& outFileContents) const { read(m_filePath.asString(), outFileContents); }

    /// \brief Adds all the lines for the file onto the end of the inputted vector, without altering any contents that might already be inside it
    static void readLines(const std::string& fullFilePath, std::vector<std::string>& outLines);
    void readLines(std::vector<std::string>& outLines) const { readLines(m_filePath.asString(), outLines); }

  private:
    Path m_filePath;
};

};