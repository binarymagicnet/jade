#!/bin/sh

# KEYWORDS
KEYWORDS=$(ack '#define (\w+.|\w+)' header.inc  --output='$1')
KEYWORDS+=$(ack '^FUNCTION \w+ (\w+.|\w+)' runtime.inc  --output='$1')
KEYWORDS+='\n'$(ack '^SUB (\w+)' runtime.inc  --output='$1')

# FUNCTION/SUB PROTOTYPES
PROTO=$(ack '^FUNCTION \w+ (.+\))' runtime.inc  --output='$1')' '
PROTO+='\n'$(ack '^SUB (.+\))' runtime.inc  --output='$1')
#

# SAVE SORTED KEYWORDS/PROTOTYPES
echo "$KEYWORDS" | sort > Keywords.txt
echo "$PROTO" | sort > Prototypes.txt
echo "Done."

