open Utils;

let component = ReasonReact.statelessComponent("ToggleButton");

let make = (~isToggled, ~onClick, _children) => {
  ...component,
  render: _self =>
    <button
      onClick
      ariaLabel="toggle autoplay"
      className=("btn btn-secondary " ++ (isToggled ? "active" : ""))>
      <i
        className=("mx-2 fa " ++ (isToggled ? "active fa-pause" : "fa-play"))
        style=(make_style(~width="12px", ()))
      />
    </button>,
};