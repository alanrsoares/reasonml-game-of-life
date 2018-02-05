let component = ReasonReact.statelessComponent("Tile");

let eventToObj = e => ReactDOMRe.domElementToObj(ReactEventRe.Mouse.target(e));

let onMouseEvent = (onToggle, isAlive, e) =>
  if (eventToObj(e)##which === 1) {
    onToggle(isAlive);
  };

let make = (~isAlive, ~onToggle, ~color="#FFF", _children) => {
  ...component,
  render: _self =>
    <div
      className="grid-tile"
      onMouseOver=(onMouseEvent(onToggle, isAlive))
      onMouseDown=(onMouseEvent(onToggle, isAlive))
      style=(ReactDOMRe.Style.make(~color=isAlive ? color : "transparent", ()))
    />
};