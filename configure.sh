:
# run fonterizer on all font files

(
    cd ttf
    for ARCHIVE in *.zip
    do
        unzip -o $ARCHIVE
    done

    [ ! -d 3270 ] && mkdir 3270
    mv 3270*.ttf 3270
)

FONTLIST=include/fontlist.h

echo "namespace fontlib" > $FONTLIST
echo "{" >> $FONTLIST

find ttf -name '*.ttf' -print|while read TTF
do
    BASE=`basename "$TTF" .ttf`
    case "${BASE}" in
        "3270-Medium 500")
            FONT=ibm3270m
            ;;
        "3270 Narrow 500")
            FONT=ibm3270n
            ;;
        "3270 Semi-Narrow 500")
            FONT=ibm3270s
            ;;
        cmu*)
            FONT=${BASE}
            ;;
    esac
    for SIZE in 14 15 16 18 20 24 28 32 36 40 44 48
    do
        NAME=${FONT}_${SIZE}
        TARGET=src/${NAME}.cpp
        echo ${FONT} ${SIZE}
        Fonterizer --name=$NAME --size=$SIZE "$TTF" > $TARGET
        echo "extern const font_t& ${FONT}_${SIZE};" >> $FONTLIST
    done
done

echo "}" >> $FONTLIST

exit 0
