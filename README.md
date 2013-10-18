remembrancer_pi
===============

Lightweight Open CPN plugin to play an alert sound every X seconds, 
repeatedly, when the Autopilot is engaged, designed to be consumed
on low-powered devices such as the Raspberry Pi.

The plugin currently monitors the OCPN JSON message stream, looking for 
OCPN_RTE_ACTIVATED messages. If a route is activated, this message will 
be broadcast.

