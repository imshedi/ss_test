#!/bin/bash

loglevel=4

# Logs the message as a warning.
#
# It is printed only if the $loglevel is set above 1.
#
# Args:
#   msg: string: message to be printed
pr_warn()
{
        local msg="$1"

        if [[ $loglevel -gt 1 ]]; then
                echo -e "WARNING: ${msg}"
        fi
}

# Logs the message as a informational.
#
# It is printed only if the $loglevel is set above 2.
#
# Args:
#   msg: string: message to be printed
pr_info()
{
        local msg="$1"

        if [[ $loglevel -gt 2 ]]; then
                echo -e "INFO: ${msg}"
        fi
}

# Logs the message as an error.
#
# Args:
#   msg: string: message to be printed
pr_err()
{
        local msg="$1"

        echo -e "ERROR: ${msg}"
}

# Logs the message as a debug information.
#
# It is printed only if the $loglevel is set above 3.
#
# Args:
#   msg: string: message to be printed
pr_dbg()
{
        local msg="$1"

        if [[ $loglevel -gt 3 ]]; then
                echo -e "DEBUG: ${msg}"
        fi
}
