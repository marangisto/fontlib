:
# run fonterizer on all font files

(
    cd ttf
    for ARCHIVE in *.zip
    do
        unzip $ARCHIVE
    done
)

FONTLIST=include/fontlist.h

echo "namespace fontlib" > $FONTLIST
echo "{" >> $FONTLIST

find ttf -name '*.ttf' -print|while read TTF
do
    FONT=`basename "$TTF" .ttf`
    echo $TTF $FONT
    for SIZE in 16 20 24 28 32 36 40 44 48
    do
        NAME=${FONT}_${SIZE}
        TARGET=src/${NAME}.cpp
        Fonterizer --name=$NAME --size=$SIZE "$TTF" > $TARGET
        echo "extern const font_t& ${FONT}_${SIZE};" >> $FONTLIST
    done
done

echo "}" >> $FONTLIST

exit 0
