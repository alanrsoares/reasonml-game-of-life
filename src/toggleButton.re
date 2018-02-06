let component = ReasonReact.statelessComponent("ToggleButton");

let make = (~label, ~isToggled, ~onClick, _children) => {
  ...component,
  render: _self =>
    <button
      onClick className=("btn btn-secondary " ++ (isToggled ? "active" : ""))>
      <i
        className=("mr-2 fa " ++ (isToggled ? "active fa-pause" : "fa-play"))
      />
      (Utils.render_string(label))
    </button>
};
