#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <QFile>
#include <QDir>
#include <vector>

#include "../pessoal/objectfile.h"

class FileController
{
public:
    FileController(QString filePath = ".");

    std::vector<ObjectFile *> assets3DSFiles();
    std::vector<std::string> assets3DSFileNames();

    ObjectFile *get3DSfromAssetsFileName(std::string fileName);

private:
    QString m_filePath;
    QDir m_rootDirectory;
    QDir m_assetsDirectory;
    QDir m_scenesDirectory;
};

#endif // FILECONTROLLER_H
