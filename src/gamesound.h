/*
 *
 * This file is part of JAG, Puzzle game where the goal is to break all
 * the target pieces in each level and do this before the time runs out.
 *
 * Many thanks to XlabSoft & Ind. Infosystems, the originals authors of JAG.
 *
 * Copyright holder 2009-2012 Developed by XlabSoft & Industrial Infosystems
 * Work continued by 2017-2018 Carlos Donizete Froes [a.k.a coringao]
 *
 * JAG is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * JAG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JAG. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef GAMESOUND_H
#define GAMESOUND_H

#include <QList>
#include <QTimer>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class GameSound : public QObject
{
    Q_OBJECT

public:
    GameSound();
    ~GameSound();

    enum Sounds {
        sndItemDisappear = 0,
        sndSmallHammer = 1,
        sndUnblock = 2,
        sndHammer = 3,
        sndBigHammer = 4,
        sndBomb = 5,
        sndRow = 6,
        sndRandomKill = 7,
        sndMixer = 8,
        sndTwin = 9,
        sndClock = 10,
        sndBonus = 11,
        sndNewItem = 12,
        sndTarget = 13,
        sndLevelStart = 14,
        sndLevelFail = 15,
        sndLevelWon = 16,
        sndBeep = 17,
        sndBonusGot = 18,
        sndTool = 19
    };

    Mix_Chunk* loadSound(const QString &filename);
    void playSound(int index, int loops = 1);
    void stopSound(int index);
    void stopAllSounds();
    void setChannelVolume(int val, int ch = -1);
    int soundVolume() const { return channel_vol; }

    void loadMusic(const QString &filename);
    void playMusic();
    void stopMusic();
    void setMusicVolume(int val);
    int musicVolume() const { return music_vol; }

    inline bool isMusicEnabled() const { return musicEnabled; }
    void enableMusic(bool on = true);

private slots:
    void checkPlayMusic();

signals:
    void musicFinished();

private:
    QList<Mix_Chunk*> m_sounds;

    int music_vol, channel_vol;

    Mix_Music *music;
    QTimer *myTimer;
    bool musicEnabled, musicPlaying;
};

extern GameSound* sndEngine;

#endif // GAMESOUND_H
