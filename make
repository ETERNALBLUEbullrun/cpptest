NAME="main"
INPUTS="$NAME.cpp"
OUTBIN="$NAME.o"

set -x #echo sh execution
CXXFLAGS+="-Wall -Werror"
CPPFLAGS+="-o $OUTBIN -lsqlite3"
test -f "$OUTBIN" && mv "$OUTBIN" "$OUTBIN.bak"
ctags -R
if hash clang++ 2>/dev/null; then
	if (clang-check -analyze $INPUTS -- $CXXFLAGS -Wno-extra-tokens); then
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

