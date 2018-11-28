[%bs.raw {|require('./tile.css')|}];

let component = ReasonReact.statelessComponent("Tile");

let handle_mouse_event = (callback, e) =>
  if (ReactEvent.Mouse.nativeEvent(e)##which === 1) {
    callback();
  };

let make = (~isAlive, ~onToggle, _children) => {
  ...component,
  render: _self =>
    <div
      className="Tile"
      onMouseOver={handle_mouse_event(onToggle)}
      onMouseDown={handle_mouse_event(onToggle)}
      style={
        Utils.make_style(~backgroundColor=isAlive ? "#fff" : "#272B30", ())
      }
    />,
};