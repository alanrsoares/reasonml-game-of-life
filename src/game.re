type grid = list(list(bool));

type position = (int, int);

let safe_index = (len, i) => i === (-1) ? len - 1 : i === len ? 0 : i;

let map_grid = (fn: (position, bool, grid) => bool, grid) : grid =>
  List.(
    mapi(
      (y, row) => row |> mapi((x, tile) => fn((y, x), tile, grid)),
      grid,
    )
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
  List.(nth(nth(g, x'), y'));
};

let get_neighbours = ((y, x): position, grid) : list(bool) =>
  [
    (y - 1, x - 1),
    (y - 1, x),
    (y - 1, x + 1),
    (y, x - 1),
    (y, x + 1),
    (y + 1, x - 1),
    (y + 1, x),
    (y + 1, x + 1),
  ]
  |> List.map(p => get_tile(p, grid));

let count_living_neighbours = (position, grid) =>
  List.(
    grid
    |> get_neighbours(position)
    |> filter(Utils.identity)  /* only live cells */
    |> length
  );

let will_live = (score: ref(int), position, is_alive: bool, grid) : bool => {
  let it_lives =
    grid
    |> count_living_neighbours(position)
    |> (n => is_alive ? n >= 2 && n <= 3 : n === 3);
  if (it_lives && ! is_alive) {
    score := score^ + 1;
  };
  it_lives;
};

let next_generation = (score: ref(int), grid) =>
  grid |> map_grid(will_live(score));

let toggle_tile = ((x, y): position) =>
  map_grid(((x', y'), is_alive, _) =>
    x === x' && y === y' ? ! is_alive : is_alive
  );