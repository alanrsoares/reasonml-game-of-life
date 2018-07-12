[%bs.raw {|require('./tile.css')|}];

let component = ReasonReact.statelessComponent("Tile");

let handleMouseEvent = (onToggle, e) =>
  if (ReactEventRe.Mouse.nativeEvent(e)##which === 1) {
    onToggle();
  };

let make = (~isAlive, ~onToggle, _children) => {
  ...component,
  render: _self =>
    <div
      className="Tile"
      onMouseOver=(handleMouseEvent(onToggle))
      onMouseDown=(handleMouseEvent(onToggle))
      style=(
        Utils.make_style(
          ~backgroundColor=isAlive ? "#fff" : "transparent",
          (),
        )
      )
    />,
};