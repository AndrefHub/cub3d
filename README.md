# pac3D

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
