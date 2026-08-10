#ifndef UART_PROTOCOL_H
#define UART_PROTOCOL_H

#include <assert.h>
#include <stdint.h>

#define UART_BAUD_RATE 115200

// These are useful for declaring both C enums and CPP enums with single source of truth
// Can also easily create Enum -> String with these
#define ARC_ROBOT_ID_LIST(X) \
    X(INVALID, 0)            \
    X(RED_HERO, 1)           \
    X(RED_ENGINEER, 2)       \
    X(RED_SOLDIER_1, 3)      \
    X(RED_SOLDIER_2, 4)      \
    X(RED_SOLDIER_3, 5)      \
    X(RED_DRONE, 6)          \
    X(RED_SENTINEL, 7)       \
    X(RED_DART, 8)           \
    X(RED_RADAR_STATION, 9)  \
    X(BLUE_HERO, 101)        \
    X(BLUE_ENGINEER, 102)    \
    X(BLUE_SOLDIER_1, 103)   \
    X(BLUE_SOLDIER_2, 104)   \
    X(BLUE_SOLDIER_3, 105)   \
    X(BLUE_DRONE, 106)       \
    X(BLUE_SENTINEL, 107)    \
    X(BLUE_DART, 108)        \
    X(BLUE_RADAR_STATION, 109)

#define UART_MESSAGE_LIST(X)  \
    X(TURRET_AIM_DATA, 1)     \
    X(ROBOT_ID, 2)            \
    X(ALIVE, 3)               \
    X(ODOMETRY, 4)            \
    X(AUTO_PATH, 5)           \
    X(HEALTH, 6)              \
    X(REF_TURRET_DATA, 7)     \
    X(VISION_LOCALIZATION, 8) \
    X(FLY_SKY_DATA, 9)        \
    X(VT13_DATA, 10)          \
    X(RESTART_DETECTOR, 11)

typedef uint16_t uart_message_t;
enum
{
#define ENUM_MEMBER(name, val) UART_MESSAGE_##name = val,
    UART_MESSAGE_LIST(ENUM_MEMBER)
#undef ENUM_MEMBER
};

typedef uint16_t arc_robot_id_t;
enum
{
#define ENUM_MEMBER(name, val) ARC_ROBOT_ID_##name = val,
    ARC_ROBOT_ID_LIST(ENUM_MEMBER)
#undef ENUM_MEMBER
};

typedef struct
{
    float yaw;
    float pitch;
    float distance;
    arc_robot_id_t robot_id;
    uint8_t padding[2];
} uart_turret_aim_t;
static_assert(
    sizeof(uart_turret_aim_t) == sizeof(float) * 3 + sizeof(arc_robot_id_t) + 2,
    "Size mismatch");

typedef struct
{
    uint8_t robot_id;
} uart_robot_id_t;
static_assert(sizeof(uart_robot_id_t) == sizeof(uint8_t), "Size mismatch");

typedef struct
{
    float pitch;
    float yaw;
    float roll;
    float yaw_vel;
} uart_turret_odometry_t;
static_assert(sizeof(uart_turret_odometry_t) == sizeof(float) * 4, "Size mismatch");

typedef struct
{
    float vel_x;
    float vel_y;
} uart_chassis_odometry_t;
static_assert(sizeof(uart_chassis_odometry_t) == sizeof(float) * 2, "Size mismatch");

typedef struct
{
    uint32_t timestamp;
    uart_chassis_odometry_t chassis_data;
    uart_turret_odometry_t turret_data;
} uart_odometry_t;
static_assert(
    sizeof(uart_odometry_t) ==
        sizeof(uint32_t) + sizeof(uart_chassis_odometry_t) + sizeof(uart_turret_odometry_t),
    "Size mismatch");

typedef struct
{
    float start[2];
    float end[2];
    float start_control[2];
    float end_control[2];
    float length;
} uart_autopath_t;
static_assert(sizeof(uart_autopath_t) == sizeof(float) * 9, "Size mismatch");

typedef struct
{
    uint16_t health;
} uart_health_t;
static_assert(sizeof(uart_health_t) == sizeof(uint16_t), "Size mismatch");

typedef struct
{
    float pos_x;
    float pos_y;
    float heading;
    uint32_t timestamp;
} uart_localization_t;
static_assert(sizeof(uart_localization_t) == sizeof(float) * 3 + sizeof(uint32_t), "Size mismatch");

#endif  // #ifndef UART_PROTOCOL_H
