#!/bin/sh

which stat > /dev/null

if [ $? -eq 1 ]; then
	echo "command 'stat' not found"
	exit 2
fi

i=0

for line in $(find . -iname '*.blip'); do
	name=`echo "$line" | sed "s/\.blip$//g"`
	blip=$name.blip
	mp3=$name.mp3
	wav=$name~.wav
	bliptime=`stat -f '%c' $blip`
	mp3time=`stat -f '%c' $mp3`

	if [[ ! -e $mp3 || bliptime -gt mp3time ]]; then
		echo "Rendering $blip..."
		bliplay -yo $wav $blip 1&> /dev/null
		ffmpeg -loglevel panic -y -i $wav -q:a 1 $mp3
		unlink $wav
		let i="$i+1"
	fi
done

if [ $i -gt 0 ]; then
	echo "Done for $i files"
else
	echo "Nothing to do"
fi
