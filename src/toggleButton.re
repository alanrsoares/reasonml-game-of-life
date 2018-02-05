let component = ReasonReact.statelessComponent("ToggleButton");

let make = (~label, ~isToggled, ~onClick, _children) => {
  ...component,
  render: _self =>
    <label
      htmlFor="autoplay"
      className=("btn btn-default " ++ (isToggled ? "active" : ""))>
      <i
        className=("fa fa-lg " ++ (isToggled ? "active fa-pause" : "fa-play"))
      />
      <input
        _type="checkbox"
        id="autoplay"
        onChange=onClick
        style=(Utils.style(~display="none", ()))
      />
      (Utils.string(label))
    </label>
};