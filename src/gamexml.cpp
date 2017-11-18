#include "gameprofile.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>

void GameProfile::saveXml()
{
    QFile f(userPath + "users.xml");
    if (!f.open(QFile::WriteOnly | QFile::Text))
        return;

    QXmlStreamWriter xsw;
    xsw.setDevice(&f);

    xsw.setAutoFormatting(true);

    xsw.writeStartDocument();
    xsw.writeDTD("<!DOCTYPE jagprofile>");
    xsw.writeStartElement("profile");
    xsw.writeAttribute("version", "1.0");

    // profile common settings
    xsw.writeTextElement("activeplayer", QString("%1").arg(m_current));
    xsw.writeTextElement("acceleration", QString("%1").arg(m_accel));

    // players
    for (int i = 0; i < m_players.count(); i++) {
        PlayerInfo *pl = m_players.at(i);
        // player info
        xsw.writeStartElement("player");
        xsw.writeAttribute("index", QString("%1").arg(i));

        xsw.writeTextElement("name", pl->name);
        xsw.writeTextElement("theme", pl->theme);
        xsw.writeTextElement("currentlevelpack", pl->currentlevelpack);
        xsw.writeTextElement("fullscreen", QString("%1").arg(pl->m_fullscreen));
        xsw.writeTextElement("screenWidth", QString("%1").arg(pl->m_width));
        xsw.writeTextElement("screenHeight", QString("%1").arg(pl->m_height));
        xsw.writeTextElement("soundVolume", QString("%1").arg(pl->soundVolume));
        xsw.writeTextElement("musicVolume", QString("%1").arg(pl->musicVolume));
        xsw.writeTextElement("musicEnabled", QString("%1").arg(pl->musicEnabled));

        // save window position
        xsw.writeTextElement("posx", QString("%1").arg(pl->x));
        xsw.writeTextElement("posy", QString("%1").arg(pl->y));
        // save screen number
        xsw.writeTextElement("screen", QString("%1").arg(pl->screen));

        // level packs
        for (int j = 0; j < pl->levelpacks.count(); j++) {
            LevelPackInfo *lpi = pl->levelpacks.at(j);

            xsw.writeStartElement("levelpack");
            xsw.writeAttribute("index", QString("%1").arg(j));

            xsw.writeTextElement("name", lpi->levelpack);
            xsw.writeTextElement("score", QString("%1").arg(lpi->score));
            xsw.writeTextElement("localScore", QString("%1").arg(lpi->localScore));
            xsw.writeTextElement("level", QString("%1").arg(lpi->level));
            xsw.writeTextElement("time_bonus", QString("%1").arg(lpi->time_bonus));
            xsw.writeTextElement("speed_bonus", QString("%1").arg(lpi->speed_bonus));
            xsw.writeTextElement("score_bonus", QString("%1").arg(lpi->score_bonus));
            xsw.writeTextElement("speed_mag_bonus", QString("%1").arg(lpi->speed_mag_bonus));
            xsw.writeTextElement("next_tool", QString("%1").arg(lpi->next_tool));
            xsw.writeTextElement("diff", QString("%1").arg(lpi->diff));
            xsw.writeTextElement("mode", QString("%1").arg(lpi->mode));

            // items info
            for (int k = 0; k < lpi->items.count(); k++) {
                xsw.writeStartElement("item");
                xsw.writeAttribute("index", QString("%1").arg(k));

                xsw.writeTextElement("tc", QString("%1").arg(lpi->items.at(k).totalCount));
                xsw.writeTextElement("lc", QString("%1").arg(lpi->items.at(k).localCount));

                xsw.writeEndElement();  // item
            }

            xsw.writeEndElement();  // levelpack
        }

        xsw.writeEndElement();  // player
    }

    xsw.writeEndElement();  // profile
    xsw.writeEndDocument();
}

void GameProfile::loadXml()
{
    QFile f(userPath + "users.xml");
    if (!f.open(QFile::ReadOnly | QFile::Text))
        return;
    QXmlStreamReader xsr;
    xsr.setDevice(&f);

    // read version
    while (!xsr.atEnd()) {
        xsr.readNext();
        if (xsr.isStartElement()) {
            if (xsr.name() == "profile" && xsr.attributes().value("version") == "1.0")
                break;
            else
                return;
        }
    }

    // read profile
    while (!xsr.atEnd()) {
        xsr.readNext();

        if (xsr.isEndElement())
            break;

        if (xsr.isStartElement()) {
            if (xsr.name() == "activeplayer")
                m_current = xsr.readElementText().toInt();
            else if (xsr.name() == "acceleration")
                m_accel = xsr.readElementText() == "0" ? false : true;
            else if (xsr.name() == "player")
                readXmlPlayer(xsr);
            else
                readXmlUnknownElement(xsr);
        }
    }
}

void GameProfile::readXmlUnknownElement(QXmlStreamReader &xsr)
{
    while (!xsr.atEnd()) {
        xsr.readNext();

        if (xsr.isEndElement())
            break;

        if (xsr.isStartElement())
            readXmlUnknownElement(xsr);
    }
}

void GameProfile::readXmlPlayer(QXmlStreamReader &xsr)
{
    PlayerInfo *pl = new PlayerInfo("");

    while (!xsr.atEnd()) {
        xsr.readNext();

        if (xsr.isEndElement())
            break;

        if (xsr.isStartElement()) {
            if (xsr.name() == "name")
                pl->name = xsr.readElementText();
            else if (xsr.name() == "theme")
                pl->theme = xsr.readElementText();
            else if (xsr.name() == "currentlevelpack")
                pl->currentlevelpack = xsr.readElementText();
            else if (xsr.name() == "fullscreen")
                pl->m_fullscreen = xsr.readElementText() == "0" ? false : true;
            else if (xsr.name() == "screenWidth")
                pl->m_width = xsr.readElementText().toInt();
            else if (xsr.name() == "screenHeight")
                pl->m_height = xsr.readElementText().toInt();
            else if (xsr.name() == "soundVolume")
                pl->soundVolume = xsr.readElementText().toInt();
            else if (xsr.name() == "musicVolume")
                pl->musicVolume = xsr.readElementText().toInt();
            else if (xsr.name() == "musicEnabled")
                pl->musicEnabled = xsr.readElementText() == "0" ? false : true;
            else if (xsr.name() == "posx")
                pl->x = xsr.readElementText().toInt();
            else if (xsr.name() == "posy")
                pl->y = xsr.readElementText().toInt();
            else if (xsr.name() == "screent")
                pl->screen = xsr.readElementText().toInt();
            else if (xsr.name() == "levelpack")
                readXmlLevelPack(xsr, pl);
            else
                readXmlUnknownElement(xsr);
        }
    }

    m_players.append(pl);
}

void GameProfile::readXmlLevelPack(QXmlStreamReader &xsr, PlayerInfo *pl)
{
    LevelPackInfo *lpi = new LevelPackInfo("");
    lpi->items.clear();

    while (!xsr.atEnd()) {
        xsr.readNext();

        if (xsr.isEndElement())
            break;

        if (xsr.isStartElement()) {
            if (xsr.name() == "name")
                lpi->levelpack = xsr.readElementText();
            else if (xsr.name() == "score")
                lpi->score = xsr.readElementText().toInt();
            else if (xsr.name() == "localScore")
                lpi->localScore = xsr.readElementText().toInt();
            else if (xsr.name() == "level")
                lpi->level = xsr.readElementText().toInt();
            else if (xsr.name() == "time_bonus")
                lpi->time_bonus = xsr.readElementText().toInt();
            else if (xsr.name() == "speed_bonus")
                lpi->speed_bonus = xsr.readElementText().toInt();
            else if (xsr.name() == "score_bonus")
                lpi->score_bonus = xsr.readElementText().toInt();
            else if (xsr.name() == "speed_mag_bonus")
                lpi->speed_mag_bonus = xsr.readElementText().toInt();
            else if (xsr.name() == "next_tool")
                lpi->next_tool = xsr.readElementText().toInt();
            else if (xsr.name() == "diff")
                lpi->diff = xsr.readElementText().toInt();
            else if (xsr.name() == "mode")
                lpi->mode = xsr.readElementText().toInt();
            else if (xsr.name() == "item")
                readXmlLevelItem(xsr, lpi);
            else
                readXmlUnknownElement(xsr);
        }
    }

    pl->addLevelPack(lpi);
}

void GameProfile::readXmlLevelItem(QXmlStreamReader &xsr, LevelPackInfo *lpi)
{
    ItemInfo ii;

    while (!xsr.atEnd()) {
        xsr.readNext();

        if (xsr.isEndElement())
            break;

        if (xsr.isStartElement()) {
            if (xsr.name() == "tc")
                ii.totalCount = xsr.readElementText().toInt();
            else if (xsr.name() == "lc")
                ii.localCount = xsr.readElementText().toInt();
            else
                readXmlUnknownElement(xsr);
        }
    }

    lpi->items.append(ii);
}
