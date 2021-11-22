NAME="main"
INPUTS="$NAME.cpp"
OUTBIN="$NAME.o"

set -x #echo sh execution
WARN="-Wall -Werror"
FLAGS="-o $OUTBIN -lsqlite3 $WARN"
test -f "$OUTBIN" && mv "$OUTBIN" "$OUTBIN.bak"
ctags -R
if hash clang++ 2>/dev/null; then
	if clang-check -analyze $INPUTS -- $WARN -Wno-extra-tokens; then
		clang++ $INPUTS $FLAGS
	fi
else
	g++ $INPUTS $FLAGS
fi
if test -f "$OUTBIN"; then
	chmod u+x "$OUTBIN"
	echo `./"$OUTBIN"`
	DBNAME="$NAME.db"
	./"$OUTBIN" $DBNAME &&
		rm "$DBNAME"
	./"$OUTBIN" Invalid+DB^name
fi

