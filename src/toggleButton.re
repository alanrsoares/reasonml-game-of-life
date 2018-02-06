let component = ReasonReact.statelessComponent("ToggleButton");

let make = (~label, ~isToggled, ~onClick, _children) => {
  ...component,
  render: _self =>
    <button
      onClick className=("btn btn-secondary " ++ (isToggled ? "active" : ""))>
      <i
        className=("fa " ++ (isToggled ? "active fa-pause" : "fa-play"))
        style=(Utils.style(~marginRight="7px", ()))
      />
      (Utils.text(label))
    </button>
};