# Net-Room
An ultrasonic sensor-driven occupancy monitoring system with visual and audio alerts for room capacity control

## Project Overview

This project uses two ultrasonic sensors to count the people leaving and entering a room. If the people in the room is less than the capacity then the box will emit a green light. If the room exceeds the capacity then the green light turns off, a red light turns on, and a tune or beeping begins to be played (whichever the user prefers). Once the room returns back to below capacity the red light turns off, the tune or beeping stops playing, and the green light turns back on. The design's main function is to count the net amount of people in a room, and make sure that the people are alerted when the max amount of people in the room is surpassed.

## How it was built

This project was built using an Arduino UNO board, two ultrasonic sensors, two led's, and one buzzer. 
