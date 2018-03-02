type grid = list(list(bool));

type position = (int, int);

let safe_index = (len, i) => i === (-1) ? len - 1 : i === len ? 0 : i;

let map_grid = (fn: (position, bool, grid) => bool, grid) : grid =>
  List.(
    mapi((y, row) => row |> mapi((x, tile) => fn((y, x), tile, grid)), grid)
  );

let make_blank_grid = (size: int) : grid =>
  Array.(make(size, make(size, false) |> to_list) |> to_list);

let make_random_grid = (size: int, seed: int) : grid => {
  Random.init(seed);
  size |> make_blank_grid |> map_grid((_, _, _) => Random.int(10) > 7);
};

let get_tile = ((x, y): position, g: grid) : bool => {
  let safe = safe_index(List.length(g));
  let x' = safe(x);
  let y' = safe(y);
  List.(nth(nth(g, y'), x'));
};

let get_neighbours = ((y, x): position) : list(position) => [
  (y - 1, x - 1),
  (y - 1, x),
  (y - 1, x + 1),
  (y, x - 1),
  (y, x + 1),
  (y + 1, x - 1),
  (y + 1, x),
  (y + 1, x + 1)
];

let count_living_neighbours = (position, g: grid) =>
  position
  |> get_neighbours
  |> List.fold_left((count, p) => get_tile(p, g) ? count + 1 : count, 0);

let will_live = (score: ref(int), p: position, isAlive: bool, g: grid) : bool => {
  let n = count_living_neighbours(p, g);
  let it_lives = isAlive ? n >= 2 && n <= 3 : n === 3;
  if (it_lives && ! isAlive) {
    score := score^ + 1;
  };
  it_lives;
};

let next_generation = (score: ref(int), g: grid) : grid =>
  g |> map_grid(will_live(score));

let toggle_tile = ((x, y): position) =>
  map_grid(((x', y'), isAlive, _) =>
    x === x' && y === y' ? ! isAlive : isAlive
  );