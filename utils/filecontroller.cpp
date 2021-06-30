#include "filecontroller.h"
#include "pessoal/objectfile.h"
#include <QDebug>
#include <QString>

FileController::FileController(QString filePath) : m_filePath(filePath), m_rootDirectory(QDir(filePath))
{
    if(this->m_rootDirectory.exists()){
        if(this->m_rootDirectory.exists("Assets") == false){
            this->m_rootDirectory.mkdir("Assets");
        }else{
            this->m_assetsDirectory = QDir("./Assets");
        }
        if(this->m_rootDirectory.exists("Scenes") == false){
            this->m_rootDirectory.mkdir("Scenes");
        }else{
            this->m_scenesDirectory = QDir("./Scenes");
        }
    }
}

std::vector<ObjectFile *> FileController::assets3DSFiles()
{
    QStringList arquivos = this->m_assetsDirectory.entryList(QStringList() << "*.3ds" << "*.3DS" << "*.3Ds" << "*.3dS", QDir::Files);
    std::vector<ObjectFile *> vector;
    foreach(QString filename, arquivos) {
        vector.push_back(new ObjectFile(QString("Assets/"+filename).toStdString()));
    }
    return vector;
}

std::vector<std::string> FileController::assets3DSFileNames()
{
    QStringList arquivos = this->m_assetsDirectory.entryList(QStringList() << "*.3ds" << "*.3DS" << "*.3Ds" << "*.3dS", QDir::Files);
    std::vector<std::string> vector;
    foreach(QString filename, arquivos) {
        vector.push_back(filename.toStdString());
    }
    return vector;
}

ObjectFile *FileController::get3DSfromAssetsFileName(string fileName)
{
    std::vector<std::string> files = this->assets3DSFileNames();

    for(std::string fname: files) {
        if(fname == fileName){
            return new ObjectFile("Assets/"+fileName);
        }
    }
    return nullptr;
}

