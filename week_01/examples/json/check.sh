if [ ! -f ./runme ]; then
	make
fi

orig=$(cat input | jq --sort-keys)
new=$(./runme < input | jq --sort-keys)

diff <(echo "$orig") <(echo "$new")