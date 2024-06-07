if [ ! -f ./runme ]; then
	make
fi

orig=$(cat input)
new=$(./runme < input)

diff -Bw <(echo "$orig") <(echo "$new")