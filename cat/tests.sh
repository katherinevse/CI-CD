#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

s21_command=(
    "./s21_cat"
    )
sys_command=(
    "cat"
    )

manual=(
"-b test_files/test_1_cat.txt"
"-e test_files/test_2_cat.txt"
"-n test_files/test_3_cat.txt"
"-s test_files/test_4_cat.txt"
"-t test_files/test_5_cat.txt"
"-v test_files/test_5_cat.txt"
)

gnu=(
"--number-nonblank test_files/test_1_cat.txt"
"-E test_files/test_1_cat.txt"
"--number test_files/test_2_cat.txt"
"--squeeze-blank test_files/test_4_cat.txt"
"-T test_files/test_1_cat.txt"
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
echo "TESTS WITH SHORT FLAGS"
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

##############################
echo "^^^^^^^^^^^^^^^^^^^^^^^"
echo "TESTS WITH GNU FLAGS"
echo "^^^^^^^^^^^^^^^^^^^^^^^"
printf "\n"
SUCCESS=0
FAIL=0
COUNTER=0

for i in "${gnu[@]}"
do
    var="-"
    run_test $i
done
printf "\n"

echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"


if [ $FAIL != 0 ]; then
    echo "CAT TESTS ARE FAILED!"
    echo $FAIL >> ../test_result.txt
else
    echo "CAT TESTS ARE PASSED!"
fi
