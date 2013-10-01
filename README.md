remembrancer_pi
===============

Simple Open CPN plugin to play an alert sound every X seconds, 
repeatedly, when the Autopilot is engaged.

The plugin currently monitors the NMEA stream, looking for $ECAPB... 
messages. If a route is active, and set up for an autopilot export,
this message will be broadcast.
