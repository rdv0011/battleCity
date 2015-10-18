#include <QFileInfo>
#include <QDir>

#include "resourcesound.h"

ResourceSoundFile::ResourceSoundFile (const QString & respath, QObject *parent)
    : QFile (parent) {
    QFileInfo resource(respath);
    QDir files = QDir::current();

    if (!files.cd(kResourceDir)) {
        files.mkdir(kResourceDir);
    }

    files.cd(kResourceDir);

    setFileName(files.filePath(resource.fileName()));
    if (!exists()) {
        QFile resfile(respath);
        if(resfile.open(QIODevice::ReadOnly)) {
            if (open(QIODevice::ReadWrite)) {
                write(resfile.readAll());
                close();
            }
            resfile.close();
        }
    }
}
