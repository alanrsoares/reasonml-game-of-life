open Utils;

[%bs.raw {|require('./grid.css')|}];

let component = ReasonReact.statelessComponent("Grid");

let renderTile = (onToggle, x: int, cell_state: Game.cell_state) =>
  <Tile
    isAlive={cell_state === Game.Alive}
    key={string_of_int(x)}
    onToggle={_ => onToggle(x)}
  />;

let renderRow = (onToggle, y: int, row) =>
  <div className="Grid--row" key={string_of_int(y)}>
    {row |> Array.mapi(renderTile(onToggle(y))) |> render_array}
  </div>;

let make = (~data: Game.grid, ~onToggle, _children) => {
  ...component,
  render: _self =>
    <div className="Grid">
      {data |> Array.mapi(renderRow(onToggle)) |> render_array}
    </div>,
};