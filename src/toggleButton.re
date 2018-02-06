let component = ReasonReact.statelessComponent("ToggleButton");

let make = (~label, ~isToggled, ~onClick, _children) => {
  ...component,
  render: _self =>
    <label
      htmlFor="autoplay"
      className=("btn btn-default " ++ (isToggled ? "active" : ""))>
      <i
        className=("fa " ++ (isToggled ? "active fa-pause" : "fa-play"))
        style=(Utils.style(~marginRight="7px", ()))
      />
      <input
        _type="checkbox"
        id="autoplay"
        onChange=onClick
        style=(Utils.style(~display="none", ()))
      />
      (Utils.text(label))
    </label>
};