open Utils;

[%bs.raw {|require('./grid.css')|}];

let component = ReasonReact.statelessComponent("Grid");

let renderTile = (onToggle, x: int, isAlive: bool) =>
  <Tile isAlive key=(string_of_int(x)) onToggle=(_ => onToggle(x)) />;

let renderRow = (onToggle, y: int, row) =>
  <div className="Grid--row" key=(string_of_int(y))>
    (row |> List.mapi(renderTile(onToggle(y))) |> render_list)
  </div>;

let make = (~data: Game.grid, ~onToggle, _children) => {
  ...component,
  render: _self =>
    <div className="Grid">
      (data |> List.mapi(renderRow(onToggle)) |> render_list)
    </div>,
};