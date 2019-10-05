#!/bin/bash

tt()
{
        local SEC="$1"

	printf "Time taken: "

        local TMP=$(($SEC / 3600 / 24))
        (($TMP > 0)) && printf "$TMP day(s) "

        TMP=$(($SEC / 3600 % 24))
        (($TMP > 0)) && printf "$TMP hour(s) "

        TMP=$(($SEC / 60 % 60))
        (($TMP > 0)) && printf "$TMP minute(s) "

        TMP=$(($SEC % 60))
        echo "$TMP second(s) "
}

generate_file()
{
        local FNAME="$1"

        seq "$RANDOM" > "$FNAME"
}

test_op()
{
        local EXEC="$1"
        local FNAME="$2"

        local MD5="$(md5sum $FNAME)"

        "$EXEC" -c "$FNAME" > /dev/null && rm -f "$FNAME"

        "$EXEC" -d "$FNAME.lzw" > /dev/null

        if [ "$(md5sum $FNAME)" != "$MD5" ]; then
                echo $MD5
                echo $(md5sum $FNAME)
                printf "\nOperation failed for file: $FNAME\n"
                exit 1
        fi

        rm -f "$FNAME.lzw" "$FNAME"
}

LOG="testlog.txt"

run_sanity_tests()
{
        local EXEC="./lzw.out"

	make clean -s
	printf "*** Running clang ***\n"
	printf "*** clang log ***\n\n" > "$LOG"
	scan-build make -s &>> "$LOG"

	printf "*** Running cppcheck ***\n"
	printf "\n*** cppcheck log ***\n\n" >> "$LOG"
	cppcheck --quiet --suppress=missingIncludeSystem --enable=all \
		*.c &>> "$LOG"

	printf "*** Running valgrind ***\n"
	printf "\n*** valgrind log ***\n\n" >> "$LOG"
        for (( n = 1; n < 11 ; n++ )); do
                #local FNAME="$(printf %d $n)"
		local FNAME="sample.txt"

                rm -f "$FNAME"
                generate_file "$FNAME"

		valgrind -q --log-file="$LOG.tmp" --leak-check=full \
			"$EXEC" -c "$FNAME" > /dev/null

		cat "$LOG.tmp" >> "$LOG"

		valgrind -q --log-file="$LOG.tmp" --leak-check=full \
			"$EXEC" -d "$FNAME.lzw" > /dev/null

		cat "$LOG.tmp" >> "$LOG"

		rm -f "$FNAME.lzw" "$FNAME" "$LOG.tmp"
        done

	printf "*** Running checkpatch.pl ***\n"
	printf "\n*** checkpatch log ***\n\n" >> "$LOG"
	/usr/src/linux-headers-$(uname -r)/scripts/checkpatch.pl \
		-q -f -no-tree --ignore NEW_TYPEDEFS *.c *.h >> "$LOG"

	if grep -Fq "No bugs found." "$LOG" > /dev/null; then
		sed -i '/scan-build:/d' "$LOG"
	fi
}

main()
{
        local END=32
        local START=1
        local EXEC="./lzw.out"

        make -Bs
        for (( n = $START; n < $((END + 1)) ; n++ )); do
        echo -ne "Running basic operation test, iteration -> $n\r"

                #local FNAME="$(printf %d $n)"
		local FNAME="sample.txt"

		rm -f "$FNAME"
                generate_file "$FNAME"
                test_op "$EXEC" "$FNAME"
        done

	printf "\nBasic tests succeeded\n"
        tt "$SECONDS"

	SECONDS=0
	printf "\nRunning sanity tests\n\n"

	run_sanity_tests

	printf "\nSanity testing done, See $LOG for various logs\n"
        tt "$SECONDS"
        make clean -s
}

main
