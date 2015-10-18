#ifndef RESOURCESOUND_H
#define RESOURCESOUND_H

#include <QFile>
#include <QSound>

// This class saves file from resource to local file sytem.
// Helps to play sounds from resources with QSound class
class ResourceSoundFile : public QFile {

    const QString kResourceDir = "sounds";

public:
    // Constructor
    // respath: path of the resource in the resource file
    ResourceSoundFile (const QString &respath, QObject * parent = 0);
};

// Playes the sound using QSound. Provides factory method for ResourceSoundFile.
class ResourceSound : private ResourceSoundFile
{
public:
    // Constructor
    // respath: path of the resource in the resource file
    ResourceSound (const QString & respath, QObject * parent = 0)
    : ResourceSoundFile (respath, parent) { }

    // Instantinates object and play sound
    static void play(const QString& respath) {
        ResourceSound sound(respath);
        QSound::play(sound.fileName());
    }

    // Returns the file name
    QString getSoundFileName() const {
        return fileName();
    }
};

#endif // RESOURCESOUND_H
