open Utils;

[%bs.raw {|require('./grid.css')|}];

let component = ReasonReact.statelessComponent("Grid");

let renderTile = (size, onToggle, x: int, isAlive: bool) =>
  <Tile isAlive size key=(string_of_int(x)) onToggle=((_) => onToggle(x)) />;

let renderRow = (tileSize, onToggle, y: int, row) =>
  <div
    className="Grid--row"
    key=(string_of_int(y))
    style=(make_style(~height=string_of_int(tileSize) ++ "px", ()))>
    (row |> List.mapi(renderTile(tileSize, onToggle(y))) |> render_list)
  </div>;

let make = (~tileSize, ~data: Game.grid, ~onToggle, _children) => {
  ...component,
  render: _self =>
    <div
      className="Grid"
      style=(make_style(~width=string_of_int(tileSize * List.length(data) + 10) ++ "px", ()))>
      (data |> List.mapi(renderRow(tileSize, onToggle)) |> render_list)
    </div>
};
