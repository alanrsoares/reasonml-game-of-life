let component = ReasonReact.statelessComponent("ToggleButton");

let make = (~label, ~isToggled, ~onClick, _children) => {
  ...component,
  render: _self =>
    <button onClick className=("btn btn-sm btn-secondary " ++ (isToggled ? "active" : ""))>
      <i
        className=("mr-2 fa " ++ (isToggled ? "active fa-pause" : "fa-play"))
        style=(Utils.make_style(~width="12px", ()))
      />
      (Utils.render_string(label))
    </button>
};
