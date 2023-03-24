# pac3D

<p align="center">
<a href="https://youtu.be/mTbOpzq9PrI" target="_blank"><img src="https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExYjhiMDVmMmNhZmI1NmJjNDQ2MjRhNjQ2ZDA3NmIyMTU2MzA0ZjRjZCZjdD1n/P5D0Zq1YTsU6Qd3RBX/giphy.gif" width=1727></a>
</p>
</div>

Ray-casting project inspired by two legendary games: [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) and [Pac-Man](https://en.wikipedia.org/wiki/Pac-Man).

Written in C using [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) and [cute_sound](https://github.com/RandyGaul/cute_headers).

## Installation

#### Download:
```bash
git clone --recurse-submodules https://github.com/AndrefHub/cub3d.git && cd cub3d
```

#### Build:
```bash
make         # Mandatory part
```
```bash
make bonus   # Bonus part
```

#### Run:
```bash
./cub3D "valid map filename"
```
```bash
./pac3D "valid map filename"
```

## Bundled maps

"maps/e1m1.cub" - map for mandatory part \
"maps/pacman.cub" - map for bonus part, replicates map from original Pac-Man game

## License

[MIT](LICENSE)
