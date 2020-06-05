command="yes | /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)""
log="prog.log"
match="this is the what i want to match"

$command > "$log" 2>&1 &
pid=$!

while sleep 60
do
    if fgrep --quiet "$match" "$log"
    then
        kill $pid
        exit 0
    fi
done
