open Utils;

[%bs.raw {|require('./grid.css')|}];

let component = ReasonReact.statelessComponent("Grid");

let render_tile = (on_toggle, x: int, cell_state: Game.cell_state) =>
  <Tile
    isAlive={cell_state === Game.Alive}
    key={string_of_int(x)}
    onToggle={_ => on_toggle(x)}
  />;

let render_row = (on_toggle, y: int, row) =>
  <div className="Grid--row" key={string_of_int(y)}>
    {row |> Array.mapi(render_tile(on_toggle(y))) |> render_array}
  </div>;

let make = (~data: Game.grid, ~onToggle, _children) => {
  ...component,
  render: _self =>
    <div className="Grid">
      {data |> Array.mapi(render_row(onToggle)) |> render_array}
    </div>,
};