#!/bin/bash

# Get the current directory
CURRENT_DIR=$(pwd)

# Make the jpa package to launch multiple instances

# Change directory to the location of each project and launch in a new terminal
gnome-terminal --working-directory="$CURRENT_DIR/backend/EurekaServer" -- mvn spring-boot:run &

gnome-terminal --working-directory="$CURRENT_DIR/backend/Player" -- mvn spring-boot:run &
gnome-terminal --working-directory="$CURRENT_DIR/backend/Chips" -- mvn spring-boot:run &
gnome-terminal --working-directory="$CURRENT_DIR/backend/Roulette" -- mvn spring-boot:run &
gnome-terminal --working-directory="$CURRENT_DIR/backend/BlackJack" -- mvn spring-boot:run &
gnome-terminal --working-directory="$CURRENT_DIR/backend/Security" -- /usr/bin/env /usr/lib/jvm/java-17-openjdk-amd64/bin/java @/tmp/cp_9oa85s4qj4a2c290gc20moabj.argfile org.ensimag.SecurityMain &
gnome-terminal --working-directory="$CURRENT_DIR/frontend" -- npm install && npm run start
