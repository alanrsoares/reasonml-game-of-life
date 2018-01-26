type grid = array(array(int));

let valueAt = (index, array) => array[index];

let make = (size: int) : grid =>
  Array.init(size, (_) => Array.init(size, (_) => Random.int(1)));

let get = (rowIndex: int, columnIndex: int, grid) =>
  grid |> valueAt(rowIndex) |> valueAt(columnIndex);