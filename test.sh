#!/bin/bash
if [ "$#" -ne 2 ]; then
	echo "usage: $0 lenght_of_array amount_of_checks" >&2; exit 1
	exit 1
fi
lenght_of_array=$1
amount_of_checks=$2
if [[ "$lenght_of_array" -lt 1 || "$lenght_of_array" -gt 100000 ]] ; then
	echo "error: lenght_of_array must be > 0 and < 100000" >&2; exit 1
fi
if [[ "$amount_of_checks" -lt 1 || "$amount_of_checks" -gt 10000 ]] ; then
	echo "error: amount_of_checks must be > 0 and < 10000" >&2; exit 1
fi

minimum=1000000000
maximum=-1
sum_of_result_comands=0
for i in `seq 1 $amount_of_checks`
do
	random_numbers=`ruby -e "puts (1..$lenght_of_array).to_a.shuffle.join(' ')"`
	IFS=
	output_commands=$(./push_swap $random_numbers)
	if [[ $output_commands != "" ]]; then
		output_commands+="\n"
	fi

	res=$(printf "$output_commands" | ./checker $random_numbers)
	if [[ $res == "OK" ]]; then
		number_of_result_comands=`printf "$output_commands" | wc -l | tr -d '[:space:]'`
		sum_of_result_comands=$(($sum_of_result_comands + $number_of_result_comands))
		if [ $number_of_result_comands -gt $maximum ]; then
			maximum=$number_of_result_comands
		fi
		if [ $number_of_result_comands -lt $minimum ]; then
			minimum=$number_of_result_comands
		fi
	else
		echo $random_numbers "\nDID NOT SORT CORRECTLY" >&2; exit 2
	fi
done

echo "average " $(echo "scale=2; $sum_of_result_comands/$amount_of_checks" | bc)
echo "maximum " $maximum
echo "minimum " $minimum
