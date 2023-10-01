#!/bin/bash
cd video_frames
#ffmpeg -framerate 60 -i screen_%04d.png -lavfi split[v],palettegen,[v]paletteuse sparks.gif
ffmpeg -f image2 -framerate 45 -i screen_%04d.png game_video.mp4
# ffmpeg -f image2 -framerate 45 -i screen_%04d.png game_video.gif
# mv game_video.gif ../
# rm *.png

