#include "Message.h"

Message::Message()
{
}

Message::Message(const std::string &nick, const PlayerState &playerState) : nick(nick), playerState(playerState)
{
}

void Message::to_bin()
{
    alloc_data(sizeof(MessageType) + NICK_SIZE);

    memset(_data, 0, sizeof(MessageType) + NICK_SIZE);

    // Serializar los campos type, nick y message en el buffer _data
    // Type
    memcpy(_data, (void *)&type, sizeof(type));

    // Nick
    char *pos = _data + sizeof(type);
    nick[NICK_SIZE - 1] = '\0';
    memcpy(pos, nick.c_str(), NICK_SIZE);

    //PlayerState TODO
}

int Message::from_bin(char *data)
{
    try
    {
        alloc_data(sizeof(MessageType) + NICK_SIZE);

        memcpy(static_cast<void *>(_data), data, sizeof(MessageType) + NICK_SIZE);

        //Reconstruir la clase usando el buffer _data
        // Type
        memcpy((void *)&type, _data, sizeof(type));

        // Nick
        char *pos = _data + sizeof(type);
        char name[NICK_SIZE];
        memcpy(name, pos, NICK_SIZE);
        name[NICK_SIZE - 1] = '\0';
        nick = name;

        //PlayerState TODO

        return 0;
    }
    catch (std::exception exception)
    {
    }

    return -1;
}