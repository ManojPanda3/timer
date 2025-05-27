# General command description
complete -c timer -d 'A simple CLI timer with animated ASCII art'

# Option: -t, --title
complete -c timer \
    -s t -l title \
    -d 'Set a description/title for the task' \
    -r \
    -a TEXT

# Option: -f, --file
complete -c timer \
    -s f -l file \
    -d 'Specify a log file for completed tasks' \
    -r \
    -a FILENAME

# Option: -h, --help
complete -c timer \
    -s h -l help \
    -d 'Display this help message and exit' \
    -x
