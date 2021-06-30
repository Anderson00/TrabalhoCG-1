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
    std::vector<std::string> scenesFileNames();

    ObjectFile *get3DSfromAssetsFileName(std::string fileName);

    bool saveScene(std::vector<Objeto*> objetos);
    bool saveScene(std::string fileName, std::vector<Objeto*> objetos);

    std::vector<Objeto *> openScene(std::string fileName);

    std::string fileSavedName();

private:
    QString m_filePath;
    std::string m_fileSavedName;
    QDir m_rootDirectory;
    QDir m_assetsDirectory;
    QDir m_scenesDirectory;


};

#endif // FILECONTROLLER_H
