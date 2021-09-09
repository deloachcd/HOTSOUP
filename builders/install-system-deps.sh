#!/bin/sh -e

prompt_yes_no() {
	PROMPT_QUESTION="$1"
	QUESTION_ANSWERED_PROPERLY=
	while test -z $QUESTION_ANSWERED_PROPERLY; do
		read -p "$PROMPT_QUESTION (y/n) " USER_ANSWER
		if test "$USER_ANSWER" = y; then
			QUESTION_ANSWERED_PROPERLY=1
			RETVAL=0
		elif test "$USER_ANSWER" = n; then
			QUESTION_ANSWERED_PROPERLY=1
			RETVAL=1
		else
			echo "Come on now, just put a 'y' or an 'n'."
		fi
	done
}

# No system dependencies yet! (hopefully never)
SYSTEM_DEPS=""

if test -z "$SYSTEM_DEPS"; then
	echo "No system dependencies required right now, and hopefully never will be."
	exit 0
fi

if ! cat /etc/os-release | grep "Debian" 1>/dev/null; then
	echo "Error: this script only supports Debian."
	exit 1
fi

if prompt_yes_no "Install system dependencies for building this project?"; then
	sudo apt install -y $SYSTEM_DEPS
fi
