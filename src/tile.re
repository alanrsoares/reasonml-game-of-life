let component = ReasonReact.statelessComponent("Tile");

let eventToObj = e => ReactDOMRe.domElementToObj(ReactEventRe.Mouse.target(e));

let onMouseEvent = (toggle, alive, e) =>
  if (eventToObj(e)##which === 1) {
    toggle(alive);
  };

let make = (~alive, ~toggle, ~color="#FFF", _children) => {
  ...component,
  render: _self =>
    <div
      className="grid-tile"
      onMouseOver=(onMouseEvent(toggle, alive))
      onMouseDown=(onMouseEvent(toggle, alive))
      style=(ReactDOMRe.Style.make(~color=alive ? color : "transparent", ()))
    />
};