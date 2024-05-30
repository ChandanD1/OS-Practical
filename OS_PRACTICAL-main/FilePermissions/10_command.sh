#!/bin/zsh

# Check if the user provided a directory to back up
if [ -z "$1" ]; then
    echo "Usage: $0 <directory_to_backup>"
    exit 1
fi

# Get the directory to back up from the first argument
DIR_TO_BACKUP="$1"

# Check if the provided directory exists
if [ ! -d "$DIR_TO_BACKUP" ]; then
    echo "Error: Directory '$DIR_TO_BACKUP' does not exist."
    exit 1
fi

# Create a timestamp for the backup
TIMESTAMP=$(date +%Y%m%d%H%M%S)

# Define the backup directory name
BACKUP_DIR="${DIR_TO_BACKUP}_backup_${TIMESTAMP}"

# Create the backup using the cp command
cp -r "$DIR_TO_BACKUP" "$BACKUP_DIR"

# Verify if the backup was successful
if [ $? -eq 0 ]; then
    echo "Backup of '$DIR_TO_BACKUP' was created successfully in '$BACKUP_DIR'."
else
    echo "Error: Backup of '$DIR_TO_BACKUP' failed."
fi

