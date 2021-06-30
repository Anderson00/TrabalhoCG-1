#include "filecontroller.h"
#include "pessoal/objectfile.h"
#include "pessoal/objetoprimitivo.h"
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

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

std::vector<string> FileController::scenesFileNames()
{
    std::vector<std::string> files;

    QStringList arquivos = this->m_scenesDirectory.entryList(QStringList() << "*.csv", QDir::Files);
    std::vector<std::string> vector;
    foreach(QString filename, arquivos) {
        files.push_back(filename.toStdString());
    }

    return files;
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

bool FileController::saveScene(std::vector<Objeto *> objetos)
{
    std::string generatedFileName;
    std::string dateTime = QDateTime::currentDateTime().toString(Qt::ISODate).toStdString();

    generatedFileName = "Scenes/"+dateTime.append(".csv");

    if(!this->fileSavedName().empty()){
       generatedFileName = this->m_fileSavedName;
    }

    qDebug() << generatedFileName.c_str();
    return saveScene(generatedFileName, objetos);
}

bool FileController::saveScene(string fileName, std::vector<Objeto *> objetos)
{
    QFile fileSave(QString::fromStdString(fileName));
    if (!fileSave.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;
    QTextStream out(&fileSave);
    glutSetWindowTitle(fileName.c_str());
    for(Objeto *obj : objetos){
        if(obj->instance() == "3ds"){
            ObjectFile *objConverted = (ObjectFile*) obj;
            out << QString::fromStdString(objConverted->instance()) << ";"
                << QString::fromStdString(objConverted->fileName()) << ";"
                << QString::fromStdString(objConverted->nome()) << ";"
                << objConverted->a.x << ";"
                << objConverted->a.y << ";"
                << objConverted->a.z << ";"
                << objConverted->s.x << ";"
                << objConverted->s.y << ";"
                << objConverted->s.z << ";"
                << objConverted->t.x << ";"
                << objConverted->t.y << ";"
                << objConverted->t.z << ";" << "\n";
        }else if(obj->instance() == "primitivo"){
            ObjetoPrimitivo *objConverted = (ObjetoPrimitivo*) obj;
            out << QString::fromStdString(objConverted->instance()) << ";"
                << QString::fromStdString(objConverted->tipo()) << ";"
                << QString::fromStdString(objConverted->nome()) << ";"
                << objConverted->a.x << ";"
                << objConverted->a.y << ";"
                << objConverted->a.z << ";"
                << objConverted->s.x << ";"
                << objConverted->s.y << ";"
                << objConverted->s.z << ";"
                << objConverted->t.x << ";"
                << objConverted->t.y << ";"
                << objConverted->t.z << ";" << "\n";
        }
    }

    fileSave.close();

    return true;
}

std::vector<Objeto *> FileController::openScene(string fileName)
{
    std::vector<Objeto *> objetosCarregados;
    QFile fileOpen(QString::fromStdString(fileName));
    if (!fileOpen.open(QIODevice::ReadOnly | QIODevice::Text))
        return objetosCarregados;

    glutSetWindowTitle(fileName.c_str());
    QTextStream in(&fileOpen);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list = line.split(";");
        if(list[0] == "3ds"){
            ObjectFile *obj = new ObjectFile(list[1].toStdString());
            obj->nome() = list[2].toStdString();
            //rotações
            obj->a.x = list[3].toFloat();
            obj->a.y = list[4].toFloat();
            obj->a.z = list[5].toFloat();
            //scalas
            obj->s.x = list[6].toFloat();
            obj->s.y = list[7].toFloat();
            obj->s.z = list[8].toFloat();
            //translações
            obj->t.x = list[9].toFloat();
            obj->t.y = list[10].toFloat();
            obj->t.z = list[11].toFloat();

            objetosCarregados.push_back(obj);
        }else if(list[0] == "primitivo"){
            ObjetoPrimitivo *obj = new ObjetoPrimitivo(list[1].toStdString());
            obj->nome() = list[2].toStdString();
            //rotações
            obj->a.x = list[3].toFloat();
            obj->a.y = list[4].toFloat();
            obj->a.z = list[5].toFloat();
            //scalas
            obj->s.x = list[6].toFloat();
            obj->s.y = list[7].toFloat();
            obj->s.z = list[8].toFloat();
            //translações
            obj->t.x = list[9].toFloat();
            obj->t.y = list[10].toFloat();
            obj->t.z = list[11].toFloat();

            objetosCarregados.push_back(obj);
        }
    }

    fileOpen.close();
}

string FileController::fileSavedName()
{
    return this->m_fileSavedName;
}

