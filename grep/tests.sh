#!/bin/bash
SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

s21_command=(
    "./s21_grep"
    )
sys_command=(
    "grep"
    )

manual=(
"for test_files/test_1_grep.txt test_files/test_2_grep.txt"
"-e int test_files/test_4_grep.txt"
"-i INT test_files/test_4_grep.txt"
"-v Okay test_files/test_5_grep.txt"
"-c Okay test_files/test_5_grep.txt"
"-l str test_files/test_1_grep.txt test_files/test_5_grep.txt"
"-n Okay test_files/test_5_grep.txt"
"-h int test_files/test_4_grep.txt test_files/test_5_grep.txt"
"-s int test_files/test_777_grep.txt"
"-f test_files/test_6_grep.txt test_files/test_7_grep.txt"
"-o int test_files/test_4_grep.txt"
"-iv int test_files/test_4_grep.txt"
"-in int test_files/test_4_grep.txt"
"-cv int test_files/test_4_grep.txt"
"-lv int test_files/test_2_grep.txt test_files/test_3_grep.txt test_files/test_4_grep.txt"
"-ho int test_files/test_2_grep.txt test_files/test_4_grep.txt"
"-nf test_files/test_6_grep.txt test_files/test_7_grep.txt"

)

run_test() {
    param=$(echo "$@" | sed "s/FLAGS/$var/")
    "${s21_command[@]}" $param > "${s21_command[@]}".log
    "${sys_command[@]}" $param > "${sys_command[@]}".log
    DIFF="$(diff -s "${s21_command[@]}".log "${sys_command[@]}".log)"
    let "COUNTER++"
    if [ "$DIFF" == "Files "${s21_command[@]}".log and "${sys_command[@]}".log are identical" ]
    then
        let "SUCCESS++"
        echo "$COUNTER - Success $param"
    else
        let "FAIL++"
        echo "$COUNTER - Fail $param"
    fi
    rm -f "${s21_command[@]}".log "${sys_command[@]}".log
}

echo "^^^^^^^^^^^^^^^^^^^^^^^"
echo "TESTS"
echo "^^^^^^^^^^^^^^^^^^^^^^^"
printf "\n"


for i in "${manual[@]}"
do
    var="-"
    run_test "$i"
done

printf "\n"
echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"


if [ $FAIL != 0 ]; then
    echo "GREP TESTS ARE FAILED!"
    echo $FAIL >> ../test_result.txt
else
    echo "GREP TESTS ARE PASSED!"
fi
