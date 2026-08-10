#ifndef UART_PROTOCOL_HPP
#define UART_PROTOCOL_HPP

#include <cstdint>

#include "protocol.h"

namespace uart
{
static constexpr std::size_t BAUD_RATE = UART_BAUD_RATE;
#undef UART_BAUD_RATE

#define ENUM_MEMBER(name, value) name = value,
enum class Message
{
    UART_MESSAGE_LIST(ENUM_MEMBER)
};
enum class RobotID
{
    ARC_ROBOT_ID_LIST(ENUM_MEMBER)
};
#undef ENUM_MEMBER

using TurretAimData = uart_turret_aim_t;
using OdometryData = uart_odometry_t;
using TurretOdometryData = uart_turret_odometry_t;
using ChassisOdometryData = uart_chassis_odometry_t;
using AprilTagLocalizationData = uart_localization_t;

}  // namespace uart

#endif  // #ifndef UART_PROTOCOL_HPP
