//
// Created by LL06p on 2024/2/16.
//

#ifndef MINECRAFTWSSLIB_EVENTS_H
#define MINECRAFTWSSLIB_EVENTS_H

#include <QObject>

namespace WSSLib {
    Q_NAMESPACE

    enum class EventType {
        NullEvent,
        EndOfDay,
        AgentCommand,
        AgentCreated,
        BlockBroken,
        BlockPlaced,
        BossKilled,
        ItemAcquired,
        ItemCrafted,
        ItemDestroyed,
        ItemDropped,
        ItemEnchanted,
        ItemSmelted,
        ItemUsed,
        MobInteracted,
        MobKilled,
        PlayerJoin,
        PlayerLeave,
        PlayerBounced,
        PlayerDied,
        PlayerMessage,
        PlayerTeleported,
        PlayerTransform,
        PlayerTravelled,
        PortalBuilt,
        PortalUsed,
    };

    Q_ENUM_NS(EventType)

    class Event {
    public:
        virtual ~Event() = default;
        enum EventType getType() {return type;}
    protected:
        enum EventType type = EventType::NullEvent;
    };
}

#endif //MINECRAFTWSSLIB_EVENTS_H
