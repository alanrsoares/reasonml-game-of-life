type grid = list(list(bool));

type position = {
  y: int,
  x: int
};

let safe_index = (len, i) => i === (-1) ? len - 1 : i === len ? 0 : i;

let map_grid = (fn, g: grid) =>
  List.mapi((y, row) => row |> List.mapi((x, tile) => fn({y, x}, tile, g)), g);

let make_blank_grid = (size: int) : grid =>
  Array.to_list(
    Array.init(size, (_) => Array.init(size, (_) => false) |> Array.to_list)
  );

let make_random_grid = (size: int, seed: int) : grid => {
  Random.init(seed);
  size |> make_blank_grid |> map_grid((_, _, _) => Random.bool());
};

let get_tile = ({x, y}: position, g: grid) : bool => {
  let safe = safe_index(List.length(g));
  let x' = safe(x);
  let y' = safe(y);
  List.nth(List.nth(g, y'), x');
};

let count_living_neighbours = ({x, y}: position, g: grid) => {
  let positions = [
    {y: y - 1, x: x - 1},
    {y: y - 1, x},
    {y: y - 1, x: x + 1},
    {y, x: x - 1},
    {y, x: x + 1},
    {y: y + 1, x: x - 1},
    {y: y + 1, x},
    {y: y + 1, x: x + 1}
  ];
  positions
  |> List.map(p => get_tile(p, g))
  |> List.filter(v => v)
  |> List.length;
};

let will_live = (p: position, isAlive: bool, g: grid) : bool => {
  let n = count_living_neighbours(p, g);
  isAlive ? n >= 2 && n <= 3 : n === 3;
};

let next_generation = map_grid(will_live);

let toggle = (p: position) =>
  map_grid(({y, x}, isAlive, _g) =>
    x === p.x && y === p.y ? ! isAlive : isAlive
  );