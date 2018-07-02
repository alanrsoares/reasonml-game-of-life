[%bs.raw {|require('./tile.css')|}];

let component = ReasonReact.statelessComponent("Tile");

let handleMouseEvent = (onToggle, e) =>
  if (ReactEventRe.Mouse.nativeEvent(e)##which === 1) {
    onToggle();
  };

let make = (~size, ~isAlive, ~onToggle, _children) => {
  ...component,
  render: _self => {
    let tileSize = string_of_int(size) ++ "px";
    <div
      className="Tile"
      onMouseOver=(handleMouseEvent(onToggle))
      onMouseDown=(handleMouseEvent(onToggle))
      style=(
        Utils.make_style(
          ~backgroundColor=isAlive ? "#fff" : "transparent",
          ~width=tileSize,
          ~height=tileSize,
          (),
        )
      )
    />;
  },
};