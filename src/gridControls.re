[%bs.raw {|require('./gridControls.css')|}];

let component = ReasonReact.statelessComponent("GridControls");

let make = (~isPlaying, ~onReset, ~onRandom, ~onTick, ~onToggleAutoplay, _children) => {
  ...component,
  render: _self =>
    <div className="GridControls">
      <div className="btn-group" role="group">
        <button className="btn btn-sm btn-danger" onClick=onReset>
          (Utils.render_string("RESET"))
        </button>
        <button className="btn btn-sm btn-success" onClick=onRandom>
          (Utils.render_string("RANDOMIZE"))
        </button>
        <button
          className="btn btn-sm btn-secondary"
          disabled=(Js.Boolean.to_js_boolean(isPlaying))
          onClick=onTick>
          <i className="mr-2 fa fa-fast-forward" />
          (Utils.render_string("NEXT"))
        </button>
        <ToggleButton label="AUTOPLAY" isToggled=isPlaying onClick=onToggleAutoplay />
      </div>
    </div>
};
