type grid = list(list(bool));

type position = {
  y: int,
  x: int
};

let safe_index = (len, i) => i === (-1) ? len - 1 : i === len ? 0 : i;

let make_grid = (size: int) : grid =>
  Array.to_list(
    Array.init(size, (_) =>
      Array.init(size, (_) => Random.bool()) |> Array.to_list
    )
  );

let get_tile = ({x, y}: position, g: grid) : bool => {
  let len = List.length(g);
  let safe_indexes = [|y, x|] |> Array.map(safe_index(len));
  List.nth(List.nth(g, safe_indexes[0]), safe_indexes[1]);
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

let will_live = (p: position, is_alive: bool, g: grid) : bool => {
  let n = count_living_neighbours(p, g);
  is_alive ? n >= 2 && n <= 3 : n === 3;
};

let next_generation = (g: grid) : grid =>
  List.mapi(
    (y, row) => row |> List.mapi((x, tile) => will_live({y, x}, tile, g)),
    g
  );