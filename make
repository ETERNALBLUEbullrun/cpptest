NAME="main"
INPUTS="$NAME.cpp"
OUTBIN="$NAME.o"

[ -n "$IGNOREWARN" ] || IGNOREWARN=0
set -x #echo sh execution
[ "$IGNOREWARN" -gt 0 ] || CXXFLAGS+="-Wall -Werror"
CPPFLAGS+="-o $OUTBIN -lsqlite3"
test -f "$OUTBIN" && mv "$OUTBIN" "$OUTBIN.bak"
ctags -R
if hash clang++ 2>/dev/null; then
	if [ "$IGNOREWARN" -gt 0 ] ||\
			(clang-check -analyze $INPUTS -- $CXXFLAGS -Wno-extra-tokens); then
		clang++ $INPUTS $CXXFLAGS $CPPFLAGS
	fi
else
	g++ $INPUTS $CXXFLAGS $CPPFLAGS
fi
if test -f "$OUTBIN"; then
	chmod u+x "$OUTBIN"
	echo `./"$OUTBIN"`
	DBNAME="$NAME.db"
	./"$OUTBIN" $DBNAME &&
		rm "$DBNAME"
	./"$OUTBIN" Invalid+DB^name
fi

