let listToElement = xs => xs |> Array.of_list |> ReasonReact.arrayToElement;

let component = ReasonReact.statelessComponent("Grid");

let renderTile = (onToggle, x: int, isAlive: bool) =>
  <Tile key=(string_of_int(x)) isAlive onToggle=((_) => onToggle(x)) />;

let renderRow = (onToggle, y: int, row) =>
  <div className="grid-row" key=(string_of_int(y))>
    (row |> List.mapi(renderTile(onToggle(y))) |> listToElement)
  </div>;

let make = (~data: Game.grid, ~onToggle, _children) => {
  ...component,
  render: _self =>
    <div className="grid">
      (data |> List.mapi(renderRow(onToggle)) |> listToElement)
    </div>
};