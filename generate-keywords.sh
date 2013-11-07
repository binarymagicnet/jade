#!/bin/sh

# KEYWORDS
KEYWORDS=$(ack '#define (\w+.|\w+)' cppbas.inc  --output='$1')
KEYWORDS+=$(ack '^FUNCTION \w+ (\w+.|\w+)' cppbasrt.inc  --output='$1')
KEYWORDS+='\n'$(ack '^SUB (\w+)' cppbasrt.inc  --output='$1')

# FUNCTION/SUB PROTOTYPES
PROTO=$(ack '^FUNCTION \w+ (.+\))' cppbasrt.inc  --output='$1')' '
PROTO+='\n'$(ack '^SUB (.+\))' cppbasrt.inc  --output='$1')
#

# SAVE SORTED KEYWORDS/PROTOTYPES
echo "$KEYWORDS" | sort > Keywords.txt
echo "$PROTO" | sort > Prototypes.txt
echo "Done."

