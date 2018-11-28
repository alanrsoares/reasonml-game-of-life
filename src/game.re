type cell_state =
  | Dead
  | Alive;

type grid = array(array(cell_state));

type position = (int, int);

let safe_index = (len, i) => i < 0 ? len - 1 : i === len ? 0 : i;

let map_grid = (fn: (position, cell_state, grid) => cell_state, grid): grid =>
  Array.(
    mapi(
      (y, row) => row |> mapi((x, tile) => fn((y, x), tile, grid)),
      grid,
    )
  );

let make_blank_grid = (size: int): grid =>
  Array.(make(size, make(size, Dead)));

let make_random_grid = (size: int, seed: int): grid => {
  Random.init(seed);
  size
  |> make_blank_grid
  |> map_grid((_, _, _) => Random.int(10) > 7 ? Alive : Dead);
};

let get_tile = (grid, (y, x): position) => {
  let safe = safe_index(Array.length(grid));

  grid[safe(y)][safe(x)];
};

let get_neighbours = ((y, x): position, grid) =>
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
  |> List.map(grid->get_tile);

let count_living_neighbours = (grid, position) =>
  List.(
    grid
    |> get_neighbours(position)
    |> filter(c => c === Alive)  /* only live cells */
    |> length
  );

let will_live = (score: ref(int), position, cell_state: cell_state, grid) => {
  let neighbours = grid->count_living_neighbours(position);
  let next_state =
    switch (cell_state, neighbours) {
    | (Alive, 2 | 3) => Alive
    | (Dead, 3) =>
      score := score^ + 1;
      Alive;
    | _ => Dead
    };

  next_state;
};

let next_generation = (score: ref(int)) => map_grid(will_live(score));

let toggle_tile = (grid, (y, x): position) => {
  let safe = safe_index(grid->Array.length);
  let tile = grid[safe(y)][safe(x)];

  grid[safe(y)][safe(x)] = (
    switch (tile) {
    | Alive => Dead
    | _ => Alive
    }
  );

  grid;
};