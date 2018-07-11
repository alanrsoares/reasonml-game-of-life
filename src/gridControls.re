open Utils;

[%bs.raw {|require('./gridControls.css')|}];

let component = ReasonReact.statelessComponent("GridControls");

let make =
    (~isPlaying, ~onReset, ~onRandom, ~onTick, ~onToggleAutoplay, _children) => {
  ...component,
  render: _self =>
    <div className="GridControls">
      <div className="btn-group" role="group">
        <button className="btn btn-danger" onClick=onReset>
          (render_string("RESET"))
        </button>
        <button className="btn btn-success" onClick=onRandom>
          (render_string("RANDOMIZE"))
        </button>
        <button
          className="btn btn-secondary" disabled=isPlaying onClick=onTick>
          <i className="mr-2 fa fa-fast-forward" />
        </button>
        <ToggleButton label="" isToggled=isPlaying onClick=onToggleAutoplay />
      </div>
    </div>,
};