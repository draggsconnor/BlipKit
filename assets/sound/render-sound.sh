#!/bin/sh

for line in $(find . -iname '*.blip'); do
	name=`echo "$line" | sed "s/\.blip$//g"`
	echo "Rendering $name..."
	bliplay -m -o $name.wav $name.blip
	ffmpeg -loglevel panic -y -i $name.wav -q:a 1 $name.mp3
	unlink $name.wav
done

echo "Done"
