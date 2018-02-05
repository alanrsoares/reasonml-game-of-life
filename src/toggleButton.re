let component = ReasonReact.statelessComponent("ToggleButton");

let make = (~label, ~isToggled,  ~onToggle, _children) => {
  ...component,
  render: _self =>
    <label htmlFor="autoplay" className="">
        (Utils.text(label))
    </label>
};